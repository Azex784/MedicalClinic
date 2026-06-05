#include <boost/test/unit_test.hpp>
#include "Personnel/Personnel.h"

//tworzymy klase czysto pokazową by sprawdzić działanie klas bazowej
struct TmpPersonnel : public Personnel
{
	TmpPersonnel(const std::string& name, const std::string& lastName, unsigned int id)
		: Personnel(name, lastName, id) {}

	bool canConductTreatment(Specialisation) const override {
		return true; 
	}
};

struct TestSuitePersonnelFixture
{
	TmpPersonnel testPersonnel;

	TestSuitePersonnelFixture()
		: testPersonnel("Walter", "White", 2137)
	{
	}

};

BOOST_FIXTURE_TEST_SUITE(TestSuitePersonnel, TestSuitePersonnelFixture)

BOOST_AUTO_TEST_CASE(ConstructorAndGettersTest)
{
	// Sprawdzenie metod z klasy bazowej (Person)
	BOOST_TEST(testPersonnel.getName() == "Walter");
	BOOST_TEST(testPersonnel.getLastName() == "White");
	BOOST_TEST(testPersonnel.getIsArchive() == false);
	BOOST_TEST(testPersonnel.getIsActive() == 1);

	// Sprawdzenie metod z klasy pochodnej (Patient)
	BOOST_TEST(testPersonnel.getUniqueParameter() == 2137);

}

BOOST_AUTO_TEST_CASE(GetInfoTest)
{
	std::string expectedInfo = "Osoba: Walter White pracownik personelu, aktywyny zawodowo";
	BOOST_TEST(testPersonnel.getInfo() == expectedInfo);
}

BOOST_AUTO_TEST_CASE(SettersTest)
{
	//niezbedne jest sprawdzenie ze nastopila zmiana
	BOOST_TEST_REQUIRE(testPersonnel.getIsActive());
	testPersonnel.setIsActive(0);
	BOOST_TEST(!testPersonnel.getIsActive());
	//czy po zmianie zmienia sie komunikat
	std::string expectedInfo = "Osoba: Walter White pracownik personelu, niedostępny";

	BOOST_TEST(testPersonnel.getInfo() == expectedInfo);
}

BOOST_AUTO_TEST_SUITE_END()