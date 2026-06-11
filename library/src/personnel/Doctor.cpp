#include "personnel/Doctor.h"
#include "enums/Specialisation.h"
#include "sstream"

namespace RehabClinic
{

	using namespace std;

	Doctor::Doctor(const std::string& name, const std::string& lastName, const unsigned personnelId,
	               const std::vector<Specialisation>& specialisation,
	               const unsigned int doctorCost) : Personnel(name, lastName, personnelId),
	                                                specialisation(specialisation),
	                                                doctorCost(doctorCost)
	{
	}

	void Doctor::setDoctorCost(const unsigned int doctorCost)
	{
		this->doctorCost = doctorCost;
	}

	const std::vector<Specialisation>& Doctor::getSpecialisation() const
	{
		return specialisation;
	}

	unsigned int Doctor::getDoctorCost() const
	{
		return doctorCost;
	}

	bool Doctor::canConductTreatment(Specialisation specjalizacja) const
	{
		for (int i = 0; i < getSpecialisation().size(); i++)
		{
			if (specjalizacja == getSpecialisation()[i])
			{
				return true;
			}
		}
		return false;
	}

	const std::string Doctor::getInfo() const
	{
		ostringstream ss;
		for (int i = 0; i < getSpecialisation().size(); i++)
		{
			if (i != getSpecialisation().size() - 1)
			{
				ss << specialisationToString(getSpecialisation()[i]) << " ";
			}
			else
			{
				ss << specialisationToString(getSpecialisation()[i]);
			}
		}
		return Personnel::getInfo() + " doktor o cenie prestizu: " + to_string(getDoctorCost()) + " specjalnosci: " + ss
			.
			str();
	};
}
