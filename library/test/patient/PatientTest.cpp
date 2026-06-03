#include <boost/test/unit_test.hpp>
#include <memory>
#include "patient/Patient.h"
#include "patient/Address.h"

struct TestSuitePatientFixture
{
	std::shared_ptr<Address> testAddress;
	Patient testPatient;

	TestSuitePatientFixture()
		: testAddress(std::make_shared<Address>("Albuquerqe", "Juan Poet", "10/15")),
		  testPatient("Walter", "White", "90010112345", testAddress)
	{
	}

	~TestSuitePatientFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(TestSuitePatient, TestSuitePatientFixture)

BOOST_AUTO_TEST_CASE(ConstructorTest)
{
	// Sprawdzenie metod z klasy bazowej (Person)
	BOOST_TEST(testPatient.getName() == "Walter");
	BOOST_TEST(testPatient.getLastName() == "White");
	BOOST_TEST(testPatient.getIsArchive() == false);

	// Sprawdzenie metod z klasy pochodnej (Patient)
	BOOST_TEST(testPatient.getPersonalNumber() == "90010112345");

	// Weryfikacja, czy adres został poprawnie przypisany i czy wskazuje na dobre dane
	BOOST_TEST_REQUIRE(testPatient.getAddress() == testAddress);
	BOOST_TEST(testPatient.getAddress()->getCity() == "Albuquerqe");
	BOOST_TEST(testPatient.getAddress()->getStreet() == "Juan Poet");
}

BOOST_AUTO_TEST_CASE(GetInfoTest)
{
	std::string expectedInfo = "Osoba: Walter White pacjent o adresie: \nMiasto: Albuquerqe, ulica: Juan Poet 10/15";

	BOOST_TEST(testPatient.getInfo() == expectedInfo);
}

BOOST_AUTO_TEST_CASE(InheritedSettersTest)
{
	testPatient.setName("Jesse");
	testPatient.setLastName("Pinkman");
	testPatient.setIsArchive(true);

	BOOST_TEST(testPatient.getName() == "Jesse");
	BOOST_TEST(testPatient.getLastName() == "Pinkman");
	BOOST_TEST(testPatient.getIsArchive() == true);

	//czy pesel jest ten sam
	BOOST_TEST(testPatient.getPersonalNumber() == "90010112345");
}

BOOST_AUTO_TEST_SUITE_END()