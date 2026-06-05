#ifndef REHABILITATIONCENTRE_CONSULTATION_H
#define REHABILITATIONCENTRE_CONSULTATION_H

#include <string>
#include "services/Service.h"

/**
 * Klasa reprezentująca konsultacje.
 * Dziedziczy ona z klasy Servide
 */
class Consultation : public Service
{
private:
	std::string topic;
	bool isOnline;

public:
	/**
	 * Konstruktor tworzący nowy obiekt konsultacji.
	 * @param serviceCost Koszt przeprowadzenia konsultacji.
	 * @param serviceDuration Przewidywany czas trwania konsultacji w minutach.
	 * @param serviceName Nazwa usługi konsultacyjnej.
	 * @param serviceId Unikalny identyfikator usługi.
	 * @param requiredDoctorSize Wymagana liczba lekarzy do przeprowadzenia konsultacji.
	 * @param requiredDoctorSpec Wymagana specjalizacja lekarza prowadzącego konsultację.
	 * @param topic Główny temat.
	 * @param isOnline Flaga logiki: true oznacza, że konsultacja odbywa się zdalnie (online), false oznacza wizytę stacjonarną.
	 */
	Consultation(const unsigned serviceCost, const unsigned serviceDuration, const std::string& serviceName,
	             const unsigned serviceId, const unsigned requiredDoctorSize,
	             const Specialisation requiredDoctorSpec,
	             const std::string& topic, const bool isOnline);

	/**
	 * Domyślny destruktor klasy.
	 */
	~Consultation() = default;

	/**
	 * Metoda zwracająca pełne informacje o konsultacji.
	 * Nadpisuje metodę wirtualną z klasy bazowej.
	 * @return Sformatowany łańcuch znaków zawierający szczegóły usługi, temat oraz formę (online/stacjonarnie).
	 */
	const std::string getInfo() const override;

	/**
	 * Pobiera temat konsultacji.
	 * @return Stała referencja do łańcucha znaków przechowującego temat.
	 */
	const std::string& getTopic() const;

	/**
	 * Sprawdza, czy konsultacja odbywa się w formie zdalnej.
	 * @return Wartość true, jeśli konsultacja jest online, w przeciwnym razie false.
	 */
	bool getIsOnline() const;
};


#endif //REHABILITATIONCENTRE_CONSULTATION_H