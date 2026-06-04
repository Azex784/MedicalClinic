#ifndef REHABILITATIONCENTRE_REHABILLITATION_H
#define REHABILITATIONCENTRE_REHABILLITATION_H

#include <string>
#include <vector>
#include "Service.h"

enum class Equipment;

/**
 * Klasa reprezentująca zabieg rehabilitacji.
 * Dziedzczy ona z klasy Service.
 */
class Rehabillitation : public Service
{
private:
	std::vector<Equipment> requiredEqupiment;
	unsigned int requiredNurseSize;

public:

	/**
	 * Konstruktor tworzący nowy obiekt zabiegu rehabilitacyjnego.
	 * @param service_cost Koszt wykonania zabiegu.
	 * @param service_duration Czas trwania zabiegu w minutach.
	 * @param service_name Nazwa zabiegu rehabilitacyjnego.
	 * @param service_id Unikalny identyfikator usługi.
	 * @param required_doctor_size Wymagana liczba lekarzy nadzorujących zabieg.
	 * @param required_doctor_spec Wymagana specjalizacja lekarza do przeprowadzenia zabiegu.
	 * @param required_equpiment Wektor przechowujący listę specjalistycznego sprzętu niezbędnego do wykonania zabiegu.
	 * @param required_nurse_size Wymagana liczba pielęgniarek lub personelu pomocniczego niezbędna do obsługi zabiegu.
	 */
	Rehabillitation(const unsigned service_cost, const unsigned service_duration, const std::string& service_name,
		const unsigned service_id, const unsigned required_doctor_size, const Specialisation required_doctor_spec,
		const std::vector<Equipment>& required_equpiment, const unsigned int required_nurse_size);

	/**
	 * Domyślny destruktor klasy.
	 * Nadpisuje wirtualny destruktor z klasy bazowej.
	 */
	~Rehabillitation() override = default;

	/**
	 * Metoda zwracająca pełne informacje o usłudze rehabilitacyjnej.
	 * Nadpisuje metodę wirtualną z klasy bazowej (Service).
	 * @return Sformatowany łańcuch znaków zawierający specyfikację zabiegu, wymagany sprzęt i potrzebny personel.
	*/
	const std::string getInfo() const override;

	/**
	 * Zwraca wymaganą liczbę pielęgniarek niezbędną do  przeprowadzenia usługi rehabilitacyjnej.
	 * @return Wymagana liczba personelu pomocniczego jako unsigned int.
	 */
	unsigned int getRequiredNurseSize() const;

	/**
	 * Zwraca listę specjalistycznego wyposażenia niezbędnego do realizacji tej usługi rehabilitacyjnej.
	 * @return Stała referencja do wektora przechowującego wymagany sprzęt.
	 */
	const std::vector<Equipment>& getRequiredEqupiment() const;
};

#endif //REHABILITATIONCENTRE_REHABILLITATION_H