#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include "Person.h"
#include "testsData/PersonData.h"

using namespace MedicalClinic;

/**
 * Potrzeba klasy przykładowej by sprawdzić działanie abstrakcyjnej klasy
 */
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


BOOST_DATA_TEST_CASE(ConstructorAndGettersTest,  boost::unit_test::data::make(data::names) ^ boost::unit_test::data::make(data::surnames), name, surname)
{
	PersonTest testPerson = PersonTest(name,surname);

	BOOST_TEST(testPerson.getName() == name);
	BOOST_TEST(testPerson.getLastName() == surname);
}

BOOST_DATA_TEST_CASE(SettersTest, boost::unit_test::data::make(data::names) ^  boost::unit_test::data::make(data::surnames), name, surname)
{
	testPerson.setName(name);
	testPerson.setLastName(surname);

	BOOST_TEST(testPerson.getName() == name);
	BOOST_TEST(testPerson.getLastName() == surname);
}

BOOST_DATA_TEST_CASE(GetInfoTest, boost::unit_test::data::make(data::names) ^ boost::unit_test::data::make(data::surnames), name, surname)
{
	PersonTest testPerson = PersonTest(name,surname);

	std::string expectedInfo = "Osoba, imię: " + name + ", nazwisko: " + surname + ", status: ";
	// Oczekujemy tego, że podstawowo będzie miał status dostępny
	BOOST_REQUIRE(testPerson.isAvailable());
	// Sprawdzamy dla każdego przypadku
	BOOST_TEST(testPerson.getInfo() == expectedInfo + "Dostępny");

	testPerson.setEntityStatus(Status::ARCHIVED);
	BOOST_TEST(testPerson.getInfo() == expectedInfo + "Archiwalny");

	testPerson.setEntityStatus(Status::UNAVAILABLE);
	BOOST_TEST(testPerson.getInfo() == expectedInfo + "Niedostępny");
}

BOOST_AUTO_TEST_SUITE_END()