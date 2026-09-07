#ifndef MEDICALCLINIC_TYPEDEFS_H
#define MEDICALCLINIC_TYPEDEFS_H

#include <memory>
#include <functional>

namespace MedicalClinic
{
const std::string ALLOWEDCHARS =
" abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890-/.ąćęłńóśźżĄĆĘŁŃÓŚŹŻ";

class Person;
typedef std::shared_ptr<Person> PersonPtr;

class Patient;
typedef std::shared_ptr<Patient> PatientPtr;

typedef std::function<bool(PatientPtr)> PatientPredicate;

class Address;
typedef std::shared_ptr<Address> AddressPtr;

class Personnel;
typedef std::shared_ptr<Personnel> PersonnelPtr;

typedef std::function<bool(PersonnelPtr)> PersonnelPredicate;

class Nurse;
typedef std::shared_ptr<Nurse> NursePtr;

class Doctor;
typedef std::shared_ptr<Doctor> DoctorPtr;

class Room;
typedef std::shared_ptr<Room> RoomPtr;

typedef std::function<bool(RoomPtr)> RoomPredicate;

class ConsultationRoom;
typedef std::shared_ptr<ConsultationRoom> ConsultationRoomPtr;

class SurgeryRoom;
typedef std::shared_ptr<SurgeryRoom> RehabillitationRoomPtr;

class Service;
typedef std::shared_ptr<Service> ServicePtr;

typedef std::function<bool(ServicePtr)> ServicePredicate;

class Rehabillitation;
typedef std::shared_ptr<Rehabillitation> RehabillitationPtr;

class Consultation;
typedef std::shared_ptr<Consultation> ConsultationPtr;

class Appointment;
typedef std::shared_ptr<Appointment> AppointmentPtr;

typedef std::function<bool(AppointmentPtr)> AppointmentPredicate;

class PatientRepository;
typedef std::shared_ptr<PatientRepository> PatientRepositoryPtr;

class RoomRepository;
typedef std::shared_ptr<RoomRepository> RoomRepositoryPtr;

class AppointmentRepository;
typedef std::shared_ptr<AppointmentRepository> AppointmentRepositoryPtr;

class PersonnelRepository;
typedef std::shared_ptr<PersonnelRepository> PersonnelRepositoryPtr;

class ServiceRepository;
typedef std::shared_ptr<ServiceRepository> ServiceRepositoryPtr;

class LogicManager;
typedef std::shared_ptr<LogicManager> LogicManagerPtr;

class PatientManager;
typedef std::shared_ptr<PatientManager> PatientManagerPtr;

class RoomManager;
typedef std::shared_ptr<RoomManager> RoomManagerPtr;

class AppointmentManager;
typedef std::shared_ptr<AppointmentManager> AppointmentManagerPtr;

class PersonnelManager;
typedef std::shared_ptr<PersonnelManager> PersonnelManagerPtr;

class ServiceManager;
typedef std::shared_ptr<ServiceManager> ServiceManagerPtr;
}

#endif //MEDICALCLINIC_TYPEDEFS_H