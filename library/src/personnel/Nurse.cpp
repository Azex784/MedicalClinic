#include "../../include/personnel/Nurse.h"
#include "enums/Specialisation.h"

using namespace std;

Nurse::Nurse(const std::string& name, const std::string& last_name, const unsigned personnel_id): Personnel(name, last_name, personnel_id)
{
}

bool Nurse::canConductTreatment(Specialisation specjalizacja) const
{
    if (specjalizacja != Specialisation::NEUROLOGIST)
    {
        return true;
    }
    return false;
}

const std::string Nurse::getInfo() const
{
    return Personnel::getInfo() + " pielegniarka";
}
