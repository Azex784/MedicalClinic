#include "managers/RoomManager.h"

#include "../../include/Exceptions.h"


using namespace std;

RoomManager::RoomManager(const std::string& fileName): ManagerTemplate<std::shared_ptr<Room>, RoomRepository, std::function<bool(std::shared_ptr<Room>)>, const
                                                                       unsigned>(fileName)
{
}

void RoomManager::addConsultationRoom(const unsigned int roomNumber) const
{
	RoomPtr room = make_shared<ConsultationRoom>(roomNumber);
	if (getRepository()->get(roomNumber) == nullptr)
	{
		getRepository()->add(room);
		return;
	}
	throw ExistException("Sala konsultacyjna",to_string(roomNumber));
}

void RoomManager::addRehabillitationRoom(const unsigned int roomNumber, std::vector<Equipment> equipment,
	const unsigned int maxCapacity)
{
	if (equipment.empty())throw LogicException("Wpisano nieprawidłowe pusty sprzęt.");
	RoomPtr room = make_shared<RehabillitationRoom>(roomNumber,equipment, maxCapacity);
	if (getRepository()->get(roomNumber) == nullptr)
	{
		getRepository()->add(room);
		return;
	}
	throw ExistException("Sala rehabilitacyjna",to_string(roomNumber));
}
