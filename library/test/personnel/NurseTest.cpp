#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>

#include "PersonnelData.h"
#include "PersonData.h"

#include "personnel/Nurse.h"

using namespace MedicalClinic;

namespace dataBoost = boost::unit_test::data;

BOOST_AUTO_TEST_SUITE(TestSuiteNurse)

BOOST_DATA_TEST_CASE(ConstructorAndGettersTest, dataBoost::make(data::names) ^ dataBoost::make(data::surnames) ^ dataBoost::make(data::personnelNumbers)
    , name, surname, personnelNumber )
{
    Nurse testNurse = Nurse(name,surname,personnelNumber);

    // Sprawdzenie metod z klasy bazowej (Person)
    BOOST_TEST(testNurse.getName() == name);
    BOOST_TEST(testNurse.getLastName() == surname);

    // Sprawdzenie metod z klasy pochodnej (Patient)
    BOOST_TEST(testNurse.getUniqueParameter() == personnelNumber);
}

BOOST_DATA_TEST_CASE(GetInfoTest, dataBoost::make(data::names) ^ dataBoost::make(data::surnames) ^ dataBoost::make(data::personnelNumbers)
    , name, surname, personnelNumber )
{
    Nurse testNurse = Nurse(name,surname,personnelNumber);
	
    // Zakładam poprawność getInfo klas Person i Addres - są na to osbne testy
    std::string expectedInfo = testNurse.Person::getInfo() + ", pracownik personelu, numer pracownika: " + std::to_string(personnelNumber) + ", pielęgniarka.";

    // Oczekujemy tego, że podstawowo będzie miał status dostępny
    BOOST_TEST(testNurse.getInfo() == expectedInfo);
}

BOOST_AUTO_TEST_SUITE_END()