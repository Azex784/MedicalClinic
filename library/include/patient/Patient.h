#ifndef REHABILITATIONCENTRE_PATIENT_H
#define REHABILITATIONCENTRE_PATIENT_H

#include <string>
#include "Person.h"
#include "typedefs.h"

/**
 * Klasa reprezentująca pacjenta dziedziczy z klasy Person
 */
class Patient : public Person
{
private:
    std::string personalNumber;
    AddressPtr address;

public:
    /**
    * Konstruktor tworzący nowy obiekt pacjenta.
    * @param name Imię pacjenta.
    * @param last_name Nazwisko pacjenta.
    * @param personal_number PESEL pacjenta - niezmienialny.
    * @param address Wskaźnik na obiekt adresu przypisany do pacjenta.
    */
    Patient(const std::string& name, const std::string& last_name, const std::string& personal_number,
            const AddressPtr& address);

    /**
     * Domyślny destruktor klasy.
     */
    ~Patient() = default;

    /**
     * Pobiera unikalny numer identyfikacyjny pacjenta.
     * @return Stała referencja do łańcucha znaków przechowującego numer pacjenta.
     */
    const std::string& getUniqueParameter() const;

    /**
     * Pobiera adres przypisany do pacjenta.
     * @return Stała referencja na inteligentny wskaźnik adresu.
     */
    const AddressPtr& getAddress() const;

    /**
     * Metoda zwracająca pełne informacje o pacjencie.
     * Nadpisuje metode wirtualną z klasy bazowej.
     * @return Łańcuch znaków zawierający dane osobowe pacjenta i jego adres.
     */
    const std::string getInfo() const override;
};


#endif //REHABILITATIONCENTRE_PATIENT_H
