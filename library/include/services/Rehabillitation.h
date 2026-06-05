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
	 * @param serviceCost Koszt wykonania zabiegu.
	 * @param serviceDuration Czas trwania zabiegu w minutach.
	 * @param serviceName Nazwa zabiegu rehabilitacyjnego.
	 * @param serviceId Unikalny identyfikator usługi.
	 * @param requiredDoctorSize Wymagana liczba lekarzy nadzorujących zabieg.
	 * @param requiredDoctorSpec Wymagana specjalizacja lekarza do przeprowadzenia zabiegu.
	 * @param requiredEqupiment Wektor przechowujący listę specjalistycznego sprzętu niezbędnego do wykonania zabiegu.
	 * @param requiredNurseSize Wymagana liczba pielęgniarek lub personelu pomocniczego niezbędna do obsługi zabiegu.
	 */
	Rehabillitation(const unsigned serviceCost, const unsigned serviceDuration, const std::string& serviceName,
		const unsigned serviceId, const unsigned requiredDoctorSize, const Specialisation requiredDoctorSpec,
		const std::vector<Equipment>& requiredEqupiment, const unsigned int requiredNurseSize);

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