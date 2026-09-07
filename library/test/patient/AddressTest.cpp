#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include "patient/Address.h"
#include "../testsData/AddressData.h"

using namespace MedicalClinic;

BOOST_AUTO_TEST_SUITE(TestSuiteAddress)

BOOST_DATA_TEST_CASE(ConstructorAndGettersTest,  boost::unit_test::data::make(data::cities) ^ boost::unit_test::data::make(data::streets) ^ boost::unit_test::data::make(data::numbers), city, street, number)
{
	Address testAddress = Address(city,street,number);

	BOOST_TEST(testAddress.getCity() == city);
	BOOST_TEST(testAddress.getStreet() == street);
	BOOST_TEST(testAddress.getNumber() == number);
}


BOOST_DATA_TEST_CASE(GetInfoTest,  boost::unit_test::data::make(data::cities) ^ boost::unit_test::data::make(data::streets) ^ boost::unit_test::data::make(data::numbers), city, street, number)
{

	Address testAddress = Address(city,street,number);

	// Sprawdzenie
	BOOST_TEST(testAddress.getInfo() == "Adres, miasto: " + city + ", ulica: " + street + ", numer: " + number);
}

BOOST_AUTO_TEST_SUITE_END()

using namespace MedicalClinic;