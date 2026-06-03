#include "Appointment.h"
#include "services/Service.h"
#include "personnel/Doctor.h"
#include "rooms/Room.h"
#include "patient/Patient.h"
#include "sstream"

using namespace std;

const boost::posix_time::ptime Appointment::setAppointmentEndDate(const boost::posix_time::ptime& appointment_end_date)
{
    // mozna tylko raz wyznaczyć datę zakończenia
    if (appointment_end_date == boost::posix_time::not_a_date_time)
    {
        appointmentEndDate = appointment_end_date;
        return getAppointmentEndDate();
    }
    else
    {
        return boost::posix_time::not_a_date_time;
    }
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
            if (person != nullptr)
            {
                appointmentCost += person->getDoctorCost();
            }
        }
        appointmentCost += getService()->getServiceCost();

        return getAppointmentCost();
    }
    return 0;
}

Appointment::Appointment(const boost::posix_time::ptime& appointment_begin_date, const unsigned int appointment_id,
    const std::vector<PersonnelPtr>& personnel, const PatientPtr& patient, const ServicePtr& service,
    const RoomPtr& room): appointmentBeginDate(appointment_begin_date),
                          appointmentId(appointment_id),
                          personnel(personnel),
                          patient(patient),
                          service(service),
                          room(room)
{
    // od razu ustalamy date zakonczenia
    setAppointmentEndDate(getAppointmentBeginDate() + boost::posix_time::minutes(service->getServiceDuration()));
}


const boost::posix_time::ptime& Appointment::getAppointmentBeginDate() const
{
    return appointmentBeginDate;
}

const boost::posix_time::ptime& Appointment::getAppointmentEndDate() const
{
    return appointmentEndDate;
}

unsigned int Appointment::getAppointmentId() const
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

const std::string Appointment::getInfo() const {
    std::stringstream ss;

    // Podstawowe dane wizyty
    ss << "=== Szczegóły wizyty (ID: " << getAppointmentId() << ") ===\n";
    ss << "Koszt: " << getAppointmentCost() << " PLN\n";

    ss << "Rozpoczęcie: " << getAppointmentBeginDate() << "\n";
    ss << "Zakończenie: " << getAppointmentEndDate() << "\n";

    // Wyciąganie informacji z obiektów
    ss << "Pacjent\n";
    ss << getPatient()->getInfo() << "\n";

    ss << "Usluga\n";
    ss << getService()->getInfo() << "\n";

    ss << "Sala\n";
    ss << getRoom()->getInfo() << "\n";

    ss << "Personel przypisany do wizyty\n";
    const auto& personelList = getPersonnel();
    for (const auto& worker : personelList) {
            ss << "- " << worker->getInfo() << "\n";
        }

    return ss.str();
};