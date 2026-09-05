#ifndef MEDICAL_CLINIC_PERSONNEL_H
#define MEDICAL_CLINIC_PERSONNEL_H

#include "Person.h"

namespace MedicalClinic
{

	/**
	 * Klasa reprezentująca pracownika kliniki.
	 */
	class Personnel : public Person
	{
    private:
			unsigned int personnelId;

    public:
		 /**
	    *Konstruktor tworzący nowy obiekt personelu.
	    *@param name Imię pracownika.
	    *@param lastName Nazwisko pracownika.
	    *@param personnelId Unikalny identyfikator przypisany do pracownika.
	    */
	    Personnel(const std::string& name, const std::string& lastName, const unsigned int personnelId);

		 /**
      * Domyślny destruktor abstrakcyjny klasy.
      */
			virtual ~Personnel() = default;

     /**
      * Pobiera unikalny identyfikator pracownika.
      * @return Identyfikator personelu jako liczba całkowita.
      */
      const unsigned int &getUniqueParameter() const;

		 /**
      * Metoda zwracająca pełne informacje o pracowniku personelu.
      * Nadpisuje metodę wirtualną z klasy bazowej.
      * @return Sformatowany łańcuch znaków zawierający dane osobowe, identyfikator oraz status aktywności.
      */
      const std::string getInfo() const override;
    };
}

#endif //MEDICAL_CLINIC_PERSONNEL_H
