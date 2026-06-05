#include "managers/ServiceManager.h"

#include <services/Consultation.h>
#include <services/Rehabillitation.h>


using namespace std;

ServiceManager::ServiceManager(const std::string& fileName) : ManagerTemplate<
	std::shared_ptr<Service>, ServiceRepository, std::function<bool(std::shared_ptr<Service>)>,
	const unsigned>(fileName)
{
}

void ServiceManager::addConsultation(const unsigned int& serviceCost, const unsigned int& serviceDuration,
                                     const std::string& serviceName, const unsigned int& serviceId,
                                     Specialisation requiredSpecialisation,
                                     const std::string& topic, const unsigned int& requiredDocSize, bool isOnline)
{
	if (getRepository()->get(serviceId) == nullptr)
	{
		ServicePtr service = make_shared<Consultation>(serviceCost, serviceDuration, serviceName, serviceId,
		                                               requiredDocSize, requiredSpecialisation, topic, isOnline);
	}
	return;
}

void ServiceManager::addRehabilitation(const unsigned int& serviceCost, const unsigned int& serviceDuration,
                                       const std::string& serviceName, const unsigned int& serviceId,
                                       std::vector<Equipment> requiredEquipment,
                                       Specialisation requiredSpecialisation, const unsigned int& requiredDocSize,
                                       const unsigned int& requiredNurseSize)
{
	if (getRepository()->get(serviceId) == nullptr)
	{
		ServicePtr service = make_shared<Rehabillitation>(serviceCost, serviceDuration, serviceName, serviceId,
		                                                  requiredDocSize
		                                                  , requiredSpecialisation, requiredEquipment,
		                                                  requiredNurseSize);
	}
	return;
}
