#include "managers/PatientManager.h"

#include <patient/Address.h>


using namespace std;

PatientManager::PatientManager(const std::string& fileName): ManagerTemplate<std::shared_ptr<Patient>, PatientRepository, std::function<bool(std::shared_ptr<Patient>)>,
                                                                             const std::string>(fileName)
{
}

void PatientManager::registerPatient(const std::string& firstName, const std::string& lastName,
                                                 const std::string& personalID, const std::string& city, const std::string& street, const std::string& number) const
{
	AddressPtr adres = make_shared<Address>(city, street, number);
	PatientPtr patient = make_shared<Patient>(firstName, lastName, personalID, adres);

	if (getRepository()->get(personalID) != nullptr)
	{
		return;
	}

	getRepository()->add(patient);
};
