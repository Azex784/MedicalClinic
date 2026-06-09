#include <boost/test/unit_test.hpp>
#include "patient/Patient.h"
#include "patient/Address.h"
#include "managers/ManagerTemplate.h"

#include "repositories/PatientRepository.h"
#include "typedefs.h"

struct TestSuitManagerTemplateFixture
{
	AddressPtr testAddress;
	PatientPtr testPatient;
	PatientPtr testPatient1;
	PatientPtr testPatient2;
	PatientPtr testPatient3;
	PatientRepositoryPtr testPatientRepository;

	ManagerTemplate<PatientPtr, PatientRepository, PatientPredicate, const std::string> pacjentManager;

	TestSuitManagerTemplateFixture()
		: testAddress(std::make_shared<Address>("Albuquerqe", "Juan Poet", "10/15")),
		  testPatient(std::make_shared<Patient>("Walter", "White", "40010112345", testAddress)),
		  testPatient1(std::make_shared<Patient>("Jesse", "Pinkman", "20010112345", testAddress)),
		  testPatient2(std::make_shared<Patient>("Skyler", "White", "93010112345", testAddress)),
		  testPatient3(std::make_shared<Patient>("Gustavo", "Fring", "91110112345", testAddress)),
		  testPatientRepository(std::make_shared<PatientRepository>("../../library/test/data/ManagerTemplate.txt"))
	{
		testPatientRepository->add(testPatient);
		testPatientRepository->add(testPatient1);
		testPatientRepository->add(testPatient2);
		testPatientRepository->add(testPatient3);
		testPatientRepository->saveData();
		pacjentManager = ManagerTemplate<PatientPtr, PatientRepository, PatientPredicate, const std::string>("../../library/test/data/ManagerTemplate.txt");

	}
	~TestSuitManagerTemplateFixture()
	{
	}
};

bool predicatePatinet1(PatientPtr v)
{
	return v->getLastName() == "White";
}

BOOST_FIXTURE_TEST_SUITE(TestSuitManagerTemplate, TestSuitManagerTemplateFixture)

	BOOST_AUTO_TEST_CASE(GetTest)
	{
		BOOST_TEST(pacjentManager.get("40010112345")->getName() == "Walter");
		BOOST_TEST(pacjentManager.get("91110112345")->getLastName() == "Fring");
		BOOST_TEST(pacjentManager.get("93010112345")->getName() == "Skyler");
		BOOST_TEST(pacjentManager.get("40010112345")->getName() == "Walter");
	}

	BOOST_AUTO_TEST_CASE(FindByFindAllTest)
	{
		PatientPredicate pacjentPredykat = predicatePatinet1;

		BOOST_TEST(pacjentManager.findBy(pacjentPredykat).size() == 2);
		BOOST_TEST(pacjentManager.findAll().size() == 4);
	}


BOOST_AUTO_TEST_SUITE_END()
