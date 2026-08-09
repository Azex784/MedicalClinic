#ifndef MEDICAL_CLINIC_DOCTOR_H
#define MEDICAL_CLINIC_DOCTOR_H

#include "personnel/Personnel.h"
#include <vector>

namespace MedicalClinic
{

	enum class Specialisation;

	class Doctor : public Personnel
	{
	private:
		std::vector<Specialisation> specialisation;
		unsigned int doctorCost;

	public:
		/**
	     * Konstruktor tworzący nowy obiekt lekarza.
	     * @param name Imię lekarza.
	     * @param lastName Nazwisko lekarza.
	     * @param personnelId Unikalny identyfikator przypisany do pracownika.
	     * @param specialisation Wektor przechowujący listę specjalności lekarza.
	     * @param doctorCost Koszt prestiżu lekarza.
	     */
		Doctor(const std::string& name, const std::string& lastName, const unsigned personnelId,
		       const std::vector<Specialisation>& specialisation, const unsigned int doctorCost);

		/**
	     * Domyślny destruktor klasy.
	     */
		~Doctor() = default;

		/**
	    * Ustawia koszt prestiżu lekarza.
	    * @param doctor_cost Nowy koszt.
	    */
		void setDoctorCost(const unsigned int doctorCost);

		/**
	     * Pobiera listę specjalizacji posiadanych przez lekarza.
	     * @return Stała referencja do wektora przechowującego specjalizacje.
	     */
		const std::vector<Specialisation>& getSpecialisation() const;

		/**
	     * Pobiera aktualny koszt usługi przypisany do lekarza.
	     * @return Koszt przypisany do lekarza jako unsigned int.
	     */
		unsigned int getDoctorCost() const;

		/**
	     * Sprawdza, czy lekarz posiada odpowiednią specjalizację do przeprowadzenia danego zabiegu.
	     * Nadpisuje metodę wirtualną z klasy bazowej.
	     * @param specjalizacja Wymagana specjalizacja do weryfikacji.
	     * @return Wartość true, jeśli lekarz może przeprowadzic zabieg, w przeciwnym razie false.
	     */
		bool canConductTreatment(Specialisation specjalizacja) const override;

		/**
	     * Metoda zwracająca pełne informacje o lekarzu.
	     * Nadpisuje metodę wirtualną z klasy bazowej.
	     * @return Sformatowany łańcuch znaków zawierający dane osobowe lekarza, jego koszt oraz specjalizacje.
	     */
		const std::string getInfo() const override;
	};
}


#endif //MEDICAL_CLINIC_DOCTOR_H
