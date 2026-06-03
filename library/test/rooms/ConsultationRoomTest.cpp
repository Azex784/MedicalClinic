#include <boost/test/unit_test.hpp>
#include <vector>
#include "rooms/ConsultationRoom.h"
#include "enums/Equipment.h"

struct TestSuiteConsultationRoomFixture
{
    ConsultationRoom testRoom;

    TestSuiteConsultationRoomFixture() : testRoom(303)
    {
    }

    ~TestSuiteConsultationRoomFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteConsultationRoom, TestSuiteConsultationRoomFixture)

BOOST_AUTO_TEST_CASE(ConstructorTest)
{
    //sprawdzenie poprawne dzialanie konstruktora
    BOOST_TEST(testRoom.getRoomNumber() == 303);
    BOOST_TEST(testRoom.getIsActive() == true);
    BOOST_TEST(testRoom.getIsArchive() == false);
}

BOOST_AUTO_TEST_CASE(CanBeUsedTest)
{
    // Pokoj konsultacyjny nie ma zadnego sprzetu
    BOOST_TEST(testRoom.canBeUsed(Equipment::NONE) == true);

    //czy zostana odrzucone inne opcje
    BOOST_TEST(testRoom.canBeUsed(Equipment::PHYSICAL_THERAPY_DEVICE) == false);
    BOOST_TEST(testRoom.canBeUsed(Equipment::KINESITHERAPY_SPACE) == false);
    BOOST_TEST(testRoom.canBeUsed(Equipment::ROBOTIC_SYSTEM) == false);
}

BOOST_AUTO_TEST_CASE(GetInfoTest){
    //Sprawdzamy czy metoda getInfo jest dobrze implementowana
    std::string expectedBaseRoomInfo = testRoom.Room::getInfo();

    std::string expectedInfo = expectedBaseRoomInfo + " pokoj do przeprowadzania konsultacji";

    BOOST_TEST(testRoom.getInfo() == expectedInfo);
}

BOOST_AUTO_TEST_SUITE_END()