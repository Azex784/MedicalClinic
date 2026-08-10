#include "enums/Specialisation.h"

using namespace std;

namespace MedicalClinic
{
	const string specialisationToString(Specialisation spec)
	{
		switch (spec)
		{
			case Specialisation::CARDIOLOGIST: return "Kardiolog";
			case Specialisation::NEUROLOGIST: return "Neurolog";
			case Specialisation::ONCOLOGIST: return "Onkolog";
			case Specialisation::PEDIATRICIAN: return "Pediatra";
			case Specialisation::GENERAL_SURGEON: return "Chirurg ogólny";
			case Specialisation::ANESTHESIOLOGIST: return "Anestezjolog";
			case Specialisation::RADIOLOGIST: return "Radiolog";
			case Specialisation::OPHTHALMOLOGIST: return "Okulista";
			case Specialisation::GYNECOLOGIST: return "Ginekolog";
			case Specialisation::UROLOGIST: return "Urolog";
			case Specialisation::PULMONOLOGIST: return "Pulmonolog";
			case Specialisation::GASTROENTEROLOGIST: return "Gastroenterolog";
			case Specialisation::ENDOCRINOLOGIST: return "Endokrynolog";
			case Specialisation::NEPHROLOGIST: return "Nefrolog";
			case Specialisation::HEMATOLOGIST: return "Hematolog";
			case Specialisation::ORTHOPEDIST: return "Ortopeda";
			case Specialisation::DERMATOLOGIST: return "Dermatolog";
			case Specialisation::PSYCHIATRIST: return "Psychiatra";
			case Specialisation::INTERNIST: return "Internista";
			case Specialisation::EMERGENCY_PHYSICIAN: return "Lekarz medycyny ratunkowej";
			case Specialisation::LARYNGOLOGIST: return "Laryngolog";
			default: return "Unknown";
		}
	}
}