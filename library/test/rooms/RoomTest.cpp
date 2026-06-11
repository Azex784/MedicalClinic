#include <boost/test/unit_test.hpp>
#include "rooms/Room.h"

using namespace RehabClinic;

//struct sluzacy do sprawdzenia dzialania metod klasy bazowej
struct TmpRoom : public Room
{
    TmpRoom(const unsigned int roomNumber) : Room(roomNumber) {}

    //Wypelnienie metody czysto wirtualnej
    bool canBeUsed(Equipment equipment) const override
    {
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
    //prawidłowe ustawienie paramtetrów
    BOOST_TEST(testRoom.getUniqueParameter() == 101);
    BOOST_TEST(testRoom.getIsActive() == true);
    BOOST_TEST(testRoom.getIsArchive() == false);
}

BOOST_AUTO_TEST_CASE(SettersTest)
{
    //sprawdzamy czy rzeczywiscie nastepuje zmiana
    BOOST_TEST_REQUIRE(testRoom.getIsActive() == true);
    testRoom.setIsActive(false);
    BOOST_TEST(testRoom.getIsActive() == false);

    BOOST_TEST_REQUIRE(testRoom.getIsArchive() == false);
    testRoom.setIsArchive(true);
    BOOST_TEST(testRoom.getIsArchive() == true);
}

BOOST_AUTO_TEST_CASE(GetInfoTest)
{
    //sprawdzamy prawidlowe dzialanie metody getInfo dla przypadkow aktywnosci pokoju i nieaktywnosci
    BOOST_TEST_REQUIRE(testRoom.getIsActive() == true);
    std::string expectedInfo = "Pokoj o numerze pokoju: 101, dostepnosc: aktywna";
    BOOST_TEST(testRoom.getInfo() == expectedInfo);

    testRoom.setIsActive(false);

    BOOST_TEST_REQUIRE(testRoom.getIsActive() == false);
    expectedInfo = "Pokoj o numerze pokoju: 101, dostepnosc: nieaktywna";
    BOOST_TEST(testRoom.getInfo() == expectedInfo);

}

BOOST_AUTO_TEST_SUITE_END()