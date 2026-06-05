#include "repositories/PersonnelRepository.h"
#include <fstream>
#include <personnel/Doctor.h>
#include <personnel/Nurse.h>

#include "enums/Specialisation.h"

using namespace std;


const std::string& PersonnelRepository::getFileName() const
{
	return fileName;
}

PersonnelRepository::PersonnelRepository(const std::string& file_name) : fileName(file_name)
{
}

bool PersonnelRepository::loadData()
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

		string name, lastName, job, tmp;
		unsigned int personnel_id;
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
			personnel_id = stoul(tmp);


			getline(ss, specjalizajce, ';');
			stringstream specializationsStream(specjalizajce);

			while (getline(specializationsStream, tmp, ','))
			{
				int enumValue = stoi(tmp);
				Specialisation spec = static_cast<Specialisation>(enumValue);

				specialisations.push_back(spec);
			}
			tmp = "";
			getline(ss, tmp, ';');
			doctor_cost = stoul(tmp);
			newPersonnel = make_shared<Doctor>(name, lastName, personnel_id, specialisations, doctor_cost);
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

			getline(ss, tmp, ';');
			//Do unsigned longa(inta)
			personnel_id = stoul(tmp);

			newPersonnel = make_shared<Nurse>(name, lastName, personnel_id);
		}
		else
		{
			return false;
		}
		newPersonnel->setIsActive(isActive);
		newPersonnel->setIsArchive(isArchive);

		add(newPersonnel);
	}
	inFile.close();
	return true;
}

bool PersonnelRepository::saveData() const
{
	ofstream outFile;

	outFile.open(getFileName());

	if (outFile.good())
	{
		for (const auto& personnel : getVectorOfData())
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
		}
		outFile.close();
		return true;
	}
	//wyczucamy wyjatek
	return false;
}
