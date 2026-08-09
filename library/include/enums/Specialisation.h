#ifndef MEDICAL_CLINIC_SPECIALISATION_H
#define MEDICAL_CLINIC_SPECIALISATION_H

#include <string>

namespace MedicalClinic
{
/**
 * Typ wyliczeniowy zawierajcy specjalizacje
 */
	enum class Specialisation
	{
		CARDIOLOGIST,
		NEUROLOGIST,
		ONCOLOGIST,
		PEDIATRICIAN,
		GENERAL_SURGEON,
		ANESTHESIOLOGIST,
		RADIOLOGIST,
		OPHTHALMOLOGIST,
		GYNECOLOGIST,
		UROLOGIST,
		PULMONOLOGIST,
		GASTROENTEROLOGIST,
		ENDOCRINOLOGIST,
		NEPHROLOGIST,
		HEMATOLOGIST,
		ORTHOPEDIST,
		DERMATOLOGIST,
		PSYCHIATRIST,
		INTERNIST,
		EMERGENCY_PHYSICIAN,
		LARYNGOLOGIST
	};

	//Konwersja do stringa
	const std::string specialisationToString(Specialisation spec);
}


#endif //MEDICAL_CLINIC_SPECIALISATION_H
