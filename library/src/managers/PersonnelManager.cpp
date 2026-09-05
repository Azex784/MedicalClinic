#include "managers/PersonnelManager.h"

#include <personnel/Doctor.h>
#include <personnel/Nurse.h>
#include "typedefs.h"
#include "Exceptions.h"

namespace MedicalClinic
{

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
		//find_first_not_of - szuka znaku z poza listy jesli znajdzie to zwraca npos
		if (firstName.find_first_not_of(ALLOWEDCHARS) != string::npos ||
			lastName.find_first_not_of(ALLOWEDCHARS) != string::npos)
		{
			throw LogicException("Wprowadzono nieprawidłowy znak.");
		}

		if (firstName.length() > 20 || lastName.length() > 20)
		{
			throw length_error("Imię lub nazwisko przekracza limit 20 znaków.");
		}

		if (specialistaion.empty())
			throw LogicException("Wpisano nieprawidłowe puste specjalizacje.");

		if (getRepository()->get(personnelId) == nullptr)
		{
			PersonnelPtr doctor = std::make_shared<
				Doctor>(firstName, lastName, personnelId, specialistaion, doctorCost);
			getRepository()->add(doctor);
			return;
		}
		throw ExistException("Lekarz", to_string(personnelId));
	}

	void PersonnelManager::addNurse(const std::string& firstName, const std::string& lastName,
	                                const unsigned int& personnelId)
	{
		//find_first_not_of - szuka znaku z poza listy jesli znajdzie to zwraca npos
		if (firstName.find_first_not_of(ALLOWEDCHARS) != string::npos ||
			lastName.find_first_not_of(ALLOWEDCHARS) != string::npos)
		{
			throw LogicException("Wprowadzono nieprawidłowy znak.");
		}

		if (firstName.length() > 20 || lastName.length() > 20)
		{
			throw length_error("Imię lub nazwisko przekracza limit 20 znaków.");
		}

		if (getRepository()->get(personnelId) == nullptr)
		{
			PersonnelPtr nurse = std::make_shared<Nurse>(firstName, lastName, personnelId);
			getRepository()->add(nurse);
			return;
		}
		throw ExistException("Pielęgniarka", to_string(personnelId));
	}
}
