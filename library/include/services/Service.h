#ifndef REHABILITATIONCENTRE_SERVICE_H
#define REHABILITATIONCENTRE_SERVICE_H

#include <string>

enum class Specialisation;

class Service
{
private:
    unsigned int serviceCost;
    unsigned int serviceDuration;
    std::string serviceName;
    unsigned int serviceId;
    unsigned int requiredDoctorSize;
    Specialisation requiredDoctorSpec;
    bool isAvailble;
    bool isArchive;
public:
    Service(const unsigned int service_cost, const unsigned int service_duration, const std::string& service_name,
        const unsigned int service_id, const unsigned int required_doctor_size,
        const Specialisation required_doctor_spec);
    ~Service() = default;
    virtual const std::string getInfo() const;
    unsigned int getServiceCost() const;
    unsigned int getServiceDuration() const;
    const std::string& getServiceName() const;
    unsigned int getServiceId() const;
    unsigned int getRequiredDoctorSize() const;
    Specialisation getRequiredDoctorSpec() const;
    bool getIsAvailble() const;
    bool getIsArchive() const;
    void setServiceCost(const unsigned int service_cost);
    void setIsAvailble(const bool is_availble);
    void setIsArchive(const bool is_archive);
};


#endif //REHABILITATIONCENTRE_SERVICE_H