#include "menu/MainMenu.h"
#include <boost/date_time/posix_time/time_parsers.hpp>

namespace RehabClinic
{
	using namespace std;

	MainMenu::MainMenu(const LogicManagerPtr& logicManager): logicManager(logicManager)
	{
	}

	bool MainMenu::isContinue() const
	{
		string tmp1;
		int input1;
		cout << "Czy chesz kontynuować/ropocząć wpisywanie potrzebnych danych? (0/1)" << endl;

		getline(cin, tmp1);

		if (!isAmount(tmp1, 1))return true;
		input1 = isDigit(tmp1[0], '1');
		if (input1 == -1)return true;

		switch (input1)
		{
		case 0:
			return false;
		case 1:
			return true;
		}
		return false;
	}

	const LogicManagerPtr& MainMenu::getLogicManager() const
	{
		return logicManager;
	}

	bool MainMenu::isAmount(const string& tmp, const int& amount) const
	{
		if (tmp.size() != amount)
		{
			cerr << "Wprowadzono nieprawidłową ilość znaków!" << endl;
			return false;
		}
		return true;
	}

	int MainMenu::isDigit(const char& znak, const char& max) const
	{
		if (znak < '0' || znak > max)
		{
			cerr << "Wprowadzono nieprawidłowy znak!" << endl;
			return -1;
		}
		return znak - '0';
	}



	bool MainMenu::checkInt(const string& tmp, unsigned int& liczba) const
	{
		try
		{
			liczba = stoul(tmp);
			return true;
		}
		catch (const invalid_argument& e)
		{
			cerr << "Podany tekst: " << tmp << " nie jest liczbą." << endl;
			return false;
		}
		catch (const out_of_range& e)
		{
			cerr << "Liczba: " << tmp << " jest za duży." << endl;
			return false;
		}
	}



	bool MainMenu::loadEquipment(vector<Equipment>& accessibleEquipment) const
	{
		bool exit1 = false;
		string tmp1;
		int input1;
		while (!exit1)
		{
			cout << "Podaj wyposażenie " << endl;
			cout << "<0> - zakończono wybór" << endl;
			cout << "<1> - " + equipmentToString(Equipment::KINESITHERAPY_SPACE) << endl;
			cout << "<2> - " + equipmentToString(Equipment::NONE) << endl;
			cout << "<3> - " + equipmentToString(Equipment::PHYSICAL_THERAPY_DEVICE) << endl;
			cout << "<4> - " + equipmentToString(Equipment::ROBOTIC_SYSTEM) << endl;

			getline(cin, tmp1);

			if (!isAmount(tmp1, 1)) return false;
			input1 = isDigit(tmp1[0], '4');
			if (input1 == -1) return false;

			switch (input1)
			{
			case 0:
				exit1 = true;
				break;
			case 1:
				if (contains<Equipment>(accessibleEquipment, Equipment::KINESITHERAPY_SPACE, "sprzętu"))
					continue;
				accessibleEquipment.push_back(Equipment::KINESITHERAPY_SPACE);
				break;
			case 2:
				if (contains<Equipment>(accessibleEquipment, Equipment::NONE, "sprzętu")) continue;
				accessibleEquipment.push_back(Equipment::NONE);
				break;
			case 3:
				if (contains<Equipment>(accessibleEquipment, Equipment::PHYSICAL_THERAPY_DEVICE, "sprzętu"))
					continue;
				accessibleEquipment.push_back(Equipment::PHYSICAL_THERAPY_DEVICE);
				break;
			case 4:
				if (contains<Equipment>(accessibleEquipment, Equipment::ROBOTIC_SYSTEM, "sprzętu")) continue;
				accessibleEquipment.push_back(Equipment::ROBOTIC_SYSTEM);
				break;
			default:
				continue;
			}
		}

		cout << "Wybrano następujący sprzęt:" << endl;
		for (auto& equipment : accessibleEquipment)
		{
			cout << equipmentToString(equipment) << endl;
		}
		return true;
	}



	bool MainMenu::jointLoadService(unsigned int& serviceCost,
	                                    unsigned int& requiredDocSize,
	                                    unsigned int& serviceId,
	                                    unsigned int& serviceDuration,
	                                    Specialisation& specjalizacja,
	                                    string& serviceName
	) const
	{
		string tmp2;
		unsigned int input1;

		cout << "Podaj nazwę usługi: ";
		getline(cin, serviceName);

		cout << "Podaj koszt usługi: ";
		getline(cin, tmp2);
		if (!checkInt(tmp2, serviceCost)) return false;

		cout << "Podaj liczbe potrzebnych lekarzy: ";
		getline(cin, tmp2);
		if (!checkInt(tmp2, requiredDocSize)) return false;

		cout << "Podaj identyfikator usługi: ";
		getline(cin, tmp2);
		if (!checkInt(tmp2, serviceId)) return false;

		cout << "Podaj długość usługi: ";
		getline(cin, tmp2);
		if (!checkInt(tmp2, serviceDuration)) return false;;

		return specialisationLoad(specjalizacja);
	}

	bool MainMenu::specialisationLoad(Specialisation& spec) const
	{
		string tmp2;
		cout << "Podaj wymaganą specjalizacje lekarza " << endl;
		cout << "<0> - " + specialisationToString(Specialisation::PHYSIOTHERAPIST) << endl;
		cout << "<1> - " + specialisationToString(Specialisation::ORTHOPEDIST) << endl;
		cout << "<2> - " + specialisationToString(Specialisation::NEUROLOGIST) << endl;
		cout << "<3> - " + specialisationToString(Specialisation::SPORTS_MEDICINE) << endl;
		cout << "<4> - " + specialisationToString(Specialisation::MASSAGE_THERAPIST) << endl;
		cout << "<5> - " + specialisationToString(Specialisation::RHEUMATOLOGIST) << endl;

		int input1;

		getline(cin, tmp2);

		if (!isAmount(tmp2, 1)) return false;;
		input1 = isDigit(tmp2[0], '5');
		if (input1 == -1) return false;

		switch (input1)
		{
		case 0:
			spec = Specialisation::PHYSIOTHERAPIST;
			break;
		case 1:
			spec = Specialisation::ORTHOPEDIST;
			break;
		case 2:
			spec = Specialisation::NEUROLOGIST;
			break;
		case 3:
			spec = Specialisation::SPORTS_MEDICINE;
			break;
		case 4:
			spec = Specialisation::MASSAGE_THERAPIST;
			break;
		case 5:
			spec = Specialisation::RHEUMATOLOGIST;
			break;
		}
		return true;
	}

	bool MainMenu::jointLoadPersonnel(std::string& firstName, std::string& lastName,
	                                      unsigned int& personnelId) const
	{
		string tmp2;
		cout << "Podaj imię specjalisty: ";
		getline(cin, firstName);

		cout << "Podaj nazwę nazwisko specjalisty: ";
		getline(cin, lastName);

		cout << "Podaj identyfikator specjalisty: ";
		getline(cin, tmp2);
		if (!checkInt(tmp2, personnelId)) return false;

		return true;
	}




	bool MainMenu::checkDate(const string& dateInput, const string& timeInput,
	                             boost::posix_time::ptime& parsedTime) const
	{
		try
		{
			string fullDateTime = dateInput + " " + timeInput + ":00";
			parsedTime = boost::posix_time::time_from_string(fullDateTime);

			return true;
		}
		catch (const exception& e)
		{
			cerr << "Niepoprawny format daty lub czasu." << endl;
			return false;
		}
	}
}
