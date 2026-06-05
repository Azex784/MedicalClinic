#ifndef REHABILITATIONCENTRE_PERSON_H
#define REHABILITATIONCENTRE_PERSON_H

#include <string>

/**
 * Klasa reprezentująca człowieka
 */
class Person
{
private:
    std::string name;
    std::string lastName;
    bool isArchive = 0;

public:
    /**
    * Metoda wirtualna zwracająca informacje o osobie.
    * @return Sformatowany łańcuch znaków zawierający dane osoby.
    */
    virtual const std::string getInfo() const;

    /**
     * Konstruktor tworzący nowy obiekt osoby.
     * @param name Imię osoby.
     * @param last_name Nazwisko osoby.
     */
    Person(const std::string& name, const std::string& last_name);

    /**
     * Domyślny destruktor klasy.
     */
    virtual ~Person() = default;

    /**
     * Pobiera imię osoby.
     * @return Stała referencja do łańcucha znaków przechowującego imię.
     */
    const std::string& getName() const;

    /**
     * Ustawia nowe imię osoby.
     * @param name Nowe imię, które ma zostać przypisane do zmiennej imie.
     */
    void setName(const std::string& name);

    /**
     * Ustawia nowe nazwisko osoby.
     * @param last_name Nowe nazwisko, które ma zostać przypisane do zmiennej nazwisko.
     */
    void setLastName(const std::string& last_name);

    /**
     * Zmienia status archiwizacji osoby.
     * @param is_archive
     */
    void setIsArchive(const bool is_archive);

    /**
     * Pobiera nazwisko osoby.
     * @return Stała referencja do łańcucha znaków przechowującego nazwisko.
     */
    const std::string& getLastName() const;

    /**
     * Sprawdza status archiwizacji osoby.
     * @return Wartość logiczna Archive.
     */
    bool getIsArchive() const;
};


#endif //REHABILITATIONCENTRE_PERSON_H
