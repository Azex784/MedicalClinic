#include <boost/test/unit_test.hpp>
#include "Person.h"

struct TestSuitePersonFixture
{
	Person testPerson;
	TestSuitePersonFixture() : testPerson("Jan", "Kowalski")
	{
	}

	~TestSuitePersonFixture()
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(TestSuitePerson, TestSuitePersonFixture)

BOOST_AUTO_TEST_CASE(ConstructorAndGettersTest)
{
	BOOST_TEST(testPerson.getName() == "Jan");
	BOOST_TEST(testPerson.getLastName() == "Kowalski");

	// Zakładam, że domyślnie przy tworzeniu obiektu isArchive to false
	BOOST_TEST(testPerson.getIsArchive() == false);
}

BOOST_AUTO_TEST_CASE(SettersTest)
{
	// Zmiana stanu obiektu za pomocą setterów
	testPerson.setName("Adam");
	testPerson.setLastName("Nowak");
	testPerson.setIsArchive(true);

	// Weryfikacja
	BOOST_TEST(testPerson.getName() == "Adam");
	BOOST_TEST(testPerson.getLastName() == "Nowak");
	BOOST_TEST(testPerson.getIsArchive() == true);
}

BOOST_AUTO_TEST_CASE(GetInfoTest)
{
	// Sprawdzamy poprawnosc dzialania metody getInfo
	BOOST_TEST(testPerson.getInfo() == "Osoba: Jan Kowalski, niearchiwalna");

	// Sprawdzenie getInfo po zmianie
	testPerson.setName("Anna");
	testPerson.setLastName("Maria");
	BOOST_TEST(testPerson.getInfo() == "Osoba: Anna Maria, niearchiwalna");
}

BOOST_AUTO_TEST_SUITE_END()