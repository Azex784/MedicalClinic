#include "services/Rehabillitation.h"
#include "enums/Equipment.h"

using namespace std;

const std::vector<Equipment>& Rehabillitation::getRequiredEqupiment() const
{
    return requiredEqupiment;
}

unsigned int Rehabillitation::getRequiredNurseSize() const
{
    return requiredNurseSize;
}

Rehabillitation::Rehabillitation(const unsigned room_number, const std::vector<Equipment>& required_equpiment,
    const unsigned int required_nurse_size): Room(room_number),
                                             requiredEqupiment(required_equpiment),
                                             requiredNurseSize(required_nurse_size)
{
}

const std::string Rehabillitation::getInfo() const
{
    return Room::getInfo() + " rehabilitacja potrzebna ilosc pielegniarek: " + to_string(getRequiredNurseSize());
}

bool Rehabillitation::canBeUsed(const Equipment equipment) const
{
    for (int i = 0; i < getRequiredEqupiment().size(); i++)
    {
        if (getRequiredEqupiment()[i] == equipment)
        {
            return true;
        }
    }
    return false;
}
