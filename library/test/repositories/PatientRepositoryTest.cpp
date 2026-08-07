#include <boost/test/unit_test.hpp>
#include <patient/Patient.h>
#include "patient/Address.h"
#include "repositories/PatientRepository.h"
#include "typedefs.h"
#include <fstream>

using namespace std;
using namespace RehabClinic;


struct TestSuitPatientRepositoryFixture
{
	const string fileName = "../../library/test/data/PatientRepository.txt";
	PatientRepositoryPtr pacjentRepo = make_shared<PatientRepository>(fileName);

	AddressPtr testAddress;
	PatientPtr testPatient;
	PatientPtr testPatient1;
	PatientPtr testPatient2;
	PatientPtr testPatient3;

	TestSuitPatientRepositoryFixture()
		: testAddress(std::make_shared<Address>("Albuquerqe", "Juan Poet", "10/15")),
		  testPatient(std::make_shared<Patient>("Walter", "White", "40010112345", testAddress)),
		  testPatient1(std::make_shared<Patient>("Jesse", "Pinkman", "20010112345", testAddress)),
		  testPatient2(std::make_shared<Patient>("Skyler", "White", "93010112345", testAddress)),
		  testPatient3(std::make_shared<Patient>("Gustavo", "Fring", "91110112345", testAddress))

	{
		pacjentRepo->add(testPatient);
		pacjentRepo->add(testPatient1);
		pacjentRepo->add(testPatient2);
		pacjentRepo->add(testPatient3);
	}

	~TestSuitPatientRepositoryFixture() = default;
};


BOOST_FIXTURE_TEST_SUITE(TestSuitePatientRepository, TestSuitPatientRepositoryFixture)

	BOOST_AUTO_TEST_CASE(SaveDataTest)
	{

		pacjentRepo->saveData();

		ifstream inFile;
		inFile.open(fileName);
		string line;

		BOOST_TEST_REQUIRE(inFile.good());
		int i = 0;
		while (getline(inFile, line))
		{
			if (line.empty()) continue;
			stringstream ss(line);
			string firstName, lastName, personalNumber, city, street, number, tmp;

			getline(ss, firstName, ';');
			getline(ss, lastName, ';');
			getline(ss, personalNumber, ';');
			getline(ss, city, ';');
			getline(ss, street, ';');
			getline(ss, number, ';');
			getline(ss, tmp);

			bool isArchived = stoi(tmp);

			BOOST_TEST(pacjentRepo->getVectorOfData()[i]->getName() == firstName);
			BOOST_TEST(pacjentRepo->getVectorOfData()[i]->getLastName() == lastName);
			BOOST_TEST(pacjentRepo->getVectorOfData()[i]->getUniqueParameter() == personalNumber);
			BOOST_TEST(pacjentRepo->getVectorOfData()[i]->getAddress()->getCity() == city);
			BOOST_TEST(pacjentRepo->getVectorOfData()[i]->getAddress()->getStreet() == street);
			BOOST_TEST(pacjentRepo->getVectorOfData()[i]->getAddress()->getNumber() == number);
			BOOST_TEST(pacjentRepo->getVectorOfData()[i]->getIsArchive() == isArchived);
			i++;
		}
		inFile.close();
	}

	BOOST_AUTO_TEST_CASE(LoadData)
{
	PatientRepositoryPtr pacjentRepo1 = make_shared<PatientRepository>(fileName);

	//Musi byc prawidlowe zapis i wczytanie pliku
	pacjentRepo->saveData();
	pacjentRepo1->loadData();

	//Weryfikacja rozmiaru
    BOOST_TEST_REQUIRE(pacjentRepo1->getVectorOfData().size() == pacjentRepo->getVectorOfData().size());

	for (int i = 0; i < (int)pacjentRepo1->getVectorOfData().size(); i++)
	{
		BOOST_TEST(pacjentRepo1->getVectorOfData()[i]->getName() == pacjentRepo->getVectorOfData()[i]->getName());
		BOOST_TEST(pacjentRepo1->getVectorOfData()[i]->getLastName() == pacjentRepo->getVectorOfData()[i]->getLastName());
		BOOST_TEST(pacjentRepo1->getVectorOfData()[i]->getUniqueParameter() == pacjentRepo->getVectorOfData()[i]->getUniqueParameter());
		BOOST_TEST(pacjentRepo1->getVectorOfData()[i]->getAddress()->getCity() == pacjentRepo->getVectorOfData()[i]->getAddress()->getCity());
		BOOST_TEST(pacjentRepo1->getVectorOfData()[i]->getAddress()->getStreet() == pacjentRepo->getVectorOfData()[i]->getAddress()->getStreet());
		BOOST_TEST(pacjentRepo1->getVectorOfData()[i]->getAddress()->getNumber() == pacjentRepo->getVectorOfData()[i]->getAddress()->getNumber());
		BOOST_TEST(pacjentRepo1->getVectorOfData()[i]->getIsArchive() == pacjentRepo->getVectorOfData()[i]->getIsArchive());
	};

	//czy zostal przypisany ten sam adres?
	BOOST_TEST(pacjentRepo1->getVectorOfData()[0]->getAddress() == pacjentRepo1->getVectorOfData()[1]->getAddress());
}


BOOST_AUTO_TEST_SUITE_END()
