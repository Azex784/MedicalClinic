#ifndef MEDICAL_CLINIC_ROOM_H
#define MEDICAL_CLINIC_ROOM_H

#include <string>
#include "Statusable.h"

namespace MedicalClinic
{
	enum class Equipment;

	/**
	 * Klasa reprezentująca pokój.
	 */
	class Room : public Statusable
	{
	private:
		unsigned int roomNumber;

	public:
	   /**
		* Konstruktor tworzący nowy obiekt sali.
		* @param roomNumber Numer przypisany do sali.
		*/
		Room(const unsigned int roomNumber);

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
		unsigned int getUniqueParameter() const;
	};
}


#endif //MEDICAL_CLINIC_ROOM_H
