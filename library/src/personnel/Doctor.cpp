#include "personnel/Doctor.h"
#include "enums/Specialisation.h"
#include "enums/Title.h"
#include <cmath>
#include "sstream"

namespace MedicalClinic
{
	using namespace std;

	Doctor::Doctor(const std::string& name, const std::string& lastName, const unsigned personnelId,
		const std::vector<Specialisation>& specialisation, const Title title): Personnel(name, lastName, personnelId),
		                                                                       specialisation(specialisation),
		                                                                       title(title)
	{
		setDoctorRate();
	}

	Title Doctor::getTitle() const
	{
		return title;
	}

	const unsigned int &Doctor::getDoctorRate() const
	{
		return doctorRate;
	}

	const std::vector<Specialisation>& Doctor::getSpecialisation() const
	{
		return specialisation;
	}

	bool Doctor::canConductTreatment(const Specialisation &specjalizacja) const
	{
		for (int i = 0; i < (int)getSpecialisation().size(); i++)
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
		for (int i = 0; i < (int)getSpecialisation().size(); i++)
		{
			if (i != (int)getSpecialisation().size() - 1)
			{
				ss << toString(getSpecialisation()[i]) << ", ";
			}
			else
			{
				ss << toString(getSpecialisation()[i]) << ".";
			}
		}
		return Personnel::getInfo() + ", lekarz o stawce (jako procent zabiegu): " + "" + to_string(getDoctorRate()) + "%, specjalności: " + ss.str();
	}

	void Doctor::setTitle(const Title title)
	{
		this->title = title;
		setDoctorRate();
	}

	void Doctor::setDoctorRate()
	{
		title = getTitle();

		if (title == Title::MD)
		{
			doctorRate = 0;
		}
		else if (title == Title::DR_MED)
		{
			doctorRate = 1;
		}
		else if (title == Title::DR_HAB_MED)
		{
			doctorRate = 2;
		}
		else if (title == Title::PROF)
		{
			doctorRate = 3;
		}
		else
		{
			// Except
		}
	};
}
