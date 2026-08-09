#include "repositories/AppointmentRepository.h"

#include <Exceptions.h>
#include <repositories/PersonnelRepository.h>
#include <repositories/PatientRepository.h>
#include <repositories/ServiceRepository.h>
#include <repositories/RoomRepository.h>

#include "Appointment.h"
#include "patient/Patient.h"
#include "personnel/Personnel.h"
#include "rooms/Room.h"
#include "services/Service.h"

#include <fstream>
#include <boost/date_time.hpp>

namespace MedicalClinic
{

	using namespace std;

	const PatientRepositoryPtr& AppointmentRepository::getPatientRepository() const
	{
		if (patientRepository == nullptr)
		{
			throw NullPointerException("patientRepository");
		}
		return patientRepository;
	}

	const PersonnelRepositoryPtr& AppointmentRepository::getPersonnelRepository() const
	{
		if (personnelRepository == nullptr)
		{
			throw NullPointerException("personnelRepository");
		}
		return personnelRepository;
	}

	const RoomRepositoryPtr& AppointmentRepository::getRoomRepository() const
	{
		if (roomRepository == nullptr)
		{
			throw NullPointerException("roomRepository");
		}
		return roomRepository;
	}

	const ServiceRepositoryPtr& AppointmentRepository::getServiceRepository() const
	{
		return serviceRepository;
	}

	AppointmentRepository::AppointmentRepository(const std::string& fileName,
	                                             const PatientRepositoryPtr& patientRepository,
	                                             const PersonnelRepositoryPtr& personnelRepository,
	                                             const RoomRepositoryPtr& roomRepository,
	                                             const ServiceRepositoryPtr& serviceRepository) :
		RepositoryTemplate<std::shared_ptr<Appointment>, std::function<bool(std::shared_ptr<Appointment>)>, const
		                   unsigned>(fileName),
		patientRepository(patientRepository),
		personnelRepository(personnelRepository),
		roomRepository(roomRepository),
		serviceRepository(serviceRepository)
	{
	}

	AppointmentRepository::AppointmentRepository(
		const PatientRepositoryPtr& patientRepository, const PersonnelRepositoryPtr& personnelRepository,
		const RoomRepositoryPtr& roomRepository,
		const ServiceRepositoryPtr& serviceRepository) :
		RepositoryTemplate<std::shared_ptr<Appointment>, std::function<bool(std::shared_ptr<Appointment>)>, const
		                   unsigned>("../../program/data/AppointmentRepository.txt"),
		patientRepository(patientRepository),
		personnelRepository(personnelRepository),
		roomRepository(roomRepository),
		serviceRepository(serviceRepository)
	{
	}

	void AppointmentRepository::loadData()
	{
		ifstream inFile;
		inFile.open(getFileName());
		string line;

		if (!inFile.is_open())
		{
			throw OpeningException(getFileName());
		}

		//Zapobiega to podwojnemu zliczeniu elementów
		clearVectorOfData();
		while (getline(inFile, line))
		{
			if (line.empty()) continue;

			//Ladujemy do strumienia
			stringstream ss(line);

			string tmp;
			boost::posix_time::ptime appointmentBeginDate;
			unsigned int appointmentId, serviceId, roomNumber, personnelId;
			string personalId;

			AppointmentPtr newAppointment;
			vector<PersonnelPtr> personnel;
			ServicePtr service;
			RoomPtr room;
			PatientPtr patient;

			getline(ss, tmp, ';');

			appointmentBeginDate = boost::posix_time::from_iso_string(tmp);

			getline(ss, tmp, ';');

			appointmentId = stoul(tmp);

			//Linijka do ; z identyfiakorami personelu
			getline(ss, tmp, ';');

			stringstream personnelIdStream(tmp);

			while (getline(personnelIdStream, tmp, ','))
			{
				personnelId = stoul(tmp);
				personnel.push_back(getPersonnelRepository()->get(personnelId));
			}

			//wczytanie pacjenta
			getline(ss, tmp, ';');
			personalId = tmp;

			patient = getPatientRepository()->get(personalId);

			//wczytanie usługi
			getline(ss, tmp, ';');
			serviceId = stoul(tmp);

			service = getServiceRepository()->get(serviceId);

			//wczytanie pokoju
			getline(ss, tmp, '\n');
			roomNumber = stoul(tmp);

			room = getRoomRepository()->get(roomNumber);

			//Tworzymy nową wizytę
			newAppointment = make_shared<Appointment>(appointmentBeginDate, appointmentId, personnel, patient, service,
			                                          room);

			add(newAppointment);

			if (inFile.fail())
			{
				throw WriteException(getFileName());
			}
		}
		inFile.close();
	}

	void AppointmentRepository::saveData() const
	{
		ofstream outFile;

		outFile.open(getFileName(), ios::trunc);

		if (!outFile.is_open())
		{
			throw OpeningException(getFileName());
		}

		if (getVectorOfData().empty())
		{
			outFile << "";
		}
		else
		{
			for (const AppointmentPtr &appointment : getVectorOfData())
			{
				outFile << boost::posix_time::to_iso_string(appointment->getAppointmentBeginDate()) << ";";
				outFile << appointment->getUniqueParameter() << ";";
				auto& personnel = appointment->getPersonnel();

				if (personnel.empty())
				{
					throw EmptyRecordException("Personnel");
				}

				int i;
				//Zapisujemy kazdy unikalny numer osoby z personelu, by móc na podstawie tego zidetyfikować interesujące nas
				//obiekty
				for (i = 0; (int)personnel.size() - 1 > i; i++)
				{
					outFile << appointment->getPersonnel()[i]->getUniqueParameter() << ",";
				}
				outFile << appointment->getPersonnel()[i]->getUniqueParameter() << ";";

				outFile << appointment->getPatient()->getUniqueParameter() << ";";
				outFile << appointment->getService()->getUniqueParameter() << ";";
				outFile << appointment->getRoom()->getUniqueParameter() << "\n";

				if (outFile.fail())
				{
					throw WriteException(getFileName());
				}
			}
		}
		outFile.close();
	}
}
