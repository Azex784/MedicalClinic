#include "menu/TextMenu.h"
#include <iostream>

using namespace std;


bool TerminalMenu::isAmount(const string& tmp, const int& amount) const
{
	if (tmp.size() != amount)
	{
		cerr << "Wprowadzono nieprawidłową ilość znaków!" << endl;
		return false;
	}
	return true;
}

int TerminalMenu::isDigit(const char& znak, const char& max) const
{
	if (znak < '0' || znak > max)
	{
		cerr << "Wprowadzono nieprawidłowy znak!" << endl;
		return -1;
	}
	return znak - '0';
}

TerminalMenu::TerminalMenu() :
	logicManger(make_shared<LogicManager>())
{
}

void TerminalMenu::start() const
{
	cout << "Witaj w centrum rehabilitacji!" << endl;

	bool exit = false;
	string tmp;
	int input;
	while (!exit)
	{
		cout << "<0> - wyjście" << endl;
		cout << "<1> - obsługa klienta" << endl;
		cout << "<2> - obsługa spotkania" << endl;
		cout << "<3> - obsługa sali" << endl;
		cout << "<4> - obsługa usługi" << endl;
		cout << "<5> - obsługa personelu" << endl;

		getline(cin, tmp);

		if (!isAmount(tmp, 1)) continue;
		input = isDigit(tmp[0], '5');

		switch (input)
		{
		case 0:
			exit = true;
			break;
		case 1:
			patient();
			break;
		case 2:
			appointment();
			break;
		case 3:
			room();
			break;
		case 4:
			service();
			break;
		case 5:
			personnel();
			break;
		default:
			continue;
		}
	}
}

void TerminalMenu::patient() const
{
	cout << "Wybrałeś obsługę pacjenta!" << endl;

	bool exit = false;
	string tmp;
	int input;
	while (!exit)
	{
		cout << "<0> - powrót" << endl;
		cout << "<1> - zarejestruj pacjenta" << endl;
		cout << "<2> - zaarchiwizuj pacjenta" << endl;
		cout << "<3> - wyświetl wszystkich pacjentów" << endl;
		cout << "<4> - wyświetl konkretnego pacjenta" << endl;

		getline(cin, tmp);

		if (!isAmount(tmp, 1)) continue;
		input = isDigit(tmp[0], '4');

		switch (input)
		{
		case 0:
			exit = true;
			break;
		case 1:
			{
				string name, lastName, personalId, city, street, number;

				cout << "Podaj imię: ";
				getline(cin, name);

				cout << "Podaj nazwisko: ";
				getline(cin, lastName);

				cout << "Podaj PESEL: ";
				getline(cin, personalId);

				cout << "Podaj miasto: ";
				getline(cin, city);

				cout << "Podaj ulicę: ";
				getline(cin, street);

				cout << "Podaj numer: ";
				getline(cin, number);

				try
				{
					logicManger->getPatientManager()->registerPatient(name, lastName, personalId, city, street, number);
					cout << "Dodano: " << logicManger->getPatientManager()->get(personalId)->getInfo() << endl;
					break;
				}
				catch (const LogicException& logicException)
				{
					cerr << logicException.what() << endl;
					continue;
				}
				catch (const length_error& length_error)
				{
					cerr << length_error.what() << endl;
					continue;
				}
				catch (const ExistException& existException)
				{
					cerr << existException.what() << endl;
					continue;
				}
			}

		case 2:
			{
				string personalId;
				cout << "Podaj PESEL pacjenta: ";
				getline(cin, personalId);

				try
				{
					logicManger->unregisterPatient(personalId);
					cout << "Sukces! Udało się zaarchiwzować Pacjenta: " << logicManger->getPatientManager()->
						get(personalId)->getInfo() << endl;
					break;
				}
				catch (const NoExistException& noExistException)
				{
					cerr << noExistException.what() << endl;
					continue;
				}
				catch (const DateException& dateException)
				{
					cerr << dateException.what() << endl;
					continue;
				}
			}
		case 3:
			{
				auto vector = logicManger->getPatientManager()->findAll();

				for (auto& element : vector)
				{
					cout << element->getInfo() << endl;
				}
				break;
			}
		case 4:
			break;
		default:
			continue;
		}
	}
}


void TerminalMenu::appointment() const
{
	cout << "Wybrałeś obsługę wizyty!" << endl;

	cout << "<0> - powrót" << endl;
	cout << "<1> - dodaj nową wizytę" << endl;
	cout << "<2> - zmień termin wizyty" << endl;
	cout << "<3> - anluj wizytę" << endl;
	cout << "<4> - wyświetl wszystkie wizyty konkretnego specjalisty" << endl;
	cout << "<5> - wyświetl wszystkie wizyty konkretnej sali" << endl;
	cout << "<6> - wyświetl wszystkie wizyty konkretnego pacjenta" << endl;
	cout << "<7> - wyświetl wszystkie wizyty konkretnej usługi" << endl;
}

void TerminalMenu::room() const
{
	cout << "Wybrałeś obsługe sali!" << endl;

	cout << "<0> - powrót" << endl;
	cout << "<1> - dodaj salę rehabilitacyjną" << endl;
	cout << "<2> - dodaj salę konsultacyjną" << endl;
	cout << "<3> - deaktywuj salę" << endl;
	cout << "<4> - wyświetl wszystkie sale" << endl;
	cout << "<5> - wyświetl konkretną salę" << endl;
}

void TerminalMenu::service() const
{
	cout << "Wybrałeś obsługę usługi!" << endl;

	cout << "<0> - powrót" << endl;
	cout << "<1> - dodaj nową rehabilitacje" << endl;
	cout << "<2> - dodaj nową konsultację" << endl;
	cout << "<3> - deaktywuj usługę" << endl;
	cout << "<4> - wyświetl wszystkie usługi" << endl;
	cout << "<5> - wyświetl konkretną usługę" << endl;
}

void TerminalMenu::personnel() const
{
	cout << "Wybrałeś obsługe personelu!" << endl;

	cout << "<0> - powrót" << endl;
	cout << "<1> - dodaj nową pielegniarkę" << endl;
	cout << "<2> - dodaj nowego lekarza" << endl;
	cout << "<3> - zwolnij specjalistę" << endl;
	cout << "<4> - wyświetl wszystkich specjalistów" << endl;
	cout << "<5> - wyświetl konkretnego specjaliste" << endl;
};
