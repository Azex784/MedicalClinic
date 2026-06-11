#ifndef REHABILITATIONCENTRE_CONSULTATIONROOM_H
#define REHABILITATIONCENTRE_CONSULTATIONROOM_H

#include "rooms/Room.h"

namespace RehabClinic
{
	/**
	 * Klasa reprezentująca pokój konsultacyjny
	 */
	class ConsultationRoom : public Room
	{
	public:
		/**
		 * Konstruktor tworzący nowy obiekt sali konsultacyjnej.
		 * @param roomNumber Numer przypisany do gabinetu konsultacyjnego.
		 */
		ConsultationRoom(const unsigned roomNumber);

		/**
		 * Domyślny destruktor klasy.
		 */
		~ConsultationRoom() = default;

		/**
		 * Metoda zwracająca pełne informacje o sali konsultacyjnej.
		 * Nadpisuje metodę wirtualną z klasy bazowej.
		 * @return Sformatowany łańcuch znaków zawierający numer sali oraz jej specyfikacje.
		 */
		const std::string getInfo() const override;

		/**
		 * Sprawdza, czy sala konsultacyjna jest przystosowana posiada dane wyposażenie.
		 * Nadpisuje metodę wirtualną z klasy bazowej.
		 * Z uwagi na charkter tego pokoju moze ono dostrczyc tylko NONE wyposażenie
		 * @param equipment Wymagane wyposażenie do weryfikacji.
		 * @return Wartość true, jeśli w sali można użyć podanego wyposażenia, w przeciwnym razie false.
		 */
		bool canBeUsed(Equipment equipment) const override;
	};
}


#endif //REHABILITATIONCENTRE_CONSULTATIONROOM_H
