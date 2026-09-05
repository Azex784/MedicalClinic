#ifndef MEDICAL_CLINIC_AppointmentREPOSITORY_H
#define MEDICAL_CLINIC_AppointmentREPOSITORY_H

#include "repositories/RepositoryTemplate.h"
#include "typedefs.h"

namespace MedicalClinic
{/**
 * Klasa przechwująca dane o wizytach
 */
	class AppointmentRepository : public RepositoryTemplate<AppointmentPtr, AppointmentPredicate, const unsigned int>
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
		AppointmentRepository(const PatientRepositoryPtr& patientRepository,
		                      const PersonnelRepositoryPtr& personnelRepository,
		                      const RoomRepositoryPtr& roomRepository,
		                      const ServiceRepositoryPtr& serviceRepository);

		/**
		 * Konstruktor do testów lub do zapisu archive, by nie zapisywać danych testowych w pliku programu
		 * @param fileName
		 */
		AppointmentRepository(const std::string& fileName, const PatientRepositoryPtr& patientRepository,
		                      const PersonnelRepositoryPtr& personnelRepository,
		                      const RoomRepositoryPtr& roomRepository,
		                      const ServiceRepositoryPtr& serviceRepository);

		/**
		 * Domyślny destrukotr
		 */
		~AppointmentRepository() = default;

		/**
		* Wczytuje dane z pliku tekstowego na dysku do pamięci operacyjnej RAM.
		*/
		void loadData() override;

		/**
		 * Zapisuje aktualny stan kolekcji z pamięci ulotnej do trwalej pamieci fizycznej.
		 */
		void saveData() const override;
	};
}

#endif //MEDICAL_CLINIC_AppointmentREPOSITORY_H