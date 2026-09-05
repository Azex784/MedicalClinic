#ifndef MEDICAL_CLINIC_PERSONNELMANAGER_H
#define MEDICAL_CLINIC_PERSONNELMANAGER_H

#include "personnel/Personnel.h"
#include <repositories/PersonnelRepository.h>
#include "typedefs.h"
#include "managers/ManagerTemplate.h"

namespace MedicalClinic
{/**
 * Klasa reprezentująca zarządce pracowników
 */
	class PersonnelManager : public ManagerTemplate<
			PersonnelPtr, PersonnelRepository, PersonnelPredicate, const unsigned int>
	{
	public:
		/**
		* Domyślny konstruktor menedżera personelu.
		* Inicjuje obiekt menedżera, korzystając z mechanizmów klasy bazowej ManagerTemplate.
		*/
			PersonnelManager() = default;

		/**
		 * Konstruktor menedżera personelu z niestandardową ścieżką do pliku danych.
		 * @param fileName Ścieżka do pliku tekstowego.
		 */
		PersonnelManager(const std::string& fileName);

		/**
		 * Domyślny destruktor menedżera personelu.
		 */
		~PersonnelManager() override = default;

		/**
		 * Metoda dodająca nowego lekarza do systemu.
		 * @param firstName Imię lekarza.
		 * @param lastName Nazwisko lekarza.
		 * @param personnelId Unikalny identyfikator pracownika.
		 * @param specialistaion Wektor określający posiadane przez lekarza specjalizacje.
		 * @param doctorCost Koszt określający prestiż lekarza.
		 */
		void addDoctor(const std::string& firstName, const std::string& lastName, const unsigned int& personnelId,
		               std::vector<Specialisation> specialistaion, const unsigned int& doctorCost);

		/**
		 * Metoda dodająca nową pielęgniarkę do systemu.
		 * @param firstName Imię pielęgniarki.
		 * @param lastName Nazwisko pielęgniarki.
		 * @param personnelId Unikalny identyfikator pracownika.
		 */
		void addNurse(const std::string& firstName, const std::string& lastName, const unsigned int& personnelId);
	};
}


#endif //MEDICAL_CLINIC_PERSONNELMANAGER_H
