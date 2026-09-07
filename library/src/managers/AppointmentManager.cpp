#include "managers/AppointmentManager.h"
#include "Appointment.h"

#include "patient/Patient.h"
#include "personnel/Personnel.h"
#include "personnel/Doctor.h"

#include "rooms/Room.h"
#include "rooms/SurgeryRoom.h"

#include "services/Service.h"
#include "services/Rehabillitation.h"

#include "Exceptions.h"

namespace MedicalClinic
{
	using namespace std;


	AppointmentManager::AppointmentManager(const PatientRepositoryPtr& patientRepository,
	                                       const PersonnelRepositoryPtr& personnelRepository,
	                                       const RoomRepositoryPtr& roomRepository,
	                                       const ServiceRepositoryPtr& serviceRepository)
	{
		repository = std::make_shared<AppointmentRepository>(patientRepository, personnelRepository, roomRepository,
		                                                     serviceRepository);
		archiveRepository = std::make_shared<AppointmentRepository>(
			"../../program/data/AppointmentRepositoryArchive.txt",
			patientRepository, personnelRepository, roomRepository,
			serviceRepository);

		try
		{
			getRepository()->loadData();
			getArchiveRepository()->loadData();
		}
		catch (const OpeningException& e)
		{
			getRepository()->saveData();
			getArchiveRepository()->saveData();
		}
	}

	AppointmentManager::AppointmentManager(const std::string& fileName, const std::string& fileNameArchive,
	                                       const PatientRepositoryPtr& patientRepository,
	                                       const PersonnelRepositoryPtr& personnelRepository,
	                                       const RoomRepositoryPtr& roomRepository,
	                                       const ServiceRepositoryPtr& serviceRepository)
	{
		repository = std::make_shared<AppointmentRepository>(fileName, patientRepository, personnelRepository,
		                                                     roomRepository,
		                                                     serviceRepository);

		archiveRepository = std::make_shared<AppointmentRepository>(fileNameArchive,
		                                                            patientRepository, personnelRepository,
		                                                            roomRepository,
		                                                            serviceRepository);
		try
		{
			getRepository()->loadData();
			getArchiveRepository()->loadData();
		}
		catch (const OpeningException& e)
		{
			getRepository()->saveData();
			getArchiveRepository()->saveData();
		}
	}

	AppointmentManager::~AppointmentManager()
	{
		getRepository()->saveData();
		getArchiveRepository()->saveData();
	}

	const std::shared_ptr<AppointmentRepository>& AppointmentManager::getArchiveRepository() const
	{
		if (archiveRepository == nullptr)
		{
			throw NullPointerException("archiveRepository");
		}
		return archiveRepository;
	}

	const std::shared_ptr<AppointmentRepository>& AppointmentManager::getRepository() const
	{
		if (repository == nullptr)
		{
			throw NullPointerException("repository");
		}
		return repository;
	}

	const AppointmentPtr AppointmentManager::get(const unsigned int up) const
	{
		return getRepository()->get(up);
	}

	const std::vector<AppointmentPtr> AppointmentManager::findBy(AppointmentPredicate up) const
	{
		return getRepository()->findBy(up);
	}

	const std::vector<AppointmentPtr> AppointmentManager::findByArchive(AppointmentPredicate up) const
	{
		return getArchiveRepository()->findBy(up);
	}

	const std::vector<AppointmentPtr> AppointmentManager::findAllArchive() const
	{
		return getArchiveRepository()->findAll();
	}

	const std::vector<AppointmentPtr> AppointmentManager::findAll() const
	{
		return getRepository()->findAll();
	}

	std::vector<AppointmentPtr> AppointmentManager::getPatientAppointments(const PatientPtr& patient) const
	{
		AppointmentPredicate func = [patient](const AppointmentPtr appointment) -> bool
		{
			if (appointment->getPatient()->getUniqueParameter() == patient->getUniqueParameter())
			{
				return true;
			}
			return false;
		};
		return findBy(func);
	}

	std::vector<AppointmentPtr> AppointmentManager::getPersonnelAppointments(const PersonnelPtr& personnel) const
	{
		AppointmentPredicate func = [personnel](const AppointmentPtr appointment) -> bool
		{
			for (PersonnelPtr personelIterated : appointment->getPersonnel())
			{
				if (personelIterated->getUniqueParameter() == personnel->getUniqueParameter())
				{
					return true;
				}
			}
			return false;
		};
		return findBy(func);
	}

	std::vector<AppointmentPtr> AppointmentManager::getServiceAppointments(const ServicePtr& service) const
	{
		AppointmentPredicate func = [service](const AppointmentPtr appointment) -> bool
		{
			if (appointment->getService()->getUniqueParameter() == service->getUniqueParameter())
			{
				return true;
			}
			return false;
		};
		return findBy(func);
	}

	std::vector<AppointmentPtr> AppointmentManager::getRoomAppointments(const RoomPtr& room) const
	{
		AppointmentPredicate func = [room](const AppointmentPtr appointment) -> bool
		{
			if (appointment->getRoom()->getUniqueParameter() == room->getUniqueParameter())
			{
				return true;
			}
			return false;
		};
		return findBy(func);
	}

	unsigned int AppointmentManager::getAppointmentsCost(const PatientPtr& patient) const
	{
		AppointmentPredicate func = [patient](const AppointmentPtr appointment) -> bool
		{
			if (appointment->getPatient()->getUniqueParameter() == patient->getUniqueParameter())
			{
				return true;
			}
			return false;
		};

		unsigned int cost = 0;

		for (auto& appointment : findByArchive(func))
		{
			appointment->setAppointmentCost();
			cost += appointment->getAppointmentCost();
		}

		return cost;
	}

	AppointmentPtr AppointmentManager::arrangeAppointment(const PatientPtr& patient, const ServicePtr& service,
	                                                      const std::vector<PersonnelPtr>& personnel,
	                                                      const boost::posix_time::ptime& appointmentBeginDate,
	                                                      const RoomPtr& room, unsigned int appointmentId)
	{
		//Sprawdzamy czy nie kolidują terminy
		unsigned int duration = service->getServiceDuration();
		std::vector<PersonnelPtr> nurses;
		std::vector<DoctorPtr> doctors;

		if (get(appointmentId) != nullptr)
		{
			throw LogicException("Wizytą o tym AppointmentId już istnieje.");
		}

		//Pacjenta
		if (isDate(getPatientAppointments(patient), appointmentBeginDate, duration))
			throw DateException("Pacjent: " + patient->getInfo());


		//Personelu
		for (auto& personel : personnel)
		{
			if (personel->getIsActive() != true) throw ActivityException("Specjalista: " + personel->getInfo());

			DoctorPtr doctor = dynamic_pointer_cast<Doctor>(personel);

			if (doctor != nullptr)
			{
				if (doctor->canConductTreatment(service->getRequiredDoctorSpec()))
					doctors.push_back(doctor);
				else throw LogicException("Lekarz " + doctor->getInfo() + " nie może przeprowadzić zabiegu.");
			}
			else
			{
				if (!personel->canConductTreatment(service->getRequiredDoctorSpec()))
					throw LogicException("Pielęgniarka " + personel->getInfo() + " nie może przeprowadzić zabiegu.");
				nurses.push_back(personel);
			}
			if (isDate(getPersonnelAppointments(personel), appointmentBeginDate, duration))
				throw DateException("Specjalista: " + personel->getInfo());
		}
		//Rozmiar lekarzy
		if (service->getRequiredDoctorSize() != doctors.size())
			throw LogicException("Przydzielono niepoprawną ilość specjalistów.");

		//Pokoju
		if (isDate(getRoomAppointments(room), appointmentBeginDate, duration))
			throw DateException("Pokój: " + room->getInfo());
		if (room->getIsActive() != true)
			throw ActivityException("Pokój: " + room->getInfo());

		//Usluga
		if (service->getIsAvailable() != true)
			throw ActivityException("Usługa: " + service->getInfo());

		//Sprawdzenie czy wyposażenie jest odpowiednie
		RehabillitationRoomPtr rehabRoom = dynamic_pointer_cast<SurgeryRoom>(room);
		RehabillitationPtr rehab = dynamic_pointer_cast<Rehabillitation>(service);

		if (rehab != nullptr)
		{
			if (rehab->getRequiredNurseSize() != nurses.size())
				throw LogicException("Przydzielono niepoprawną ilość pielęgniarek.");

			//Nie może być rehabilitacja gdy nie ma pokoju rehabilitacyjnego!!!
			if (rehabRoom == nullptr)
				throw LogicException("Przydzielono rehabilitacje do pokoju konsultacyjnego.");

			if (rehabRoom->getMaxCapacity() < personnel.size())
				throw LogicException("Przekroczono maksymalny rozmiar sali. Liczba specjalistów jest zbyt duża.");

			for (auto& serviceEq : rehab->getRequiredEqupiment())
			{
				if (!rehabRoom->canBeUsed(serviceEq))
					throw LogicException("Sala nie ma wymaganego sprzętu.");
			}
		}

		AppointmentPtr newAppointment = std::make_shared<Appointment>(appointmentBeginDate, appointmentId, personnel,
		                                                              patient, service, room);

		getRepository()->add(newAppointment);

		return newAppointment;
	}

	unsigned int AppointmentManager::finishAppointment(unsigned int appointmentId)
	{
		boost::posix_time::ptime teraz = boost::posix_time::second_clock::local_time();
		auto appointment = get(appointmentId);


		if (appointment == nullptr)
			throw LogicException("Nie znaleziono podanego spotkania.");

		if (teraz < appointment->getAppointmentBeginDate())
			throw LogicException("Nie można przejść do podsumowania bez zakończenia spotkania.");


		if (getArchiveRepository()->get((unsigned int)appointment->getUniqueParameter()) != nullptr)
		{
			throw LogicException(
				"Próba dodania spotkania do ArchiveRepository o unikalnym numerze, który juz jest w systemie.");
		}
		else
		{
			getArchiveRepository()->add(appointment);
		}

		getRepository()->remove(appointment);

		return appointment->setAppointmentCost();
	}

	void AppointmentManager::changeAppointment(const boost::posix_time::ptime& _date, const unsigned int appointmentId)
	{
		AppointmentPtr appointment = getRepository()->get((unsigned int)appointmentId);
		unsigned int duration = appointment->getService()->getServiceDuration();

		if (isDate(getPatientAppointments(appointment->getPatient()), _date, duration))
			throw DateException("Pacjent " + appointment->getPatient()->getInfo());
		if (isDate(getRoomAppointments(appointment->getRoom()), _date, duration))
			throw DateException("Sala " + appointment->getRoom()->getInfo());

		for (auto& personel : appointment->getPersonnel())
		{
			if (isDate(getPersonnelAppointments(personel), _date, duration))
				throw DateException("Specjalista " + personel->getInfo());
		}

		appointment->setAppointmentBeginDate(_date);
	}

	void AppointmentManager::cancelAppointment(const unsigned int appointmentId)
	{
		AppointmentPtr appointment = getRepository()->get(appointmentId);

		if (appointment == nullptr)
			throw LogicException("Nie znaleziono podanego spotkania.");

		getRepository()->remove(appointment);
	}

	bool AppointmentManager::isDate(std::vector<AppointmentPtr> appointments,
	                                const boost::posix_time::ptime beginDate,
	                                unsigned int duration) const
	{
		for (auto& appointment : appointments)
		{
			const boost::posix_time::ptime appointmentEndDate = beginDate + boost::posix_time::minutes(
				duration);

			if (beginDate < appointment->getAppointmentEndDate() &&
				appointmentEndDate > appointment->getAppointmentBeginDate())
				return true;
		}
		return false;
	}
}
