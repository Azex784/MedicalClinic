#include <boost/test/unit_test.hpp>
#include "Statusable.h"
#include "enums/Equipment.h"
#include "rooms/Room.h"

using namespace MedicalClinic;

// Struct slużący do sprawdzenia dzialania metod klasy bazowej
struct TmpRoom : public Room
{
    TmpRoom(const unsigned int roomNumber) : Room(roomNumber) {}

    // Wypełnienie metody czysto wirtualnej
    bool canBeUsed(Equipment equipment) const override
    {
        if (equipment == Equipment::CT_SCANNER) {

        };
        return true;
    }
};
struct TestSuiteRoomFixture
{
    TmpRoom testRoom;

    TestSuiteRoomFixture() : testRoom(101)
    {
    }

    ~TestSuiteRoomFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteRoom, TestSuiteRoomFixture)

BOOST_AUTO_TEST_CASE(ConstructorAndGettersTest)
{
    // Prawidłowe ustawienie paramtetrów
    BOOST_TEST(testRoom.getUniqueParameter() == 101);
}

BOOST_AUTO_TEST_CASE(GetInfoTest)
{
    // Sprawdzamy prawidłowe działanie metody getInfo dla przypadków aktywności pokoju i nieaktywnosci
    BOOST_TEST_REQUIRE(testRoom.isAvailable() == true);
    std::string expectedInfo = "Pokój o numerze: 101, status: Dostępny";
    BOOST_TEST(testRoom.getInfo() == expectedInfo);

    testRoom.setEntityStatus(Status::ARCHIVED);

    BOOST_TEST_REQUIRE(testRoom.isAvailable() == false);
    expectedInfo = "Pokój o numerze: 101, status: Archiwalny";
    BOOST_TEST(testRoom.getInfo() == expectedInfo);
}

BOOST_AUTO_TEST_SUITE_END()