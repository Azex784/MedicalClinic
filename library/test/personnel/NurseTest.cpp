#include <boost/test/unit_test.hpp>
#include "personnel/Nurse.h"

using namespace MedicalClinic;


struct TestSuiteNurseFixture
{
    Nurse testNurse;

    TestSuiteNurseFixture()
        : testNurse("Elżbieta", "Kowalczyk", 12341)
    {
    }

    ~TestSuiteNurseFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteNurse, TestSuiteNurseFixture)

BOOST_AUTO_TEST_CASE(ConstructorAndGettersTest)
{
    BOOST_TEST(testNurse.getName() == "Elżbieta");
    BOOST_TEST(testNurse.getLastName() == "Kowalczyk");
    BOOST_TEST(testNurse.getUniqueParameter() == 12341);
}


BOOST_AUTO_TEST_CASE(GetInfoTest)
{
    std::string expectedInfo = testNurse.Personnel::getInfo() + ", pielęgniarka.";
    BOOST_TEST(testNurse.getInfo() == expectedInfo);
}

BOOST_AUTO_TEST_SUITE_END()