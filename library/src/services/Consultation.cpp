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

Consultation::Consultation(const unsigned service_cost, const unsigned service_duration,
                           const std::string& service_name, const unsigned service_id,
                           const unsigned required_doctor_size,
                           const Specialisation required_doctor_spec, const std::string& topic,
                           const bool is_online) : Service(service_cost, service_duration, service_name, service_id,
                                                           required_doctor_size, required_doctor_spec),
                                                   topic(topic),
                                                   isOnline(is_online)
{
}

const std::string Consultation::getInfo() const
{
	string tmp;
	if (getIsOnline())
	{
		tmp = "w trybie online";
	}
	else
	{
		tmp = "w trybie stacjonarnym";
	}

	return Service::getInfo() + " pokoj do konsultacji, " + tmp + " o temacie: " + getTopic();
}
