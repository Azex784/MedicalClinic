#include "enums/Equipment.h"

using namespace std;

namespace RehabClinic
{
	const std::string equipmentToString(Equipment eq)
	{
		switch (eq)
		{
		case Equipment::NONE: return "Brak";
		case Equipment::PHYSICAL_THERAPY_DEVICE: return "Urządzenie do fizykoterapii";
		case Equipment::KINESITHERAPY_SPACE: return "Przestrzeń do kinezyterapii";
		case Equipment::ROBOTIC_SYSTEM: return "System zrobotyzowany";
		default: return "Unknown";
		}
	}
}
