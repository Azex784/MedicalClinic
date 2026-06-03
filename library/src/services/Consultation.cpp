#include "services/Consultation.h"


using namespace std;

const std::string& Consultation::getTopic() const
{
    return topic;
}

bool Consultation::getIsOnline() const
{
    return isOnline;
}

Consultation::Consultation(const std::string& topic, const bool is_online): topic(topic),
                                                                            isOnline(is_online)
{
}

const std::string Consultation::getInfo() const
{
    return Service::getInfo() + " pokoj do konsultacji, w trybie online: " + to_string(getIsOnline()) + " o temacie: " + getTopic();
}
