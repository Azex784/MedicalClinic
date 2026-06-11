#include "services/Service.h"
#include "enums/Specialisation.h"

namespace RehabClinic
{

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

    unsigned int Service::getUniqueParameter() const
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
        return isAvailable;
    }

    bool Service::getIsArchive() const
    {
        return isArchive;
    }

    void Service::setServiceCost(const unsigned int service_cost)
    {
        serviceCost = service_cost;
    }

    void Service::setIsAvailable(const bool isAvailble1)
    {
        isAvailable = isAvailble1;
    }

    void Service::setIsArchive(const bool isArchive)
    {
        this->isArchive = isArchive;
    }

    Service::Service(const unsigned int serviceCost, const unsigned int serviceDuration, const std::string& serviceName,
                     const unsigned int serviceId, const unsigned int requiredDoctorSize,
                     const Specialisation requiredDoctorSpec) : serviceCost(serviceCost),
                                                                serviceDuration(serviceDuration),
                                                                serviceName(serviceName),
                                                                serviceId(serviceId),
                                                                requiredDoctorSize(requiredDoctorSize),
                                                                requiredDoctorSpec(requiredDoctorSpec)
    {
        setIsAvailable(1);
        setIsArchive(0);
    }

    Service::~Service()
    {
    }

    const std::string Service::getInfo() const
    {
        return "Nazwa usługi: " + getServiceName() + ", koszt usług: " + to_string(getServiceCost()) +
            ", czas trwania " + to_string(getServiceDuration()) + ", identyfikator: " + to_string(getUniqueParameter())
            + ", liczba lekarzy: " + to_string(getRequiredDoctorSize()) + ", specjalizacja lekarza/y: " +
            specialisationToString(getRequiredDoctorSpec());;
    }

}
