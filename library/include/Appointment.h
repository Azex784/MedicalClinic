#ifndef REHABILITATIONCENTRE_APPOINTMENT_H
#define REHABILITATIONCENTRE_APPOINTMENT_H

#include <boost/date_time.hpp>
#include <string>
#include <vector>
#include "typedefs.h"
#include "sstream"

class Appointment
{
public:
    const boost::posix_time::ptime& getAppointmentBeginDate() const;

    const boost::posix_time::ptime& getAppointmentEndDate() const;

    unsigned int getAppointmentId() const;

    unsigned int getAppointmentCost() const;

    const std::vector<PersonnelPtr>& getPersonnel() const;

    const PatientPtr& getPatient() const;

    const ServicePtr& getService() const;

    const RoomPtr& getRoom() const;

    Appointment(const boost::posix_time::ptime& appointment_begin_date, const unsigned int appointment_id,
                const unsigned int appointment_cost, const std::vector<PersonnelPtr>& personnel, const PatientPtr& patient,
                const ServicePtr& service, const RoomPtr& room);

private:
    boost::posix_time::ptime appointmentBeginDate;
    boost::posix_time::ptime appointmentEndDate;
    unsigned int appointmentId;
    unsigned int appointmentCost;
    std::vector<PersonnelPtr> personnel;
    PatientPtr patient;
    ServicePtr service;
    RoomPtr room;
public:
    const std::string getInfo() const;
};


#endif //REHABILITATIONCENTRE_APPOINTMENT_H