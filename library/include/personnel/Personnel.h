#ifndef REHABILITATIONCENTRE_PERSONNEL_H
#define REHABILITATIONCENTRE_PERSONNEL_H

#include <string>
#include <vector>
#include "Person.h"

enum class Specialisation;

/**
 * Klasa reprezentująca personel
 */
class Personnel : public Person{
private:
    bool isActive;
    unsigned int personnelId;
public:
    /**
    * Konstruktor tworzący nowy obiekt personelu.
    * @param name Imię pracownika.
    * @param lastName Nazwisko pracownika.
    * @param personnelId Unikalny identyfikator przypisany do pracownika.
    */
    Personnel(const std::string& name, const std::string& lastName, const unsigned int personnelId);

    /**
     * Domyślny destruktor klasy.
     */
    virtual ~Personnel() = default;

    /**
     * Zmienia status aktywności zawodowej pracownika.
     * * @param is_active Flaga aktywności: true - pracuje, false - nie pracuje.
     */
    void setIsActive(const bool isActive);

    /**
     * Sprawdza, czy pracownik jest obecnie aktywny zawodowo.
     * @return Flaga aktywności: true - pracuje, false - nie pracuje.
     */
    bool getIsActive() const;

    /**
     * Pobiera unikalny identyfikator pracownika.
     * @return Identyfikator personelu jako liczba całkowita.
     */
    unsigned int getUniqueParameter() const;

    /**
     * Czysto wirtualna metoda sprawdzająca, czy pracownik posiada uprawnienia do przeprowadzenia danego leczenia.
     * @param specjalizacja Wymagana specjalizacja do weryfikacji.
     * @return Wartość true, jeśli pracownik może przeprowadzić zabieg, w przeciwnym razie false.
     */
    virtual bool canConductTreatment(Specialisation specjalizacja) const = 0;

    /**
     * Metoda zwracająca pełne informacje o pracowniku personelu.
     * Nadpisuje metodę wirtualną z klasy bazowej.
     * @return Sformatowany łańcuch znaków zawierający dane osobowe, identyfikator oraz status aktywności.
     */
    const std::string getInfo() const override;
};

#endif //REHABILITATIONCENTRE_PERSONNEL_H
