#include <boost/test/unit_test.hpp>
#include <vector>
#include "rooms/RehabillitationRoom.h"
#include "enums/Equipment.h"

using namespace MedicalClinic;


struct TestSuiteRehabillitationRoomFixture
{
    std::vector<Equipment> testEquipment;
    RehabillitationRoom testRoom;

    TestSuiteRehabillitationRoomFixture() 
        : testEquipment{Equipment::PHYSICAL_THERAPY_DEVICE, Equipment::KINESITHERAPY_SPACE},
          testRoom(202, testEquipment, 3)
    {
    }

    ~TestSuiteRehabillitationRoomFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteRehabillitationRoom, TestSuiteRehabillitationRoomFixture)

BOOST_AUTO_TEST_CASE(ConstructorAndGettersTest)
{
    BOOST_TEST(testRoom.getUniqueParameter() == 202);
    BOOST_TEST(testRoom.getIsActive() == true);
    BOOST_TEST(testRoom.getIsArchive() == false);

    BOOST_TEST(testRoom.getMaxCapacity() == 3);
    BOOST_TEST_REQUIRE(testRoom.getAccessibleEqupiment().size() == 2);

    BOOST_TEST(equipmentToString(testRoom.getAccessibleEqupiment()[0]) == equipmentToString(Equipment::PHYSICAL_THERAPY_DEVICE));
    BOOST_TEST(equipmentToString(testRoom.getAccessibleEqupiment()[1]) == equipmentToString(Equipment::KINESITHERAPY_SPACE));
}

BOOST_AUTO_TEST_CASE(CanBeUsedTest)
{
    BOOST_TEST(testRoom.canBeUsed(Equipment::PHYSICAL_THERAPY_DEVICE) == true);
    BOOST_TEST(testRoom.canBeUsed(Equipment::KINESITHERAPY_SPACE) == true);

    //czy sprzet ktorego nie ma sprawi ze metoda canBeUsed zwroci falsz
    BOOST_TEST(testRoom.canBeUsed(Equipment::ROBOTIC_SYSTEM) == false);
    BOOST_TEST(testRoom.canBeUsed(Equipment::NONE) == false);
}

BOOST_AUTO_TEST_CASE(GetInfoTest)
{
    //Sprawdzamy prawidlowe funkcjonowanie getInfo
    std::string expectedBaseRoomInfo = testRoom.Room::getInfo();
    
    std::string expectedInfo = expectedBaseRoomInfo +
        " pokoj rehabilitacyjny co moze maskymalnie pomiescic 3 osob z personulu, sprzęt dostępny w pokoju: Urządzenie do fizykoterapii, Przestrzeń do kinezyterapii";

    BOOST_TEST(testRoom.getInfo() == expectedInfo);
}

BOOST_AUTO_TEST_SUITE_END()