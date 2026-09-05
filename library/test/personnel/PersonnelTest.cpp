#include <boost/test/unit_test.hpp>
#include "personnel/Personnel.h"

using namespace MedicalClinic;

// Tworzymy klase czysto pokazową by sprawdzić działanie klas bazowej
struct TmpPersonnel : public Personnel
{
	TmpPersonnel(const std::string& name, const std::string& lastName, const unsigned int& id)
		: Personnel(name, lastName, id) {}
};

struct TestSuitePersonnelFixture
{
	TmpPersonnel testPersonnel;

	TestSuitePersonnelFixture()
		: testPersonnel("Walter", "White", 1234)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(TestSuitePersonnel, TestSuitePersonnelFixture)

BOOST_AUTO_TEST_CASE(ConstructorAndGettersTest)
{
	// Sprawdzenie metod z klasy bazowej (Person)
	BOOST_TEST(testPersonnel.getName() == "Walter");
	BOOST_TEST(testPersonnel.getLastName() == "White");

	// Sprawdzenie metod z klasy pochodnej
	BOOST_TEST(testPersonnel.getUniqueParameter() == 1234);
}

BOOST_AUTO_TEST_CASE(GetInfoTest)
{
	std::string expectedInfo = testPersonnel.Person::getInfo() + ", pracownik personelu, numer pracownika: 1234, aktywyny/a zawodowo";
	BOOST_TEST(testPersonnel.getInfo() == expectedInfo);
}

BOOST_AUTO_TEST_SUITE_END()