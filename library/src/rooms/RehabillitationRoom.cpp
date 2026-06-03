#include "rooms/RehabillitationRoom.h"


using namespace std;

const std::string RehabillitationRoom::getInfo() const
{
    return Room::getInfo() + " pokoj rehabilitacyjny co moze maskymalnie pomiescic " + to_string(getMaxCapacity()) + " osob z personulu";
}

RehabillitationRoom::RehabillitationRoom(const unsigned room_number, const std::vector<Equipment>& accessible_equpiment,
    const unsigned int max_capacity): Room(room_number),
                                      accessibleEqupiment(accessible_equpiment),
                                      maxCapacity(max_capacity)
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
