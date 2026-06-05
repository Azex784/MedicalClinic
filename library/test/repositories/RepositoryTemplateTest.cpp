#include <boost/test/unit_test.hpp>
#include <patient/Patient.h>
#include "patient/Address.h"
#include "repositories/RepositoryTemplate.h"
#include "typedefs.h"


//Struktura tymczasowa, potrzebna tylko by sprawdzic prawidłowe działanie klasy abstrakcyjnej RepositoryTemplate
struct TmpTemplate :  RepositoryTemplate<PatientPtr, PatientPredicate, const std::string>
{

	TmpTemplate()
		: RepositoryTemplate<std::shared_ptr<Patient>, std::function<bool(std::shared_ptr<Patient>)>, const std::string
		>("<placeholder>")
	{
	}

	~TmpTemplate() = default;
	bool loadData() override
	{
		return true;
	}
	bool saveData() const override
	{
		return true;
	}
};

struct TestSuitRepositoryTemplateFixture
{
	TmpTemplate pacjentRepo;
	AddressPtr testAddress;
	PatientPtr testPatient;
	PatientPtr testPatient1;
	PatientPtr testPatient2;
	PatientPtr testPatient3;

	TestSuitRepositoryTemplateFixture()
		: testAddress(std::make_shared<Address>("Albuquerqe", "Juan Poet", "10/15")),
		  testPatient(std::make_shared<Patient>("Walter", "White", "40010112345", testAddress)),
		  testPatient1(std::make_shared<Patient>("Jesse", "Pinkman", "20010112345", testAddress)),
		  testPatient2(std::make_shared<Patient>("Skyler", "White", "93010112345", testAddress)),
		  testPatient3(std::make_shared<Patient>("Gustavo", "Fring", "91110112345", testAddress))
	{
	}

	~TestSuitRepositoryTemplateFixture() = default;
};

bool predicatePatinet(PatientPtr v)
{
	return v->getLastName() == "White";
}

BOOST_FIXTURE_TEST_SUITE(TestSuiteRepository, TestSuitRepositoryTemplateFixture)

	BOOST_AUTO_TEST_CASE(GetTest)
	{
		pacjentRepo.add(testPatient);
		pacjentRepo.add(testPatient1);
		pacjentRepo.add(testPatient2);
		pacjentRepo.add(testPatient3);

		BOOST_TEST(pacjentRepo.get("40010112345")->getName() == "Walter");
		BOOST_TEST(pacjentRepo.get("91110112345")->getLastName() == "Fring");
		BOOST_TEST(pacjentRepo.get("93010112345")->getName() == "Skyler");
	}

	BOOST_AUTO_TEST_CASE(AddGetRemoveSizeTest)
	{
		pacjentRepo.add(testPatient);
		pacjentRepo.add(testPatient1);
		pacjentRepo.add(testPatient2);
		pacjentRepo.add(testPatient3);

		BOOST_TEST(pacjentRepo.get(0) == testPatient);
		BOOST_TEST(pacjentRepo.get(1) == testPatient1);
		BOOST_TEST(pacjentRepo.get(2) == testPatient2);
		BOOST_TEST(pacjentRepo.get(3) == testPatient3);

		BOOST_TEST_REQUIRE(pacjentRepo.size() == 4);

		pacjentRepo.remove(testPatient);

		BOOST_TEST(pacjentRepo.size() == 3);
	}

	BOOST_AUTO_TEST_CASE(ReportTest)
	{
		pacjentRepo.add(testPatient);
		pacjentRepo.add(testPatient1);
		pacjentRepo.add(testPatient2);
		pacjentRepo.add(testPatient3);
		std::stringstream oss;

		oss << testPatient->getInfo() << std::endl;
		oss << testPatient1->getInfo() << std::endl;
		oss << testPatient2->getInfo() << std::endl;
		oss << testPatient3->getInfo() << std::endl;

		BOOST_TEST(pacjentRepo.report() == oss.str());
	}

	BOOST_AUTO_TEST_CASE(findByfindAllTest)
	{
		pacjentRepo.add(testPatient);
		pacjentRepo.add(testPatient1);
		pacjentRepo.add(testPatient2);
		pacjentRepo.add(testPatient3);
		PatientPredicate pacjentPredykat = predicatePatinet;

		BOOST_TEST(pacjentRepo.findBy(pacjentPredykat).size() == 2);

		BOOST_TEST(pacjentRepo.findAll().size() == 4);
	}


BOOST_AUTO_TEST_SUITE_END()
