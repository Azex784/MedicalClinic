#include <boost/test/unit_test.hpp>
#include <enums/Specialisation.h>
#include "services/Service.h"

//Tymczasowa struktura potrzebna do testow
struct TmpService : public Service
{
	TmpService(const unsigned service_cost, const unsigned service_duration, const std::string& service_name,
	           const unsigned service_id, const unsigned required_doctor_size,
	           const Specialisation required_doctor_spec)
		: Service(service_cost, service_duration, service_name, service_id, required_doctor_size, required_doctor_spec)
	{
	}

	~TmpService() override{};
};


struct TestSuiteServiceFixture
{
	TmpService testService;

	TestSuiteServiceFixture() : testService(213, 60, "Masaz stop",
	                                        1, 1, Specialisation::MASSAGE_THERAPIST)
	{
	};
	~TestSuiteServiceFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteService, TestSuiteServiceFixture)

	BOOST_AUTO_TEST_CASE(ConstructorAndGettersTest)
	{
		//prawidłowe ustawienie paramtetrów i sprawdzenie getterów
		BOOST_TEST(testService.getServiceCost() == 213);
		BOOST_TEST(testService.getServiceDuration() == 60);
		BOOST_TEST(testService.getServiceName() == "Masaz stop");
		BOOST_TEST(testService.getServiceId() == 1);
		BOOST_TEST(specialisationToString(testService.getRequiredDoctorSpec()) == specialisationToString(Specialisation::MASSAGE_THERAPIST));
		BOOST_TEST(testService.getRequiredDoctorSize() == 1);
	}

	BOOST_AUTO_TEST_CASE(SettersTest)
	{
		//sprawdzamy czy rzeczywiscie nastepuje zmiana
		BOOST_TEST_REQUIRE(testService.getServiceCost() == 213);
		testService.setServiceCost(2183);
		BOOST_TEST(testService.getServiceCost() == 2183);

		BOOST_TEST_REQUIRE(testService.getIsArchive() == false);
		testService.setIsArchive(true);
		BOOST_TEST(testService.getIsArchive() == true);

		BOOST_TEST_REQUIRE(testService.getIsAvailable() == false);
		testService.setIsAvailable(1);
		BOOST_TEST(testService.getIsAvailable() == true);
	}

	BOOST_AUTO_TEST_CASE(GetInfoTest)
	{
	//Sprawdzamy prawidlowe dzialanie metody getInfo()
		std::string expectedInfo =
			"Nazwa usługi: Masaz stop, koszt usług: 213, czas trwania 60, identyfikator: 1, liczba lekarzy: 1, specjalizacja lekarza/y: Masażysta";

		BOOST_TEST(testService.getInfo() == expectedInfo);
	}

BOOST_AUTO_TEST_SUITE_END()
