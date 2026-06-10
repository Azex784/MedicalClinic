#include "managers/PatientManager.h"

#include <iostream>
#include <boost/algorithm/string/predicate.hpp>
#include "patient/Address.h"
#include "Exceptions.h"

using namespace std;

PatientManager::PatientManager(const std::string& fileName) : ManagerTemplate<
	std::shared_ptr<Patient>, PatientRepository, std::function<bool(std::shared_ptr<Patient>)>,
	const std::string>(fileName)
{
}

void PatientManager::registerPatient(const std::string& firstName, const std::string& lastName,
                                     const std::string& personalID, const std::string& city, const std::string& street,
                                     const std::string& number) const
{


	//find_first_not_of - szuka znaku z poza listy jesli znajdzie to zwraca npos
	if (firstName.find_first_not_of(ALLOWEDCHARS) != string::npos ||
		lastName.find_first_not_of(ALLOWEDCHARS) != string::npos ||
		personalID.find_first_not_of(ALLOWEDCHARS) != string::npos ||
		city.find_first_not_of(ALLOWEDCHARS) != string::npos ||
		street.find_first_not_of(ALLOWEDCHARS) != string::npos ||
		number.find_first_not_of(ALLOWEDCHARS) != string::npos)
	{
		throw LogicException("Wprowadzono nieprawidłowy znak.");
	}

	if (get(personalID) != nullptr)
	{
		throw ExistException("Pacjent",personalID);
	}

	//Szybkie sprawdzenie czy pesel to same cyfry i czy size sie zgadza
	if (personalID.size() != 11 || !all_of(personalID.begin(), personalID.end(), [](unsigned char c) {
		return isdigit(c);
	}))
	{
		throw LogicException("Wpisany pesel jest nieprawidłowy.");
	};

	PatientPredicate func = [&city, &street, &number](const PatientPtr patient) -> bool
	{
		if (patient->getAddress()->getCity() == city && patient->getAddress()->getStreet() == street && patient->
			getAddress()->getNumber() == number)
		{
			return true;
		}
		return false;
	};
	PatientPtr patient;

	auto found = findBy(func);

	if (!found.empty())
	{
		patient = make_shared<Patient>(firstName, lastName, personalID, found[0]->getAddress());
	}
	else
	{
		AddressPtr adres = make_shared<Address>(city, street, number);
		patient = make_shared<Patient>(firstName, lastName, personalID, adres);
	}

	getRepository()->add(patient);
};
