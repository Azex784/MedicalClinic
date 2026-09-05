#ifndef MEDICAL_CLINIC_NURSE_H
#define MEDICAL_CLINIC_NURSE_H

#include "personnel/Personnel.h"

namespace MedicalClinic
{
   /**
	* Klasa reprezentująca pielęgniarkę.
	* Dziedziczy ona z klasy Perosnnel
	*/
	class Nurse : public Personnel
	{
	public:
	   /**
		* Konstruktor tworzący nowy obiekt pielęgniarki.
		* @param name Imię pielęgniarki.
		* @param lastName Nazwisko pielęgniarki.
		* @param personnelId Unikalny identyfikator przypisany do pracownika.
		*/
		Nurse(const std::string& name, const std::string& lastName, const unsigned personnelId);

	   /**
	    * Domyślny destruktor klasy.
	    */
	    ~Nurse() = default;

	   /**
		* Metoda zwracająca pełne informacje o pielęgniarce.
		* Nadpisuje metodę wirtualną z klasy bazowej.
		* @return Sformatowany łańcuch znaków zawierający dane osobowe oraz identyfikator pielęgniarki.
		*/
		const std::string getInfo() const override;
    };
}


#endif //MEDICAL_CLINIC_NURSE_H