#include "services/Consultation.h"

namespace RehabClinic
{
	using namespace std;

	const std::string& Consultation::getTopic() const
	{
		return topic;
	}

	bool Consultation::getIsOnline() const
	{
		return isOnline;
	}

	Consultation::Consultation(const unsigned serviceCost, const unsigned serviceDuration,
	                           const std::string& serviceName, const unsigned serviceId,
	                           const unsigned requiredDoctorSize,
	                           const Specialisation requiredDoctorSpec, const std::string& topic,
	                           const bool isOnline) : Service(serviceCost, serviceDuration, serviceName, serviceId,
	                                                          requiredDoctorSize, requiredDoctorSpec),
	                                                  topic(topic),
	                                                  isOnline(isOnline)
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

		return Service::getInfo() + " konsultacje, " + tmp + " o temacie: " + getTopic();
	}
}
