#ifndef REHABILITATIONCENTRE_PersonnelREPOSITORY_H
#define REHABILITATIONCENTRE_PersonnelREPOSITORY_H

#include "repositories/RepositoryTemplate.h"
#include "typedefs.h"

/**
 * Klasa przechwująca dane o personelu
 */
class PersonnelRepository : public RepositoryTemplate<PersonnelPtr,PersonnelPredicate,const unsigned int>
{
public:

	/**
	 * Konstruktor do testów, by nie zapisywać danych tetowych w pliku programu
	 * @param file_name
	 */
	PersonnelRepository(const std::string& fileName);

	/**
	 * Domyślny konstrukotr, domyślna ścieżka "../../program/data/PersonnelRepository.txt"
	 */
	PersonnelRepository();

	/**
	 * Destrukotr
	 */
	~PersonnelRepository() = default;

	/**
	* Wczytuje dane z pliku tekstowego na dysku do pamięci operacyjnej RAM.
	*/
	void loadData() override;

	/**
	 * Zapisuje aktualny stan kolekcji z pamięci ulotnej do trwalej pamieci fizycznej.
	 */
	void saveData() const override;
};


#endif //REHABILITATIONCENTRE_PersonnelREPOSITORY_H