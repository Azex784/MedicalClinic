#include "services/Rehabillitation.h"
#include "enums/Equipment.h"
#include <sstream>

using namespace std;

const std::vector<Equipment>& Rehabillitation::getRequiredEqupiment() const
{
    return requiredEqupiment;
}

unsigned int Rehabillitation::getRequiredNurseSize() const
{
    return requiredNurseSize;
}

const std::string Rehabillitation::getInfo() const
{
    ostringstream oss;
    int i;
    for (i = 0; i < getRequiredEqupiment().size() - 1; i++)
    {
        oss << equipmentToString(getRequiredEqupiment()[i]) << " ";
    }
    oss << equipmentToString(getRequiredEqupiment()[i]);
    return Service::getInfo() + " rehabilitacja potrzebna ilosc pielegniarek: " + to_string(getRequiredNurseSize()) +
         + " potrzebny sprzet:  " + oss.str();
}
