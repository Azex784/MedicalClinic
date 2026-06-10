#include "repositories/RoomRepository.h"

#include <Exceptions.h>

#include "rooms/RehabillitationRoom.h"
#include "rooms/ConsultationRoom.h"
#include "enums/Equipment.h"

#include <fstream>
#include <sstream>

using namespace std;

RoomRepository::RoomRepository(const std::string& fileName)
	: RepositoryTemplate<std::shared_ptr<Room>, std::function<bool(std::shared_ptr<Room>)>, const unsigned>(fileName)
{
}

RoomRepository::RoomRepository()
	: RepositoryTemplate<std::shared_ptr<Room>, std::function<bool(std::shared_ptr<Room>)>, const unsigned>(
		"../../program/data/RoomRepository.txt")
{
}

bool RoomRepository::loadData()
{
	ifstream inFile;
	inFile.open(getFileName());
	string line;

	if (!inFile.is_open())
	{
		throw OpeningException(getFileName());
	}
	//Zapobiega to podwojnemu zliczeniu elementów
	clearVectorOfData();
	while (getline(inFile, line))
	{
		if (line.empty()) continue;

		//Ladujemy do strumienia
		stringstream ss(line);

		string tmp;
		bool isActive, isArchive;

		getline(ss, tmp, ';');
		unsigned int roomNumber;

		RoomPtr room;
		//Wczytujemy dane dla pokoju rehabilitacyjnego
		if (tmp == "R")
		{
			unsigned int maxCapacity;
			vector<Equipment> equipment;

			getline(ss, tmp, ';');
			roomNumber = stoi(tmp);

			getline(ss, tmp, ';');
			isActive = stoi(tmp);

			getline(ss, tmp, ';');
			isArchive = stoi(tmp);

			getline(ss, tmp, ';');
			stringstream equipmentStream(tmp);

			while (getline(equipmentStream, tmp, ','))
			{
				int enumValue = stoi(tmp);
				Equipment spec = static_cast<Equipment>(enumValue);
				equipment.push_back(spec);
			}

			getline(ss, tmp, '\n');
			maxCapacity = stoi(tmp);

			room = make_shared<RehabillitationRoom>(roomNumber, equipment, maxCapacity);
			//Wczytujemy dane dla pokoju konsultacyjnego
		}
		else if (tmp == "C")
		{
			getline(ss, tmp, ';');
			roomNumber = stoi(tmp);

			getline(ss, tmp, ';');
			isActive = stoi(tmp);

			getline(ss, tmp, '\n');
			isArchive = stoi(tmp);
			room = make_shared<ConsultationRoom>(roomNumber);
		}
		else
		{
			throw UnexpectedCharacterException("Room");
		}

		room->setIsArchive(isArchive);
		room->setIsActive(isActive);
		add(room);

		if (inFile.fail())
		{
			throw WriteException(getFileName());
		}

	}
	inFile.close();
	return true;
}

bool RoomRepository::saveData() const
{
	ofstream outFile;

	outFile.open(getFileName(), std::ios::trunc);

	if (!outFile.is_open())
	{
		throw OpeningException(getFileName());
	}

	if (getVectorOfData().empty())
	{
		outFile << "";
	}
	else
	{
		for (const RoomPtr& room : getVectorOfData())
		{
			RehabillitationRoomPtr rehabilitationRoom = dynamic_pointer_cast<RehabillitationRoom>(room);

			if (rehabilitationRoom != nullptr)
			{
				//Pokoj rehabilitacyjny
				outFile << "R" << ";";

				outFile << rehabilitationRoom->getUniqueParameter() << ";";
				outFile << rehabilitationRoom->getIsActive() << ";";
				outFile << rehabilitationRoom->getIsArchive() << ";";

				auto eqp = rehabilitationRoom->getAccessibleEqupiment();

				if (eqp.empty())
				{
					throw EmptyRecordException("Equipment");
				}
				int i;
				//Zapisujemy enuma za pomocą inta
				for (i = 0; eqp.size() - 1 > i; i++)
				{
					outFile << static_cast<int>(rehabilitationRoom->getAccessibleEqupiment()[i]) << ",";
				}
				outFile << static_cast<int>(rehabilitationRoom->getAccessibleEqupiment()[i]) << ";";
				outFile << rehabilitationRoom->getMaxCapacity() << "\n";
			}
			else if (rehabilitationRoom == nullptr)
			{
				//Pokoj konsultacyjny
				outFile << "C" << ";";

				outFile << room->getUniqueParameter() << ";";
				outFile << room->getIsActive() << ";";
				outFile << room->getIsArchive() << '\n';
			}

			if (outFile.fail())
			{
				throw WriteException(getFileName());
			}
		}
		outFile.close();
	}
	return true;
}
