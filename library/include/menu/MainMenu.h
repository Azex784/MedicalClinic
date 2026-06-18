#ifndef REHABILITATIONCENTRE_MAINMENU_H
#define REHABILITATIONCENTRE_MAINMENU_H

#include "managers/LogicManager.h"
#include <iostream>

namespace RehabClinic
{
	class MainMenu
	{
	private:
		LogicManagerPtr logicManager;

	public:
		MainMenu(const LogicManagerPtr& logicManager);
		const LogicManagerPtr& getLogicManager() const;
		//Metoda sprawdzająca prawidłową liczbę znaków.
		bool isAmount(const std::string& tmp, const int& amount) const;

		//Metoda sprawdzająca czy znak należy do przedziału od 0 do max
		int isDigit(const char& znak, const char& max) const;

		//Metoda szablonowa sprawdzająca czy item należy do wektora.
		template <typename type>
		bool contains(std::vector<type> vectorOfValues, type value, const std::string& itemName) const
		{
			if (vectorOfValues.empty()) return false;
			for (auto& item : vectorOfValues)
			{
				if (item == value)
				{
					std::cerr << "Nie można dodać tego samego " + itemName + " dwa razy!" << std::endl;
					return true;
				}
			}
			return false;
		}

		//Metoda sprawdzająca czy item należy do wektora.
		bool checkInt(const std::string& tmp, unsigned int& liczba) const;

		//Metoda szablonowa wyświetlająca wszystkie elementy wektora.
		template <typename type>
		void displayAll(std::vector<type> wektor) const
		{
			for (auto& element : wektor)
			{
				std::cout << element->getInfo() << std::endl;
			}
		}

		template <typename type>
		bool displaySpecific(type patient, const std::string& msg) const
		{
			if (patient == nullptr)
			{
				std::cerr << "Wprowadzono nieprawidłowy " + msg + "." << std::endl;
				return false;
			}
			std::cout << patient->getInfo() << std::endl;
			return true;
		}

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
		template <typename type, typename JakisPtr>
		bool findByInt(const std::string& msg, JakisPtr manager, type* returnValue = nullptr) const
		{
			std::string tmp2;
			unsigned int uniqeParamter = 0;

			std::cout << "Podaj identyfikator " + msg + ", która ma być wyświetlony: ";
			getline(std::cin, tmp2);

			if (!checkInt(tmp2, uniqeParamter)) return false;
			auto thing = manager->get(uniqeParamter);
			if (returnValue != nullptr) *returnValue = manager->get(uniqeParamter);

			if (!displaySpecific<type>(thing, "identyfikator" + msg)) return false;

			return true;
		}

		//Metoda pytająca się użytkownika czy chec kontynować.
		//Zwraca wartość logiczną w zależności od wyboru użytkownika.
		bool isContinue() const;

		//Metoda sprawdzająca czy wpisana data jest prawidłowa.
		bool checkDate(const std::string& dateInput, const std::string& timeInput,
		               boost::posix_time::ptime& parsedTime) const;
	};
}

#endif //REHABILITATIONCENTRE_MAINMENU_H
