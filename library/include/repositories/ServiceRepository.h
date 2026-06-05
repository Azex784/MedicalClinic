#ifndef REHABILITATIONCENTRE_ServiceREPOSITORY_H
#define REHABILITATIONCENTRE_ServiceREPOSITORY_H

#include "repositories/RepositoryTemplate.h"
#include "typedefs.h"

/**
 * Klasa przechwująca dane o usługach
 */
class ServiceRepository : public RepositoryTemplate<ServicePtr,ServicePredicate,const unsigned int>
{
public:
	/**
	 * Konstruktor do testów, by nie zapisywać danych tetowych w pliku programu
	 * @param file_name
	 */
	ServiceRepository(const std::string& file_name);

	/**
	 * Domyślny konstrukotr, ustawia fileName na ../../program/data/ServiceRepository.txt
	 */
	ServiceRepository();
	/**
	 * Destrukotr
	 */
	~ServiceRepository() = default;

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


#endif //REHABILITATIONCENTRE_ServiceREPOSITORY_H