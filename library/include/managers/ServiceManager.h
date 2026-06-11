#ifndef REHABILITATIONCENTRE_SERVICEMANAGER_H
#define REHABILITATIONCENTRE_SERVICEMANAGER_H

#include "enums/Specialisation.h"
#include "enums/Equipment.h"
#include "repositories/ServiceRepository.h"
#include "managers/ManagerTemplate.h"
#include "typedefs.h"

namespace RehabClinic
{/**
 * Klasa reprezentująca zarządce usług
 */
	class ServiceManager : public ManagerTemplate<ServicePtr, ServiceRepository, ServicePredicate, const unsigned int>
	{
	public:
		/**
		 * Domyślny konstruktor menedżera usług.
		 * Inicjuje obiekt menedżera, korzystając z mechanizmów klasy bazowej ManagerTemplate.
		 */
		ServiceManager() = default;

		/**
		 * Konstruktor menedżera usług z niestandardową ścieżką do pliku danych.
		 * @param fileName Ścieżka do pliku tekstowego, która pełni rolę bazy danych usług.
		 */
		ServiceManager(const std::string& fileName);

		/**
		 * Domyślny destruktor menedżera usług.
		 */
		~ServiceManager() override = default;

		/**
		 * Metoda dodająca nową konsultację do systemu.
		 * @param serviceCost Koszt wykonania usługi.
		 * @param serviceDuration Czas trwania usługi w minutach.
		 * @param serviceName Nazwa usługi.
		 * @param serviceId Unikalny identyfikator usługi .
		 * @param requiredSpecialisation Wymagana specjalizacja lekarza do przeprowadzenia konsultacji.
		 * @param topic Temat konsultacji.
		 * @param requiredDocSize Liczba potrzebnych lekarzy.
		 * @param isOnline Wartość okreslająca czy konsultacje są przeprowadzane w trybie online.
		 */
		void addConsultation(const unsigned int& serviceCost, const unsigned int& serviceDuration,
		                     const std::string& serviceName, const unsigned int& serviceId,
		                     Specialisation requiredSpecialisation, const std::string& topic,
		                     const unsigned int& requiredDocSize, bool isOnline);

		/**
		 * Metoda dodająca nową usługę rehabilitacyjną do systemu.
		 * @param serviceCost Koszt wykonania usługi.
		 * @param serviceDuration Czas trwania usługi w minutach.
		 * @param serviceName Nazwa usługi.
		 * @param serviceId Unikalny identyfikator usługi.
		 * @param requiredEquipment Wektor określający sprzęt wymagany do przeprowadzenia zabiegu.
		 * @param requiredSpecialisation Wymagana specjalizacja personelu do przeprowadzenia rehabilitacji.
		 * @param requiredDocSize Liczba potrzebnych lekarzy.
		 * @param requiredNurseSize Liczba potrzebnych pielęgniarek.
		 */
		void addRehabilitation(const unsigned int& serviceCost, const unsigned int& serviceDuration,
		                       const std::string& serviceName, const unsigned int& serviceId,
		                       std::vector<Equipment> requiredEquipment, Specialisation requiredSpecialisation,
		                       const unsigned int& requiredDocSize, const unsigned int& requiredNurseSize);
	};
}


#endif //REHABILITATIONCENTRE_SERVICEMANAGER_H
