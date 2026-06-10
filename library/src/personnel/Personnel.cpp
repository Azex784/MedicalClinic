#include "personnel/Personnel.h"
#include "sstream"

using namespace std;

bool Personnel::getIsActive() const
{
	return isActive;
}

unsigned int Personnel::getUniqueParameter() const
{
	return personnelId;
}

Personnel::Personnel(const std::string& name, const std::string& lastName, const unsigned int personnelId) :
	Person(name, lastName),
	personnelId(personnelId)
{
	setIsActive(1);
}

void Personnel::setIsActive(const bool isActive)
{
	this->isActive = isActive;
}

const std::string Personnel::getInfo() const
{
	string tmp;
	if (getIsActive())
	{
		tmp = "aktywyny zawodowo";
	}else
	{
		tmp = "niedostępny";
	}

	return Person::getInfo() + " pracownik personelu, " + tmp;
}
