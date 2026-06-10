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

#include "repositories/PatientRepository.h"
#include "repositories/PersonnelRepository.h"
#include "repositories/RoomRepository.h"
#include "repositories/ServiceRepository.h"
#include "repositories/AppointmentRepository.h"

#include "enums/Equipment.h"
#include "enums/Specialisation.h"
#include "../../include/Exceptions.h"

using namespace boost::posix_time;

struct TestSuitAppointmentManagerFixture
{
	//Pacjent
	AddressPtr testAddress;
	PatientPtr testPatient;
	PatientPtr testPatient1;
	PatientRepositoryPtr testPatientRepository;

	//Sale
	std::vector<Equipment> wyposazenie;
	RoomPtr testRoom1;
	RoomPtr testRoom2;
	RoomRepositoryPtr testRoomRepository;

	//Personel
	std::vector<Specialisation> specjalizacje;
	PersonnelPtr testPersonnel1;
	PersonnelPtr testPersonnel2;
	PersonnelRepositoryPtr testPersonnelRepository;

	//Serwis
	std::vector<Equipment> eq1;
	std::vector<Equipment> eq2;
	ServiceRepositoryPtr serviceRepo;

	ServicePtr cons1;
	ServicePtr rehab1;

	//Spotkanie

	AppointmentPtr testAppointment;
	AppointmentPtr testAppointment1;
	AppointmentPtr testAppointment2;
	AppointmentRepositoryPtr testAppointmentRepository;

	std::vector<PersonnelPtr> personnel;
	std::vector<PersonnelPtr> personnel1;

	ptime startTime;
	ptime startTime2;

	AppointmentManagerPtr appointmentManager;

	TestSuitAppointmentManagerFixture()
		: testAddress(std::make_shared<Address>("Albuquerqe", "Juan Poet", "10/15")),
		  testPatient(std::make_shared<Patient>("Walter", "White", "40010112345", testAddress)),
		  testPatient1(std::make_shared<Patient>("Jesse", "Pinkman", "20010112345", testAddress)),
		  testPatientRepository(
			  std::make_shared<PatientRepository>("../../library/test/data/AppointmentPatientManager.txt")),
		  wyposazenie({Equipment::PHYSICAL_THERAPY_DEVICE, Equipment::ROBOTIC_SYSTEM}),
		  testRoom1(std::make_shared<ConsultationRoom>(101)),
		  testRoom2(std::make_shared<RehabillitationRoom>(102, wyposazenie, 3)),
		  testRoomRepository(std::make_shared<RoomRepository>("../../library/test/data/AppointmentRoomManager.txt")),
		  specjalizacje({Specialisation::MASSAGE_THERAPIST, Specialisation::NEUROLOGIST}),
		  testPersonnel1(std::make_shared<Nurse>("Jesse", "Pinkman", 123)),
		  testPersonnel2(std::make_shared<Doctor>("Walter", "White", 124, specjalizacje, 200)),
		  testPersonnelRepository(
			  std::make_shared<PersonnelRepository>("../../library/test/data/AppointmentPersonnelManager.txt")),

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
		                                           eq1, 1)),
		  serviceRepo(std::make_shared<ServiceRepository>("../../library/test/data/AppointmentServiceManager.txt")),
		  testAppointmentRepository(std::make_shared<AppointmentRepository>(
				  "../../library/test/data/AppointmentManager.txt", testPatientRepository, testPersonnelRepository,
				  testRoomRepository, serviceRepo)
		  )
	{
		startTime = time_from_string("2025-06-15 10:30:00");
		startTime2 = time_from_string("2025-07-15 10:30:00");
		personnel = {testPersonnel1};
		personnel1 = {testPersonnel2};

		testAppointment = std::make_shared<Appointment>(startTime, 999, personnel, testPatient, rehab1, testRoom2);
		testAppointment1 = std::make_shared<Appointment>(startTime2, 978, personnel1, testPatient, cons1, testRoom1);

		testAppointment2 = std::make_shared<Appointment>(startTime, 999, personnel, testPatient, rehab1, testRoom2);

		testPatientRepository->add(testPatient);
		testPatientRepository->add(testPatient1);
		testPatientRepository->saveData();

		testRoomRepository->add(testRoom1);
		testRoomRepository->add(testRoom2);
		testRoomRepository->saveData();

		testPersonnelRepository->add(testPersonnel1);
		testPersonnelRepository->add(testPersonnel2);
		testPersonnelRepository->saveData();

		serviceRepo->add(rehab1);
		serviceRepo->add(cons1);
		serviceRepo->saveData();

		testAppointmentRepository->add(testAppointment);
		testAppointmentRepository->add(testAppointment1);
		testAppointmentRepository->saveData();

		appointmentManager = std::make_shared<AppointmentManager>("../../library/test/data/AppointmentManager.txt",
		                                                          "../../library/test/data/AppointmentManagerArchive.txt",
		                                                          testPatientRepository, testPersonnelRepository,
		                                                          testRoomRepository, serviceRepo);
	}

	~TestSuitAppointmentManagerFixture()
	{
	}
};

bool predicateAppointment(AppointmentPtr v)
{
	return v->getPatient()->getLastName() == "White";
}

BOOST_FIXTURE_TEST_SUITE(TestSuitAppointmentManager, TestSuitAppointmentManagerFixture)

	BOOST_AUTO_TEST_CASE(GetTest)
	{
		BOOST_TEST(appointmentManager->get(999)->getAppointmentBeginDate() == startTime);
		BOOST_TEST(appointmentManager->get(978)->getAppointmentBeginDate() == startTime2);
		BOOST_TEST(appointmentManager->get(2137) == nullptr);
	}

	BOOST_AUTO_TEST_CASE(FindByFindAllTest)
	{
		AppointmentPredicate appointmentPredicate = predicateAppointment;
		appointmentManager->get((unsigned int)0);
		BOOST_TEST(appointmentManager->findAll()[0] != nullptr);
	}

	BOOST_AUTO_TEST_CASE(GetAppointmensText)
	{
		// Sprawdzamy ilość spotkań czy jest odpowiednia
		BOOST_TEST(appointmentManager->getPatientAppointments(testPatient).size() == 2);
		BOOST_TEST(appointmentManager->getPersonnelAppointments(testPersonnel1).size() == 1);
		BOOST_TEST(appointmentManager->getPersonnelAppointments(testPersonnel2).size() == 1);
		BOOST_TEST(appointmentManager->getServiceAppointments(rehab1).size() == 1);
		BOOST_TEST(appointmentManager->getServiceAppointments(cons1).size() == 1);
		BOOST_TEST(appointmentManager->getRoomAppointments(testRoom1).size() == 1);
		BOOST_TEST(appointmentManager->getRoomAppointments(testRoom2).size() == 1);
	}

	BOOST_AUTO_TEST_CASE(IsDateTest)
	{
		// Sprawdzamy czy wykrywana jest prawidłowa relacja
		// Brak nakładania się dat
		// Daty tych spotkan to: 2025-06-15 10:30:00, 2025-07-15 10:30:00
		std::vector<AppointmentPtr> appointments = {testAppointment1, testAppointment};

		//Nie nakładają się
		BOOST_TEST(appointmentManager->isDate(appointments, time_from_string("2025-06-15 11:30:00"),60) == false);

		//Nakładają się
		BOOST_TEST(appointmentManager->isDate(appointments, time_from_string("2025-06-15 10:00:00"),60));
	}

	BOOST_AUTO_TEST_CASE(ArrangeAppointmentTest)
	{
		//Możliwe jest ustalenie:
		BOOST_TEST(appointmentManager->arrangeAppointment(testPatient,
			rehab1,
			personnel,
			time_from_string("2024-06-15 10:30:00"),
			testRoom2,
			1) != nullptr);
		BOOST_TEST(appointmentManager->get(1)->getAppointmentBeginDate() == time_from_string("2024-06-15 10:30:00"));

		BOOST_TEST(
			appointmentManager->arrangeAppointment(testPatient, cons1, personnel1, time_from_string(
				"2024-08-15 10:30:00"), testRoom1, 2) != nullptr);
		BOOST_TEST(appointmentManager->get(2)->getAppointmentBeginDate() == time_from_string("2024-08-15 10:30:00"));


		testRoom2->setIsActive(false);
		//Niemozliwe ustalenie terminów:
		BOOST_CHECK_THROW(appointmentManager->arrangeAppointment(testPatient,
			                  cons1,
			                  personnel,
			                  time_from_string("2004-06-15 10:30:00"),
			                  testRoom2,
			                  32), LogicException);

		BOOST_CHECK_THROW(appointmentManager->arrangeAppointment(testPatient,
			                  rehab1,
			                  personnel,
			                  time_from_string("2024-08-15 10:30:00"),
			                  testRoom2,
			                  1), LogicException);
	}

	BOOST_AUTO_TEST_CASE(FinishAppointmentTest)
	{
		//Czy dobrze zostanie obsłuzone brak da;nego wizyty?
		BOOST_CHECK_THROW(appointmentManager->finishAppointment(testPatient,time_from_string("2024-02-15 11:30:00")),
		                  LogicException);

		//Upewniamy sie ze nie ma juz spotkania o tym numerze

		if (appointmentManager->getArchiveRepository()->get((unsigned int)100) != nullptr)
		{
			appointmentManager->getArchiveRepository()->remove(
				appointmentManager->getArchiveRepository()->get((unsigned int)100));
		}

		if (appointmentManager->getArchiveRepository()->get((unsigned int)30) != nullptr)
		{
			appointmentManager->getArchiveRepository()->remove(
				appointmentManager->getArchiveRepository()->get((unsigned int)30));
		}


		if (appointmentManager->getArchiveRepository()->get((unsigned int)99) != nullptr)
		{
			appointmentManager->getArchiveRepository()->remove(
				appointmentManager->getArchiveRepository()->get((unsigned int)99));
		}

		//Wymagane jest prawidłowe dodanie wizyt
		BOOST_TEST_REQUIRE(appointmentManager->arrangeAppointment(testPatient,
			rehab1,
			personnel,
			time_from_string("2024-06-15 10:30:00"),
			testRoom2,
			100) != nullptr);

		BOOST_TEST_REQUIRE(
			appointmentManager->arrangeAppointment(testPatient, cons1, personnel1, time_from_string(
				"2024-08-15 10:30:00"), testRoom1, 30) != nullptr);

		//Czy zwracany jest prawidłowy koszt?
		BOOST_TEST(appointmentManager->finishAppointment(testPatient,time_from_string("2024-06-15 10:30:00")) == 100);
		//Czy zostało dodane do repozytorium archive?
		BOOST_TEST(
			appointmentManager->getArchiveRepository()->get((unsigned int)100)->getAppointmentBeginDate() ==
			time_from_string("2024-06-15 10:30:00"));

		BOOST_TEST(appointmentManager->finishAppointment(testPatient,time_from_string("2024-08-15 10:30:00")) == 350);


		//Czy zostało dodane do repozytorium archive?
		BOOST_TEST(
			appointmentManager->getArchiveRepository()->get((unsigned int)30)->getAppointmentBeginDate() ==
			time_from_string("2024-08-15 10:30:00"));
		//Sprawdzenie metody getAppointmentsCost
		BOOST_TEST(appointmentManager->getAppointmentsCost(testPatient) == 450);

		ptime now = time_from_string("2137-08-15 10:30:00");

		BOOST_TEST_REQUIRE(
			appointmentManager->arrangeAppointment(testPatient, cons1, personnel1, now, testRoom1, 99) != nullptr);

		//Czy niemożliwe jest zakończenie wizyty podczas trwania wizyty?
		BOOST_CHECK_THROW(appointmentManager->finishAppointment(testPatient,now), LogicException);

		//Czy nie został dodany nowy obiekt?
		BOOST_TEST(appointmentManager->getArchiveRepository()->size() == 2);
	}

	BOOST_AUTO_TEST_CASE(ChangeAppointmentTest)
	{
		BOOST_TEST_REQUIRE(appointmentManager->arrangeAppointment(testPatient,
			rehab1,
			personnel,
			time_from_string("2024-06-15 10:30:00"),
			testRoom2,
			1) != nullptr);

		BOOST_TEST_REQUIRE(
			appointmentManager->arrangeAppointment(testPatient, cons1, personnel1, time_from_string(
				"2024-08-15 10:30:00"), testRoom1, 2) != nullptr);

		//Poprawna zmiana
		BOOST_TEST(appointmentManager->changeAppointment(time_from_string("2027-06-15 10:30:00"),1) == true);

		//Nieprawidłowa zmiana
		BOOST_CHECK_THROW(appointmentManager->changeAppointment(time_from_string("2024-08-15 10:30:00"),1),
		                  DateException);
	}

	BOOST_AUTO_TEST_CASE(CancelAppointmentTest)
	{
		BOOST_TEST_REQUIRE(appointmentManager->arrangeAppointment(testPatient,
			rehab1,
			personnel,
			time_from_string("2024-06-15 10:30:00"),
			testRoom2,
			1) != nullptr);
		BOOST_TEST(appointmentManager->get(1) != nullptr);

		appointmentManager->cancelAppointment(1);
		BOOST_TEST(appointmentManager->get(1) == nullptr);
	}


BOOST_AUTO_TEST_SUITE_END()
