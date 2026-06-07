#ifndef REHABILITATIONCENTRE_MANAGERTEMPLATE_H
#define REHABILITATIONCENTRE_MANAGERTEMPLATE_H

/**
 * Szablon klasy dla menadzerow
 *
 */
template <typename UniqueClass, typename UniqueRepoClass, typename PredicateT, typename UniqueParameter>
class ManagerTemplate
{
protected:
	std::shared_ptr<UniqueRepoClass> repository;

public:
	/**
	 * Domyślny konstruktor menedżera.
	 * Inicjuje puste repozytorium i automatycznie wczytuje dane
	 * z domyślnego pliku.
	 */
	ManagerTemplate()
	{
		repository = std::make_shared<UniqueRepoClass>();
		getRepository()->loadData();
	}

	/**
	  * Konstruktor menedżera ze wskazaną ścieżką do pliku.
	  * Inicjuje repozytorium z konkretną ścieżką dostępu.
	  * @param fileName Ścieżka do pliku tekstowego.
	  */
	ManagerTemplate(std::string fileName)
	{
		repository = std::make_shared<UniqueRepoClass>(fileName);
		getRepository()->loadData();
	}

	/**
	 * Destruktor menedżera.
	 * Automatycznie zapisuje dane.
	 */
	virtual ~ManagerTemplate()
	{
		getRepository()->saveData();
	}

	/**
	 * Zwraca obiekt repozytorium przypisany do tego menedżera.
	 * @return Stała referencja do obiektu repozytorium.
	 */
	const std::shared_ptr<UniqueRepoClass>& getRepository() const
	{
		return repository;
	}

	/**
	 * Zwraca pojedynczy obiekt z repozytorium na podstawie unikalnego parametru.
	 * @param up Unikalny parametr identyfikujący obiekt.
	 * @return Stała referencja do znalezionego obiektu.
	 */
	const UniqueClass get(UniqueParameter up) const
	{
		return repository->get(up);
	}

	/**
	 * Wyszukuje obiekty w repozytorium spełniające zadany warunek.
	 * @param up Predykat.
	 * @return Wektor zawierający obiekty spełniające kryteria predykatu.
	 */
	const std::vector<UniqueClass> findBy(PredicateT up) const
	{
		return getRepository()->findBy(up);
	}

	/**
	 *
	 * Zwraca wszystkie obiekty znajdujące się obecnie w repozytorium.
	 * @return Wektor zawierający wszystkie obiekty.
	 */
	const std::vector<UniqueClass> findAll() const
	{
		return getRepository()->findAll();
	}
};

#endif //REHABILITATIONCENTRE_MANAGERTEMPLATE_H
