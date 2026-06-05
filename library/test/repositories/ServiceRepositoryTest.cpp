#include <boost/test/unit_test.hpp>
#include "repositories/ServiceRepository.h"
#include "services/Service.h"
#include "services/Consultation.h"
#include "services/Rehabillitation.h"

#include "enums/Specialisation.h"
#include "enums/Equipment.h"
#include "typedefs.h"

#include <fstream>
#include <vector>

using namespace std;

struct TestSuiteServiceRepositoryFixture
{
	const string fileName = "../../library/test/data/ServiceRepository.txt";
	ServiceRepositoryPtr serviceRepo = make_shared<ServiceRepository>(fileName);

	ServicePtr cons1;
	ServicePtr cons2;
	ServicePtr rehab1;
	ServicePtr rehab2;

	TestSuiteServiceRepositoryFixture()
	{
		vector<Equipment> eq1 = {Equipment::NONE, Equipment::KINESITHERAPY_SPACE};
		vector<Equipment> eq2 = {Equipment::PHYSICAL_THERAPY_DEVICE};

		cons1 = make_shared<Consultation>(150, 30, "Konsultacja odnosnie masażu", 101, 1,
		                                  Specialisation::MASSAGE_THERAPIST, "Omowienie wynikow", false);
		cons2 = make_shared<Consultation>(200, 45, "Neurologiczna online porada", 102, 1,
		                                  Specialisation::NEUROLOGIST, "Omowienie wynikow", true);

		rehab1 = make_shared<Rehabillitation>(100, 60, "Masaz kregoslupa", 201, 0,
		                                      Specialisation::MASSAGE_THERAPIST, eq1, 1);
		rehab2 = make_shared<Rehabillitation>(250, 90, "Fizykoterapia", 202, 1,
		                                      Specialisation::ORTHOPEDIST, eq2, 2);
		//Dodanie usług
		serviceRepo->add(cons1);
		serviceRepo->add(cons2);
		serviceRepo->add(rehab1);
		serviceRepo->add(rehab2);
	}

	~TestSuiteServiceRepositoryFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteServiceRepository, TestSuiteServiceRepositoryFixture)

	BOOST_AUTO_TEST_CASE(SaveDataTest)
	{
		// Sprawdzamy czy zapis się powiódł
		BOOST_TEST_REQUIRE(serviceRepo->saveData() == true);

		ifstream inFile(fileName);
		string line;

		BOOST_TEST_REQUIRE(inFile.is_open());
		// Konsultacja 1
		getline(inFile, line);
		BOOST_TEST(line == "C;150;30;Konsultacja odnosnie masażu;101;1;5;1;0;Omowienie wynikow;0");

		// Konsultacja 2
		getline(inFile, line);
		BOOST_TEST(line == "C;200;45;Neurologiczna online porada;102;1;2;1;0;Omowienie wynikow;1");

		// Rehabilitacja 1
		getline(inFile, line);
		BOOST_TEST(line == "R;100;60;Masaz kregoslupa;201;0;5;1;0;0,2;1");

		// Rehabilitacja 2
		getline(inFile, line);
		BOOST_TEST(line == "R;250;90;Fizykoterapia;202;1;1;1;0;1;2");

		inFile.close();
	}

	BOOST_AUTO_TEST_CASE(LoadDataTest)
	{
		ServiceRepositoryPtr serviceRepo1 = make_shared<ServiceRepository>(fileName);

		// Zapisujemy stan oryginalnego repozytorium i ładujemy do nowego
		BOOST_TEST_REQUIRE(serviceRepo->saveData() == true);
		BOOST_TEST_REQUIRE(serviceRepo1->loadData() == true);

		// Weryfikacja rozmiaru
		BOOST_TEST_REQUIRE(serviceRepo1->getVectorOfData().size() == serviceRepo->getVectorOfData().size());

		// Pętla weryfikująca
		for (int i = 0; i < serviceRepo1->getVectorOfData().size(); i++)
		{
			ServicePtr loadedService = serviceRepo1->getVectorOfData()[i];
			ServicePtr originalService = serviceRepo->getVectorOfData()[i];

			// Sprawdzamy parametry wspólne
			BOOST_TEST(loadedService->getServiceName() == originalService->getServiceName());
			BOOST_TEST(loadedService->getUniqueParameter() == originalService->getUniqueParameter());
			BOOST_TEST(loadedService->getIsAvailable() == originalService->getIsAvailable());
			BOOST_TEST(loadedService->getIsArchive() == originalService->getIsArchive());
			BOOST_TEST(loadedService->getServiceCost() == originalService->getServiceCost());
			BOOST_TEST(loadedService->getServiceDuration() == originalService->getServiceDuration());
			BOOST_TEST(loadedService->getRequiredDoctorSize() == originalService->getRequiredDoctorSize());
			BOOST_TEST(
				static_cast<int>(loadedService->getRequiredDoctorSpec()) == static_cast<int>(originalService->
					getRequiredDoctorSpec()));

			// Sprawdzamy dla konsultacji
			ConsultationPtr loadedConsultation = dynamic_pointer_cast<Consultation>(loadedService);
			ConsultationPtr originalConsultation = dynamic_pointer_cast<Consultation>(originalService);
			if (originalConsultation != nullptr)
			{
				// Sprawdzamy prawidłowe rzutowanie
				BOOST_TEST_REQUIRE(loadedConsultation != nullptr);

				// Unikalne atrybuty konsultacji
				BOOST_TEST(loadedConsultation->getTopic() == originalConsultation->getTopic());
				BOOST_TEST(loadedConsultation->getIsOnline() == originalConsultation->getIsOnline());
			}

			// Sprawdzamy dla Rehabilitacji
			RehabillitationPtr originalRehabillitation = dynamic_pointer_cast<Rehabillitation>(originalService);
			if (originalRehabillitation != nullptr)
			{
				RehabillitationPtr loadedRehabillitation = dynamic_pointer_cast<Rehabillitation>(loadedService);
				BOOST_TEST_REQUIRE(loadedRehabillitation != nullptr);

				// Unikalne atrybuty
				BOOST_TEST(
					loadedRehabillitation->getRequiredNurseSize() == originalRehabillitation->getRequiredNurseSize());
				//By porownac wektor enumów należy upewnić się że rozmiar jest taki sam
				BOOST_TEST_REQUIRE(
					loadedRehabillitation->getRequiredEqupiment().size() == originalRehabillitation->
					getRequiredEqupiment().size());

				// Weryfikacja wartości wektora enumów
				for (int j = 0; j < loadedRehabillitation->getRequiredEqupiment().size(); j++)
				{
					BOOST_TEST(equipmentToString(loadedRehabillitation->getRequiredEqupiment()[j]) ==
						equipmentToString(originalRehabillitation->getRequiredEqupiment()[j]));
				}
			}
		}
	}

BOOST_AUTO_TEST_SUITE_END()
