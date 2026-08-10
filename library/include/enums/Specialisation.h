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

	/**
	 * Funckja przekształcająca do postaci stringa typ status
	 * @param spec
	 * @return
	 */
	const std::string toString(Specialisation spec);

	/**
	 * Operator przeciązaenia.
	 * Podczas wypisywania wywołuje funkcje toString.
	 * @param os
	 * @param spec
	 * @return
	 */
	std::ostream& operator<<(std::ostream& os, const Specialisation& spec);
}


#endif //MEDICAL_CLINIC_SPECIALISATION_H
