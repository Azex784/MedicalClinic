#ifndef MEDICAL_CLINIC_ROOMMANAGER_H
#define MEDICAL_CLINIC_ROOMMANAGER_H

#include "repositories/RoomRepository.h"
#include "managers/ManagerTemplate.h"
#include "typedefs.h"
#include "rooms/ConsultationRoom.h"
#include <vector>
#include "rooms/RehabillitationRoom.h"

namespace MedicalClinic
{/**
 * Klasa reprezentująca zarządce pracowników
 */
	class RoomManager : public ManagerTemplate<RoomPtr, RoomRepository, RoomPredicate, const unsigned int>
	{
	public:
		/**
		 * Domyślny konstruktor menedżera pokoi.
		 * Inicjuje obiekt menedżera, korzystając z mechanizmów klasy bazowej ManagerTemplate.
		 */
		RoomManager() = default;

		/**
		 * Konstruktor menedżera pokoi z niestandardową ścieżką do pliku danych.
		 * @param fileName Ścieżka do pliku tekstowego.
		 */
		RoomManager(const std::string& fileName);

		/**
		 * Domyślny destruktor menedżera pokoi.
		 */
		~RoomManager() override = default;

		/**
		 * Metoda dodająca nowy pokój konsultacyjny do systemu.
		 * @param roomNumber Unikalny numer pokoju.
		 */
		void addConsultationRoom(const unsigned int roomNumber) const;

		/**
		 * Metoda dodająca nową salę rehabilitacyjną do systemu.
		 * @param roomNumber Unikalny numer pokoju.
		 * @param equipment Wektor określający dostępne wyposażenie sali.
		 * @param maxCapacity Maksymalna pojemność sali(maksymlana liczba personelu).
		 */
		void addRehabillitationRoom(const unsigned int roomNumber, std::vector<Equipment> equipment,
		                            const unsigned int maxCapacity);
	};
}


#endif //MEDICAL_CLINIC_ROOMMANAGER_H
