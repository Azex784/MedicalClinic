#ifndef REHABILITATIONCENTRE_ServiceREPOSITORY_H
#define REHABILITATIONCENTRE_ServiceREPOSITORY_H

#include "repositories/RepositoryTemplate.h"
#include "typedefs.h"

namespace RehabClinic
{
	/**
	 * Klasa przechwująca dane o usługach
	 */
	class ServiceRepository : public RepositoryTemplate<ServicePtr, ServicePredicate, const unsigned int>
	{
	public:
		/**
		 * Konstruktor do testów, by nie zapisywać danych tetowych w pliku programu
		 * @param file_name
		 */
		ServiceRepository(const std::string& fileName);

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
		*/
		void loadData() override;

		/**
		 * Zapisuje aktualny stan kolekcji z pamięci ulotnej do trwalej pamieci fizycznej.
		 */
		void saveData() const override;
	};
}

#endif //REHABILITATIONCENTRE_ServiceREPOSITORY_H
