#ifndef REHABILITATIONCENTRE_SERVICE_H
#define REHABILITATIONCENTRE_SERVICE_H

#include <string>

namespace RehabClinic
{
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
		bool isAvailable;
		bool isArchive;

	public:
		/**
		 * Konstruktor tworzący nowy obiekt usługi medycznej.
		 * @param serviceCost Koszt wykonania usługi.
		 * @param serviceDuration Czas trwania usługi w minutach.
		 * @param serviceName Nazwa świadczonej usługi.
		 * @param serviceId Unikalny identyfikator usługi.
		 * @param requiredDoctorSize Wymagana liczba lekarzy do przeprowadzenia usługi.
		 * @param requiredDoctorSpec Wymagana specjalizacja lekarza wykonującego usługę.
		 */
		Service(const unsigned int serviceCost, const unsigned int serviceDuration, const std::string& serviceName,
		        const unsigned int serviceId, const unsigned int requiredDoctorSize,
		        const Specialisation requiredDoctorSpec);

		/**
		 * Domyślny abstrakcyjny destruktor klasy.
		 */
		virtual ~Service() = 0;

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
		unsigned int getUniqueParameter() const;

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
		 * @param serviceCost1 Nowa wartość kosztu.
		 */
		void setServiceCost(const unsigned int serviceCost1);

		/**
		 * Zmienia status dostępności usługi.
		 * @param is_availble.
		 */
		void setIsAvailable(const bool isAvailble1);

		/**
		 * Zmienia status archiwizacji usługi.
		 * @param isArchive
		 */
		void setIsArchive(const bool isArchive);
	};
}


#endif //REHABILITATIONCENTRE_SERVICE_H
