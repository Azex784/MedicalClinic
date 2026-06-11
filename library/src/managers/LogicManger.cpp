#include "Appointment.h"
#include "managers/LogicManager.h"
#include "services/Service.h"
#include "Exceptions.h"


namespace RehabClinic
{
	using namespace std;

	LogicManager::LogicManager()
		: personnelManager(std::make_shared<PersonnelManager>()),
		  patientManager(std::make_shared<PatientManager>()),
		  serviceManager(std::make_shared<ServiceManager>()),
		  roomManager(std::make_shared<RoomManager>()),
		  appointmentManager(std::make_shared<AppointmentManager>(
			  patientManager->getRepository(),
			  personnelManager->getRepository(),
			  roomManager->getRepository(),
			  serviceManager->getRepository()))
	{
	}

	LogicManager::LogicManager(const std::string& fileName1, const std::string& fileName2, const std::string& fileName3,
	                           const std::string& fileName4, const std::string& fileName5, const std::string& fileName6)
		: personnelManager(std::make_shared<PersonnelManager>(fileName1)),
		  patientManager(std::make_shared<PatientManager>(fileName2)),
		  serviceManager(std::make_shared<ServiceManager>(fileName3)),
		  roomManager(std::make_shared<RoomManager>(fileName4)),
		  appointmentManager(std::make_shared<AppointmentManager>(fileName5, fileName6,
		                                                          patientManager->getRepository(),
		                                                          personnelManager->getRepository(),
		                                                          roomManager->getRepository(),
		                                                          serviceManager->getRepository()))
	{
	}

	void LogicManager::removePersonnel(unsigned int personnelId)
	{
		auto personnel = getPersonnelManager()->get((unsigned int)personnelId);

		if (personnel == nullptr)
			throw NoExistException("Specjalista", to_string(personnelId));


		if (personnel->getIsArchive())
			throw ArchiveArchivedException("specjalisty");

		auto appointmens = getAppointmentManager()->getPersonnelAppointments(personnel);

		if (!appointmens.empty())
		{
			for (auto appointment : appointmens)
			{
				getAppointmentManager()->cancelAppointment(appointment->getUniqueParameter());
			}
		}
		personnel->setIsActive(false);
		personnel->setIsArchive(true);
	}

	void LogicManager::unregisterPatient(const std::string& personalID)
	{
		auto patient = getPatientManager()->get(personalID);

		if (patient == nullptr)
			throw NoExistException("Pacjent", personalID);

		if (patient->getIsArchive())
			throw ArchiveArchivedException("pacjenta");

		auto appointmens = getAppointmentManager()->getPatientAppointments(patient);

		if (!appointmens.empty())
		{
			throw DateException("Pacjent");
		}

		patient->setIsArchive(true);
	}

	void LogicManager::removeRoom(unsigned int roomNumber)
	{
		auto room = getRoomManager()->get(roomNumber);
		if (room == nullptr)
			throw NoExistException("Sala", to_string(roomNumber));

		if (room->getIsArchive())
			throw ArchiveArchivedException("sali");

		auto appointmens = getAppointmentManager()->getRoomAppointments(room);

		if (!appointmens.empty())
		{
			for (auto appointment : appointmens)
			{
				getAppointmentManager()->cancelAppointment(appointment->getUniqueParameter());
			}
		}
		room->setIsActive(false);
		room->setIsArchive(true);
	}

	void LogicManager::removeService(unsigned int serviceID)
	{
		auto service = getServiceManager()->get(serviceID);
		if (service == nullptr)
			throw NoExistException("Usługa", to_string(serviceID));

		if (service->getIsArchive())
			throw ArchiveArchivedException("usługi");

		auto appointmens = getAppointmentManager()->getServiceAppointments(service);

		if (!appointmens.empty())
		{
			throw DateException("Sala");
		}

		service->setIsAvailable(false);
		service->setIsArchive(true);
	}

	const std::shared_ptr<PersonnelManager>& LogicManager::getPersonnelManager() const
	{
		if (personnelManager == nullptr)
		{
			throw NullPointerException("personnelManager");
		}
		return personnelManager;
	}

	const std::shared_ptr<PatientManager>& LogicManager::getPatientManager() const
	{
		if (patientManager == nullptr)
		{
			throw NullPointerException("patientManager");
		}
		return patientManager;
	}

	const std::shared_ptr<ServiceManager>& LogicManager::getServiceManager() const
	{
		if (serviceManager == nullptr)
		{
			throw NullPointerException("serviceManager");
		}
		return serviceManager;
	}

	const std::shared_ptr<AppointmentManager>& LogicManager::getAppointmentManager() const
	{
		if (appointmentManager == nullptr)
		{
			throw NullPointerException("appointmentManager");
		}
		return appointmentManager;
	}

	const std::shared_ptr<RoomManager>& LogicManager::getRoomManager() const
	{
		if (roomManager == nullptr)
		{
			throw NullPointerException("roomManager");
		}
		return roomManager;
	}
}
