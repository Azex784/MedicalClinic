#include "enums/Specialisation.h"

using namespace std;


const string specialisationToString(Specialisation spec)
{
	switch (spec)
	{
	case Specialisation::PHYSIOTHERAPIST: return "Fizjoterapeuta";
	case Specialisation::ORTHOPEDIST: return "Ortopeda";
	case Specialisation::NEUROLOGIST: return "Neurolog";
	case Specialisation::SPORTS_MEDICINE: return "Medycyna sportowa";
	case Specialisation::OSTEOPATH: return "Osteopata";
	case Specialisation::MASSAGE_THERAPIST: return "Masażysta";
	case Specialisation::RHEUMATOLOGIST: return "Reumatolog";
	default: return "Nieznana specjalizacja";
	}
}
