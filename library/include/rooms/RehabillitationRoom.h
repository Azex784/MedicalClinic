#ifndef REHABILITATIONCENTRE_REHABILLITATIONROOM_H
#define REHABILITATIONCENTRE_REHABILLITATIONROOM_H

#include "rooms/Room.h"
#include <vector>

//deklaracja wyprzedzająca
enum class Equipment;

/**
 * Klasa reprezentująca pokój do przeprowadzania zabiegów
 * Dziedziczy z klasy Room
 */
class RehabillitationRoom : public Room
{
private:
	std::vector<Equipment> accessibleEqupiment;
	unsigned int maxCapacity;

public:
	/**
	 * Konstruktor tworzący nowy obiekt sali rehabilitacyjnej.
	 * @param roomNumber Numer przypisany do sali rehabilitacyjnej.
	 * @param accessibleEqupiment Wektor przechowujący listę wyposażenia dostępnego w sali.
	 * @param maxCapacity Maksymalna pojemność sali - liczba personelu.
	 */
	RehabillitationRoom(const unsigned roomNumber, const std::vector<Equipment>& accessibleEqupiment,
	                    const unsigned int maxCapacity);

	/**
	 * Domyślny destruktor klasy.
	 */
	~RehabillitationRoom() = default;

	/**
	 * Sprawdza, czy sala rehabilitacyjna dysponuje określonym wyposażeniem.
	 * Nadpisuje metodę wirtualną z klasy bazowej.
	 * @param equipment Wymagane wyposażenie (reprezentowane przez enum Equipment) do weryfikacji.
	 * @return Wartość true, jeśli sala posiada wymagany sprzęt, w przeciwnym razie false.
	 */
	bool canBeUsed(Equipment equipment) const override;

	/**
	 * Metoda zwracająca pełne informacje o sali rehabilitacyjnej.
	 * Nadpisuje metodę wirtualną z klasy bazowej.
	 * @return Sformatowany łańcuch znaków zawierający numer sali, maksymalną pojemność oraz listę sprzętu.
	 */
	const std::string getInfo() const override;

	/**
	 * Zwraca listę wyposażenia dostępnego w sali rehabilitacyjnej.
	 * @return Stała referencja do wektora przechowującego dostępne wyposażenie.
	 */
	const std::vector<Equipment>& getAccessibleEqupiment() const;

	/**
	 * Zwraca maksymalną pojemność sali rehabilitacyjnej.
	 * @return Maksymalna liczba personelu jako liczba całkowita bez znaku.
	 */
	unsigned int getMaxCapacity() const;
};


#endif //REHABILITATIONCENTRE_REHABILLITATIONROOM_H
