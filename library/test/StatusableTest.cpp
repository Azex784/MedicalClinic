#include <boost/test/unit_test.hpp>
#include "Statusable.h"

using namespace MedicalClinic;

/**
 * Potrzeba klasy przykładowej by sprawdzić działanie abstrakcyjnej klasy
 */
struct Example : public Statusable
{
	Example() = default;

	virtual ~Example()
	{
	};
};

struct TestSuiteStatusableFixture
{
	Example testExample;

	TestSuiteStatusableFixture() : testExample()
	{
	}

	~TestSuiteStatusableFixture()
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteStatusable, TestSuiteStatusableFixture)

BOOST_AUTO_TEST_CASE(GettersTest)
{
	BOOST_TEST(testExample.getEntityStatus() == Status::AVAILABLE);
	BOOST_TEST(testExample.isAvailable());
}

BOOST_AUTO_TEST_CASE(SettersTest)
{
	// Zmiana stanu obiektu za pomocą setterów
	testExample.setEntityStatus(Status::UNAVAILABLE);

	// Weryfikacja
	BOOST_TEST(testExample.getEntityStatus() == Status::UNAVAILABLE);
}

BOOST_AUTO_TEST_SUITE_END()