#include "rooms/RehabillitationRoom.h"
#include "enums/Equipment.h"
#include "sstream"

namespace RehabClinic
{

	using namespace std;

	const std::string RehabillitationRoom::getInfo() const
	{
		ostringstream oss;
		int i;
		for (i = 0; i < getAccessibleEqupiment().size() - 1; i++)
		{
			oss << equipmentToString(getAccessibleEqupiment()[i]) << ", ";
		}
		oss << equipmentToString(getAccessibleEqupiment()[i]);
		return Room::getInfo() + " pokoj rehabilitacyjny co moze maskymalnie pomiescic " + to_string(getMaxCapacity()) +
			" osob z personulu, sprzęt dostępny w pokoju: " + oss.str();
	}

	RehabillitationRoom::RehabillitationRoom(const unsigned roomNumber,
	                                         const std::vector<Equipment>& accessibleEqupiment,
	                                         const unsigned int maxCapacity) : Room(roomNumber),
	                                                                           accessibleEqupiment(accessibleEqupiment),
	                                                                           maxCapacity(maxCapacity)
	{
	}

	bool RehabillitationRoom::canBeUsed(Equipment equipment) const
	{
		for (int i = 0; i < getAccessibleEqupiment().size(); i++)
		{
			if (equipment == getAccessibleEqupiment()[i])
			{
				return true;
			}
		}
		return false;
	}

	const std::vector<Equipment>& RehabillitationRoom::getAccessibleEqupiment() const
	{
		return accessibleEqupiment;
	}

	unsigned int RehabillitationRoom::getMaxCapacity() const
	{
		return maxCapacity;
	}
}
