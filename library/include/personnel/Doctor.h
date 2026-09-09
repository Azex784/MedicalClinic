#ifndef MEDICAL_CLINIC_DOCTOR_H
#define MEDICAL_CLINIC_DOCTOR_H

#include "personnel/Personnel.h"
#include <vector>

namespace MedicalClinic
{
	enum class Specialisation;
	enum class Title;

	class Doctor : public Personnel
	{
	private:
		std::vector<Specialisation> specialisation;
		Title title;
		unsigned int doctorRate;

	   /**
		* Wyznacza procentowy koszt lekarza na podstawie tytułu naukowego.
		* MD - 0.0
		* DR_MED - 0.01
		* DR_HAB_MED - 0.02
		* PROF - 0.03
		*/
		void setDoctorRate();
	public:
	   /**
		* Konstruktor tworzący nowy obiekt lekarza.
		* @param name Imię lekarza.
		* @param lastName Nazwisko lekarza.
		* @param personnelId Unikalny identyfikator przypisany do pracownika.
		* @param specialisation Wektor przechowujący listę specjalności lekarza.
		* @param title Tytuł naukowy lekarza.
		*/
		Doctor(const std::string& name, const std::string& lastName, const unsigned int personnelId,
			const std::vector<Specialisation>& specialisation, const Title title);

	   /**
		* Domyślny destruktor klasy.
		*/
	    ~Doctor() = default;

	   /**
		* Zwraca aktualny tytuł naukowy przypisany do lekarza.
		* @return Koszt przypisany do lekarza jako unsigned int.
		*/
		Title getTitle() const;

	   /**
		* Zwraca aktualny koszt usługi przypisany do lekarza.
		* @return Koszt przypisany do lekarza jako float.
		*/
		const unsigned int &getDoctorRate() const;

	   /**
		* Zmienia aktualny tytuł naukowy przypisany do lekarza.
		* @return Koszt przypisany do lekarza jako unsigned int.
		*/
		void setTitle(const Title& title);

	   /**
		* Zwraca listę specjalizacji posiadanych przez lekarza.
		* @return Stała referencja do wektora przechowującego specjalizacje.
		*/
		const std::vector<Specialisation>& getSpecialisation() const;

	   /**
		* Metoda zwracająca pełne informacje o lekarzu.
		* Nadpisuje metodę wirtualną z klasy bazowej.
		* @return Sformatowany łańcuch znaków zawierający dane osobowe lekarza, jego koszt oraz specjalizacje.
		*/
		const std::string getInfo() const override;

	   /**
		* Sprawdza, czy lekarz posiada odpowiednią specjalizację do przeprowadzenia danego zabiegu.
		* Nadpisuje metodę wirtualną z klasy bazowej.
		* @param specjalizacja Wymagana specjalizacja do weryfikacji.
		* @return Wartość true, jeśli lekarz może przeprowadzic zabieg, w przeciwnym razie false.
		*/
	    bool canConductTreatment(const Specialisation &specjalizacja) const;
	};
}


#endif //MEDICAL_CLINIC_DOCTOR_H
