#include "repositories/AppointmentRepository.h"

#include <Appointment.h>
#include <fstream>
#include <boost/date_time.hpp>
#include <patient/Patient.h>
#include <personnel/Personnel.h>
#include <repositories/PersonnelRepository.h>
#include <repositories/PatientRepository.h>
#include <repositories/ServiceRepository.h>
#include <repositories/RoomRepository.h>
#include <rooms/Room.h>
#include <services/Service.h>


using namespace std;

const PatientRepositoryPtr& AppointmentRepository::getPatientRepository() const
{
	return patientRepository;
}

const PersonnelRepositoryPtr& AppointmentRepository::getPersonnelRepository() const
{
	return personnelRepository;
}

const RoomRepositoryPtr& AppointmentRepository::getRoomRepository() const
{
	return roomRepository;
}

const ServiceRepositoryPtr& AppointmentRepository::getServiceRepository() const
{
	return serviceRepository;
}

const std::string& AppointmentRepository::getFileName() const
{
	return fileName;
}

AppointmentRepository::AppointmentRepository(const std::string& file_name) : fileName(file_name)
{
}

bool AppointmentRepository::loadData()
{
	ifstream inFile;
	inFile.open(getFileName());
	string line;

	if (!inFile.is_open())
	{
		return false;
	}

	while (getline(inFile, line))
	{
		if (line.empty()) continue;

		//Ladujemy do strumienia
		stringstream ss(line);

		string tmp;
		boost::posix_time::ptime appointmentBeginDate;
		unsigned int appointmentId, personnelId, personalId, serviceId, roomNumber;

		AppointmentPtr newAppointment;
		vector<PersonnelPtr> personnel;
		ServicePtr service;
		RoomPtr room;
		PatientPtr patient;


		getline(ss, tmp, ';');

		appointmentBeginDate = boost::posix_time::from_iso_string(tmp);

		getline(ss, tmp, ';');
		appointmentId = stoul(tmp);

		//Linjka do ; z identyfiakorami personelu
		getline(ss, tmp, ';');

		stringstream personnelIdStream(tmp);

		while (getline(personnelIdStream, tmp, ','))
		{
			personalId = stoul(tmp);
			personnel.push_back(getPersonnelRepository()->get(personalId));
		}

		//wczytanie pacjenta
		getline(ss, tmp, ';');
		personalId = stoul(tmp);

		patient = getPatientRepository()->get(personalId);

		//wczytanie usługi
		getline(ss, tmp, ';');
		serviceId = stoul(tmp);

		service = getServiceRepository()->get(serviceId);

		//wczytanie pokoju
		getline(ss, tmp, ';');
		roomNumber = stoul(tmp);

		room = getRoomRepository()->get(roomNumber);

		//Tworzymy nową wizytę
		newAppointment = make_shared<Appointment>(appointmentBeginDate, appointmentId, personnel, patient, service,
		                                          room);


		add(newAppointment);
	}
	inFile.close();
	return true;
}

bool AppointmentRepository::saveData() const
{
	ofstream outFile;

	outFile.open(getFileName());

	if (outFile.good())
	{
		for (const auto& appointment : getVectorOfData())
		{
			outFile << appointment->getAppointmentBeginDate() << ";";

			outFile << appointment->getAppointmentId() << ";";

			int i;
			//Zapisujemy kazdy unikalny numer osoby z personelu
			for (i = 0; appointment->getPersonnel().size() - 1 > i; i++)
			{
				outFile << appointment->getPersonnel()[i]->getPersonnelId() << ",";
			}
			outFile << appointment->getPersonnel()[i]->getPersonnelId() << ";";

			outFile << appointment->getPatient()->getPersonalNumber()<< ";";
			outFile << appointment->getService()->getServiceId()<< ";";
			outFile << appointment->getRoom()->getRoomNumber()<< "\n";

		}
		outFile.close();
		return true;
	}
	return false;
}
