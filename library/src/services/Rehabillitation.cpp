#include "services/Rehabillitation.h"
#include "enums/Equipment.h"
#include <sstream>

namespace MedicalClinic
{

    using namespace std;

    const std::vector<Equipment>& Rehabillitation::getRequiredEqupiment() const
    {
        return requiredEqupiment;
    }

    unsigned int Rehabillitation::getRequiredNurseSize() const
    {
        return requiredNurseSize;
    }

    Rehabillitation::Rehabillitation(const unsigned serviceCost, const unsigned serviceDuration,
                                     const std::string& serviceName, const unsigned serviceId,
                                     const unsigned requiredDoctorSize,
                                     const Specialisation requiredDoctorSpec,
                                     const std::vector<Equipment>& requiredEqupiment,
                                     const unsigned int requiredNurseSize) : Service(serviceCost, serviceDuration,
                                                                                 serviceName, serviceId,
                                                                                 requiredDoctorSize,
                                                                                 requiredDoctorSpec),
                                                                             requiredEqupiment(requiredEqupiment),
                                                                             requiredNurseSize(requiredNurseSize)
    {
    }

    const std::string Rehabillitation::getInfo() const
    {
        ostringstream oss;
        int i;
        for (i = 0; i < (int)getRequiredEqupiment().size() - 1; i++)
        {
            oss << equipmentToString(getRequiredEqupiment()[i]) << " ";
        }
        oss << equipmentToString(getRequiredEqupiment()[i]);
        return Service::getInfo() + ", rehabilitacja, potrzebna ilosc pielegniarek: " + to_string(
                getRequiredNurseSize()) +
            +", potrzebny sprzet: " + oss.str();
    }
}
