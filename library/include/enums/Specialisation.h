#ifndef REHABILITATIONCENTRE_SPECIALISATION_H
#define REHABILITATIONCENTRE_SPECIALISATION_H

#include <string>

namespace RehabClinic
{/**
 * Typ wyliczeniowy zawierajcy specjalizacje
 */
	enum class Specialisation
	{
		PHYSIOTHERAPIST,
		ORTHOPEDIST,
		NEUROLOGIST,
		SPORTS_MEDICINE,
		OSTEOPATH,
		MASSAGE_THERAPIST,
		RHEUMATOLOGIST
	};

	//Konwersja do stringa
	const std::string specialisationToString(Specialisation spec);
}


#endif //REHABILITATIONCENTRE_SPECIALISATION_H
