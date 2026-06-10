#include <boost/test/unit_test.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "managers/AppointmentManager.h"
#include "Appointment.h"
#include "patient/Patient.h"
#include "patient/Address.h"
#include "personnel/Doctor.h"
#include "personnel/Nurse.h"
#include "rooms/ConsultationRoom.h"
#include "rooms/RehabillitationRoom.h"
#include "services/Consultation.h"
#include "services/Rehabillitation.h"


#include "enums/Equipment.h"
#include "enums/Specialisation.h"
#include "managers/LogicManager.h"

using namespace boost::posix_time;

struct TestSuitLogicManagerFixture
{
	//Pacjent
	AddressPtr testAddress;
	PatientPtr testPatient;
	PatientPtr testPatient1;

	//Sale
	std::vector<Equipment> wyposazenie;
	RoomPtr testRoom1;
	RoomPtr testRoom2;

	//Personel
	std::vector<Specialisation> specjalizacje;
	PersonnelPtr testPersonnel1;
	PersonnelPtr testPersonnel2;

	//Serwis
	std::vector<Equipment> eq1;
	std::vector<Equipment> eq2;
	ServicePtr cons1;
	ServicePtr rehab1;

	//Spotkanie

	AppointmentPtr testAppointment;
	AppointmentPtr testAppointment1;
	AppointmentPtr testAppointment2;

	std::vector<PersonnelPtr> personnel;
	std::vector<PersonnelPtr> personnel1;

	ptime startTime;
	ptime startTime2;
	LogicManagerPtr logicManager;


	TestSuitLogicManagerFixture()
		: testAddress(std::make_shared<Address>("Albuquerqe", "Juan Poet", "10/15")),
		  testPatient(std::make_shared<Patient>("Walter", "White", "40010112345", testAddress)),
		  testPatient1(std::make_shared<Patient>("Jesse", "Pinkman", "20010112345", testAddress)),
		  wyposazenie({Equipment::PHYSICAL_THERAPY_DEVICE, Equipment::ROBOTIC_SYSTEM}),
		  testRoom1(std::make_shared<ConsultationRoom>(101)),
		  testRoom2(std::make_shared<RehabillitationRoom>(102, wyposazenie, 3)),
		  specjalizacje({Specialisation::MASSAGE_THERAPIST, Specialisation::NEUROLOGIST}),
		  testPersonnel1(std::make_shared<Nurse>("Jesse", "Pinkman", 123)),
		  testPersonnel2(std::make_shared<Doctor>("Walter", "White", 124, specjalizacje, 200)),
		  eq1({Equipment::PHYSICAL_THERAPY_DEVICE}
		  )
		  ,
		  eq2({Equipment::PHYSICAL_THERAPY_DEVICE}
		  )
		  ,
		  cons1(std::make_shared<Consultation>(150, 30, "Konsultacja odnosnie masażu", 101, 1,
		                                       Specialisation::MASSAGE_THERAPIST, "Omowienie wynikow", false)),
		  rehab1(std::make_shared<Rehabillitation>(100, 60, "Masaz kregoslupa", 201, 0,
		                                           Specialisation::MASSAGE_THERAPIST,
		                                           eq1, 1))
	{
		startTime = time_from_string("2025-06-15 10:30:00");
		startTime2 = time_from_string("2025-07-15 10:30:00");
		personnel = {testPersonnel1};
		personnel1 = {testPersonnel2};

		testAppointment = std::make_shared<Appointment>(startTime, 999, personnel, testPatient, rehab1, testRoom2);
		testAppointment1 = std::make_shared<Appointment>(startTime2, 978, personnel1, testPatient, cons1, testRoom1);


		logicManager = std::make_shared<LogicManager>("../../library/test/data/PersonnelLogicManager.txt",
		                                              "../../library/test/data/PatientLogicManager.txt",
		                                              "../../library/test/data/ServiceLogicManager.txt",
		                                              "../../library/test/data/RoomLogicManager.txt",
		                                              "../../library/test/data/AppointmentLogicManager.txt",
		                                              "../../library/test/data/AppointmentLogicManagerArchive.txt");


		logicManager->getPatientManager()->getRepository()->add(testPatient);
		logicManager->getPatientManager()->getRepository()->add(testPatient1);

		logicManager->getPersonnelManager()->getRepository()->add(testPersonnel1);
		logicManager->getPersonnelManager()->getRepository()->add(testPersonnel2);

		logicManager->getServiceManager()->getRepository()->add(cons1);
		logicManager->getServiceManager()->getRepository()->add(rehab1);

		logicManager->getRoomManager()->getRepository()->add(testRoom1);
		logicManager->getRoomManager()->getRepository()->add(testRoom2);

		logicManager->getAppointmentManager()->arrangeAppointment(testPatient,
		                                                          rehab1,
		                                                          personnel,
		                                                          time_from_string("2024-06-15 10:30:00"),
		                                                          testRoom2,
		                                                          1
		);
	}

	~TestSuitLogicManagerFixture()
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(TestSuitLogicManager, TestSuitLogicManagerFixture)

	BOOST_AUTO_TEST_CASE(GettersTest)
	{
		//Sprawdzenie getterów
		BOOST_TEST(logicManager->getPatientManager()->get("40010112345") != nullptr);
		BOOST_TEST(logicManager->getPersonnelManager()->get(123) != nullptr);
		BOOST_TEST(logicManager->getRoomManager()->get(101) != nullptr);
		BOOST_TEST(logicManager->getServiceManager()->get(101) != nullptr);
		BOOST_TEST(logicManager->getAppointmentManager()->get(1) != nullptr);
	}

	BOOST_AUTO_TEST_CASE(RemovePersonnelTest)
	{
		BOOST_TEST_REQUIRE(logicManager->getAppointmentManager()->getRepository()->getVectorOfData().size() == 1);
		logicManager->getPersonnelManager()->get(123)->setIsArchive(false);
		logicManager->getPersonnelManager()->get(123)->setIsActive(true);

		BOOST_TEST_REQUIRE(logicManager->getPersonnelManager()->get(123)->getIsActive() == true);
		BOOST_TEST_REQUIRE(logicManager->getPersonnelManager()->get(123)->getIsArchive() == false);

		// Wywołanie akcji
		logicManager->removePersonnel(123);

		// Personel staje się archiwalny i nieaktywny
		BOOST_TEST(logicManager->getPersonnelManager()->get(123)->getIsArchive() == true);
		BOOST_TEST(logicManager->getPersonnelManager()->get(123)->getIsActive() == false);

		// Wszystkie wizyty anulowane
		BOOST_TEST(logicManager->getAppointmentManager()->getRepository()->getVectorOfData().size() == 0);
	}

	BOOST_AUTO_TEST_CASE(UnregisterPatientTest)
	{
		BOOST_TEST_REQUIRE(logicManager->getPatientManager()->getRepository()->getVectorOfData().size() == 2);

		logicManager->getPatientManager()->get("40010112345")->setIsArchive(false);
		logicManager->getPatientManager()->get("20010112345")->setIsArchive(false);

		BOOST_TEST_REQUIRE(logicManager->getPatientManager()->get("40010112345")->getIsArchive() == false);
		BOOST_TEST_REQUIRE(logicManager->getPatientManager()->get("20010112345")->getIsArchive() == false);

		//Nieprawidłowe
		BOOST_TEST(!logicManager->unregisterPatient("40010112345"));
		BOOST_TEST(logicManager->getPatientManager()->get("40010112345")->getIsArchive() == false);

		//Prawidłowe
		BOOST_TEST(logicManager->unregisterPatient("20010112345"));
		BOOST_TEST(logicManager->getPatientManager()->get("20010112345")->getIsArchive() == true);
	}

	BOOST_AUTO_TEST_CASE(RemoveRoomTest)
	{
		BOOST_TEST_REQUIRE(logicManager->getRoomManager()->getRepository()->getVectorOfData().size() == 2);

		logicManager->getRoomManager()->get(101)->setIsArchive(false);
		logicManager->getRoomManager()->get(101)->setIsActive(true);

		logicManager->getRoomManager()->get(102)->setIsArchive(false);
		logicManager->getRoomManager()->get(102)->setIsActive(true);

		BOOST_TEST_REQUIRE(logicManager->getRoomManager()->get(101)->getIsActive() == true);
		BOOST_TEST_REQUIRE(logicManager->getRoomManager()->get(101)->getIsArchive() == false);

		BOOST_TEST_REQUIRE(logicManager->getRoomManager()->get(102)->getIsActive() == true);
		BOOST_TEST_REQUIRE(logicManager->getRoomManager()->get(102)->getIsArchive() == false);


		// Wywołanie akcji dla pokoju bez spotkan
		logicManager->removeRoom(101);

		// Sala staje się archiwalny i nieaktywny
		BOOST_TEST(logicManager->getRoomManager()->get(101)->getIsArchive() == true);
		BOOST_TEST(logicManager->getRoomManager()->get(101)->getIsActive() == false);

		// Wywołanie akcji dla pokoju z spotkaniami
		logicManager->removeRoom(102);

		// Personel staje się archiwalny i nieaktywny
		BOOST_TEST(logicManager->getRoomManager()->get(102)->getIsArchive() == true);
		BOOST_TEST(logicManager->getRoomManager()->get(102)->getIsActive() == false);
	}

	BOOST_AUTO_TEST_CASE(RemoveServiceTest)
	{
		BOOST_TEST_REQUIRE(logicManager->getServiceManager()->getRepository()->getVectorOfData().size() == 2);

		logicManager->getServiceManager()->get(101)->setIsArchive(false);
		logicManager->getServiceManager()->get(101)->setIsAvailable(true);

		logicManager->getServiceManager()->get(201)->setIsArchive(false);
		logicManager->getServiceManager()->get(201)->setIsAvailable(true);

		BOOST_TEST_REQUIRE(logicManager->getServiceManager()->get(101)->getIsArchive() == false);
		BOOST_TEST_REQUIRE(logicManager->getServiceManager()->get(101)->getIsAvailable() == true);

		BOOST_TEST_REQUIRE(logicManager->getServiceManager()->get(201)->getIsArchive() == false);
		BOOST_TEST_REQUIRE(logicManager->getServiceManager()->get(201)->getIsAvailable() == true);

		//Nieprawidłowe
		BOOST_TEST(!logicManager->removeService(201));
		BOOST_TEST(logicManager->getServiceManager()->get(201)->getIsArchive() == false);
		BOOST_TEST(logicManager->getServiceManager()->get(201)->getIsAvailable() == true);

		//Prawidłowe
		BOOST_TEST(logicManager->removeService(101));
		BOOST_TEST(logicManager->getServiceManager()->get(101)->getIsArchive() == true);
		BOOST_TEST(logicManager->getServiceManager()->get(101)->getIsAvailable() == false);
	}

BOOST_AUTO_TEST_SUITE_END()
