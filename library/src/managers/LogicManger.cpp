#include <Appointment.h>

#include "managers/LogicManager.h"
#include "services/Service.h"
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

	if (personnel == nullptr) return;

	auto appointmens = getAppointmentManager()->getPersonnelAppointments(personnel);

	if (!appointmens.empty())
	{
		for (auto appointment : appointmens)
		{
			getAppointmentManager()->cancelAppointment(appointment->getAppointmentBeginDate(),
			                                           appointment->getUniqueParameter());
		}
	}
	personnel->setIsActive(false);
	personnel->setIsArchive(true);
}

bool LogicManager::unregisterPatient(const std::string& personalID)
{
	auto patient = getPatientManager()->get(personalID);

	if (patient == nullptr) return false;

	auto appointmens = getAppointmentManager()->getPatientAppointments(patient);

	if (!appointmens.empty())
	{
		return false;
	}

	patient->setIsArchive(true);
	return true;
}

void LogicManager::removeRoom(unsigned int roomNumber)
{
	auto room = getRoomManager()->get((unsigned int)roomNumber);
	if (room == nullptr) return;

	auto appointmens = getAppointmentManager()->getRoomAppointments(room);

	if (!appointmens.empty())
	{
		for (auto appointment : appointmens)
		{
			getAppointmentManager()->cancelAppointment(appointment->getAppointmentBeginDate(),
			                                           appointment->getUniqueParameter());
		}
	}
	room->setIsActive(false);
	room->setIsArchive(true);
}

bool LogicManager::removeService(unsigned int serviceID)
{
	auto service = getServiceManager()->get(serviceID);
	if (service == nullptr) return false;

	auto appointmens = getAppointmentManager()->getServiceAppointments(service);

	if (!appointmens.empty())
	{
		return false;
	}

	service->setIsAvailable(false);
	service->setIsArchive(true);
	return true;
}


const std::shared_ptr<PersonnelManager>& LogicManager::getPersonnelManager() const
{
	return personnelManager;
}

const std::shared_ptr<PatientManager>& LogicManager::getPatientManager() const
{
	return patientManager;
}

const std::shared_ptr<ServiceManager>& LogicManager::getServiceManager() const
{
	return serviceManager;
}

const std::shared_ptr<AppointmentManager>& LogicManager::getAppointmentManager() const
{
	return appointmentManager;
}

const std::shared_ptr<RoomManager>& LogicManager::getRoomManager() const
{
	return roomManager;
}
