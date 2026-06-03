#include "Appointment.h"


using namespace std;

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

Appointment::Appointment(const boost::posix_time::ptime& appointment_begin_date, const unsigned int appointment_id,
                         const unsigned int appointment_cost, const std::vector<PersonnelPtr>& personnel, const PatientPtr& patient,
                         const ServicePtr& service, const RoomPtr& room): appointmentBeginDate(appointment_begin_date),
                                                                          appointmentId(appointment_id),
                                                                          appointmentCost(appointment_cost),
                                                                          personnel(personnel),
                                                                          patient(patient),
                                                                          service(service),
                                                                          room(room)
{
}
