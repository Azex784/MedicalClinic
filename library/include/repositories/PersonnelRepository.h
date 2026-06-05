#ifndef REHABILITATIONCENTRE_PersonnelREPOSITORY_H
#define REHABILITATIONCENTRE_PersonnelREPOSITORY_H

#include "repositories/RepositoryTemplate.h"
#include "typedefs.h"

/**
 * Klasa przechwująca dane o personelu
 */
class PersonnelRepository : public RepositoryTemplate<PersonnelPtr,PersonnelPredicate,const unsigned int>
{
private:
	//Sciezka rozpoczyna sie od cmake-build-debug/library
	const std::string fileName = "../../program/data/PersonnelRepository.txt";

public:
	/**
	 * Metoda zwracająca nazwe pliku
	 * @return Nazwa pliku
	 */
	const std::string& getFileName() const;

	/**
	 * Konstruktor do testów, by nie zapisywać danych tetowych w pliku programu
	 * @param file_name
	 */
	PersonnelRepository(const std::string& file_name);

	/**
	 * Domyślny konstrukotr
	 */
	PersonnelRepository() = default;
	/**
	 * Destrukotr
	 */
	~PersonnelRepository() = default;

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
};


#endif //REHABILITATIONCENTRE_PersonnelREPOSITORY_H