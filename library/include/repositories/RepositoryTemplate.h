#ifndef MEDICAL_CLINIC_REPOSITORYTEMPLATE_H
#define MEDICAL_CLINIC_REPOSITORYTEMPLATE_H

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

namespace MedicalClinic
{


	template <typename T, typename PredicateT, typename UniqueParameter>
	class RepositoryTemplate
	{
	private:
		std::string fileName;
		std::vector<T> vectorOfData;

	public:
		/**
		* Domyślny konstruktor klasy szablonowej repozytorium.
		*/
		RepositoryTemplate(const std::string& fileName)
			: fileName(fileName)
		{
		}

		/**
		 * Domyślny destruktor klasy szablonowej repozytorium.
		 */
		~RepositoryTemplate()
		{
		}

		/**
		 * Metoda czysci wektor z danymi
		 */
		void clearVectorOfData()
		{
			vectorOfData.clear();
		}

		/**
		 * Getter do fileName
		 * @return nazwa pliku do którego bedzię odbywał się zapis danych.
		 */
		const std::string& getFileName() const
		{
			return fileName;
		}

		/**
		 * Pobiera konkretny obiekt z repozytorium na podstawie pozycji w wektorze.
		 * @param variable int i
		 * @return Znaleziony obiekt typu T.
		 */
		T get(int i) const
		{
			return getVectorOfData()[i];
		}

		/**
		 * Dodaje nowy obiekt do repozytorium.
		 * @param t Obiekt typu T, który ma zostać dodany do kolekcji.
		 */
		void add(T t)
		{
			if (get(t->getUniqueParameter()) != nullptr)
			{
				return;
			}
			vectorOfData.push_back(t);
		}

		/**
		 * Usuwa wskazany obiekt z repozytorium.
		 * @param t Obiekt typu T, który ma zostać skasowany z kolekcji.
		 */
		void remove(T t)
		{
			vectorOfData.erase(std::remove(vectorOfData.begin(), vectorOfData.end(), t));
		}

		/**
		 * Generuje sformatowany raport tekstowy o stanie i zawartości repozytorium.
		 * @return Stały łańcuch znaków zawierający pełny raport.
		 */
		const std::string report() const
		{
			std::stringstream oss;

			for (int i = 0; i < size(); i++)
			{
				oss << getVectorOfData()[i]->getInfo() << std::endl;
			}
			return oss.str();
		}

		/**
		 * Pobiera aktualną liczbę elementów przechowywanych w repozytorium.
		 * @return Liczba elementów jako stała wartość typu int.
		 */
		int size() const
		{
			return getVectorOfData().size();
		}

		/**
		 * Filtruje i wyszukuje elementy w repozytorium spełniające warunek podanego predykatu.
		 * @param predicate Obiekt kryterium  filtrujący kolekcję.
		 * @return Stała referencja do wektora zawierającego przefiltrowane obiekty typu T.
		 */
		const std::vector<T> findBy(PredicateT predicate) const
		{
			std::vector<T> found;
			for (int i = 0; i < size(); i++)
			{
				T t = getVectorOfData()[i];
				if (predicate(t))
				{
					found.push_back(t);
				}
			}
			return found;
		}

		/**
		 * Pobiera pełną listę wszystkich obiektów znajdujących się w repozytorium.
		 * @return Stała referencja do wektora przechowującego całą kolekcję obiektów typu T.
		 */
		const std::vector<T>& findAll() const
		{
			return vectorOfData;
		}

		/**
		 * Getter do vectorOfData
		 * @return Stała referencja do wektora vectorOfData
		 */
		const std::vector<T>& getVectorOfData() const
		{
			return vectorOfData;
		}

		/**
		 * Metoda pozwalająca znaleźć klasę na podstawie uniklane parametru.
		 * Jeśli nie odnzalziona zwracany jest nullptr.
		 * @param up
		 * @return
		 */
		const T get(UniqueParameter up) const
		{
			auto found = findBy([up](const T t) -> bool
			{
				if (t->getUniqueParameter() == up)
					return true;
				return false;
			});
			if (found.empty())
			{
				return nullptr;
			}
			else
			{
				return found[0];
			}
		}

		/**
		* Czysto abstrakcyjna metoda odczytująca dane na dysku
		* @return Zwraca wartosc określającą czy doszło do prawidłowego odczytu
		*/
		virtual void loadData() = 0;

		/**
		 * Czysto abstrakcyjna metoda zapisująca dane na dysku
		 */
		virtual void saveData() const = 0;
	};
}

#endif //MEDICAL_CLINIC_REPOSITORYTEMPLATE_H
