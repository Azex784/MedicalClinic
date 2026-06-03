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
    for (int i = 0; i < getRequiredEqupiment().size(); i++)
    {
        oss << equipmentToString(getRequiredEqupiment()[i]) << " ";
    }
    return Service::getInfo() + " rehabilitacja potrzebna ilosc pielegniarek: " + to_string(getRequiredNurseSize()) +
         + " potrzebny sprzet:  " + oss.str();
}
