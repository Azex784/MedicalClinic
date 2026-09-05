#include <boost/test/unit_test.hpp>
#include "personnel/Doctor.h"
#include "enums/Specialisation.h"
#include "enums/Title.h"

using namespace MedicalClinic;


struct TestSuiteDoctorFixture
{
    std::vector<Specialisation> testSpecs;
    Doctor testDoctor;

    TestSuiteDoctorFixture()
        : testSpecs{Specialisation::ANESTHESIOLOGIST,Specialisation::CARDIOLOGIST},
          testDoctor("Maciej", "Kowalczyk", 9876, testSpecs, Title::PROF)
    {
    }

    ~TestSuiteDoctorFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteDoctor, TestSuiteDoctorFixture)

BOOST_AUTO_TEST_CASE(ConstructorAndGettersTest)
{
    // Constructor check.
    BOOST_TEST(testDoctor.getName() == "Maciej");
    BOOST_TEST(testDoctor.getLastName() == "Kowalczyk");
    BOOST_TEST(testDoctor.getUniqueParameter() == 9876);

    // Sprawdzenie zmiennych klasy Doctor.
    BOOST_CHECK(testDoctor.getDoctorRate() == 3);

    BOOST_TEST(toString(testDoctor.getTitle())== toString(Title::PROF));

    // Weryfikacja wektora specjalizacji.
    BOOST_TEST_REQUIRE(testDoctor.getSpecialisation().size() == 2);
    BOOST_TEST(toString(testDoctor.getSpecialisation()[0]) == toString(Specialisation::ANESTHESIOLOGIST));
    BOOST_TEST(toString(testDoctor.getSpecialisation()[1]) == toString(Specialisation::CARDIOLOGIST));
}

BOOST_AUTO_TEST_CASE(SettersTest)
{
    // Obowiązkowe upewniene się, że tytuł jest poprawny.
    BOOST_TEST_REQUIRE(toString(testDoctor.getTitle())== toString(Title::PROF));

    // Zmiana tytułu
    testDoctor.setTitle(Title::MD);

    BOOST_TEST(toString(testDoctor.getTitle())== toString(Title::MD));
    // Czy nastąpiła zmiana stawki po zmianie tytułu?
    BOOST_CHECK(testDoctor.getDoctorRate() == 0);
}

BOOST_AUTO_TEST_CASE(CanConductTreatmentTest)
{
    BOOST_TEST(testDoctor.canConductTreatment(Specialisation::ANESTHESIOLOGIST) == true);
    BOOST_TEST(testDoctor.canConductTreatment(Specialisation::CARDIOLOGIST) == true);

    // Lekarz nie posiada tej specjalizacji wiec nie powinem moc wykonywac zabiegow
    BOOST_TEST(testDoctor.canConductTreatment(Specialisation::NEUROLOGIST) == false);
}

BOOST_AUTO_TEST_CASE(GetInfoTest)
{
    std::string expectedInfo = testDoctor.Personnel::getInfo() + ", lekarz o stawce (jako procent zabiegu): 3%, specjalności: Anestezjolog, Kardiolog.";
    BOOST_TEST(testDoctor.getInfo() == expectedInfo);
}

BOOST_AUTO_TEST_SUITE_END()