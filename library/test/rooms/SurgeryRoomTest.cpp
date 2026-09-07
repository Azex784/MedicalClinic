#include <boost/test/unit_test.hpp>
#include <vector>
#include "rooms/SurgeryRoom.h"
#include "enums/Equipment.h"

using namespace MedicalClinic;


struct TestSuiteSurgeryRoomFixture
{
    std::vector<Equipment> testEquipment;
    SurgeryRoom testRoom;

    TestSuiteSurgeryRoomFixture()
        : testEquipment{Equipment::INFUSION_PUMP, Equipment::X_RAY_MACHINE},
          testRoom(202, testEquipment, 3)
    {
    }

    ~TestSuiteSurgeryRoomFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteSurgeryRoom, TestSuiteSurgeryRoomFixture)

BOOST_AUTO_TEST_CASE(ConstructorAndGettersTest)
{
    BOOST_TEST(testRoom.getUniqueParameter() == 202);

    BOOST_TEST(testRoom.getMaxCapacity() == 3);
    BOOST_TEST_REQUIRE(testRoom.getAccessibleEqupiment().size() == 2);

    BOOST_TEST(toString(testRoom.getAccessibleEqupiment()[0]) == toString(Equipment::INFUSION_PUMP));
    BOOST_TEST(toString(testRoom.getAccessibleEqupiment()[1]) == toString(Equipment::X_RAY_MACHINE));
}

BOOST_AUTO_TEST_CASE(CanBeUsedTest)
{
    BOOST_TEST(testRoom.canBeUsed(Equipment::INFUSION_PUMP) == true);
    BOOST_TEST(testRoom.canBeUsed(Equipment::X_RAY_MACHINE) == true);

    // Czy sprzęt, którego nie ma sprawi ze metoda canBeUsed zwróci fałsz?
    BOOST_TEST(testRoom.canBeUsed(Equipment::ECG_MACHINE) == false);
    BOOST_TEST(testRoom.canBeUsed(Equipment::NONE) == false);
}

BOOST_AUTO_TEST_CASE(GetInfoTest)
{
    // Sprawdzamy prawidłowe funkcjonowanie getInfo
    std::string expectedBaseRoomInfo = testRoom.Room::getInfo();
    std::string expectedInfo = expectedBaseRoomInfo +
        ", pokój operacyjny, maksymalna ładowność: 3 osób z personulu, sprzęt dostępny w pokoju: Pompa infuzyjna, Aparat RTG.";

    BOOST_TEST(testRoom.getInfo() == expectedInfo);
}

BOOST_AUTO_TEST_SUITE_END()