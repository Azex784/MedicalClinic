#include <boost/test/unit_test.hpp>
#include <managers/PatientManager.h>

#include "patient/Patient.h"
#include "patient/Address.h"
#include "managers/PatientManager.h"

#include "repositories/PatientRepository.h"
#include "typedefs.h"
#include "../../include/Exceptions.h"


struct TestSuitPatientTemplateFixture
{
	AddressPtr testAddress;
	PatientPtr testPatient;
	PatientPtr testPatient1;
	PatientPtr testPatient2;
	PatientPtr testPatient3;
	PatientRepositoryPtr testPatientRepository;

	PatientManager pacjentManager;

	TestSuitPatientTemplateFixture()
		: testAddress(std::make_shared<Address>("Albuquerqe", "Juan Poet", "10/15")),
		  testPatient(std::make_shared<Patient>("Walter", "White", "40010112345", testAddress)),
		  testPatient1(std::make_shared<Patient>("Jesse", "Pinkman", "20010112345", testAddress)),
		  testPatient2(std::make_shared<Patient>("Skyler", "White", "93010112345", testAddress)),
		  testPatient3(std::make_shared<Patient>("Gustavo", "Fring", "91110112345", testAddress)),
		  testPatientRepository(std::make_shared<PatientRepository>("../../library/test/data/PatientManager.txt"))
	{
		//Zapisujemy dane przed rozpoczeciem testowania
		testPatientRepository->add(testPatient);
		testPatientRepository->add(testPatient1);
		testPatientRepository->add(testPatient2);
		testPatientRepository->add(testPatient3);
		testPatientRepository->saveData();
		pacjentManager = PatientManager("../../library/test/data/PatientManager.txt");
	}

	~TestSuitPatientTemplateFixture()
	{

	}
};

BOOST_FIXTURE_TEST_SUITE(TestSuitPatientTemplate, TestSuitPatientTemplateFixture)

	BOOST_AUTO_TEST_CASE(RegisterPatientTest)
	{
		BOOST_TEST_REQUIRE(pacjentManager.getRepository()->get("40010112345") != nullptr);
		BOOST_TEST_REQUIRE(pacjentManager.getRepository()->getVectorOfData().size() == 4);
		//Testy wyjątku
		BOOST_CHECK_THROW(pacjentManager.registerPatient("Walter", "White", "40010112345", "Albuquerqe", "Juan Poet", "10/15"),ExistException);
		BOOST_CHECK_THROW(pacjentManager.registerPatient("Walter", "White", "2", "Albuquerqe", "Juan Poet", "10/15"),LogicException);
		BOOST_CHECK_THROW(pacjentManager.registerPatient("Walter", "White", "Walthu", "Albuquerqe", "Juan Poet", "10/15"),LogicException);

		BOOST_TEST(pacjentManager.getRepository()->getVectorOfData().size() == 4);

		pacjentManager.registerPatient("Walter Junior", "White", "40010112346", "Albuquerqe", "Juan Poet", "10/15");

		BOOST_TEST(pacjentManager.getRepository()->getVectorOfData().size() == 5);
		//Czy poprawnie taki sam adres zostal przypisany?
		BOOST_TEST(pacjentManager.getRepository()->get("40010112346") != nullptr);
		BOOST_TEST(
			pacjentManager.getRepository()->get("40010112345")->getAddress() == pacjentManager.getRepository()->get(
				"40010112346")->getAddress());

		// Zwykłe dodanie
		pacjentManager.registerPatient("Kim", "Wexler", "40010112347", "Albuquerqe", "Crimson Street", "1/25");
		BOOST_TEST(pacjentManager.getRepository()->get("40010112347") != nullptr);
		BOOST_TEST(pacjentManager.getRepository()->getVectorOfData().size() == 6);
	}


BOOST_AUTO_TEST_SUITE_END()
