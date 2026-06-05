#ifndef REHABILITATIONCENTRE_AppointmentREPOSITORY_H
#define REHABILITATIONCENTRE_AppointmentREPOSITORY_H

#include "repositories/RepositoryTemplate.h"
#include "typedefs.h"

/**
 * Klasa przechwująca dane o wizytach
 */
class AppointmentRepository : public RepositoryTemplate<AppointmentPtr,AppointmentPredicate>
{
private:
	//Sciezka rozpoczyna sie od cmake-build-debug/library
	const std::string fileName = "../../program/data/AppointmentRepository.txt";

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
	 * Metoda zwracająca nazwe pliku
	 * @return Nazwa pliku
	 */
	const std::string& getFileName() const;

	/**
	 * Konstruktor do testów lub do zapisu archive, by nie zapisywać danych tetowych w pliku programu
	 * @param file_name
	 */
	AppointmentRepository(const std::string& file_name);

	/**
	 * Domyślny konstrukotr
	 */
	AppointmentRepository() = default;
	/**
	 * Destrukotr
	 */
	~AppointmentRepository() = default;

	/**
	* Wczytuje dane z pliku tekstowego na dysku do pamięci operacyjnej RAM.
	* @return true Jeśli plik został pomyślnie otwarty, a dane załadowane do RAM-u.
	* @return false Jeśli nie udało się wczytac danych/otworzyc pliku.
	*/
	bool loadData();

	/**
	 * Zapisuje aktualny stan kolekcji z pamięci ulotnej do trwalej pamieci fizycznej.
	 * @return true Jeśli proces zapisu na dysku zakończył się sukcesem.
	 * @return false Jeśli wystąpił błąd przy zapisie.
	 */
	bool saveData() const;

	/**
	 * Metoda zwracająca wartość danego czlowieka personelu na podsatwie wartosci AppointmentId
	 * @param appointmentId
	 * @return AppointmentPtr
	 */
	const AppointmentPtr get(const int &appointmentId) const;
};


#endif //REHABILITATIONCENTRE_AppointmentREPOSITORY_H