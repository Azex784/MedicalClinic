#include <boost/test/unit_test.hpp>
#include "patient/Patient.h"
#include "patient/Address.h"

using namespace MedicalClinic;

struct TestSuitePatientFixture
{
	AddressPtr testAddress;
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

	// Sprawdzenie metod z klasy pochodnej (Patient)
	BOOST_TEST(testPatient.getUniqueParameter() == "90010112345");

	// Weryfikacja, czy adres został poprawnie przypisany i czy wskazuje na prawidłowe dane
	BOOST_TEST_REQUIRE(testPatient.getAddress() == testAddress);
	BOOST_TEST(testPatient.getAddress()->getCity() == "Albuquerqe");
	BOOST_TEST(testPatient.getAddress()->getStreet() == "Juan Poet");
}

BOOST_AUTO_TEST_CASE(GetInfoTest)
{
	std::string expectedInfo = testPatient.Person::getInfo() + ", pacjent, pesel: 90010112345, " + testAddress->getInfo();

	BOOST_TEST(testPatient.getInfo() == expectedInfo);
}

BOOST_AUTO_TEST_SUITE_END()