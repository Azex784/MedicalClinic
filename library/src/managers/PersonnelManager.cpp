#include "managers/PersonnelManager.h"

#include <personnel/Doctor.h>
#include <personnel/Nurse.h>


using namespace std;

PersonnelManager::PersonnelManager(const std::string& fileName): ManagerTemplate<std::shared_ptr<Personnel>, PatientRepository, std::function<bool(std::shared_ptr<Personnel>)>
	, const unsigned>(fileName)
{
}

void PersonnelManager::addDoctor(const std::string& firstName, const std::string& lastName,
                                 const unsigned int& personnelId, std::vector<Specialisation> specialistaion, const unsigned int &doctorCost)
{
	if (getRepository()->get(personnelId) == nullptr)
	{
		PersonnelPtr doctor = std::make_shared<Doctor>(firstName, lastName, personnelId,specialistaion, doctorCost);
	}
	return;
}

void PersonnelManager::addNurse(const std::string& firstName, const std::string& lastName,
	const unsigned int& personnelId)
{
	if (getRepository()->get(personnelId) == nullptr)
	{
		PersonnelPtr doctor = std::make_shared<Nurse>(firstName, lastName, personnelId);
	}
	return;
}
