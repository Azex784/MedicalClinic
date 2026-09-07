#include <boost/test/unit_test.hpp>
#include "rooms/ConsultationRoom.h"
#include "enums/Equipment.h"

using namespace MedicalClinic;


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
    // Sprawdzenie poprawne dzialanie konstruktora
    BOOST_TEST(testRoom.getUniqueParameter() == 303);
}

BOOST_AUTO_TEST_CASE(CanBeUsedTest)
{
    // Pokój konsultacyjny nie ma zadnego sprzetu
    BOOST_TEST(testRoom.canBeUsed(Equipment::NONE) == true);

    // Czy zostaną odrzucone inne opcje?
    BOOST_TEST(testRoom.canBeUsed(Equipment::CT_SCANNER) == false);
    BOOST_TEST(testRoom.canBeUsed(Equipment::INFUSION_PUMP) == false);
    BOOST_TEST(testRoom.canBeUsed(Equipment::X_RAY_MACHINE) == false);
}

BOOST_AUTO_TEST_CASE(GetInfoTest){
    // Sprawdzamy czy metoda getInfo jest dobrze implementowana
    std::string expectedInfo = testRoom.Room::getInfo() + ", pokój do przeprowadzania konsultacji.";
    BOOST_TEST(testRoom.getInfo() == expectedInfo);
}

BOOST_AUTO_TEST_SUITE_END()