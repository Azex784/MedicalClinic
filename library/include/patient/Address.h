#ifndef REHABILITATIONCENTRE_ADDRESS_H
#define REHABILITATIONCENTRE_ADDRESS_H

#include <string>

namespace RehabClinic
{/**
 * Klasa reprezentująca adres
 */
    class Address
    {
    private:
        std::string city;
        std::string street;
        std::string number;

    public:
        /**
        * Konstruktor tworzący nowy obiekt adresu.
        * @param city Nazwa miasta.
        * @param street Nazwa ulicy.
        * @param number Numer budynku.
        */
        Address(const std::string& city, const std::string& street, const std::string& number);

        /**
        * Domyślny destruktor klasy.
        */
        ~Address() = default;

        /**
        * Metoda zwracająca pełne informacje o adresie.
        * @return Sformatowany łańcuch znaków zawierający miasto, ulicę oraz numer.
        */
        const std::string getInfo() const;

        /**
	     * Pobiera nazwę miasta.
	     * @return Stała referencja do łańcucha znaków przechowującego miasto.
	     */
        const std::string& getCity() const;

        /**
	     * Pobiera nazwę ulicy.
	     * @return Stała referencja do łańcucha znaków przechowującego ulicę.
	     */
        const std::string& getStreet() const;

        /**
	     * Pobiera numer budynku.
	     * @return Stała referencja do łańcucha znaków przechowującego numer.
	     */
        const std::string& getNumber() const;
    };
}

#endif //REHABILITATIONCENTRE_ADDRESS_H