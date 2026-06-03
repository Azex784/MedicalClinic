#include "personnel/Doctor.h"
#include "enums/Specialisation.h"
#include "sstream"

using namespace std;

Doctor::Doctor(const std::string& name, const std::string& last_name, const unsigned personnel_id,
               const std::vector<Specialisation>& specialisation,
               const unsigned int doctor_cost) : Personnel(name, last_name, personnel_id),
                                                 specialisation(specialisation),
                                                 doctorCost(doctor_cost)
{
}

void Doctor::setDoctorCost(const unsigned int doctor_cost)
{
	doctorCost = doctor_cost;
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
	return Personnel::getInfo() + " doktor o cenie prestizu: " + to_string(getDoctorCost()) + " specjalnosci: " + ss.
		str();
};
