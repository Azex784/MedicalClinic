#include <boost/test/unit_test.hpp>
#include "personnel/Personnel.h"
#include "personnel/Doctor.h"
#include "personnel/Nurse.h"
#include "repositories/PersonnelRepository.h"
#include "enums/Specialisation.h"
#include "typedefs.h"
#include <fstream>
#include <vector>

using namespace std;
using namespace MedicalClinic;


struct TestSuitePersonnelRepositoryFixture
{
    const string fileName = "../../library/test/data/PersonnelRepository.txt";
    PersonnelRepositoryPtr personnelRepo = make_shared<PersonnelRepository>(fileName);

    PersonnelPtr doc1;
    PersonnelPtr doc2;
    PersonnelPtr nurse1;
    PersonnelPtr nurse2;

    TestSuitePersonnelRepositoryFixture()
    {
        vector<Specialisation> specs1 = {Specialisation::MASSAGE_THERAPIST, Specialisation::NEUROLOGIST };
        vector<Specialisation> specs2 = {Specialisation::ORTHOPEDIST};

        doc1 = make_shared<Doctor>("Walter", "White", 101, specs1, 250);
        doc2 = make_shared<Doctor>("Saul", "Goodman", 102, specs2, 500);
        nurse1 = make_shared<Nurse>("Jesse", "Pinkman", 201);
        nurse2 = make_shared<Nurse>("Taylor", "Smith", 202);

        // Dodajemy do naszej bazy
        personnelRepo->add(doc1);
        personnelRepo->add(doc2);
        personnelRepo->add(nurse1);
        personnelRepo->add(nurse2);
    }

    ~TestSuitePersonnelRepositoryFixture() = default;
};


BOOST_FIXTURE_TEST_SUITE(TestSuitePersonnelRepository, TestSuitePersonnelRepositoryFixture)


BOOST_AUTO_TEST_CASE(SaveDataTest)
{
    //Czy zapis się powiódł
    personnelRepo->saveData();

    ifstream inFile(fileName);
    string line;

    BOOST_TEST_REQUIRE(inFile.is_open());

    //Sprawdzamy czy zapis jest prawidłowy dla pielęgniarek i doktorów

    // Lekarz 1
    getline(inFile, line);
    BOOST_TEST(line == "D;Walter;White;1;0;101;5,2;250");

    // Lekarz 2
    getline(inFile, line);
    BOOST_TEST(line == "D;Saul;Goodman;1;0;102;1;500");

    // Pielęgniarka 1
    getline(inFile, line);
    BOOST_TEST(line == "N;Jesse;Pinkman;1;0;201");

    // Pielęgniarka 2
    getline(inFile, line);
    BOOST_TEST(line == "N;Taylor;Smith;1;0;202");

    inFile.close();
}

BOOST_AUTO_TEST_CASE(LoadDataTest)
{
    PersonnelRepositoryPtr personnelRepo1 = make_shared<PersonnelRepository>(fileName);

    // Zapisujemy stan oryginalnego repozytorium i ładujemy do nowego
    personnelRepo->saveData();
    personnelRepo1->loadData();

    // Weryfikacja rozmiaru
    BOOST_TEST_REQUIRE(personnelRepo1->getVectorOfData().size() == personnelRepo->getVectorOfData().size());

    // Pętla weryfikująca odczytane obiekty
    for (int i = 0; i < (int)personnelRepo1->getVectorOfData().size(); i++)
    {
        PersonnelPtr loadedPerson = personnelRepo1->getVectorOfData()[i];
        PersonnelPtr originalPerson = personnelRepo->getVectorOfData()[i];

        //Sprawdzamy podstawowe parametry wspólne dla lekarza i pielegniarki
        BOOST_TEST(loadedPerson->getName() == originalPerson->getName());
        BOOST_TEST(loadedPerson->getLastName() == originalPerson->getLastName());
        BOOST_TEST(loadedPerson->getUniqueParameter() == originalPerson->getUniqueParameter());
        BOOST_TEST(loadedPerson->getIsActive() == originalPerson->getIsActive());
        BOOST_TEST(loadedPerson->getIsArchive() == originalPerson->getIsArchive());

        // Sprawdzamy dla doktora
        DoctorPtr loadedDoctor = dynamic_pointer_cast<Doctor>(loadedPerson);
        DoctorPtr originalDoctor = dynamic_pointer_cast<Doctor>(originalPerson);

        if (originalDoctor != nullptr)
        {
            //Sprawdzamy czy wczytany nie jest nullptr - czy został wczytany
            BOOST_TEST_REQUIRE(loadedDoctor != nullptr);

            // Porównujemy uniklane atrybuty lekrza
            BOOST_TEST(loadedDoctor->getDoctorCost() == originalDoctor->getDoctorCost());
            BOOST_TEST_REQUIRE(loadedDoctor->getSpecialisation().size() == originalDoctor->getSpecialisation().size());

            // Weryfikacja wartości enuma
            for (int j = 0; j < (int)loadedDoctor->getSpecialisation().size(); j++)
            {
                BOOST_TEST(specialisationToString(loadedDoctor->getSpecialisation()[j]) ==
                           specialisationToString(originalDoctor->getSpecialisation()[j]));
            }
        }

        // Sprawdzamy dla pielęgniarki
        NursePtr originalNurse = dynamic_pointer_cast<Nurse>(originalPerson);
        if (originalNurse != nullptr)
        {
            NursePtr loadedNurse = dynamic_pointer_cast<Nurse>(loadedPerson);
            //Możemy jedynie sprawdzic czy zostało to wczytane, gdyz parametry pielęgniarki zostały już sprawdzone
            BOOST_TEST_REQUIRE(loadedNurse != nullptr);
        }
    }
}

BOOST_AUTO_TEST_SUITE_END()