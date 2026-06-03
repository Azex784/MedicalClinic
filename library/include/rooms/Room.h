#ifndef REHABILITATIONCENTRE_ROOM_H
#define REHABILITATIONCENTRE_ROOM_H
#include <string>

//deklaracja wyprzedzająca
enum class Equipment;

/**
 * Klasa reprezentująca pokój
 */
class Room
{
private:
	unsigned int roomNumber;
	bool isActive;
	bool isArchive;

public:
	/**
	* Konstruktor tworzący nowy obiekt sali.
	* @param room_number Numer przypisany do sali.
	*/
	Room(const unsigned int room_number);

	/**
	 * Domyślny destruktor klasy.
	 */
	virtual ~Room() = default;

	/**
	 * Metoda wirtualna zwracająca podstawowe informacje o sali.
	 * @return Sformatowany łańcuch znaków zawierający numer sali oraz jej status.
	 */
	virtual const std::string getInfo() const;

	/**
	 * Czysto wirtualna metoda sprawdzająca, czy sala jest przystosowana do użycia określonego wyposażenia.
	 * @param equipment Wymagane wyposażenie (reprezentowane przez enum Equipment) do weryfikacji.
	 * @return Wartość true, jeśli w sali jest dane wyposażenie, w przeciwnym razie false.
	 */
	virtual bool canBeUsed(Equipment equipment) const = 0;

	/**
	 * Pobiera numer sali.
	 * @return Numer sali jako unsigned int.
	 */
	unsigned int getRoomNumber() const;

	/**
	 * Sprawdza, czy sala jest obecnie dostępna.
	 * @return Wartość true, jeśli sala jest aktywna, w przeciwnym razie false.
	 */
	bool getIsActive() const;

	/**
	 * Sprawdza, czy sala została przeniesiona do archiwum.
	 * @return Wartość true, jeśli sala jest zarchiwizowana, w przeciwnym razie false.
	 */
	bool getIsArchive() const;

	/**
	* Zmienia status aktywności sali.
	* @param is_active Flaga określająca
	*/
	void setIsActive(const bool is_active);

	/**
	 * Zmienia status archiwizacji sali.
	 * @param is_archive Flaga logiki
	 */
	void setIsArchive(const bool is_archive);
};


#endif //REHABILITATIONCENTRE_ROOM_H
