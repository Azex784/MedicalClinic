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

Rehabillitation::Rehabillitation(const unsigned service_cost, const unsigned service_duration,
    const std::string& service_name, const unsigned service_id, const unsigned required_doctor_size,
    const Specialisation required_doctor_spec, const std::vector<Equipment>& required_equpiment,
    const unsigned int required_nurse_size): Service(service_cost, service_duration, service_name, service_id, required_doctor_size, required_doctor_spec),
                                             requiredEqupiment(required_equpiment),
                                             requiredNurseSize(required_nurse_size)
{
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
    return Service::getInfo() + ", rehabilitacja, potrzebna ilosc pielegniarek: " + to_string(getRequiredNurseSize()) +
         + ", potrzebny sprzet: " + oss.str();
}
