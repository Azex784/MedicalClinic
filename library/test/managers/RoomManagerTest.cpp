#include <boost/test/unit_test.hpp>
#include "managers/RoomManager.h"

#include "rooms/ConsultationRoom.h"
#include "rooms/RehabillitationRoom.h"
#include "managers/ManagerTemplate.h"
#include "enums/Equipment.h"

#include "repositories/RoomRepository.h"
#include "typedefs.h"
#include "../../include/Exceptions.h"

using namespace std;

struct TestSuitRoomManagerFixture
{
	std::vector<Equipment> wyposazenie;

	RoomPtr testRoom1;
	RoomPtr testRoom2;
	RoomRepositoryPtr testRoomRepository;
	RoomManager roomManager;

	TestSuitRoomManagerFixture()
		:
		wyposazenie({Equipment::KINESITHERAPY_SPACE, Equipment::ROBOTIC_SYSTEM}),
		testRoom1(std::make_shared<ConsultationRoom>(101)),
		testRoom2(std::make_shared<RehabillitationRoom>(102, wyposazenie, 3)),
		testRoomRepository(std::make_shared<RoomRepository>("../../library/test/data/RoomManager.txt"))
	{
		testRoomRepository->add(testRoom1);
		testRoomRepository->add(testRoom2);
		testRoomRepository->saveData();
		roomManager = RoomManager("../../library/test/data/RoomManager.txt");
	}

	~TestSuitRoomManagerFixture()
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(TestSuitRoomManager, TestSuitRoomManagerFixture)

	BOOST_AUTO_TEST_CASE(AddRoomsTest)
	{
		// Sprawdzenie stanu początkowego
		BOOST_TEST_REQUIRE(roomManager.getRepository()->get((unsigned int)101) != nullptr);
		BOOST_TEST_REQUIRE(roomManager.getRepository()->getVectorOfData().size() == 2);

		// Próba dodania już istniejącego gabinetu
		BOOST_CHECK_THROW(roomManager.addConsultationRoom(101), ExistException);
		BOOST_TEST(roomManager.getRepository()->getVectorOfData().size() == 2);

		// Zwykłe dodanie nowej sali
		roomManager.addConsultationRoom(103);
		BOOST_TEST(roomManager.getRepository()->getVectorOfData().size() == 3);
		BOOST_TEST(roomManager.getRepository()->get((unsigned int)103) != nullptr);

		// Dodanie nowej sali rehabilitacyjnej
		roomManager.addRehabillitationRoom(104, wyposazenie, 5);

		BOOST_TEST(roomManager.getRepository()->getVectorOfData().size() == 4);
		BOOST_TEST(roomManager.getRepository()->get((unsigned int)104) != nullptr);

		// Próba dodania istniejącej sali rehabilitacyjnej
		BOOST_CHECK_THROW(roomManager.addRehabillitationRoom(104, wyposazenie, 5);, ExistException);
		BOOST_TEST(roomManager.getRepository()->getVectorOfData().size() == 4);
	}

BOOST_AUTO_TEST_SUITE_END()
