#include "enums/Title.h"

using namespace std;

namespace MedicalClinic
{
	const std::string toString(Title title)
	{
		switch (title)
		{
			case Title::MD: return "Lekarz";
			case Title::DR_MED: return "Doktor";
			case Title::DR_HAB_MED: return "Doktor habilitowany";
			case Title::PROF: return "Profesor";
			default: return "Unknown";
		}
	}
}
