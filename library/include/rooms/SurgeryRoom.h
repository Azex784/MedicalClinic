#ifndef MEDICAL_CLINIC_SURGERYROOM_H
#define MEDICAL_CLINIC_SURGERYROOM_H

#include "rooms/Room.h"
#include <vector>

namespace MedicalClinic
{
	enum class Equipment;

	/**
	 * Klasa reprezentująca pokój do przeprowadzania zabiegów.
	 * Dziedziczy z klasy Room.
	 */
	class SurgeryRoom : public Room
	{
	private:
		std::vector<Equipment> accessibleEqupiment;
		unsigned int maxCapacity;

	public:
		/**
		 * Konstruktor tworzący nowy obiekt sali operacyjnej.
		 * @param roomNumber Numer przypisany do sali operacyjnej.
		 * @param accessibleEqupiment Wektor przechowujący listę wyposażenia dostępnego w sali.
		 * @param maxCapacity Maksymalna pojemność sali - liczba personelu.
		 */
		SurgeryRoom(const unsigned roomNumber, const std::vector<Equipment>& accessibleEqupiment,
		                    const unsigned int maxCapacity);

		/**
		 * Domyślny destruktor klasy.
		 */
		~SurgeryRoom() = default;

		/**
		 * Sprawdza, czy sala rehabilitacyjna dysponuje określonym wyposażeniem.
		 * Nadpisuje metodę wirtualną z klasy bazowej.
		 * @param equipment Wymagane wyposażenie (reprezentowane przez enum Equipment) do weryfikacji.
		 * @return Wartość true, jeśli sala posiada wymagany sprzęt, w przeciwnym razie false.
		 */
		bool canBeUsed(Equipment equipment) const override;

		/**
		 * Metoda zwracająca pełne informacje o sali operacyjnej.
		 * Nadpisuje metodę wirtualną z klasy bazowej.
		 * @return Sformatowany łańcuch znaków zawierający numer sali, maksymalną pojemność oraz listę sprzętu.
		 */
		const std::string getInfo() const override;

		/**
		 * Zwraca listę wyposażenia dostępnego w sali operacyjnej.
		 * @return Stała referencja do wektora przechowującego dostępne wyposażenie.
		 */
		const std::vector<Equipment>& getAccessibleEqupiment() const;

		/**
		 * Zwraca maksymalną pojemność sali operacyjnej.
		 * @return Maksymalna liczba personelu jako liczba całkowita bez znaku.
		 */
		unsigned int getMaxCapacity() const;
	};
}

#endif //MEDICAL_CLINIC_SURGERYROOM_H
