#include "personnel/Personnel.h"
#include "sstream"

using namespace std;

bool Personnel::getIsActive() const
{
    return isActive;
}

unsigned int Personnel::getPersonnelId() const
{
    return personnelId;
}

Personnel::Personnel(const std::string& name, const std::string& last_name, const unsigned int personnel_id): Person(name, last_name),
    personnelId(personnel_id)
{
}

void Personnel::setIsActive(const bool is_active)
{
    isActive = is_active;
}

const std::string Personnel::getInfo() const
{
    return Person::getInfo() + " personel";
}
