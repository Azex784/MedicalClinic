#include "repositories/PersonnelRepository.h"

#include <Exceptions.h>
#include <fstream>
#include <personnel/Doctor.h>
#include <personnel/Nurse.h>

#include "enums/Specialisation.h"

namespace RehabClinic
{

	using namespace std;

	PersonnelRepository::PersonnelRepository(const std::string& file_name)
		: RepositoryTemplate<std::shared_ptr<Personnel>, std::function<bool(std::shared_ptr<Personnel>)>, const
		                     unsigned>(file_name)
	{
	}

	PersonnelRepository::PersonnelRepository()
		: RepositoryTemplate<std::shared_ptr<Personnel>, std::function<bool(std::shared_ptr<Personnel>)>, const
		                     unsigned>(
			"../../program/data/PersonnelRepository.txt")
	{
	}


	void PersonnelRepository::loadData()
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

			string name, lastName, job, tmp;
			unsigned int personnelId;
			PersonnelPtr newPersonnel;
			bool isActive, isArchive;

			getline(ss, job, ';');

			//Gdy mamy doktora
			if (job == "D")
			{
				unsigned int doctor_cost;
				vector<Specialisation> specialisations;
				string specjalizajce;


				getline(ss, name, ';');
				getline(ss, lastName, ';');

				getline(ss, tmp, ';');
				isActive = stoi(tmp);

				getline(ss, tmp, ';');
				isArchive = stoi(tmp);

				getline(ss, tmp, ';');
				personnelId = stoul(tmp);


				getline(ss, specjalizajce, ';');
				stringstream specializationsStream(specjalizajce);

				while (getline(specializationsStream, tmp, ','))
				{
					int enumValue = stoi(tmp);
					Specialisation spec = static_cast<Specialisation>(enumValue);

					specialisations.push_back(spec);
				}
				tmp = "";
				getline(ss, tmp, '\n');
				doctor_cost = stoul(tmp);
				newPersonnel = make_shared<Doctor>(name, lastName, personnelId, specialisations, doctor_cost);
				//Gdy mamy pielegniarke
			}
			else if (job == "N")
			{
				getline(ss, name, ';');
				getline(ss, lastName, ';');

				getline(ss, tmp, ';');
				isActive = stoi(tmp);

				getline(ss, tmp, ';');
				isArchive = stoi(tmp);

				getline(ss, tmp, '\n');
				//Do unsigned longa(inta)
				personnelId = stoul(tmp);

				newPersonnel = make_shared<Nurse>(name, lastName, personnelId);
			}
			else
			{
				throw UnexpectedCharacterException("Personnel");
			}
			newPersonnel->setIsActive(isActive);
			newPersonnel->setIsArchive(isArchive);

			add(newPersonnel);

			if (inFile.fail())
			{
				throw WriteException(getFileName());
			}
		}
		inFile.close();
	}

	void PersonnelRepository::saveData() const
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
			for (const PersonnelPtr& personnel : getVectorOfData())
			{
				DoctorPtr doctor = dynamic_pointer_cast<Doctor>(personnel);
				if (doctor != nullptr)
				{
					outFile << "D" << ";";

					outFile << personnel->getName() << ";";
					outFile << personnel->getLastName() << ";";
					outFile << personnel->getIsActive() << ";";
					outFile << personnel->getIsArchive() << ";";
					outFile << personnel->getUniqueParameter() << ";";

					int i;
					//Zapisujemy enuma za pomocą inta
					for (i = 0; doctor->getSpecialisation().size() - 1 > i; i++)
					{
						outFile << static_cast<int>(doctor->getSpecialisation()[i]) << ",";
					}
					outFile << static_cast<int>(doctor->getSpecialisation()[i]) << ";";
					outFile << doctor->getDoctorCost() << "\n";
				}
				else
				{
					outFile << "N" << ";";

					outFile << personnel->getName() << ";";
					outFile << personnel->getLastName() << ";";
					outFile << personnel->getIsActive() << ";";
					outFile << personnel->getIsArchive() << ";";
					outFile << personnel->getUniqueParameter() << "\n";
				}

				if (outFile.fail())
				{
					throw WriteException(getFileName());
				}
			}
			outFile.close();
		}
	}
}
