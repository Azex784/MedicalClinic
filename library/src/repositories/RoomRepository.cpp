#include "repositories/RoomRepository.h"
#include <fstream>

using namespace std;


const std::string& RoomRepository::getFileName() const
{
	return fileName;
}

RoomRepository::RoomRepository(const std::string& file_name): fileName(file_name)
{
}

bool RoomRepository::loadData()
{
	ifstream inFile;
	inFile.open(getFileName());
	string line;

	if (!inFile.is_open()) {
		return false;
	}

	while (getline(inFile, line)) {
		if (line.empty()) continue;

		//Ladujemy do strumienia
		stringstream ss(line);

		string firstName, lastName, personalNumber, city, street, number,tmp;

		getline(ss, firstName, ';');
		getline(ss, lastName, ';');
		getline(ss, personalNumber, ';');
		getline(ss, city, ';');
		getline(ss, street, ';');
		getline(ss, number, ';');
		getline(ss, tmp);

		bool isArchived = stoi(tmp);

		//Tworzenie nowych obiektow z wczytanymi danymi
		AddressPtr nowyAdress = make_shared<Address>(city,street,number);
		RoomPtr nowyPacjent =  make_shared<Room>(firstName,lastName,personalNumber,nowyAdress);

		nowyPacjent->setIsArchive(isArchived);
		add(nowyPacjent);
	}
	inFile.close();
	return true;
}
bool RoomRepository::saveData() const
{
	ofstream outFile;

	outFile.open(getFileName());

	if (outFile.good())
	{
		for (const auto& Room : getVectorOfData())
		{
			outFile << Room->getName() << ";";
			outFile << Room->getLastName() << ";";
			outFile << Room->getPersonalNumber() << ";";
			outFile << Room->getAddress()->getCity() << ";";
			outFile << Room->getAddress()->getStreet() << ";";
			outFile << Room->getAddress()->getNumber() << ';';
			outFile << Room->getIsArchive() << '\n';
		}
		outFile.close();
		return true;
	}
	//wyczucamy wyjatek
	return false;
}

