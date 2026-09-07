#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include "patient/Patient.h"
#include "patient/Address.h"

#include "../testsData/PatientData.h"
#include "../testsData/AddressData.h"
#include "../testsData/PersonData.h"

using namespace MedicalClinic;
namespace dataBoost = boost::unit_test::data;

BOOST_AUTO_TEST_SUITE(TestSuitePatient)

BOOST_DATA_TEST_CASE(ConstructorAndGettersTest, dataBoost::make(data::cities) ^ dataBoost::make(data::streets) ^ dataBoost::make(data::numbers)
^ dataBoost::make(data::names) ^ boost::unit_test::data::make(data::surnames) ^ boost::unit_test::data::make(data::personalNumbers)
	, city, street, number, name, surname, personalNumber )
{
	AddressPtr testAddress = std::make_shared<Address>(city,street,number);
	Patient testPatient = Patient(name,surname,personalNumber,testAddress);

	// Sprawdzenie metod z klasy bazowej (Person)
	BOOST_TEST(testPatient.getName() == name);
	BOOST_TEST(testPatient.getLastName() == surname);

	// Sprawdzenie metod z klasy pochodnej (Patient)
	BOOST_TEST(testPatient.getUniqueParameter() == personalNumber);

	// Weryfikacja, czy adres został poprawnie przypisany i czy wskazuje na prawidłowe dane
	BOOST_TEST_REQUIRE(testPatient.getAddress() == testAddress);
	BOOST_TEST(testPatient.getAddress()->getCity() == city);
	BOOST_TEST(testPatient.getAddress()->getStreet() == street);
	BOOST_TEST(testPatient.getAddress()->getNumber() == number);
}

BOOST_DATA_TEST_CASE(GetInfoTest, dataBoost::make(data::cities) ^ dataBoost::make(data::streets) ^ dataBoost::make(data::numbers)
^ dataBoost::make(data::names) ^ boost::unit_test::data::make(data::surnames) ^ boost::unit_test::data::make(data::personalNumbers)
	, city, street, number, name, surname, personalNumber )
{
	AddressPtr testAddress = std::make_shared<Address>(city,street,number);
	Patient testPatient = Patient(name,surname,personalNumber,testAddress);

	// Zakładam poprawność getInfo klas Person i Addres - są na to osbne testy
	std::string expectedInfo = testPatient.Person::getInfo() + ", pacjent, pesel: " + personalNumber + ", " + testPatient.getAddress()->getInfo();

	BOOST_TEST(testPatient.getInfo() == expectedInfo);
}

BOOST_AUTO_TEST_SUITE_END()