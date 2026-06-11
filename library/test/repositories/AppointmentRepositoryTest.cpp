#include <Appointment.h>
#include <boost/test/unit_test.hpp>
#include "repositories/AppointmentRepository.h"
#include "repositories/PatientRepository.h"
#include "repositories/PersonnelRepository.h"
#include "repositories/RoomRepository.h"
#include "repositories/ServiceRepository.h"

#include "patient/Address.h"
#include "patient/Patient.h"

#include "enums/Specialisation.h"
#include "enums/Equipment.h"

#include "personnel/Doctor.h"
#include "personnel/Nurse.h"

#include "rooms/RehabillitationRoom.h"

#include "services/Consultation.h"

#include <fstream>
#include <vector>

using namespace std;
using namespace RehabClinic;


struct TestSuiteAppointmentRepositoryFixture
{
	// Ścieżki do plików
	const string fileName = "../../library/test/data/AppointmentRepository.txt";
	const string fileName1 = "../../library/test/data/PatientRepository.txt";
	const string fileName2 = "../../library/test/data/PersonnelRepository.txt";
	const string fileName3 = "../../library/test/data/RoomRepository.txt";
	const string fileName4 = "../../library/test/data/ServiceRepository.txt";

	// Inicjalizacja repozytoriów
	PatientRepositoryPtr pacjentRepo = make_shared<PatientRepository>(fileName1);
	PersonnelRepositoryPtr personnelRepo = make_shared<PersonnelRepository>(fileName2);
	RoomRepositoryPtr roomRepo = make_shared<RoomRepository>(fileName3);
	ServiceRepositoryPtr serviceRepo = make_shared<ServiceRepository>(fileName4);

	AppointmentRepositoryPtr appointmentRepo = make_shared<AppointmentRepository>(
		fileName, pacjentRepo, personnelRepo, roomRepo, serviceRepo);

	AddressPtr testAddress;
	PatientPtr testPatient;

	PersonnelPtr doc1;
	PersonnelPtr doc2;

	RoomPtr rehab1;
	ServicePtr cons1;

	AppointmentPtr appoint, appoint1;

	boost::posix_time::ptime nowTime;

	TestSuiteAppointmentRepositoryFixture()
	{
		testAddress = make_shared<Address>("Albuquerque", "Juan Tabo", "10/15");
		testPatient = make_shared<Patient>("Walter", "White", "40010112345", testAddress);
		pacjentRepo->add(testPatient);

		vector<Specialisation> specs1 = {Specialisation::MASSAGE_THERAPIST, Specialisation::NEUROLOGIST};
		vector<Specialisation> specs2 = {Specialisation::ORTHOPEDIST};
		vector<Equipment> eq1 = {Equipment::NONE, Equipment::KINESITHERAPY_SPACE};

		doc1 = make_shared<Doctor>("Walter", "White", 100, specs1, 250);
		doc2 = make_shared<Doctor>("Saul", "Goodman", 102, specs2, 500);

		personnelRepo->add(doc1);
		personnelRepo->add(doc2);

		rehab1 = make_shared<RehabillitationRoom>(101, eq1, 10);
		roomRepo->add(rehab1);

		cons1 = make_shared<Consultation>(150, 30, "Konsultacja odnosnie masazu", 101, 1,
		                                  Specialisation::MASSAGE_THERAPIST, "Omowienie wynikow", false);
		serviceRepo->add(cons1);

		nowTime = boost::posix_time::time_from_string("2025-06-15 10:30:00");

		boost::posix_time::ptime startTime{nowTime};

		appoint = make_shared<Appointment>(startTime, 999, personnelRepo->findAll(), testPatient, cons1, rehab1);
		appoint1 = make_shared<Appointment>(startTime, 99, personnelRepo->findAll(), testPatient, cons1, rehab1);

		appointmentRepo->add(appoint);
		appointmentRepo->add(appoint1);
	}

	~TestSuiteAppointmentRepositoryFixture() = default;
};


BOOST_FIXTURE_TEST_SUITE(TestSuiteAppointmentRepository, TestSuiteAppointmentRepositoryFixture)

	BOOST_AUTO_TEST_CASE(GetterTests)
	{
		//Sprawdzenie prawidłowe działanie getterów
		BOOST_TEST(appointmentRepo->getRoomRepository()->getVectorOfData()[0]->getUniqueParameter() == 101);
		BOOST_TEST(appointmentRepo->getPatientRepository()->getVectorOfData()[0]->getUniqueParameter() == "40010112345")
		;
		BOOST_TEST(appointmentRepo->getServiceRepository()->getVectorOfData()[0]->getUniqueParameter() == 101);
		BOOST_TEST(appointmentRepo->getPersonnelRepository()->getVectorOfData()[0]->getUniqueParameter() == 100);
	}

	BOOST_AUTO_TEST_CASE(SaveDataTest)
	{
		appointmentRepo->saveData();

		ifstream inFile(fileName);
		string line;

		BOOST_TEST_REQUIRE(inFile.is_open());

		// Spotkanie 1
		getline(inFile, line);
		BOOST_TEST(line == "20250615T103000;999;100,102;40010112345;101;101");

		// Spotkanie 2
		getline(inFile, line);
		BOOST_TEST(line == "20250615T103000;99;100,102;40010112345;101;101");

		inFile.close();
	}

	BOOST_AUTO_TEST_CASE(LoadDataTest)
	{
		AppointmentRepositoryPtr appointmentRepo1 = make_shared<AppointmentRepository>(
			fileName, pacjentRepo, personnelRepo, roomRepo, serviceRepo);

		appointmentRepo->saveData();
		appointmentRepo1->loadData();

		BOOST_TEST_REQUIRE(appointmentRepo1->size() == appointmentRepo->size());

		// Weryfikacja równości obu obiektów z wczytanymi danymi i tymi ktore były zapisane
		for (int i = 0; i < appointmentRepo1->getVectorOfData().size(); i++)
		{
			AppointmentPtr loadedAppointment = appointmentRepo1->getVectorOfData()[i];

			AppointmentPtr orginalAppointment = appointmentRepo->getVectorOfData()[i];

			// Sprawdzamy parametry wspólne wizyt
			BOOST_TEST(loadedAppointment->getUniqueParameter() == orginalAppointment->getUniqueParameter());
			BOOST_TEST(loadedAppointment->getAppointmentBeginDate() == orginalAppointment->getAppointmentBeginDate());
			BOOST_TEST(loadedAppointment->getPersonnel().size() == orginalAppointment->getPersonnel().size());

			//Czy taki same są wskazniki na odpowiednie parametry
			BOOST_TEST(loadedAppointment->getService() == orginalAppointment->getService());
			BOOST_TEST(loadedAppointment->getRoom() == orginalAppointment->getRoom());
			BOOST_TEST(loadedAppointment->getPatient() == orginalAppointment->getPatient());
		}
	}


BOOST_AUTO_TEST_SUITE_END()
