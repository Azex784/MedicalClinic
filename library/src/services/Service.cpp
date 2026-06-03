#include "services/Service.h"
#include "enums/Specialisation.h"

using namespace std;

unsigned int Service::getServiceCost() const
{
    return serviceCost;
}

unsigned int Service::getServiceDuration() const
{
    return serviceDuration;
}

const std::string& Service::getServiceName() const
{
    return serviceName;
}

unsigned int Service::getServiceId() const
{
    return serviceId;
}

unsigned int Service::getRequiredDoctorSize() const
{
    return requiredDoctorSize;
}

const Specialisation Service::getRequiredDoctorSpec() const
{
    return requiredDoctorSpec;
}

bool Service::getIsAvailable() const
{
    return isAvailble;
}

bool Service::getIsArchive() const
{
    return isArchive;
}

void Service::setServiceCost(const unsigned int service_cost)
{
    serviceCost = service_cost;
}

void Service::setIsAvailable(const bool is_availble)
{
    isAvailble = is_availble;
}

void Service::setIsArchive(const bool is_archive)
{
    isArchive = is_archive;
}

Service::Service(const unsigned int service_cost, const unsigned int service_duration, const std::string& service_name,
    const unsigned int service_id, const unsigned int required_doctor_size, const Specialisation required_doctor_spec): serviceCost(service_cost),
    serviceDuration(service_duration),
    serviceName(service_name),
    serviceId(service_id),
    requiredDoctorSize(required_doctor_size),
    requiredDoctorSpec(required_doctor_spec)
{
}

const std::string Service::getInfo() const
{
    return "Nazwa usługi: " + getServiceName() + " koszt usług: " + to_string(getServiceCost()) +
        " czas trwania" + to_string(getServiceDuration()) + " idetyfikator: " + to_string(getServiceId())
        + " liczba lekarzy: " + to_string(getRequiredDoctorSize()) + " specjalziacja lekarza/y" + specialisationToString(getRequiredDoctorSpec());
    ;
}
