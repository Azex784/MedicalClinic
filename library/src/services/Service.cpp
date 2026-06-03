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

Specialisation Service::getRequiredDoctorSpec() const
{
    return requiredDoctorSpec;
}

bool Service::getIsAvailble() const
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

void Service::setIsAvailble(const bool is_availble)
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

}
