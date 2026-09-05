#include "personnel/Nurse.h"
#include "enums/Specialisation.h"

namespace MedicalClinic
{
	using namespace std;

	Nurse::Nurse(const std::string& name, const std::string& lastName, const unsigned personnelId) : Personnel(
		name, lastName, personnelId)
	{
	}

	const std::string Nurse::getInfo() const
	{
		return Personnel::getInfo() + ", pielęgniarka.";
	}
}
