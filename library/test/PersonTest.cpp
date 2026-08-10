#include <boost/test/unit_test.hpp>
#include "Person.h"

using namespace MedicalClinic;

struct PersonTest: public Person
{
	PersonTest(const std::string& name, const std::string& lastName)
		: Person(name, lastName)
	{
	}

	virtual ~PersonTest()
	{

	};
};


struct TestSuitePersonFixture
{
	PersonTest testPerson;
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
}

BOOST_AUTO_TEST_CASE(SettersTest)
{
	// Zmiana stanu obiektu za pomocą setterów
	testPerson.setName("Adam");
	testPerson.setLastName("Nowak");

	// Weryfikacja
	BOOST_TEST(testPerson.getName() == "Adam");
	BOOST_TEST(testPerson.getLastName() == "Nowak");
}

BOOST_AUTO_TEST_CASE(GetInfoTest)
{
	// Sprawdzamy poprawność działania metody getInfo
	BOOST_TEST(testPerson.getInfo() == "Osoba, imię: Jan, nazwisko: Kowalski, status: Dostępny");

	// Sprawdzenie getInfo po zmianie
	testPerson.setName("Anna");
	testPerson.setLastName("Maria");

	BOOST_TEST(testPerson.getInfo() == "Osoba, imię: Anna, nazwisko: Maria, status: Dostępny");
}

BOOST_AUTO_TEST_SUITE_END()