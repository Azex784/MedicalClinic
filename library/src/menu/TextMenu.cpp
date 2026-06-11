#include "menu/TextMenu.h"
#include <iostream>
#include "services/Service.h"

using namespace std;

bool TerminalMenu::isContinue() const
{
	string tmp1;
	int input1;
	cout << "Czy chesz kontynuować? (0/1)" << endl;

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
}

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

template <typename type>
bool TerminalMenu::contains(vector<type> vectorOfValues, type value, const string& itemName) const
{
	if (vectorOfValues.empty()) return false;
	for (auto& item : vectorOfValues)
	{
		if (item == value)
		{
			cerr << "Nie można dodać tego samego " + itemName + " dwa razy!" << endl;
			return true;
		}
	}
	return false;
}

bool TerminalMenu::checkInt(const string& tmp, unsigned int& liczba) const
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

template <typename type>
void TerminalMenu::displayAll(vector<type> wektor) const
{
	for (auto& element : wektor)
	{
		cout << element->getInfo() << endl;
	}
}

bool TerminalMenu::loadEquipment(vector<Equipment>& accessibleEquipment) const
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

template <typename type>
bool TerminalMenu::displaySpecific(type patient, const string& msg) const
{
	if (patient == nullptr)
	{
		cerr << "Wprowadzono nieprawidłowy " + msg + "." << endl;
		return false;
	}
	cout << patient->getInfo() << endl;
	return true;
}

bool TerminalMenu::jointLoadService(unsigned int& serviceCost,
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

bool TerminalMenu::specialisationLoad(Specialisation& spec) const
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

bool TerminalMenu::jointLoadPersonnel(std::string& firstName, std::string& lastName,
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


template <typename type, typename ManagerPtr>
bool TerminalMenu::findByInt(const string& msg, ManagerPtr manager, type returnValue) const
{
	string tmp2;
	unsigned int uniqeParamter = 0;

	cout << "Podaj identyfikator " + msg + ", która ma być wyświetlona: ";
	getline(cin, tmp2);

	if (!checkInt(tmp2, uniqeParamter)) return false;

	if (returnValue != nullptr)
	{
		returnValue = manager->get(uniqeParamter);
	}
	auto& thing = manager->get(uniqeParamter);
	if (!displaySpecific<type>(thing, "identyfikator" + msg)) return false;

	return true;
}


TerminalMenu::TerminalMenu() :
	logicManger(make_shared<LogicManager>())
{
}

//Zrobione
void TerminalMenu::start() const
{
	cout << "Witaj w centrum rehabilitacji!" << endl;

	bool exit = false;
	string tmp;
	int input;
	while (!exit)
	{
		cout << "<0> - wyjście" << endl;
		cout << "<1> - obsługa pacjenta" << endl;
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

//Zrobione
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
				catch (const ArchiveArchivedException& logicException)
				{
					cerr << logicException.what() << endl;
					continue;
				}
			}
		case 3:
			{
				auto vector = logicManger->getPatientManager()->findAll();
				displayAll<PatientPtr>(vector);

				break;
			}
		case 4:
			{
				string personalId;
				cout << "Podaj PESEL pacjenta: ";
				getline(cin, personalId);

				auto& patient = logicManger->getPatientManager()->get(personalId);
				if (!displaySpecific<PatientPtr>(patient, "pesel")) continue;

				break;
			}
		default:
			continue;
		}
	}
}

void TerminalMenu::appointment() const
{
	cout << "Wybrałeś obsługę wizyty!" << endl;

	bool exit = false;
	string tmp;
	int input;
	while (!exit)
	{
		cout << "<0> - powrót" << endl;
		cout << "<1> - dodaj nową wizytę" << endl;
		cout << "<2> - zmień termin wizyty" << endl;
		cout << "<3> - anuluj wizytę" << endl;
		cout << "<4> - wyświetl wszystkie wizyty konkretnego specjalisty" << endl;
		cout << "<5> - wyświetl wszystkie wizyty konkretnej sali" << endl;
		cout << "<6> - wyświetl wszystkie wizyty konkretnego pacjenta" << endl;
		cout << "<7> - wyświetl wszystkie wizyty konkretnej usługi" << endl;

		getline(cin, tmp);

		if (!isAmount(tmp, 1)) continue;
		input = isDigit(tmp[0], '7');

		switch (input)
		{
		case 0:
			exit = true;
			break;
		case 1:
			{
				string personalId;
				unsigned int appointmentId;

				cout << "Podaj odpowiednie unikalne wartości poszczeólnych atrybutów spotkania." << endl;

				cout << "Podaj PESEL pacjenta: ";
				getline(cin, personalId);

				auto& patient = logicManger->getPatientManager()->get(personalId);
				if (!displaySpecific<PatientPtr>(patient, "pesel")) continue;


				cout << "Podaj uniklane parametry personelu, który chesz przypisać do wizyty" << endl;

				while (true)
				{
					PersonnelPtr searchedPersonnel = nullptr;
					if (!findByInt<PersonnelPtr>("specjalisty", logicManger->getPersonnelManager(), searchedPersonnel))
						continue;

					if (!isContinue()) break;
				}


				RoomPtr searchedRoom = nullptr;
				if (!findByInt<RoomPtr>("sali", logicManger->getRoomManager(), searchedRoom)) continue;

				ServicePtr searchedService = nullptr;
				if (!findByInt<ServicePtr>("usługi", logicManger->getServiceManager(), searchedService)) continue;

				cout << "Podaj unikalny parametr spotkania" << endl;
				getline(cin, tmp);
				if (!checkInt(tmp, appointmentId)) continue;

			}
		case 2:
			{
			}
		case 3:
			{
			}
		case 4:
			{
			}
		case 5:
			{
			}
		case 6:
			{
			}
		case 7:
			{
			}
		default:
			continue;
		}
	}
}

//Zrobione
void TerminalMenu::room() const
{
	cout << "Wybrałeś obsługe sali!" << endl;

	bool exit = false;
	string tmp;
	int input;
	while (!exit)
	{
		cout << "<0> - powrót" << endl;
		cout << "<1> - dodaj salę rehabilitacyjną" << endl;
		cout << "<2> - dodaj salę konsultacyjną" << endl;
		cout << "<3> - deaktywuj salę" << endl;
		cout << "<4> - wyświetl wszystkie sale" << endl;
		cout << "<5> - wyświetl konkretną salę" << endl;

		getline(cin, tmp);

		if (!isAmount(tmp, 1)) continue;
		input = isDigit(tmp[0], '5');

		switch (input)
		{
		case 0:
			exit = true;
			break;
		case 1:
			{
				string tmp2;
				unsigned int roomNumber = 0;
				unsigned int maxCapacity = 0;
				vector<Equipment> accessibleEquipment;

				cout << "Podaj numer sali: ";
				getline(cin, tmp2);

				if (!checkInt(tmp2, roomNumber)) continue;

				cout << "Podaj maksymlną ilość specjalistów: ";
				getline(cin, tmp2);

				if (!checkInt(tmp2, maxCapacity)) continue;

				if (!loadEquipment(accessibleEquipment)) continue;

				try
				{
					logicManger->getRoomManager()->addRehabillitationRoom(roomNumber, accessibleEquipment, maxCapacity);
					cout << "Sukces! Udało się dodać salę rehabilitacyjną: " << logicManger->getRoomManager()->
						get(roomNumber)->getInfo() << endl;
					break;
				}
				catch (LogicException& le)
				{
					cerr << le.what() << endl;
					continue;
				}
				catch (ExistException& ee)
				{
					cerr << ee.what() << endl;
					continue;
				}
			}
		case 2:
			{
				string tmp2;
				unsigned int roomNumber = 0;

				cout << "Podaj numer sali: ";
				getline(cin, tmp2);

				if (!checkInt(tmp2, roomNumber)) continue;

				try
				{
					logicManger->getRoomManager()->addConsultationRoom(roomNumber);
					cout << "Sukces! Udało się dodać salę konsultacyjną: " << logicManger->getRoomManager()->
						get(roomNumber)->getInfo() << endl;
					break;
				}
				catch (ExistException& ee)
				{
					cerr << ee.what() << endl;
					continue;
				}
			}
		case 3:
			{
				string tmp2;
				unsigned int roomNumber = 0;

				cout << "Podaj numer sali, która ma być wyłączona z użytku: ";
				getline(cin, tmp2);

				if (!checkInt(tmp2, roomNumber)) continue;

				try
				{
					logicManger->removeRoom(roomNumber);
					cout << "Sukces! Udało się wyłączyć z użytku sale: " << logicManger->getRoomManager()->
						get(roomNumber)->getInfo() << endl;
					break;
				}
				catch (NoExistException& ee)
				{
					cerr << ee.what() << endl;
					continue;
				}
				catch (const ArchiveArchivedException& logicException)
				{
					cerr << logicException.what() << endl;
					continue;
				}
			}
		case 4:
			{
				auto w = logicManger->getRoomManager()->findAll();
				displayAll<RoomPtr>(w);
				break;
			}
		case 5:
			{
				if (!findByInt<RoomPtr>("sali", logicManger->getRoomManager())) continue;
				break;
			}
		default:
			continue;
		}
	}
}

//Zrobione
void TerminalMenu::service() const
{
	cout << "Wybrałeś obsługę usługi!" << endl;

	bool exit = false;
	string tmp;
	int input;
	while (!exit)
	{
		cout << "<0> - powrót" << endl;
		cout << "<1> - dodaj nową rehabilitacje" << endl;
		cout << "<2> - dodaj nową konsultację" << endl;
		cout << "<3> - deaktywuj usługę" << endl;
		cout << "<4> - wyświetl wszystkie usługi" << endl;
		cout << "<5> - wyświetl konkretną usługę" << endl;

		getline(cin, tmp);

		if (!isAmount(tmp, 1)) continue;
		input = isDigit(tmp[0], '5');

		switch (input)
		{
		case 0:
			exit = true;
			break;
		case 1:
			{
				string tmp2, serviceName;
				unsigned int serviceCost, serviceDuration, requiredNurseSize, requiredDocSize, serviceId;
				vector<Equipment> requiredEquipment;
				Specialisation requiredSpecialisation;

				if (!jointLoadService(serviceCost, requiredDocSize, serviceId, serviceDuration, requiredSpecialisation,
				                      serviceName))
					continue;

				cout << "Podaj potrzebną ilość pielęgniarek: ";
				getline(cin, tmp2);
				if (!checkInt(tmp2, requiredNurseSize)) continue;

				if (!loadEquipment(requiredEquipment)) continue;

				try
				{
					logicManger->getServiceManager()->addRehabilitation(serviceCost, serviceDuration,
					                                                    serviceName, serviceId,
					                                                    requiredEquipment,
					                                                    requiredSpecialisation, requiredDocSize,
					                                                    requiredNurseSize);
					cout << "Sukces! Udało się dodać rehabilitacje: " << logicManger->getServiceManager()->
						get(serviceId)->getInfo() << endl;
					break;
				}
				catch (LogicException& le)
				{
					cerr << le.what() << endl;
					continue;
				}
				catch (ExistException& ee)
				{
					cerr << ee.what() << endl;
					continue;
				}
				catch (length_error& ee)
				{
					cerr << ee.what() << endl;
					continue;
				}
			}
		case 2:
			{
				string tmp2, serviceName, topic;
				unsigned int serviceCost, serviceDuration, requiredDocSize, serviceId, input1;
				Specialisation requiredSpecialisation;
				bool isOnline;

				if (!jointLoadService(serviceCost, requiredDocSize, serviceId, serviceDuration, requiredSpecialisation,
				                      serviceName))
					continue;

				cout << "Podaj tematat konsultacji: ";
				getline(cin, topic);

				cout << "Czy konsultacja jest w trybie online(<0>,<1>)? " << endl;

				getline(cin, tmp2);

				if (!isAmount(tmp2, 1)) continue;
				input1 = isDigit(tmp2[0], '1');
				if (input1 == -1) continue;

				switch (input1)
				{
				case 0:
					isOnline = false;
					break;
				case 1:
					isOnline = true;
					break;
				}
				try
				{
					logicManger->getServiceManager()->addConsultation(serviceCost, serviceDuration,
					                                                  serviceName, serviceId,
					                                                  requiredSpecialisation, topic, requiredDocSize,
					                                                  isOnline);
					cout << "Sukces! Udało się dodać konsultacje: " << logicManger->getServiceManager()->
						get(serviceId)->getInfo() << endl;
					break;
				}
				catch (LogicException& le)
				{
					cerr << le.what() << endl;
					continue;
				}
				catch (ExistException& ee)
				{
					cerr << ee.what() << endl;
					continue;
				}
				catch (length_error& ee)
				{
					cerr << ee.what() << endl;
					continue;
				}
			}
		case 3:
			{
				string tmp2;
				unsigned int serviceId = 0;

				cout << "Podaj identyfikator, usługi która ma być wyłączona z użytku: ";
				getline(cin, tmp2);

				if (!checkInt(tmp2, serviceId)) continue;

				try
				{
					logicManger->removeService(serviceId);
					cout << "Sukces! Udało się wyłączyć z użytku usługę: " << logicManger->getServiceManager()->
						get(serviceId)->getInfo() << endl;
					break;
				}
				catch (NoExistException& ee)
				{
					cerr << ee.what() << endl;
					continue;
				}
				catch (const ArchiveArchivedException& logicException)
				{
					cerr << logicException.what() << endl;
					continue;
				}
				catch (const DateException& dateException)
				{
					cerr << dateException.what() << endl;
					continue;
				}
			}
		case 4:
			{
				auto w = logicManger->getServiceManager()->findAll();
				displayAll<ServicePtr>(w);
				break;
			}
		case 5:
			{
				if (!findByInt<ServicePtr>("usługi", logicManger->getServiceManager())) continue;
				break;
			}
		default:
			continue;
		}
	}
}


void TerminalMenu::personnel() const
{
	cout << "Wybrałeś obsługe personelu!" << endl;

	bool exit = false;
	string tmp;
	int input;
	while (!exit)
	{
		cout << "<0> - powrót" << endl;
		cout << "<1> - dodaj nowego lekarza" << endl;
		cout << "<2> - dodaj nową pielegniarkę" << endl;
		cout << "<3> - zwolnij specjalistę" << endl;
		cout << "<4> - wyświetl wszystkich specjalistów" << endl;
		cout << "<5> - wyświetl konkretnego specjaliste" << endl;

		getline(cin, tmp);

		if (!isAmount(tmp, 1)) continue;
		input = isDigit(tmp[0], '5');

		switch (input)
		{
		case 0:
			exit = true;
			break;
		case 1:
			{
				string tmp2, name, lastName;
				unsigned int personnelId, doctorCost;
				vector<Specialisation> specialisations;

				if (!jointLoadPersonnel(name, lastName, personnelId)) continue;

				cout << "Podaj koszt prestiżu lekarza: ";
				getline(cin, tmp2);
				if (!checkInt(tmp2, doctorCost)) continue;;

				while (true)
				{
					Specialisation spc;
					if (!specialisationLoad(spc))
					{
						cerr << "Wprowadzona niepoprawną specjalizację." << endl;
						continue;
					}

					if (contains<Specialisation>(specialisations, spc, "specjalizacji")) continue;

					specialisations.push_back(spc);

					if (!isContinue()) break;
				}

				try
				{
					logicManger->getPersonnelManager()->addDoctor(name, lastName, personnelId, specialisations,
					                                              doctorCost);

					cout << "Sukces! Udało się dodać lekarza: " << logicManger->getPersonnelManager()->
						get(personnelId)->getInfo() << endl;
					break;
				}
				catch (LogicException& le)
				{
					cerr << le.what() << endl;
					continue;
				}
				catch (ExistException& ee)
				{
					cerr << ee.what() << endl;
					continue;
				}
				catch (length_error& ee)
				{
					cerr << ee.what() << endl;
					continue;
				}
			}
		case 2:
			{
				string tmp2, name, lastName;
				unsigned int personnelId = 0;

				if (!jointLoadPersonnel(name, lastName, personnelId)) continue;

				try
				{
					logicManger->getPersonnelManager()->addNurse(name, lastName, personnelId);

					cout << "Sukces! Udało się dodać pielęgniarke: " << logicManger->getPersonnelManager()->
						get(personnelId)->getInfo() << endl;
					break;
				}
				catch (LogicException& le)
				{
					cerr << le.what() << endl;
					continue;
				}
				catch (ExistException& ee)
				{
					cerr << ee.what() << endl;
					continue;
				}
				catch (length_error& ee)
				{
					cerr << ee.what() << endl;
					continue;
				}
			}
		case 3:
			{
				string tmp2;
				unsigned int personnelId = 0;

				cout << "Podaj identyfikator specialisty, który ma zostać zwolniony(zaarchiwiowany): ";
				getline(cin, tmp2);
				if (!checkInt(tmp2, personnelId)) continue;

				try
				{
					logicManger->removePersonnel(personnelId);
					cout << "Sukces! Udało się zwolnić specialistę: " << logicManger->getPersonnelManager()->
						get(personnelId)->getInfo() << endl;
					break;
				}
				catch (NoExistException& ee)
				{
					cerr << ee.what() << endl;
					continue;
				}
				catch (const ArchiveArchivedException& logicException)
				{
					cerr << logicException.what() << endl;
					continue;
				}
			}
		case 4:
			{
				auto w = logicManger->getPersonnelManager()->findAll();
				displayAll<PersonnelPtr>(w);
				break;
			}
		case 5:
			{
				if (!findByInt<PersonnelPtr>("specialisty", logicManger->getPersonnelManager())) continue;
				break;
			}
		default:
			continue;
		}
	}
};
