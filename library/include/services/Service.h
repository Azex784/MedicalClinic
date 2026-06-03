#ifndef REHABILITATIONCENTRE_SERVICE_H
#define REHABILITATIONCENTRE_SERVICE_H

#include <string>

enum class Specialisation;

class Service
{
private:
	unsigned int serviceCost;
	unsigned int serviceDuration;
	std::string serviceName;
	unsigned int serviceId;
	unsigned int requiredDoctorSize;
	Specialisation requiredDoctorSpec;
	bool isAvailble;
	bool isArchive;

public:
	/**
	 * Konstruktor tworzący nowy obiekt usługi medycznej.
	 * @param service_cost Koszt wykonania usługi.
	 * @param service_duration Czas trwania usługi w minutach.
	 * @param service_name Nazwa świadczonej usługi.
	 * @param service_id Unikalny identyfikator usługi.
	 * @param required_doctor_size Wymagana liczba lekarzy do przeprowadzenia usługi.
	 * @param required_doctor_spec Wymagana specjalizacja lekarza wykonującego usługę.
	 */
	Service(const unsigned int service_cost, const unsigned int service_duration, const std::string& service_name,
	        const unsigned int service_id, const unsigned int required_doctor_size,
	        const Specialisation required_doctor_spec);

	/**
	 * Domyślny destruktor klasy.
	 */
	virtual ~Service() =  0;

	/**
	 * Metoda wirtualna zwracająca pełne informacje o usłudze.
	 * @return Sformatowany łańcuch znaków zawierający szczegóły usługi.
	 */
	virtual const std::string getInfo() const;

	/**
	 * Zwraca koszt wykonania usługi.
	 * @return Koszt usługi jako liczba całkowita bez znaku.
	 */
	unsigned int getServiceCost() const;

	/**
	 * Zwraca przewidywany czas trwania usługi.
	 * @return Czas trwania usługi.
	 */
	unsigned int getServiceDuration() const;

	/**
	 * Zwraca nazwę usługi.
	 * @return Stała referencja do łańcucha znaków przechowującego nazwę.
	 */
	const std::string& getServiceName() const;

	/**
	 * Zwraca unikalny identyfikator usługi.
	 * @return Identyfikator usługi jako liczba całkowita bez znaku.
	 */
	unsigned int getServiceId() const;

	/**
	 * Zwraca wymaganą liczbę lekarzy do przeprowadzenia usługi.
	 * @return Wymagana liczba personelu lekarskiego.
	 */
	unsigned int getRequiredDoctorSize() const;

	/**
	 * Zwraca specjalizację wymaganą do przeprowadzenia usługi.
	 * @return Specjalizacja lekarska zdefiniowana w enumie Specialisation.
	 */
	const Specialisation getRequiredDoctorSpec() const;

	/**
	 * Sprawdza, czy usługa jest obecnie dostępna do rezerwacji/wykonania.
	 * @return Wartość true, jeśli usługa jest dostępna, w przeciwnym razie false.
	 */
	bool getIsAvailable() const;

	/**
	 * Sprawdza, czy usługa została przeniesiona do archiwum (trwale wycofana z oferty).
	 * @return Wartość true, jeśli usługa jest zarchiwizowana, w przeciwnym razie false.
	 */
	bool getIsArchive() const;

	/**
	 * Ustawia nowy koszt wykonania usługi.
	 * @param service_cost Nowa wartość kosztu.
	 */
	void setServiceCost(const unsigned int service_cost);

	/**
	 * Zmienia status dostępności usługi.
	 * @param is_availble.
	 */
	void setIsAvailable(const bool is_availble);

	/**
	 * Zmienia status archiwizacji usługi.
	 * @param is_archive
	 */
	void setIsArchive(const bool is_archive);
};


#endif //REHABILITATIONCENTRE_SERVICE_H
