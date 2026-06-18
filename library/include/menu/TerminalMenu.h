#ifndef REHABILITATIONCENTRE_TERMINALMENU_H
#define REHABILITATIONCENTRE_TERMINALMENU_H

#include "MainMenu.h"
#include "managers/LogicManager.h"

namespace RehabClinic
{
	/**
	* Klasa zapewniające tekstowe menu do obsługi centrum rehabilitacji
	*/
	class TerminalMenu : public MainMenu
	{
	private:
		LogicManagerPtr logicManager;

	public:
		/**
		 * Domyślny konstruktor, inicjalizuje logicManger
		 */
		TerminalMenu();

		/**
		 * Getter do logicManager
		 * @return Stała referencja do logicManager
		 */
		const LogicManagerPtr& getLogicManager() const;

		/**
		 * Domyślny destruktor
		 */
		~TerminalMenu() = default;

		/**
		 * Metoda rozpoczynająca obsługę.
		 */
		void start() const;

		/**
		 * Metoda przeznaczona na obsługę pacjenta.
		 */
		void patient() const;

		/**
		 * Metoda przeznaczona na obsługę wizyty.
		 */
		void appointment() const;

		/**
		 * Metoda przeznaczona na obsługę sali.
		 */
		void room() const;

		/**
		 * Metoda przeznaczona na obsługę usługi.
		 */
		void service() const;

		/**
		 * Metoda przeznaczona na obsługę personelu.
		 */
		void personnel() const;

		/**
		 * Rejestruje nowego pacjenta w systemie.
		 * @return True w przypadku pełnego sukcesu operacji, false w przypadku przerwania.
		 */
		bool registerPatient() const;

		/**
		 * Archiwizuje wybranego pacjenta.
		 * @return True w przypadku sukcesu, false w przypadku przerwania.
		 */
		bool archivePatient() const;

		/**
		 * Dodaje nową wizytę.
		 * @return True w przypadku sukcesu, false w przypadku przerwania.
		 */
		bool arrangeAppointment() const;

		/**
		 * Zmienia termin istniejącej wizyty.
		 * @return True w przypadku sukcesu, false w przypadku przerwania.
		 */
		bool changeAppointment() const;

		/**
		 * Dodaje nową salę rehabilitacyjną do zasobów.
		 * @return True w przypadku sukcesu, false w przypadku przerwania.
		 */
		bool addRehabilitationRoom() const;

		/**
		 * Dodaje nową salę konsultacyjną.
		 * @return True w przypadku sukcesu, false w przypadku przerwania.
		 */
		bool addConsultationRoom() const;

		/**
		 * Dezaktywuje wybraną salę w systemie.
		 * @return True w przypadku sukcesu, false w przypadku przerwania.
		 */
		bool deactivateRoom() const;

		/**
		 * Dodaje nową usługę rehabilitacyjną.
		 * @return True w przypadku sukcesu, false w przypadku przerwania.
		 */
		bool addRehabilitationService() const;

		/**
		 * Dodaje nową usługę konsultacyjną .
		 * @return True w przypadku sukcesu, false w przypadku przerwania.
		 */
		bool addConsultationService() const;

		/**
		 * Dezaktywuje wybraną usługę w systemie.
		 * @return True w przypadku sukcesu, false w przypadku przerwania.
		 */
		bool deactivateService() const;

		/**
		 * Anuluje wybraną wizytę w systemie.
		 * @return True w przypadku sukcesu, false w przypadku przerwania.
		 */
		bool cancelAppointment() const;

		/**
		 * Kończy spotkanie i podsumowuje jego stan.
		 * @return True w przypadku sukcesu, false w przypadku przerwania.
		 */
		bool finishAppointment() const;

		/**
		 * Dodaje nową pielęgniarkę do personelu.
		 * @return True w przypadku sukcesu, false w przypadku przerwania.
		 */
		bool addNurse() const;

		/**
		 * Dodaje nowego lekarza do personelu.
		 * @return True w przypadku sukcesu, false w przypadku przerwania.
		 */
		bool addDoctor() const;

		/**
		 * Zwalnia (archiwizuje) wybranego specjalistę.
		 * @return True w przypadku sukcesu, false w przypadku przerwania.
		 */
		bool dismissPersonnel() const;
	};
}

#endif //REHABILITATIONCENTRE_TERMINALMENU_H
