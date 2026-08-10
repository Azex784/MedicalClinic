#include "enums/Equipment.h"

using namespace std;

namespace MedicalClinic
{
	const std::string equipmentToString(Equipment eq)
	{
		switch (eq)
		{
			case Equipment::NONE: return "Brak";
			case Equipment::DEFIBRILLATOR: return "Defibrylator";
			case Equipment::ECG_MACHINE: return "Aparat EKG";
			case Equipment::PATIENT_MONITOR: return "Monitor pacjenta";
			case Equipment::VENTILATOR: return "Respirator";
			case Equipment::INFUSION_PUMP: return "Pompa infuzyjna";
			case Equipment::ULTRASOUND_MACHINE: return "Aparat USG";
			case Equipment::X_RAY_MACHINE: return "Aparat RTG";
			case Equipment::CT_SCANNER: return "Tomograf komputerowy";
			case Equipment::MRI_SCANNER: return "Rezonans magnetyczny";
			case Equipment::ANESTHESIA_MACHINE: return "Aparat do znieczulenia";
			case Equipment::SURGICAL_TABLE: return "Stół operacyjny";
			case Equipment::INCUBATOR: return "Inkubator";
			default: return "Unknown";
		}
	}
}
