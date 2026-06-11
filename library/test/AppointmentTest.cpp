#include <boost/test/unit_test.hpp>
#include <memory>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "typedefs.h"
#include "Appointment.h"
#include "enums/Specialisation.h"
#include "patient/Patient.h"
#include "patient/Address.h"
#include "personnel/Doctor.h"
#include "services/Consultation.h"
#include "rooms/ConsultationRoom.h"
#include "sstream"

using namespace RehabClinic;

struct TestSuiteAppointmentFixture
{
	// Adres i Pacjent
	AddressPtr testAddress = std::make_shared<Address>("Warszawa", "Polna", "10");
	PatientPtr testPatient = std::make_shared<Patient>("Jan", "Kowalski", "90010112345", testAddress);

	// Specjalizacje, Lekarz i wektor personelu
	std::vector<Specialisation> docSpecs = {Specialisation::ORTHOPEDIST};
	PersonnelPtr testDoctor = std::make_shared<Doctor>("Anna", "Nowak", 1001, docSpecs, 50);
	std::vector<PersonnelPtr> testPersonnel = {testDoctor};

	// Usługa
	ServicePtr testService = std::make_shared<Consultation>(150, 30, "Konsultacja ortopedyczna", 2001, 1,
	                                                        Specialisation::ORTHOPEDIST, "Ból pleców", false);

	RoomPtr testRoom = std::make_shared<ConsultationRoom>(101);

	boost::posix_time::ptime nowTime = boost::posix_time::time_from_string("2025-06-15 10:30:00");

	boost::posix_time::ptime startTime{nowTime};

	Appointment testAppointment;

	TestSuiteAppointmentFixture()
		: testAppointment(startTime, 999, testPersonnel, testPatient, testService, testRoom)
	{
	}

	~TestSuiteAppointmentFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteAppointment, TestSuiteAppointmentFixture)

	BOOST_AUTO_TEST_CASE(ConstructorAndGettersTest)
	{
		//Sprawdzenie prawidlowe dzialanie getterów i konstruktora
		BOOST_TEST(testAppointment.getUniqueParameter() == 999);
		BOOST_TEST(testAppointment.getAppointmentBeginDate() == startTime);
		BOOST_TEST(testAppointment.getPatient() == testPatient);
		BOOST_TEST(testAppointment.getService() == testService);
		BOOST_TEST(testAppointment.getRoom() == testRoom);
		BOOST_TEST(testAppointment.getPersonnel().size() == 1);
		BOOST_TEST(testAppointment.getPersonnel().size() == 1);
		BOOST_TEST(testAppointment.getAppointmentCost() == 0);

		BOOST_TEST(
			testAppointment.getAppointmentEndDate() == boost::posix_time::time_from_string("2025-06-15 11:00:00"));
	}

	BOOST_AUTO_TEST_CASE(SettersTest)
	{
		//Czy koszt nie byl zmienany?
		BOOST_TEST_REQUIRE(testAppointment.getAppointmentCost() == 0);

		BOOST_TEST_REQUIRE(testAppointment.setAppointmentCost() == 200);

		BOOST_TEST_REQUIRE(testAppointment.getAppointmentCost() == 200);

		//Czy niemozliwa bedzie zmiana?
		BOOST_TEST(testAppointment.setAppointmentCost() == 0);

		//Za jednym razem sprawdzamy poprawność settera zmieniającego datę rozpoczęcia i zakończenia, bo
		// metoda rozpoczenia wywoulje zmiane zakonczenia

		BOOST_TEST_REQUIRE(
			testAppointment.getAppointmentBeginDate() == boost::posix_time::time_from_string("2025-06-15 10:30:00"));

		BOOST_TEST_REQUIRE(
			testAppointment.getAppointmentEndDate() == boost::posix_time::time_from_string("2025-06-15 11:00:00"));

		testAppointment.setAppointmentBeginDate(boost::posix_time::time_from_string("2025-06-15 12:00:00"));


		BOOST_TEST(
			testAppointment.getAppointmentBeginDate() == boost::posix_time::time_from_string("2025-06-15 12:00:00"));
		BOOST_TEST(
			testAppointment.getAppointmentEndDate() == boost::posix_time::time_from_string("2025-06-15 12:30:00"));
	}

	BOOST_AUTO_TEST_CASE(GetInfoTest)
	{
		std::stringstream ss;

		ss << "Wizyta: ID: " << testAppointment.getUniqueParameter() << std::endl;
		ss << "Rozpoczęcie: " << testAppointment.getAppointmentBeginDate() << std::endl;
		ss << "Zakończenie: " << testAppointment.getAppointmentEndDate() << std::endl;
		ss << "Pacjent:\n";
		ss << testAppointment.getPatient()->getInfo() << std::endl;
		ss << "Usluga:\n";
		ss << testAppointment.getService()->getInfo() << std::endl;
		ss << "Sala:\n";
		ss << testAppointment.getRoom()->getInfo() << std::endl;
		ss << "Personel przypisany do wizyty:\n";
		ss << " * " << testAppointment.getPersonnel()[0]->getInfo() << std::endl;

		BOOST_TEST(testAppointment.getInfo() == ss.str());
	}


BOOST_AUTO_TEST_SUITE_END()
