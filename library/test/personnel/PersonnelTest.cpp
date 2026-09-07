#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>

#include "PersonnelData.h"
#include "PersonData.h"

#include "personnel/Personnel.h"

using namespace MedicalClinic;

namespace dataBoost = boost::unit_test::data;

// Tworzymy klase czysto pokazową by sprawdzić działanie klas bazowej
struct TestPersonnel : public Personnel
{
	TestPersonnel(const std::string& name, const std::string& lastName, unsigned int id)
		: Personnel(name, lastName, id) {}
};

BOOST_AUTO_TEST_SUITE(TestSuitePersonnel)

BOOST_DATA_TEST_CASE(ConstructorAndGettersTest, dataBoost::make(data::names) ^ dataBoost::make(data::surnames) ^ dataBoost::make(data::personnelNumbers)
	, name, surname, personnelNumber )
{
	TestPersonnel testPersonnel = TestPersonnel(name,surname,personnelNumber);

	// Sprawdzenie metod z klasy bazowej (Person)
	BOOST_TEST(testPersonnel.getName() == name);
	BOOST_TEST(testPersonnel.getLastName() == surname);

	// Sprawdzenie metod z klasy pochodnej (Patient)
	BOOST_TEST(testPersonnel.getUniqueParameter() == personnelNumber);
}

BOOST_DATA_TEST_CASE(GetInfoTest, dataBoost::make(data::names) ^ boost::unit_test::data::make(data::surnames) ^ boost::unit_test::data::make(data::personnelNumbers)
	, name, surname, personnelNumber )
{
	TestPersonnel testPersonnel = TestPersonnel(name,surname,personnelNumber);
	
	// Zakładam poprawność getInfo klas Person i Addres - są na to osbne testy
	std::string expectedInfo = testPersonnel.Person::getInfo() + ", pracownik personelu, numer pracownika: " + std::to_string(personnelNumber);

	// Oczekujemy tego, że podstawowo będzie miał status dostępny
	BOOST_TEST(testPersonnel.getInfo() == expectedInfo);
}

BOOST_AUTO_TEST_SUITE_END()