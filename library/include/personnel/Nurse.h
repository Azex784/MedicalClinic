#ifndef REHABILITATIONCENTRE_NURSE_H
#define REHABILITATIONCENTRE_NURSE_H

#include "personnel/Personnel.h"

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
     * Zakladam proste założenie, że jeśli każda pielęgniarka posiada kążdą specjalizacje
     * oprócz neurologicznej, którą może wykonać tylko lekarz
     * Nadpisuje metodę wirtualną z klasy bazowej.
     * @param specjalizacja Wymagana specjalizacja do weryfikacji.
     * @return Wartość true, jesli specjalizacja nie jest neurologiczna
     *  ewneutlanie moge to nadpisac
     */
    bool canConductTreatment(Specialisation specjalizacja) const override;

    /**
     * Metoda zwracająca pełne informacje o pielęgniarce.
     * Nadpisuje metodę wirtualną z klasy bazowej.
     * @return Sformatowany łańcuch znaków zawierający dane osobowe oraz identyfikator pielęgniarki.
     */
    const std::string getInfo() const override;
};


#endif //REHABILITATIONCENTRE_NURSE_H