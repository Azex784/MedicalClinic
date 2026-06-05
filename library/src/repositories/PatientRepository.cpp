#include "repositories/PatientRepository.h"
#include "patient/Address.h"
#include "patient/Patient.h"

#include <fstream>

using namespace std;


PatientRepository::PatientRepository(const std::string& file_name) : RepositoryTemplate<
	std::shared_ptr<Patient>, std::function<bool(std::shared_ptr<Patient>)>, const std::string>(file_name)
{
}

PatientRepository::PatientRepository() : RepositoryTemplate<
	std::shared_ptr<Patient>, std::function<bool(std::shared_ptr<Patient>)>, const std::string>("../../program/data/PatientRepository.txt")
{
}

bool PatientRepository::loadData()
{
	ifstream inFile;
	inFile.open(getFileName());
	string line;

	if (!inFile.is_open())
	{
		return false;
	}

	while (getline(inFile, line))
	{
		if (line.empty()) continue;

		//Ladujemy do strumienia
		stringstream ss(line);

		string firstName, lastName, personalNumber, city, street, number, tmp;

		getline(ss, firstName, ';');
		getline(ss, lastName, ';');
		getline(ss, personalNumber, ';');
		getline(ss, city, ';');
		getline(ss, street, ';');
		getline(ss, number, ';');
		getline(ss, tmp, '\n');

		bool isArchived = stoi(tmp);

		//Tworzenie nowych obiektow z wczytanymi danymi
		AddressPtr nowyAdress = make_shared<Address>(city, street, number);
		PatientPtr nowyPacjent = make_shared<Patient>(firstName, lastName, personalNumber, nowyAdress);

		nowyPacjent->setIsArchive(isArchived);
		add(nowyPacjent);
	}
	inFile.close();
	return true;
}

bool PatientRepository::saveData() const
{
	ofstream outFile;

	outFile.open(getFileName());

	if (outFile.good())
	{
		for (const auto& patient : getVectorOfData())
		{
			outFile << patient->getName() << ";";
			outFile << patient->getLastName() << ";";
			outFile << patient->getUniqueParameter() << ";";
			outFile << patient->getAddress()->getCity() << ";";
			outFile << patient->getAddress()->getStreet() << ";";
			outFile << patient->getAddress()->getNumber() << ';';
			outFile << patient->getIsArchive() << '\n';
		}
		outFile.close();
		return true;
	}
	//wyczucamy wyjatek
	return false;
}
