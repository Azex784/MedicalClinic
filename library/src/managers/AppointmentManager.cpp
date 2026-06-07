#include "managers/AppointmentManager.h"
#include "Appointment.h"

#include "patient/Patient.h"
#include "personnel/Personnel.h"
#include "personnel/Doctor.h"

#include "rooms/Room.h"
#include "rooms/RehabillitationRoom.h"

#include "services/Service.h"
#include "services/Rehabillitation.h"


using namespace std;


AppointmentManager::AppointmentManager(const PatientRepositoryPtr& patientRepository,
                                       const PersonnelRepositoryPtr& personnelRepository,
                                       const RoomRepositoryPtr& roomRepository,
                                       const ServiceRepositoryPtr& serviceRepository)
{
	repository = std::make_shared<AppointmentRepository>(patientRepository, personnelRepository, roomRepository,
	                                                     serviceRepository);
	archiveRepository = std::make_shared<AppointmentRepository>("../../program/data/AppointmentRepositoryArchive.txt",
	                                                            patientRepository, personnelRepository, roomRepository,
	                                                            serviceRepository);

	getRepository()->loadData();
	getArchiveRepository()->loadData();
}

AppointmentManager::AppointmentManager(const std::string& fileName, const PatientRepositoryPtr& patientRepository,
                                       const PersonnelRepositoryPtr& personnelRepository,
                                       const RoomRepositoryPtr& roomRepository,
                                       const ServiceRepositoryPtr& serviceRepository)
{
	repository = std::make_shared<AppointmentRepository>(patientRepository, personnelRepository, roomRepository,
	                                                     serviceRepository);
	getRepository()->loadData();
	getArchiveRepository()->loadData();
}

AppointmentManager::~AppointmentManager()
{
	getRepository()->saveData();
	getArchiveRepository()->saveData();
}

const std::shared_ptr<AppointmentRepository>& AppointmentManager::getArchiveRepository() const
{
	return archiveRepository;
}

const std::shared_ptr<AppointmentRepository>& AppointmentManager::getRepository() const
{
	return repository;
}

const AppointmentPtr AppointmentManager::get(const unsigned int up) const
{
	return repository->get(up);
}

const std::vector<AppointmentPtr> AppointmentManager::findBy(AppointmentPredicate up) const
{
	return getRepository()->findBy(up);
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

	for (auto appointment : findBy(func))
	{
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

	//Pacjenta
	if (isDate(getPatientAppointments(patient), appointmentBeginDate, duration)) return nullptr;

	//Personelu
	for (auto& personel : personnel)
	{
		if (personel->getIsActive() != true) return nullptr;

		DoctorPtr doctor = dynamic_pointer_cast<Doctor>(personel);
		if (doctor != nullptr)
		{
			if (doctor->canConductTreatment(service->getRequiredDoctorSpec()))doctors.push_back(doctor);

			else return nullptr;
		}
		else
		{
			if (personel->canConductTreatment(service->getRequiredDoctorSpec())) return nullptr;
			nurses.push_back(personel);
		}
		if (isDate(getPersonnelAppointments(personel), appointmentBeginDate, duration)) return nullptr;
	}

	//Rozmiar lekarzy
	if (service->getRequiredDoctorSize() != doctors.size()) return nullptr;

	//Pokoju
	if (isDate(getRoomAppointments(room), appointmentBeginDate, duration)) return nullptr;
	if (room->getIsActive() != true) return nullptr;

	//Usluga
	if (service->getIsAvailable() != true) return nullptr;

	//Sprawdzenie czy wyposażenie jest odpowiednie
	RehabillitationRoomPtr rehabRoom = dynamic_pointer_cast<RehabillitationRoom>(room);
	RehabillitationPtr rehab = dynamic_pointer_cast<Rehabillitation>(service);


	if (rehab != nullptr)
	{
		if (rehab->getRequiredNurseSize() != nurses.size()) return nullptr;

		if (rehabRoom == nullptr) return nullptr;

		for (auto& serviceEq : rehab->getRequiredEqupiment())
		{
			if (!rehabRoom->canBeUsed(serviceEq)) return nullptr;
		}
	}

	AppointmentPtr newAppointment = std::make_shared<Appointment>(appointmentBeginDate, appointmentId, personnel,
	                                                              patient, service, room);

	getRepository()->add(newAppointment);

	return newAppointment;
}

unsigned int AppointmentManager::finishAppointment(const PatientPtr& patient,
                                                   const boost::posix_time::ptime& beginTime)
{
	boost::posix_time::ptime teraz = boost::posix_time::second_clock::local_time();

	if (teraz < beginTime) return 0;

	AppointmentPredicate func = [beginTime,patient](const AppointmentPtr appointment) -> bool
	{
		if (appointment->getAppointmentBeginDate() == beginTime && appointment->getPatient()->getUniqueParameter() ==
			patient->getUniqueParameter())
		{
			return true;
		}
		return false;
	};

	AppointmentPtr appointment = findBy(func)[0];

	getArchiveRepository()->add(appointment);
	getRepository()->remove(appointment);

	return appointment->setAppointmentCost();
}

bool AppointmentManager::changeAppointment(const boost::posix_time::ptime& _date, const unsigned int appointmentId)
{
	AppointmentPtr appointment = getRepository()->get((unsigned int)appointmentId);
	unsigned int duration = appointment->getService()->getServiceDuration();


	if (isDate(getPatientAppointments(appointment->getPatient()), _date, duration)) return false;

	if (isDate(getRoomAppointments(appointment->getRoom()), _date, duration)) return false;

	for (auto& personel : appointment->getPersonnel())
	{
		if (isDate(getPersonnelAppointments(personel), _date, duration)) return false;
	}

	appointment->setAppointmentBeginDate(_date);
	return true;
}

void AppointmentManager::cancelAppointment(const boost::posix_time::ptime& _date, const unsigned int appointmentId)
{
	AppointmentPtr appointment = getRepository()->get((unsigned int)appointmentId);
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
