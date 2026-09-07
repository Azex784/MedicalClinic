#include "rooms/SurgeryRoom.h"
#include "enums/Equipment.h"
#include "sstream"

namespace MedicalClinic
{
	using namespace std;

	const std::string SurgeryRoom::getInfo() const
	{
		ostringstream oss;
		int i;
		for (i = 0; i < (int)getAccessibleEqupiment().size() - 1; i++)
		{
			oss << toString(getAccessibleEqupiment()[i]) << ", ";
		}
		oss << toString(getAccessibleEqupiment()[i]) << ".";
		return Room::getInfo() + ", pokój operacyjny, maksymalna ładowność: " + to_string(getMaxCapacity()) +
			" osób z personulu, sprzęt dostępny w pokoju: " + oss.str();
	}

	SurgeryRoom::SurgeryRoom(const unsigned roomNumber,
	                                         const std::vector<Equipment>& accessibleEqupiment,
	                                         const unsigned int maxCapacity) : Room(roomNumber),
	                                                                           accessibleEqupiment(accessibleEqupiment),
	                                                                           maxCapacity(maxCapacity)
	{
	}

	bool SurgeryRoom::canBeUsed(Equipment equipment) const
	{
		for (int i = 0; i < (int)getAccessibleEqupiment().size(); i++)
		{
			if (equipment == getAccessibleEqupiment()[i])
			{
				return true;
			}
		}
		return false;
	}

	const std::vector<Equipment>& SurgeryRoom::getAccessibleEqupiment() const
	{
		return accessibleEqupiment;
	}

	unsigned int SurgeryRoom::getMaxCapacity() const
	{
		return maxCapacity;
	}
}
