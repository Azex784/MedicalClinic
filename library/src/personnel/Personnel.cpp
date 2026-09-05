#include "personnel/Personnel.h"
#include "sstream"

namespace MedicalClinic
{
	using namespace std;

	const unsigned int &Personnel::getUniqueParameter() const
	{
		return personnelId;
	}

	Personnel::Personnel(const std::string& name, const std::string& lastName, const unsigned int personnelId) :
		Person(name, lastName),
		personnelId(personnelId)
	{
	}

	const std::string Personnel::getInfo() const
	{
		string tmp;
		if (isAvailable())
		{
			tmp = ", aktywyny/a zawodowo";
		}
		else
		{
			tmp = ", niedostępny/a";
		}

		return Person::getInfo() + ", pracownik personelu, numer pracownika: " + to_string(personnelId) + tmp;
	}
}
