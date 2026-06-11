#include "personnel/Nurse.h"
#include "enums/Specialisation.h"

namespace RehabClinic
{
	using namespace std;

	Nurse::Nurse(const std::string& name, const std::string& lastName, const unsigned personnelId) : Personnel(
		name, lastName, personnelId)
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
}
