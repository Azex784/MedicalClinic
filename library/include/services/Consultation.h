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
    Consultation(const std::string& topic, const bool is_online);
    ~Consultation() = default;
    const std::string getInfo() const override;
    const std::string& getTopic() const;
    bool getIsOnline() const;
};


#endif //REHABILITATIONCENTRE_CONSULTATION_H