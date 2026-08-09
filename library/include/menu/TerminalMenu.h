#ifndef MEDICALCLINIC_TERMINALMENU_H
#define MEDICALCLINIC_TERMINALMENU_H

#include "managers/LogicManager.h"

namespace MedicalClinic
{
	/**
	* Klasa zapewniające tekstowe menu do obsługi centrum rehabilitacji
	*/
	class TerminalMenu
	{
	private:
		LogicManagerPtr logicManager;

	private:
		//Metoda sprawdzająca prawidłową liczbę znaków.
		bool isAmount(const std::string& tmp, const int& amount) const;

		//Metoda sprawdzająca czy znak należy do przedziału od 0 do max
		int isDigit(const char& znak, const char& max) const;

		//Metoda szablonowa sprawdzająca czy item należy do wektora.
		template <typename type>
		bool contains(std::vector<type> vectorOfValues, type value, const std::string& itemName) const;

		//Metoda sprawdzająca czy item należy do wektora.
		bool checkInt(const std::string& tmp, unsigned int& liczba) const;

		//Metoda szablonowa wyświetlająca wszystkie elementy wektora.
		template <typename type>
		void displayAll(std::vector<type> wektor) const;

		//Metoda szablonowa wyświetlająca konkrente elementy wektora.
		template <typename type>
		bool displaySpecific(type patient, const std::string& msg) const;

		//Metoda wczytująca sprzęt w postaci wektora.
		bool loadEquipment(std::vector<Equipment>& accessibleEquipment) const;

		//Metoda zawierająca wspólne wspólne elementy wczytania konsultacji i rehabilitacji.
		bool jointLoadService(unsigned int& serviceCost,
		                      unsigned int& requiredDocSize,
		                      unsigned int& serviceId,
		                      unsigned int& serviceDuration,
		                      Specialisation& specjalizacja,
		                      std::string& serviceName) const;

		//Metoda zawierająca wspólne wspólne elementy wczytania lekarza i pielęgniarki.
		bool jointLoadPersonnel(std::string& firstName, std::string& lastName,
		                        unsigned int& personnelId) const;

		//Metoda wczytująca specjalizację.
		bool specialisationLoad(Specialisation& spec) const;

		//Metoda szablonowa znajdująca konkretne obiekty w zależności od wczytanej danej.
		//Metoda ta dodatko zwraca przez wskaznik znaleziony obiekt
		template <typename type, typename ManagerPtr>
		bool findByInt(const std::string& msg, ManagerPtr manage, type* returnValue = nullptr) const;

		//Metoda pytająca się użytkownika czy chec kontynować.
		//Zwraca wartość logiczną w zależności od wyboru użytkownika.
		bool isContinue() const;

		//Metoda sprawdzająca czy wpisana data jest prawidłowa.
		bool checkDate(const std::string& dateInput, const std::string& timeInput,
		               boost::posix_time::ptime& parsedTime) const;

	public:
		/**
		 * Domyślny konstruktor, inicjalizuje logicManger
		 */
		TerminalMenu();

		/**
		 * Getter do logicManager
		 * @return Stała referencja do logicManager
		 */
		const LogicManagerPtr& getLogicManager() const;

		/**
		 * Domyślny destruktor
		 */
		~TerminalMenu() = default;

		/**
		 * Metoda rozpoczynająca obsługę.
		 */
		void start() const;

		/**
		 * Metoda przeznaczona na obsługę pacjenta.
		 */
		void patient() const;

		/**
		 * Metoda przeznaczona na obsługę wizyty.
		 */
		void appointment() const;

		/**
		 * Metoda przeznaczona na obsługę sali.
		 */
		void room() const;

		/**
		 * Metoda przeznaczona na obsługę usługi.
		 */
		void service() const;

		/**
		 * Metoda przeznaczona na obsługę personelu.
		 */
		void personnel() const;

		/**
		 * Rejestruje nowego pacjenta w systemie.
		 * @return True w przypadku pełnego sukcesu operacji, false w przypadku przerwania.
		 */
		bool registerPatient() const;

		/**
		 * Archiwizuje wybranego pacjenta.
		 * @return True w przypadku sukcesu, false w przypadku przerwania.
		 */
		bool archivePatient() const;

		/**
		 * Dodaje nową wizytę.
		 * @return True w przypadku sukcesu, false w przypadku przerwania.
		 */
		bool arrangeAppointment() const;

		/**
		 * Zmienia termin istniejącej wizyty.
		 * @return True w przypadku sukcesu, false w przypadku przerwania.
		 */
		bool changeAppointment() const;

		/**
		 * Dodaje nową salę rehabilitacyjną do zasobów.
		 * @return True w przypadku sukcesu, false w przypadku przerwania.
		 */
		bool addRehabilitationRoom() const;

		/**
		 * Dodaje nową salę konsultacyjną.
		 * @return True w przypadku sukcesu, false w przypadku przerwania.
		 */
		bool addConsultationRoom() const;

		/**
		 * Dezaktywuje wybraną salę w systemie.
		 * @return True w przypadku sukcesu, false w przypadku przerwania.
		 */
		bool deactivateRoom() const;

		/**
		 * Dodaje nową usługę rehabilitacyjną.
		 * @return True w przypadku sukcesu, false w przypadku przerwania.
		 */
		bool addRehabilitationService() const;

		/**
		 * Dodaje nową usługę konsultacyjną .
		 * @return True w przypadku sukcesu, false w przypadku przerwania.
		 */
		bool addConsultationService() const;

		/**
		 * Dezaktywuje wybraną usługę w systemie.
		 * @return True w przypadku sukcesu, false w przypadku przerwania.
		 */
		bool deactivateService() const;

		/**
		 * Anuluje wybraną wizytę w systemie.
		 * @return True w przypadku sukcesu, false w przypadku przerwania.
		 */
		bool cancelAppointment() const;

		/**
		 * Kończy spotkanie i podsumowuje jego stan.
		 * @return True w przypadku sukcesu, false w przypadku przerwania.
		 */
		bool finishAppointment() const;

		/**
		 * Dodaje nową pielęgniarkę do personelu.
		 * @return True w przypadku sukcesu, false w przypadku przerwania.
		 */
		bool addNurse() const;

		/**
		 * Dodaje nowego lekarza do personelu.
		 * @return True w przypadku sukcesu, false w przypadku przerwania.
		 */
		bool addDoctor() const;

		/**
		 * Zwalnia (archiwizuje) wybranego specjalistę.
		 * @return True w przypadku sukcesu, false w przypadku przerwania.
		 */
		bool dismissPersonnel() const;
	};
}

#endif //MEDICALCLINIC_TERMINALMENU_H
