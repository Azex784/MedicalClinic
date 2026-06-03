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
	 * @param service_cost Koszt przeprowadzenia konsultacji.
	 * @param service_duration Przewidywany czas trwania konsultacji w minutach.
	 * @param service_name Nazwa usługi konsultacyjnej.
	 * @param service_id Unikalny identyfikator usługi.
	 * @param required_doctor_size Wymagana liczba lekarzy do przeprowadzenia konsultacji.
	 * @param required_doctor_spec Wymagana specjalizacja lekarza prowadzącego konsultację.
	 * @param topic Główny temat.
	 * @param is_online Flaga logiki: true oznacza, że konsultacja odbywa się zdalnie (online), false oznacza wizytę stacjonarną.
	 */
	Consultation(const unsigned service_cost, const unsigned service_duration, const std::string& service_name,
	             const unsigned service_id, const unsigned required_doctor_size,
	             const Specialisation required_doctor_spec,
	             const std::string& topic, const bool is_online);

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