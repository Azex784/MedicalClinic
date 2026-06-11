#include <boost/test/unit_test.hpp>
#include "personnel/Doctor.h"
#include "enums/Specialisation.h"

struct TestSuiteDoctorFixture
{
    std::vector<Specialisation> testSpecs;
    Doctor testDoctor;

    TestSuiteDoctorFixture()
        : testSpecs{Specialisation::PHYSIOTHERAPIST, Specialisation::ORTHOPEDIST},
          testDoctor("Maciej", "Kowalczyk", 9876, testSpecs, 250)
    {
    }

    ~TestSuiteDoctorFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteDoctor, TestSuiteDoctorFixture)

BOOST_AUTO_TEST_CASE(ConstructorAndGettersTest)
{
    // Constructor check
    BOOST_TEST(testDoctor.getName() == "Maciej");
    BOOST_TEST(testDoctor.getLastName() == "Kowalczyk");
    BOOST_TEST(testDoctor.getUniqueParameter() == 9876);

    // Sprawdzenie zmiennych klasy Doctor
    BOOST_TEST(testDoctor.getDoctorCost() == 250);

    // Weryfikacja wektora specjalizacji
    BOOST_TEST_REQUIRE(testDoctor.getSpecialisation().size() == 2);
    BOOST_TEST(specialisationToString(testDoctor.getSpecialisation()[0]) == specialisationToString(Specialisation::PHYSIOTHERAPIST));
    BOOST_TEST(specialisationToString(testDoctor.getSpecialisation()[1]) == specialisationToString(Specialisation::ORTHOPEDIST));
}

BOOST_AUTO_TEST_CASE(SettersTest)
{
    testDoctor.setDoctorCost(400);
    BOOST_TEST(testDoctor.getDoctorCost() == 400);
}

BOOST_AUTO_TEST_CASE(CanConductTreatmentTest)
{
    BOOST_TEST(testDoctor.canConductTreatment(Specialisation::PHYSIOTHERAPIST) == true);
    BOOST_TEST(testDoctor.canConductTreatment(Specialisation::ORTHOPEDIST) == true);

    // Lekarz nie posiada tej specjalizacji wiec nie powinem moc jej wykonywac
    BOOST_TEST(testDoctor.canConductTreatment(Specialisation::NEUROLOGIST) == false);
}

BOOST_AUTO_TEST_CASE(GetInfoTest)
{
    std::string expectedInfo = "Osoba: Maciej Kowalczyk pracownik personelu o numerze pracownika: 9876, aktywyny zawodowo doktor o cenie prestizu: 250 specjalnosci: Fizjoterapeuta Ortopeda";
    BOOST_TEST(testDoctor.getInfo() == expectedInfo);
}

BOOST_AUTO_TEST_SUITE_END()