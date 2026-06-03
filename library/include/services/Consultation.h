#ifndef REHABILITATIONCENTRE_CONSULTATION_H
#define REHABILITATIONCENTRE_CONSULTATION_H

#include <string>
#include "services/Service.h"

class Consultation : public Service
{
private:
    std::string topic;
    bool isOnline;
public:
    Consultation(const unsigned service_cost, const unsigned service_duration, const std::string& service_name,
        const unsigned service_id, const unsigned required_doctor_size, const Specialisation required_doctor_spec,
        const std::string& topic, const bool is_online);

    ~Consultation() = default;
    const std::string getInfo() const override;
    const std::string& getTopic() const;
    bool getIsOnline() const;
};


#endif //REHABILITATIONCENTRE_CONSULTATION_H