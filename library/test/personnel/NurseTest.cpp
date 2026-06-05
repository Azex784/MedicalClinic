#include <boost/test/unit_test.hpp>
#include "personnel/Nurse.h"
#include "enums/Specialisation.h"

struct TestSuiteNurseFixture
{
    std::vector<Specialisation> testSpecs;
    Nurse testNurse;

    TestSuiteNurseFixture()
        : testNurse("Elzbieta", "Kowalczyk", 12341)
    {
    }

    ~TestSuiteNurseFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteNurse, TestSuiteNurseFixture)

BOOST_AUTO_TEST_CASE(ConstructorAndGettersTest)
{
    // Constructor check
    BOOST_TEST(testNurse.getName() == "Elzbieta");
    BOOST_TEST(testNurse.getLastName() == "Kowalczyk");
    BOOST_TEST(testNurse.getUniqueParameter() == 12341);
}

BOOST_AUTO_TEST_CASE(CanConductTreatmentTest)
{
    BOOST_TEST(testNurse.canConductTreatment(Specialisation::PHYSIOTHERAPIST) == true);
    BOOST_TEST(testNurse.canConductTreatment(Specialisation::ORTHOPEDIST) == true);
    BOOST_TEST(testNurse.canConductTreatment(Specialisation::SPORTS_MEDICINE) == true);
    BOOST_TEST(testNurse.canConductTreatment(Specialisation::OSTEOPATH) == true);
    BOOST_TEST(testNurse.canConductTreatment(Specialisation::MASSAGE_THERAPIST) == true);
    BOOST_TEST(testNurse.canConductTreatment(Specialisation::RHEUMATOLOGIST) == true);
    //czy nie moze przeprowadizc neurologi
    BOOST_TEST(testNurse.canConductTreatment(Specialisation::NEUROLOGIST) == false);
}

BOOST_AUTO_TEST_CASE(GetInfoTest)
{
    std::string expectedInfo = "Osoba: Elzbieta Kowalczyk pracownik personelu, aktywyny zawodowo pielegniarka";
    BOOST_TEST(testNurse.getInfo() == expectedInfo);
}

BOOST_AUTO_TEST_SUITE_END()