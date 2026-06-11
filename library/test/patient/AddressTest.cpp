#include <boost/test/unit_test.hpp>
#include "patient/Address.h"

using namespace RehabClinic;

struct TestSuiteAddressFixture
{
	Address testAddress;

	TestSuiteAddressFixture() : testAddress("Warszawa", "Marszałkowska", "10/15")
	{
	}

	~TestSuiteAddressFixture()
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteAddress, TestSuiteAddressFixture)

BOOST_AUTO_TEST_CASE(ConstructorAndGettersTest)
{
	BOOST_TEST(testAddress.getCity() == "Warszawa");
	BOOST_TEST(testAddress.getStreet() == "Marszałkowska");
	BOOST_TEST(testAddress.getNumber() == "10/15");
}

BOOST_AUTO_TEST_CASE(GetInfoTest)
{
	//sprawdzenie getInfo
	BOOST_TEST(testAddress.getInfo() == "Miasto: Warszawa, ulica: Marszałkowska 10/15");
}

BOOST_AUTO_TEST_SUITE_END()