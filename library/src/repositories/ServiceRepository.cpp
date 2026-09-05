#include "repositories/ServiceRepository.h"

#include <Exceptions.h>

#include "services/Service.h"
#include "services/Rehabillitation.h"
#include "services/Consultation.h"

#include "enums/Equipment.h"
#include "enums/Specialisation.h"

#include <fstream>
#include <sstream>

namespace MedicalClinic
{

	using namespace std;

	ServiceRepository::ServiceRepository(const std::string& fileName)
		: RepositoryTemplate<std::shared_ptr<Service>, std::function<bool(std::shared_ptr<Service>)>, const
		                     unsigned>(fileName)
	{
	}

	ServiceRepository::ServiceRepository()
		: RepositoryTemplate<std::shared_ptr<Service>, std::function<bool(std::shared_ptr<Service>)>, const unsigned>(
			"../../program/data/ServiceRepository.txt")
	{
	}

	void ServiceRepository::loadData()
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

			string serviceName, tmp;
			unsigned int serviceCost, serviceDuration, serviceId, requiredDoctorSize;

			bool isActive, isArchive;

			getline(ss, tmp, ';');

			ServicePtr service;
			//Wczytujemy dane rehabilitacji
			if (tmp == "R")
			{
				unsigned int requiredNurseSize;
				vector<Equipment> requiredEqupiment;

				getline(ss, tmp, ';');
				serviceCost = stoi(tmp);

				getline(ss, tmp, ';');
				serviceDuration = stoi(tmp);

				getline(ss, tmp, ';');
				serviceName = tmp;

				getline(ss, tmp, ';');
				serviceId = stoi(tmp);

				getline(ss, tmp, ';');
				requiredDoctorSize = stoi(tmp);

				getline(ss, tmp, ';');
				int enumSpec = stoi(tmp);
				Specialisation requiredDoctorSpec = static_cast<Specialisation>(enumSpec);

				getline(ss, tmp, ';');
				isActive = stoi(tmp);

				getline(ss, tmp, ';');
				isArchive = stoi(tmp);

				//Wczytanie wymaganego sprzętu
				getline(ss, tmp, ';');
				stringstream equipmentStream(tmp);

				while (getline(equipmentStream, tmp, ','))
				{
					int enumValue = stoi(tmp);
					Equipment equ = static_cast<Equipment>(enumValue);
					requiredEqupiment.push_back(equ);
				}

				getline(ss, tmp, '\n');
				requiredNurseSize = stoul(tmp);

				service = make_shared<Rehabillitation>(serviceCost, serviceDuration, serviceName, serviceId,
				                                       requiredDoctorSize, requiredDoctorSpec, requiredEqupiment,
				                                       requiredNurseSize);
				//Wczytujemy dane dla konsultacji
			}
			else if (tmp == "C")
			{
				string topic;
				bool isOnline;

				getline(ss, tmp, ';');
				serviceCost = stoi(tmp);

				getline(ss, tmp, ';');
				serviceDuration = stoi(tmp);

				getline(ss, tmp, ';');
				serviceName = tmp;

				getline(ss, tmp, ';');
				serviceId = stoi(tmp);

				getline(ss, tmp, ';');
				requiredDoctorSize = stoi(tmp);

				getline(ss, tmp, ';');
				int enumSpec = stoi(tmp);
				Specialisation requiredDoctorSpec = static_cast<Specialisation>(enumSpec);

				getline(ss, tmp, ';');
				isActive = stoi(tmp);

				getline(ss, tmp, ';');
				isArchive = stoi(tmp);

				getline(ss, tmp, ';');
				topic = tmp;

				getline(ss, tmp, '\n');
				isOnline = stoi(tmp);
				service = make_shared<Consultation>(serviceCost, serviceDuration, serviceName, serviceId,
				                                    requiredDoctorSize, requiredDoctorSpec, topic, isOnline);
			}
			else
			{
				throw UnexpectedCharacterException("Service");
			}

			service->setIsArchive(isArchive);
			service->setIsAvailable(isActive);
			add(service);

			if (inFile.fail())
			{
				throw WriteException(getFileName());
			}
		}
		inFile.close();
	}

	void ServiceRepository::saveData() const
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
			for (const ServicePtr& service : getVectorOfData())
			{
				RehabillitationPtr rehabilitationService = dynamic_pointer_cast<Rehabillitation>(service);

				if (rehabilitationService != nullptr)
				{
					//Rehabilitacja
					outFile << "R" << ";";

					outFile << rehabilitationService->getServiceCost() << ";";
					outFile << rehabilitationService->getServiceDuration() << ";";
					outFile << rehabilitationService->getServiceName() << ";";
					outFile << rehabilitationService->getUniqueParameter() << ";";

					outFile << rehabilitationService->getRequiredDoctorSize() << ";";
					outFile << static_cast<int>(rehabilitationService->getRequiredDoctorSpec()) << ";";
					outFile << rehabilitationService->getIsAvailable() << ";";
					outFile << rehabilitationService->getIsArchive() << ";";

					int i;
					//Zapisujemy enuma za pomocą inta
					auto eqp = rehabilitationService->getRequiredEqupiment();

					if (eqp.empty())
					{
						throw EmptyRecordException("Equipment");
					};

					for (i = 0; (int)eqp.size() - 1 > i; i++)
					{
						outFile << static_cast<int>(rehabilitationService->getRequiredEqupiment()[i]) << ",";
					}
					outFile << static_cast<int>(rehabilitationService->getRequiredEqupiment()[i]) << ";";
					outFile << rehabilitationService->getRequiredNurseSize() << "\n";
				}
				else if (rehabilitationService == nullptr)
				{
					ConsultationPtr consultationService = dynamic_pointer_cast<Consultation>(service);

					//Pokoj konsultacyjny
					outFile << "C" << ";";

					outFile << consultationService->getServiceCost() << ";";
					outFile << consultationService->getServiceDuration() << ";";
					outFile << consultationService->getServiceName() << ";";
					outFile << consultationService->getUniqueParameter() << ";";
					outFile << consultationService->getRequiredDoctorSize() << ";";
					outFile << static_cast<int>(consultationService->getRequiredDoctorSpec()) << ";";
					outFile << consultationService->getIsAvailable() << ";";
					outFile << consultationService->getIsArchive() << ";";
					outFile << consultationService->getTopic() << ";";
					outFile << consultationService->getIsOnline() << "\n";
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
