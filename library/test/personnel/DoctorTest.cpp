#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <algorithm>

#include "PersonnelData.h"
#include "PersonData.h"
#include "DoctorData.h"

#include "personnel/Personnel.h"
#include "personnel/Doctor.h"
#include "enums/Specialisation.h"
#include "enums/Title.h"

using namespace MedicalClinic;

namespace dataBoost = boost::unit_test::data;


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

BOOST_DATA_TEST_CASE(ConstructorAndGettersTest, dataBoost::make(data::names) ^ dataBoost::make(data::surnames) ^ dataBoost::make(data::personnelNumbers) ^
    dataBoost::make(data::titles) ^ dataBoost::make(data::specialisations),
    name, surname, personnelNumber, title, specialsations )
{
    Doctor testDoctor = Doctor(name,surname,personnelNumber,specialsations, title);

    // Sprawdzenie metod z klasy bazowej (Person)
    BOOST_TEST(testDoctor.getName() == name);
    BOOST_TEST(testDoctor.getLastName() == surname);

    // Sprawdzenie metod z klasy pochodnej (Patient)
    BOOST_TEST(testDoctor.getUniqueParameter() == personnelNumber);

    BOOST_TEST(toString(testDoctor.getTitle()) == toString(title));

    BOOST_TEST_REQUIRE(testDoctor.getSpecialisation().size() == specialsations.size());

    for (int i = 0; i < (int)specialsations.size(); i++)
    {
        BOOST_TEST(toString(testDoctor.getSpecialisation()[i]) == toString(specialsations[i]));
    };

    unsigned int rate = static_cast<int>(title);

    BOOST_TEST(testDoctor.getDoctorRate() == rate);
}

BOOST_AUTO_TEST_CASE(SettersTest)
{
    // Obowiązkowe upewniene się, że tytuł jest poprawny.
    BOOST_TEST_REQUIRE(toString(testDoctor.getTitle()) == toString(Title::PROF));
    // Zakładam, że doctorRate rośnie o 1 dla każdego stopnia.
    for (int i = 0; i < static_cast<int>(Title::LAST); i++) {
        Title current = static_cast<Title>(i);
        testDoctor.setTitle(current);

        BOOST_TEST(toString(testDoctor.getTitle())== toString(current));
        // Czy nastąpiła zamiana rate?
        BOOST_TEST(testDoctor.getDoctorRate() == i);
    }
}

BOOST_DATA_TEST_CASE(CanConductTreatmentTest, dataBoost::make(data::names) ^ dataBoost::make(data::surnames) ^ dataBoost::make(data::personnelNumbers) ^
    dataBoost::make(data::titles) ^ dataBoost::make(data::specialisations),
    name, surname, personnelNumber, title, specialsations )
{
    Doctor testDoctor = Doctor(name,surname,personnelNumber,specialsations, title);

    for (int i = 0; i < static_cast<int>(Specialisation::LAST); i++) {
        Specialisation current = static_cast<Specialisation>(i);

        if (std::find(specialsations.begin(), specialsations.end(), current) == specialsations.end())
        {
            BOOST_TEST(testDoctor.canConductTreatment(current) == false);
        }
        else
        {
            BOOST_TEST(testDoctor.canConductTreatment(current) == true);
        }
    }
}

BOOST_DATA_TEST_CASE(GetInfoTest, dataBoost::make(data::names) ^ dataBoost::make(data::surnames) ^ dataBoost::make(data::personnelNumbers) ^
    dataBoost::make(data::titles) ^ dataBoost::make(data::specialisations),
    name, surname, personnelNumber, title, specialsations )
{
    Doctor testDoctor = Doctor(name,surname,personnelNumber,specialsations, title);

    std::string expectedInfo = testDoctor.Personnel::getInfo() + ", lekarz o stawce (jako procent zabiegu): " + std::to_string(testDoctor.getDoctorRate()) + "%, specjalności: ";

    std::ostringstream oss;

    for (int i = 0; i < (int)specialsations.size(); i++)
    {
        if (i != (int)specialsations.size() - 1)
        {
            oss << toString(specialsations[i]) << ", ";
        }
        else
        {
            oss << toString(specialsations[i]) << ".";
        }
    }

    BOOST_TEST(testDoctor.getInfo() == expectedInfo + oss.str());
}

BOOST_AUTO_TEST_SUITE_END()