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
	* @return true Jeśli plik został pomyślnie otwarty, a dane załadowane do RAM-u.
	* @return false Jeśli nie udało się wczytac danych/otworzyc pliku.
	*/
	bool loadData() ;

	/**
	 * Zapisuje aktualny stan kolekcji z pamięci ulotnej do trwalej pamieci fizycznej.
	 * @return true Jeśli proces zapisu na dysku zakończył się sukcesem.
	 * @return false Jeśli wystąpił błąd przy zapisie.
	 */
	bool saveData() const;
};


#endif //REHABILITATIONCENTRE_PATIENTREPOSITORY_H