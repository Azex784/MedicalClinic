#ifndef REHABILITATIONCENTRE_PATIENTMANAGER_H
#define REHABILITATIONCENTRE_PATIENTMANAGER_H

#include "repositories/PatientRepository.h"
#include "managers/ManagerTemplate.h"
#include "typedefs.h"
#include "patient/Patient.h"

class PatientManager : public ManagerTemplate<PatientPtr, PatientRepository,PatientPredicate,const std::string>
{
public:
	/**
	 * Metoda rejestrująca nowych pacjentów w systemie, jesli pesel nie wystepuje w repozytorium
	 * @param firstName Imię pacjenta.
	 * @param lastName Nazwisko pacjenta.
	 * @param personalID Numer PESEL pacjenta (unikalny identyfikator w systemie).
	 * @param city Miasto zamieszkania pacjenta.
	 * @param street Ulica zamieszkania pacjenta.
	 * @param number Numer mieszkania pacjenta.
	 * @return const PatientPtr Inteligentny wskaźnik na pacjenta.
	 */
	void registerPatient(const std::string & firstName, const std::string & lastName, const std::string &personalID, const std::string & city, const std::string &street, const std::string &number) const;

	/**
	 * Domyślny konstruktor menedżera pacjentów.
	 * Inicjuje obiekt menedżera, korzystając z mechanizmów klasy bazowej ManagerTemplate.
	 */
	PatientManager() = default;

	/**
	 * Konstruktor menedżera pacjentów z niestandardową ścieżką do pliku danych.
	 * @param fileName Ścieżka do pliku tekstowego.
	 */
	PatientManager(const std::string& fileName);
};


#endif //REHABILITATIONCENTRE_PATIENTMANAGER_H