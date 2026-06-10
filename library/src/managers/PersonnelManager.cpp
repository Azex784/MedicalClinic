#include "managers/PersonnelManager.h"

#include <personnel/Doctor.h>
#include <personnel/Nurse.h>
#include "typedefs.h"
#include "../../include/Exceptions.h"

using namespace std;

PersonnelManager::PersonnelManager(const std::string& fileName) : ManagerTemplate<
	std::shared_ptr<Personnel>, PersonnelRepository, std::function<bool(std::shared_ptr<Personnel>)>
	, const unsigned>(fileName)
{
}

void PersonnelManager::addDoctor(const std::string& firstName, const std::string& lastName,
                                 const unsigned int& personnelId, std::vector<Specialisation> specialistaion,
                                 const unsigned int& doctorCost)
{
	if (specialistaion.empty())
	throw LogicException("Wpisano nieprawidłowe puste specjalizacje.");

	if (getRepository()->get(personnelId) == nullptr)
	{
		PersonnelPtr doctor = std::make_shared<Doctor>(firstName, lastName, personnelId, specialistaion, doctorCost);
		getRepository()->add(doctor);
		return;
	}
	throw ExistException("Lekarz",to_string(personnelId));
}

void PersonnelManager::addNurse(const std::string& firstName, const std::string& lastName,
                                const unsigned int& personnelId)
{
	if (getRepository()->get(personnelId) == nullptr)
	{
		PersonnelPtr doctor = std::make_shared<Nurse>(firstName, lastName, personnelId);
		getRepository()->add(doctor);
		return;

	}
	throw ExistException("Pielęgniarka",to_string(personnelId));
}
