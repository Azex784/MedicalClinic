#include "managers/ServiceManager.h"

#include <services/Consultation.h>
#include <services/Rehabillitation.h>

#include "Exceptions.h"


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
	//find_first_not_of - szuka znaku z poza listy jesli znajdzie to zwraca npos
	if (serviceName.find_first_not_of(ALLOWEDCHARS) != string::npos ||
		topic.find_first_not_of(ALLOWEDCHARS) != string::npos)
	{
		throw LogicException("Wprowadzono nieprawidłowy znak.");
	}


	if (getRepository()->get(serviceId) == nullptr)
	{
		ServicePtr service = make_shared<Consultation>(serviceCost, serviceDuration, serviceName, serviceId,
		                                               requiredDocSize, requiredSpecialisation, topic, isOnline);
		getRepository()->add(service);
		return;
	}
	throw ExistException("Konsultacja", to_string(serviceId));
}

void ServiceManager::addRehabilitation(const unsigned int& serviceCost, const unsigned int& serviceDuration,
                                       const std::string& serviceName, const unsigned int& serviceId,
                                       std::vector<Equipment> requiredEquipment,
                                       Specialisation requiredSpecialisation, const unsigned int& requiredDocSize,
                                       const unsigned int& requiredNurseSize)
{

	//find_first_not_of - szuka znaku z poza listy jesli znajdzie to zwraca npos
	if (serviceName.find_first_not_of(ALLOWEDCHARS) != string::npos)
	{
		throw LogicException("Wprowadzono nieprawidłowy znak.");
	}


	if (requiredEquipment.empty())throw LogicException("Wpisano nieprawidłowe pusty sprzęt.");

	if (getRepository()->get(serviceId) == nullptr)
	{
		ServicePtr service = make_shared<Rehabillitation>(serviceCost, serviceDuration, serviceName, serviceId,
		                                                  requiredDocSize
		                                                  , requiredSpecialisation, requiredEquipment,
		                                                  requiredNurseSize);
		getRepository()->add(service);
		return;
	}
	throw ExistException("Rehabilitacja", to_string(serviceId));
}
