#ifndef REHABILITATIONCENTRE_PATIENTREPOSITORY_H
#define REHABILITATIONCENTRE_PATIENTREPOSITORY_H

#include "repositories/RepositoryTemplate.h"
#include "typedefs.h"

/**
 * Klasa przechwująca dane o pacjentach
 */
class PatientRepository : public RepositoryTemplate<PatientPtr,PatientPredicate,const std::string>
{
public:

	/**
	 * Konstruktor do testów, by nie zapisywać danych tetowych w pliku programu
	 * @param fileName
	 */
	PatientRepository(const std::string& fileName);

	/**
	 * Domyślny konsturktor, które ustawia fileNaame na "../../program/data/PatientRepository.txt"
	 */
	PatientRepository();

	/**
	 * Destrukotr
	 */
	~PatientRepository() = default;

	/**
	* Wczytuje dane z pliku tekstowego na dysku do pamięci operacyjnej RAM.
	*/
	void loadData() override;

	/**
	 * Zapisuje aktualny stan kolekcji z pamięci ulotnej do trwalej pamieci fizycznej.
	 */
	void saveData() const override;
};


#endif //REHABILITATIONCENTRE_PATIENTREPOSITORY_H