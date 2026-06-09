#include <boost/test/unit_test.hpp>
#include "managers/PersonnelManager.h"

#include "personnel/Doctor.h"
#include "personnel/Nurse.h"
#include "managers/ManagerTemplate.h"
#include "enums/Equipment.h"
#include "enums/Specialisation.h"

#include "repositories/PersonnelRepository.h"
#include "typedefs.h"

using namespace std;

struct TestSuitPersonnelManagerFixture
{
	std::vector<Specialisation> specjalizacje;

	PersonnelPtr testPersonnel1;
	PersonnelPtr testPersonnel2;
	PersonnelRepositoryPtr testPersonnelRepository;
	PersonnelManager personnelManager;

	TestSuitPersonnelManagerFixture()
		:
		specjalizacje({Specialisation::MASSAGE_THERAPIST, Specialisation::NEUROLOGIST}),
		testPersonnel1(std::make_shared<Nurse>("Skyler", "White", 123)),
		testPersonnel2(std::make_shared<Doctor>("Walter", "White", 124, specjalizacje, 200)),
		testPersonnelRepository(std::make_shared<PersonnelRepository>("../../library/test/data/PersonnelManager.txt"))
	{
		testPersonnelRepository->add(testPersonnel1);
		testPersonnelRepository->add(testPersonnel2);
		testPersonnelRepository->saveData();
		personnelManager = PersonnelManager("../../library/test/data/PersonnelManager.txt");
	}

	~TestSuitPersonnelManagerFixture()
	{
		testPersonnelRepository->remove(testPersonnel1);
		testPersonnelRepository->remove(testPersonnel2);
		testPersonnelRepository->saveData();
	}
};

BOOST_FIXTURE_TEST_SUITE(TestSuitPersonnelManager, TestSuitPersonnelManagerFixture)

	BOOST_AUTO_TEST_CASE(AddPersonnelTest)
	{
		// Sprawdzenie stanu początkowego
		BOOST_TEST_REQUIRE(personnelManager.getRepository()->get((unsigned int)123) != nullptr);
		BOOST_TEST_REQUIRE(personnelManager.getRepository()->getVectorOfData().size() == 2);

		// Próba dodania już istniejącego personela
		personnelManager.addNurse("Marie", "Schrader", 123);
		BOOST_TEST(personnelManager.getRepository()->getVectorOfData().size() == 2);

		// Zwykłe dodanie nowej personela
		personnelManager.addNurse("Marie", "Schrader", 125);
		BOOST_TEST(personnelManager.getRepository()->getVectorOfData().size() == 3);
		BOOST_TEST(personnelManager.getRepository()->get((unsigned int)125) != nullptr);

		// Dodanie nowego lekarza
		personnelManager.addDoctor("Hank", "Schrader", 126, specjalizacje, 400);

		BOOST_TEST(personnelManager.getRepository()->getVectorOfData().size() == 4);
		BOOST_TEST(personnelManager.getRepository()->get((unsigned int)126) != nullptr);

		// Próba dodania istniejącego lekarza
		personnelManager.addDoctor("Hank", "Schrader", 126, specjalizacje, 400);
		BOOST_TEST(personnelManager.getRepository()->getVectorOfData().size() == 4);
	}

BOOST_AUTO_TEST_SUITE_END()
