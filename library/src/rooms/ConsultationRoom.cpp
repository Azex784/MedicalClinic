#include "rooms/ConsultationRoom.h"
#include "enums/Equipment.h"

namespace MedicalClinic
{

	using namespace std;

	ConsultationRoom::ConsultationRoom(const unsigned roomNumber) : Room(roomNumber)
	{
	}

	const std::string ConsultationRoom::getInfo() const
	{
		return Room::getInfo() + ", pokój do przeprowadzania konsultacji.";
	}

	bool ConsultationRoom::canBeUsed(Equipment equipment) const
	{
		if (equipment == Equipment::NONE)
		{
			return true;
		}
		return false;
	}
}
