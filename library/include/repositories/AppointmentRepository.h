#ifndef REHABILITATIONCENTRE_AppointmentREPOSITORY_H
#define REHABILITATIONCENTRE_AppointmentREPOSITORY_H

#include "repositories/RepositoryTemplate.h"
#include "typedefs.h"

/**
 * Klasa przechwująca dane o wizytach
 */
class AppointmentRepository : public RepositoryTemplate<AppointmentPtr,AppointmentPredicate,const unsigned int>
{
private:
	//Potrzebne by odnalezc obiekty w innych repozyteriach -
	// w appointment zapisujemy tylko unikalne identyfikatory
	PatientRepositoryPtr patientRepository;
	PersonnelRepositoryPtr personnelRepository;
	RoomRepositoryPtr roomRepository;
	ServiceRepositoryPtr serviceRepository;

public:

	/**
	 * Zwraca stałą referencję do repozytorium pacjentów.
	 * * @return const PatientRepositoryPtr& Stała referencja do inteligentnego wskaźnika repozytorium pacjentów.
	 */
	const PatientRepositoryPtr& getPatientRepository() const;

	/**
	 * Zwraca stałą referencję do repozytorium personelu.
	 * @return const PersonnelRepositoryPtr& Stała referencja do inteligentnego wskaźnika repozytorium personelu.
	 */
	const PersonnelRepositoryPtr& getPersonnelRepository() const;

	/**
	 * Zwraca stałą referencję do repozytorium sal.
	 * @return const RoomRepositoryPtr& Stała referencja do inteligentnego wskaźnika repozytorium sal.
	 */
	const RoomRepositoryPtr& getRoomRepository() const;

	/**
	 * Zwraca stałą referencję do repozytorium usług.
	 * @return const ServiceRepositoryPtr& Stała referencja do inteligentnego wskaźnika repozytorium usług.
	 */
	const ServiceRepositoryPtr& getServiceRepository() const;

	/**
	* Domyślny konstrukotr, domyslna sciezka: "../../program/data/AppointmentRepository.txt"
	*/
	AppointmentRepository(const PatientRepositoryPtr& patient_repository,
		const PersonnelRepositoryPtr& personnel_repository, const RoomRepositoryPtr& room_repository,
		const ServiceRepositoryPtr& service_repository);


	/**
	 * Konstruktor do testów lub do zapisu archive, by nie zapisywać danych testowych w pliku programu
	 * @param file_name
	 */
	AppointmentRepository(const std::string& file_name, const PatientRepositoryPtr& patient_repository,
		const PersonnelRepositoryPtr& personnel_repository, const RoomRepositoryPtr& room_repository,
		const ServiceRepositoryPtr& service_repository);

	/**
	 * Destrukotr
	 */
	~AppointmentRepository() = default;

	/**
	* Wczytuje dane z pliku tekstowego na dysku do pamięci operacyjnej RAM.
	* @return true Jeśli plik został pomyślnie otwarty, a dane załadowane do RAM-u.
	* @return false Jeśli nie udało się wczytac danych/otworzyc pliku.
	*/
	bool loadData() override;

	/**
	 * Zapisuje aktualny stan kolekcji z pamięci ulotnej do trwalej pamieci fizycznej.
	 * @return true Jeśli proces zapisu na dysku zakończył się sukcesem.
	 * @return false Jeśli wystąpił błąd przy zapisie.
	 */
	bool saveData() const override;
};


#endif //REHABILITATIONCENTRE_AppointmentREPOSITORY_H