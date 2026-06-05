#include <boost/test/unit_test.hpp>
#include <enums/Equipment.h>
#include <enums/Specialisation.h>
#include "services/Rehabillitation.h"

struct TestSuiteRehabillitationFixture
{
    std::vector<Equipment> tmp = {Equipment::PHYSICAL_THERAPY_DEVICE};
    Rehabillitation testRehabillitation;

    TestSuiteRehabillitationFixture()
        : testRehabillitation(200, 45, "Masaaż fizyczno-kregowy", 1, 1, Specialisation::ORTHOPEDIST, tmp,  2)
    {
    }

    ~TestSuiteRehabillitationFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteRehabillitation, TestSuiteRehabillitationFixture)

BOOST_AUTO_TEST_CASE(ConstructorAndGettersTest)
{
    //Poprawne dzialanie konstruktora i getterów
    BOOST_TEST(testRehabillitation.getServiceCost() == 200);
    BOOST_TEST(testRehabillitation.getServiceDuration() == 45);
    BOOST_TEST(testRehabillitation.getServiceName() == "Masaaż fizyczno-kregowy");
    BOOST_TEST(testRehabillitation.getUniqueParameter() == 1);
    BOOST_TEST(specialisationToString(testRehabillitation.getRequiredDoctorSpec()) == specialisationToString(Specialisation::ORTHOPEDIST));
    BOOST_TEST(testRehabillitation.getRequiredDoctorSize() == 1);
    BOOST_TEST(testRehabillitation.getRequiredNurseSize() == 2);
    BOOST_TEST(equipmentToString(testRehabillitation.getRequiredEqupiment()[0]) == equipmentToString(Equipment::PHYSICAL_THERAPY_DEVICE));
    BOOST_TEST(testRehabillitation.getRequiredEqupiment().size() == 1);

}

//Sprawdzamy dla  poprawne dzialanie metody getInfo()
BOOST_AUTO_TEST_CASE(GetInfoTest)
{
    std::string expectedBaseInfo = testRehabillitation.Service::getInfo();
    std::string expectedInfo = expectedBaseInfo + ", rehabilitacja, potrzebna ilosc pielegniarek: 2, potrzebny sprzet: " + equipmentToString(Equipment::PHYSICAL_THERAPY_DEVICE);

    BOOST_TEST(testRehabillitation.getInfo() == expectedInfo);
}


BOOST_AUTO_TEST_SUITE_END()
