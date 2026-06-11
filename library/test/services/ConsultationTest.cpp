#include <boost/test/unit_test.hpp>
#include <enums/Specialisation.h>
#include "services/Consultation.h"

using namespace RehabClinic;

struct TestSuiteConsultationFixture
{
    Consultation testConsultation;

    TestSuiteConsultationFixture()
        : testConsultation(200, 45, "Konsultacja ortopedyczna", 3001, 1,
                           Specialisation::ORTHOPEDIST, "Ból kolana", true)
    {
    }

    ~TestSuiteConsultationFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteConsultation, TestSuiteConsultationFixture)

BOOST_AUTO_TEST_CASE(ConstructorAndGettersTest)
{
    BOOST_TEST(testConsultation.getServiceCost() == 200);
    BOOST_TEST(testConsultation.getServiceDuration() == 45);
    BOOST_TEST(testConsultation.getServiceName() == "Konsultacja ortopedyczna");
    BOOST_TEST(testConsultation.getUniqueParameter() == 3001);
    BOOST_TEST(specialisationToString(testConsultation.getRequiredDoctorSpec()) == specialisationToString(Specialisation::ORTHOPEDIST));
    BOOST_TEST(testConsultation.getRequiredDoctorSize() == 1);

    BOOST_TEST(testConsultation.getTopic() == "Ból kolana");
    BOOST_TEST(testConsultation.getIsOnline() == true);
}

//Sprawdzamy dla  online
BOOST_AUTO_TEST_CASE(GetInfoOnlineTest)
{
    std::string expectedBaseInfo = testConsultation.Service::getInfo();
    std::string expectedInfo = expectedBaseInfo + " konsultacje, w trybie online o temacie: Ból kolana";

    //Upewniamy sie ze spotkanie jest w trybie online
    BOOST_TEST_REQUIRE(testConsultation.getIsOnline());
    BOOST_TEST(testConsultation.getInfo() == expectedInfo);
}

//Sprawdzamy dla stacjonarnej wizyty
BOOST_AUTO_TEST_CASE(GetInfoOfflineTest)
{
    Consultation offlineConsultation(200, 45, "Konsultacja ortopedyczna", 3001, 1,
                           Specialisation::ORTHOPEDIST, "Ból kolana", false);

    std::string expectedBaseInfo = offlineConsultation.Service::getInfo();
    std::string expectedInfo = expectedBaseInfo + " konsultacje, w trybie stacjonarnym o temacie: Ból kolana";

    //Upewniamy sie ze spotkanie jest w trybie stacjonarnym
    BOOST_TEST_REQUIRE(!offlineConsultation.getIsOnline());
    BOOST_TEST(offlineConsultation.getInfo() == expectedInfo);
}

BOOST_AUTO_TEST_SUITE_END()
