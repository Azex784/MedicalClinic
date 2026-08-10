#include "repositories/RoomRepository.h"
#include "rooms/Room.h"
#include "rooms/RehabillitationRoom.h"
#include "rooms/ConsultationRoom.h"
#include "enums/Equipment.h"
#include "typedefs.h"

#include <boost/test/unit_test.hpp>
#include <fstream>
#include <vector>

using namespace std;
using namespace MedicalClinic;


struct TestSuiteRoomRepositoryFixture
{
	const string fileName = "../../library/test/data/RoomRepository.txt";
	RoomRepositoryPtr roomRepo = make_shared<RoomRepository>(fileName);

	RoomPtr rehab1;
	RoomPtr rehab2;
	RoomPtr consult1;
	RoomPtr consult2;

	TestSuiteRoomRepositoryFixture()
	{
		vector<Equipment> eq1 = {Equipment::NONE, Equipment::KINESITHERAPY_SPACE};
		vector<Equipment> eq2 = {Equipment::PHYSICAL_THERAPY_DEVICE};

		rehab1 = make_shared<RehabillitationRoom>(101, eq1, 10);
		rehab2 = make_shared<RehabillitationRoom>(102, eq2, 5);
		consult1 = make_shared<ConsultationRoom>(201);
		consult2 = make_shared<ConsultationRoom>(202);

		roomRepo->add(rehab1);
		roomRepo->add(rehab2);
		roomRepo->add(consult1);
		roomRepo->add(consult2);
	}

	~TestSuiteRoomRepositoryFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteRoomRepository, TestSuiteRoomRepositoryFixture)

	BOOST_AUTO_TEST_CASE(SaveDataTest)
	{
		roomRepo->saveData();

		ifstream inFile(fileName);
		string line;

		BOOST_TEST_REQUIRE(inFile.is_open());

		// Sala rehabilitacyjna 1
		getline(inFile, line);
		BOOST_TEST(line == "R;101;1;0;0,2;10");

		// Sala rehabilitacyjna 2
		getline(inFile, line);
		BOOST_TEST(line == "R;102;1;0;1;5");

		// Sala konsultacyjna 1
		getline(inFile, line);
		BOOST_TEST(line == "C;201;1;0");

		// Sala konsultacyjna 2
		getline(inFile, line);
		BOOST_TEST(line == "C;202;1;0");

		inFile.close();
	}

	BOOST_AUTO_TEST_CASE(LoadDataTest)
	{
		RoomRepositoryPtr roomRepo1 = make_shared<RoomRepository>(fileName);

		// Zapisujemy stan oryginalnego repozytorium i ładujemy do nowego
		roomRepo->saveData();
		roomRepo1->loadData();

		// Weryfikacja rozmiaru
		BOOST_TEST_REQUIRE(roomRepo1->getVectorOfData().size() == roomRepo->getVectorOfData().size());

		// Weryfikacja równości obu obiektów - z wczytanymi danymi i tymi ktore były zapisane
		for (int i = 0; i < (int)roomRepo1->getVectorOfData().size(); i++)
		{
			RoomPtr loadedRoom = roomRepo1->getVectorOfData()[i];
			RoomPtr originalRoom = roomRepo->getVectorOfData()[i];

			// Sprawdzamy podstawowe parametry wspólne dla wszystkich sal
			BOOST_TEST(loadedRoom->getUniqueParameter() == originalRoom->getUniqueParameter());
			BOOST_TEST(loadedRoom->getIsActive() == originalRoom->getIsActive());
			BOOST_TEST(loadedRoom->getIsArchive() == originalRoom->getIsArchive());

			RehabillitationRoomPtr loadedRehabillitationRoom = dynamic_pointer_cast<RehabillitationRoom>(loadedRoom);
			RehabillitationRoomPtr originalRehabillitationRoom = dynamic_pointer_cast<
				RehabillitationRoom>(originalRoom);

			//Sprawdzamy dla pokoju rehabilitacji
			if (originalRehabillitationRoom != nullptr)
			{
				// Sprawdzamy prawidłowe rzutowanie
				BOOST_TEST_REQUIRE(loadedRehabillitationRoom != nullptr);

				BOOST_TEST(loadedRehabillitationRoom->getMaxCapacity() == originalRehabillitationRoom->getMaxCapacity())
				;

				//Sprawdzenie rozmiarów jest niezbędne by zacząć porównywanie wartości enumów
				BOOST_TEST_REQUIRE(
					loadedRehabillitationRoom->getAccessibleEqupiment().size() == originalRehabillitationRoom->
					getAccessibleEqupiment().size());

				// Weryfikacja wartości enumów
				for (int j = 0; j < (int)loadedRehabillitationRoom->getAccessibleEqupiment().size(); j++)
				{
					BOOST_TEST(toString(loadedRehabillitationRoom->getAccessibleEqupiment()[j]) ==
						toString(originalRehabillitationRoom->getAccessibleEqupiment()[j]));
				}
			}

			ConsultationRoomPtr originalConsult = dynamic_pointer_cast<ConsultationRoom>(originalRoom);
			if (originalConsult != nullptr)
			{
				ConsultationRoomPtr loadedConsultation = dynamic_pointer_cast<ConsultationRoom>(loadedRoom);
				// Podstawowe parametry zostaly sprawdzone, wiec mozliwe jest tylko sprawdzenie czy jest to obiekt
				// klasy konsultacji
				BOOST_TEST_REQUIRE(loadedConsultation != nullptr);
			}
		}
	}

BOOST_AUTO_TEST_SUITE_END()
