#include "Appointment.h"
#include "services/Service.h"
#include "personnel/Doctor.h"
#include "rooms/Room.h"
#include "patient/Patient.h"
#include "sstream"

using namespace std;

void Appointment::setAppointmentEndDate()
{
	appointmentEndDate = getAppointmentBeginDate() +
		boost::posix_time::minutes(service->getServiceDuration());
}

const int unsigned Appointment::setAppointmentCost()
{
	boost::posix_time::ptime teraz = boost::posix_time::second_clock::local_time();
	// zmiana może nastapić gdy koszt nie był zmieniany i jest już po dacie zakończenia wizyty
	if (getAppointmentCost() == 0 && teraz >= getAppointmentEndDate())
	{
		for (unsigned int i = 0; i < getPersonnel().size(); i++)
		{
			shared_ptr<Doctor> person = dynamic_pointer_cast<Doctor>(getPersonnel()[i]);
			appointmentCost += person->getDoctorCost();
		}
		appointmentCost += getService()->getServiceCost();

		return getAppointmentCost();
	}
	return 0;
}

Appointment::Appointment(const boost::posix_time::ptime& appointmentBeginDate, const unsigned int appointmentId,
                         const std::vector<PersonnelPtr>& personnel, const PatientPtr& patient,
                         const ServicePtr& service,
                         const RoomPtr& room) : appointmentBeginDate(appointmentBeginDate),
                                                appointmentId(appointmentId),
                                                personnel(personnel),
                                                patient(patient),
                                                service(service),
                                                room(room)
{
	// od razu ustalamy date zakonczenia
	setAppointmentEndDate();
}


const boost::posix_time::ptime& Appointment::getAppointmentBeginDate() const
{
	return appointmentBeginDate;
}

const boost::posix_time::ptime& Appointment::getAppointmentEndDate() const
{
	return appointmentEndDate;
}

unsigned int Appointment::getUniqueParameter() const
{
	return appointmentId;
}

unsigned int Appointment::getAppointmentCost() const
{
	return appointmentCost;
}

const std::vector<PersonnelPtr>& Appointment::getPersonnel() const
{
	return personnel;
}

const PatientPtr& Appointment::getPatient() const
{
	return patient;
}

const ServicePtr& Appointment::getService() const
{
	return service;
}

const RoomPtr& Appointment::getRoom() const
{
	return room;
}

void Appointment::setAppointmentBeginDate(const boost::posix_time::ptime& appointmentBeginDate)
{
	this->appointmentBeginDate = appointmentBeginDate;

	setAppointmentEndDate();
}

const std::string Appointment::getInfo() const
{
	std::stringstream ss;

	// Podstawowe dane wizyty
	ss << "Wizyta: ID: " << getUniqueParameter() << ")\n";
	ss << "Koszt: " << getAppointmentCost() << " PLN\n";

	ss << "Rozpoczęcie: " << getAppointmentBeginDate() << "\n";
	ss << "Zakończenie: " << getAppointmentEndDate() << "\n";

	// Wyciąganie informacji z obiektów
	ss << "Pacjent:\n";
	ss << getPatient()->getInfo() << "\n";

	ss << "Usluga:\n";
	ss << getService()->getInfo() << "\n";

	ss << "Sala:\n";
	ss << getRoom()->getInfo() << "\n";

	ss << "Personel przypisany do wizyty:\n";

	for (int i = 0; i < getPersonnel().size(); i++)
	{
		ss << "- " << getPersonnel()[i]->getInfo() << "\n";
	}

	return ss.str();
};
