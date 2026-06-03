#ifndef REHABILITATIONCENTRE_DOCTOR_H
#define REHABILITATIONCENTRE_DOCTOR_H

#include "personnel/Personnel.h"
#include <vector>

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
     * @param last_name Nazwisko lekarza.
     * @param personnel_id Unikalny identyfikator przypisany do pracownika.
     * @param specialisation Wektor przechowujący listę specjalności lekarza.
     * @param doctor_cost Koszt prestiżu lekarza.
     */
    Doctor(const std::string& name, const std::string& last_name, const unsigned personnel_id,
           const std::vector<Specialisation>& specialisation, const unsigned int doctor_cost);

    /**
     * Domyślny destruktor klasy.
     */
    ~Doctor() = default;

    /**
    * Ustawia koszt prestiżu lekarza.
    * @param doctor_cost Nowy koszt.
    */
    void setDoctorCost(const unsigned int doctor_cost);

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


#endif //REHABILITATIONCENTRE_DOCTOR_H
