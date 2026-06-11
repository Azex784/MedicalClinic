#include <boost/test/unit_test.hpp>
#include "managers/ServiceManager.h"

#include "services/Consultation.h"
#include "services/Rehabillitation.h"
#include "managers/ManagerTemplate.h"

#include "enums/Equipment.h"
#include "enums/Specialisation.h"

#include "repositories/ServiceRepository.h"
#include "typedefs.h"
#include "Exceptions.h"

using namespace std;

struct TestSuitServiceManagerFixture
{
	std::vector<Equipment> eq1;
	std::vector<Equipment> eq2;
	const string fileName = "../../library/test/data/ServiceManagerTest.txt";
	ServiceRepositoryPtr serviceRepo = make_shared<ServiceRepository>(fileName);

	ServicePtr cons1;
	ServicePtr cons2;
	ServicePtr rehab1;
	ServicePtr rehab2;

	ServiceManagerPtr serviceManager;

	TestSuitServiceManagerFixture() :
		eq1
		({Equipment::NONE, Equipment::KINESITHERAPY_SPACE}
		)
		,
		eq2({Equipment::PHYSICAL_THERAPY_DEVICE}
		)
		,
		cons1(std::make_shared<Consultation>(150, 30, "Konsultacja odnosnie masażu", 101, 1,
		                                     Specialisation::MASSAGE_THERAPIST, "Omowienie wynikow", false)),
		cons2(std::make_shared<Consultation>(200, 45, "Neurologiczna online porada", 102, 1,
		                                     Specialisation::NEUROLOGIST, "Omowienie wynikow", true)
		)
		,
		rehab1(std::make_shared<Rehabillitation>(100, 60, "Masaz kregoslupa", 201, 0, Specialisation::MASSAGE_THERAPIST,
		                                         eq1, 1)),
		rehab2(std::make_shared<Rehabillitation>(250, 90, "Fizykoterapia", 202, 1, Specialisation::ORTHOPEDIST, eq2,
		                                         2)
		)
	{
		serviceRepo->add(cons1);
		serviceRepo->add(cons2);
		serviceRepo->add(rehab1);
		serviceRepo->add(rehab2);
		serviceRepo->saveData();
		serviceManager = make_shared<ServiceManager>(fileName);
	}

	~TestSuitServiceManagerFixture()
	{

	}
};

BOOST_FIXTURE_TEST_SUITE(TestSuitServiceManager, TestSuitServiceManagerFixture)

	BOOST_AUTO_TEST_CASE(AddServicesTest)
	{
		// Sprawdzenie stanu początkowego
		BOOST_TEST_REQUIRE(serviceManager->getRepository()->get((unsigned int)101) != nullptr);
		BOOST_TEST_REQUIRE(serviceManager->getRepository()->getVectorOfData().size() == 4);

		// Próba dodania już istniejącego zabiegu
		BOOST_CHECK_THROW(serviceManager->addConsultation(150, 30, "Masaż", 101, Specialisation::MASSAGE_THERAPIST,
		                               "Omowienie wynikow", 1, false),ExistException);
		BOOST_TEST(serviceManager->getRepository()->getVectorOfData().size() == 4);

		// Zwykłe dodanie nowego zabiegu
		serviceManager->addConsultation(150, 30, "Masaż", 118, Specialisation::MASSAGE_THERAPIST,
		                               "Omowienie wynikow", 1, false);
		BOOST_TEST(serviceManager->getRepository()->getVectorOfData().size() == 5);
		BOOST_TEST(serviceManager->getRepository()->get((unsigned int)118) != nullptr);

		// Dodanie nowego zabiegu
		serviceManager->addRehabilitation(250, 90, "Fizykoterapia", 302, eq2, Specialisation::ORTHOPEDIST, 1,
		                                 2);

		BOOST_TEST(serviceManager->getRepository()->getVectorOfData().size() == 6);
		BOOST_TEST(serviceManager->getRepository()->get((unsigned int)302) != nullptr);

		// Próba dodania istniejącej sali rehabilitacyjnej
		BOOST_CHECK_THROW(serviceManager->addRehabilitation(250, 90, "Fizykoterapia", 202, eq2, Specialisation::ORTHOPEDIST, 1,
		                                 2),ExistException);
		BOOST_TEST(serviceManager->getRepository()->getVectorOfData().size() == 6);
	}

BOOST_AUTO_TEST_SUITE_END()
