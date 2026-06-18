#include "../../include/menu/TerminalMenu.h"

#include <Appointment.h>
#include <iostream>
#include "services/Service.h"

namespace RehabClinic
{
	using namespace std;


	TerminalMenu::TerminalMenu(): logicManager(make_shared<LogicManager>()), MainMenu(logicManager)
	{
	}

	bool TerminalMenu::registerPatient() const
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
			getLogicManager()->getPatientManager()->registerPatient(
				name, lastName, personalId, city, street, number);
			cout << "Dodano: " << getLogicManager()->getPatientManager()->get(personalId)->getInfo() << endl;
			return true;
		}
		catch (const LogicException& logicException)
		{
			cerr << logicException.what() << endl;
			return false;
		}
		catch (const length_error& length_error)
		{
			cerr << length_error.what() << endl;
			return false;;
		}
		catch (const ExistException& existException)
		{
			cerr << existException.what() << endl;
			return false;;
		}
	}

	bool TerminalMenu::archivePatient() const
	{
		string personalId;
		cout << "Podaj PESEL pacjenta: ";
		getline(cin, personalId);

		try
		{
			getLogicManager()->unregisterPatient(personalId);
			cout << "Sukces! Udało się zaarchiwzować Pacjenta: " << getLogicManager()->getPatientManager()->
				get(personalId)->getInfo() << endl;
			return true;
		}
		catch (const NoExistException& noExistException)
		{
			cerr << noExistException.what() << endl;
			return false;
		}
		catch (const DateException& dateException)
		{
			cerr << dateException.what() << endl;
			return false;
		}
		catch (const ArchiveArchivedException& logicException)
		{
			cerr << logicException.what() << endl;
			return false;
		}
	}

	bool TerminalMenu::addRehabilitationRoom() const
	{
		string tmp2;
		unsigned int roomNumber = 0;
		unsigned int maxCapacity = 0;
		vector<Equipment> accessibleEquipment;

		cout << "Podaj numer sali: ";
		getline(cin, tmp2);

		if (!checkInt(tmp2, roomNumber)) return false;

		cout << "Podaj maksymlną ilość specjalistów: ";
		getline(cin, tmp2);

		if (!checkInt(tmp2, maxCapacity)) return false;

		if (!loadEquipment(accessibleEquipment)) return false;

		try
		{
			getLogicManager()->getRoomManager()->addRehabillitationRoom(
				roomNumber, accessibleEquipment, maxCapacity);
			cout << "Sukces! Udało się dodać salę rehabilitacyjną: " << getLogicManager()->getRoomManager()
				->
				get(roomNumber)->getInfo() << endl;
			return true;
		}
		catch (LogicException& le)
		{
			cerr << le.what() << endl;
			return false;
		}
		catch (ExistException& ee)
		{
			cerr << ee.what() << endl;
			return false;
		}
	}

	bool TerminalMenu::addRehabilitationService() const
	{
		string tmp2, serviceName;
		unsigned int serviceCost, serviceDuration, requiredNurseSize, requiredDocSize, serviceId;
		vector<Equipment> requiredEquipment;
		Specialisation requiredSpecialisation;

		if (!jointLoadService(serviceCost, requiredDocSize, serviceId, serviceDuration,
		                      requiredSpecialisation,
		                      serviceName))
			return false;

		cout << "Podaj potrzebną ilość pielęgniarek: ";
		getline(cin, tmp2);
		if (!checkInt(tmp2, requiredNurseSize)) return false;

		if (!loadEquipment(requiredEquipment)) return false;

		try
		{
			getLogicManager()->getServiceManager()->addRehabilitation(serviceCost, serviceDuration,
			                                                          serviceName, serviceId,
			                                                          requiredEquipment,
			                                                          requiredSpecialisation, requiredDocSize,
			                                                          requiredNurseSize);
			cout << "Sukces! Udało się dodać rehabilitacje: " << getLogicManager()->getServiceManager()->
				get(serviceId)->getInfo() << endl;
			return true;
		}
		catch (LogicException& le)
		{
			cerr << le.what() << endl;
			return false;
		}
		catch (ExistException& ee)
		{
			cerr << ee.what() << endl;
			return false;
		}
		catch (length_error& ee)
		{
			cerr << ee.what() << endl;
			return false;
		}
	}

	bool TerminalMenu::addConsultationService() const
	{
		string tmp2, serviceName, topic;
		unsigned int serviceCost, serviceDuration, requiredDocSize, serviceId, input1;
		Specialisation requiredSpecialisation;
		bool isOnline;

		if (!jointLoadService(serviceCost, requiredDocSize, serviceId, serviceDuration,
		                      requiredSpecialisation,
		                      serviceName))
			return false;

		cout << "Podaj tematu konsultacji: ";
		getline(cin, topic);

		cout << "Czy konsultacja jest w trybie online(<0>,<1>)? " << endl;

		getline(cin, tmp2);

		if (!isAmount(tmp2, 1)) return false;
		input1 = isDigit(tmp2[0], '1');
		if (input1 == -1) return false;

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
			getLogicManager()->getServiceManager()->addConsultation(serviceCost, serviceDuration,
			                                                        serviceName, serviceId,
			                                                        requiredSpecialisation, topic,
			                                                        requiredDocSize,
			                                                        isOnline);
			cout << "Sukces! Udało się dodać konsultacje: " << getLogicManager()->getServiceManager()->
				get(serviceId)->getInfo() << endl;
			return true;
		}
		catch (LogicException& le)
		{
			cerr << le.what() << endl;
			return false;
		}
		catch (ExistException& ee)
		{
			cerr << ee.what() << endl;
			return false;
		}
		catch (length_error& ee)
		{
			cerr << ee.what() << endl;
			return false;
		}
	}

	bool TerminalMenu::addConsultationRoom() const
	{
		string tmp2;
		unsigned int roomNumber = 0;

		cout << "Podaj numer sali: ";
		getline(cin, tmp2);

		if (!checkInt(tmp2, roomNumber)) return false;

		try
		{
			getLogicManager()->getRoomManager()->addConsultationRoom(roomNumber);
			cout << "Sukces! Udało się dodać salę konsultacyjną: " << getLogicManager()->getRoomManager()->
				get(roomNumber)->getInfo() << endl;
			return true;
		}
		catch (ExistException& ee)
		{
			cerr << ee.what() << endl;
			return false;
		}
	}

	bool TerminalMenu::dismissPersonnel() const
	{
		string tmp2;
		unsigned int personnelId = 0;

		cout << "Podaj identyfikator specialisty, który ma zostać zwolniony(zaarchiwiowany): ";
		getline(cin, tmp2);
		if (!checkInt(tmp2, personnelId)) return false;

		try
		{
			getLogicManager()->removePersonnel(personnelId);
			cout << "Sukces! Udało się zwolnić specialistę: " << getLogicManager()->getPersonnelManager()->
				get(personnelId)->getInfo() << endl;
			return true;
		}
		catch (NoExistException& ee)
		{
			cerr << ee.what() << endl;
			return false;
		}
		catch (const ArchiveArchivedException& logicException)
		{
			cerr << logicException.what() << endl;
			return false;
		}
	}

	bool TerminalMenu::addNurse() const
	{
		string tmp2, name, lastName;
		unsigned int personnelId = 0;

		if (!jointLoadPersonnel(name, lastName, personnelId)) return false;

		try
		{
			getLogicManager()->getPersonnelManager()->addNurse(name, lastName, personnelId);

			cout << "Sukces! Udało się dodać pielęgniarke: " << getLogicManager()->getPersonnelManager()->
				get(personnelId)->getInfo() << endl;
			return true;
		}
		catch (LogicException& le)
		{
			cerr << le.what() << endl;
			return false;
		}
		catch (ExistException& ee)
		{
			cerr << ee.what() << endl;
			return false;
		}
		catch (length_error& ee)
		{
			cerr << ee.what() << endl;
			return false;
		}
	}

	bool TerminalMenu::deactivateService() const
	{
		string tmp2;
		unsigned int serviceId = 0;

		cout << "Podaj identyfikator, usługi która ma być wyłączona z użytku: ";
		getline(cin, tmp2);

		if (!checkInt(tmp2, serviceId)) return false;

		try
		{
			getLogicManager()->removeService(serviceId);
			cout << "Sukces! Udało się wyłączyć z użytku usługę: " << getLogicManager()->getServiceManager()
				->
				get(serviceId)->getInfo() << endl;
			return true;
		}
		catch (NoExistException& ee)
		{
			cerr << ee.what() << endl;
			return false;
		}
		catch (const ArchiveArchivedException& logicException)
		{
			cerr << logicException.what() << endl;
			return false;
		}
		catch (const DateException& dateException)
		{
			cerr << dateException.what() << endl;
			return false;
		}
	}

	bool TerminalMenu::addDoctor() const
	{
		string tmp2, name, lastName;
		unsigned int personnelId, doctorCost;
		vector<Specialisation> specialisations;

		if (!jointLoadPersonnel(name, lastName, personnelId)) return false;

		cout << "Podaj koszt prestiżu lekarza: ";
		getline(cin, tmp2);
		if (!checkInt(tmp2, doctorCost)) return false;;

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
			getLogicManager()->getPersonnelManager()->addDoctor(
				name, lastName, personnelId, specialisations,
				doctorCost);

			cout << "Sukces! Udało się dodać lekarza: " << getLogicManager()->getPersonnelManager()->
			                                                                  get(personnelId)->getInfo() << endl;
			return true;
		}
		catch (LogicException& le)
		{
			cerr << le.what() << endl;
			return false;
		}
		catch (ExistException& ee)
		{
			cerr << ee.what() << endl;
			return false;
		}
		catch (length_error& ee)
		{
			cerr << ee.what() << endl;
			return false;
		}
	}

	bool TerminalMenu::deactivateRoom() const
	{
		string tmp2;
		unsigned int roomNumber = 0;

		cout << "Podaj numer sali, która ma być wyłączona z użytku: ";
		getline(cin, tmp2);

		if (!checkInt(tmp2, roomNumber)) return false;

		try
		{
			getLogicManager()->removeRoom(roomNumber);
			cout << "Sukces! Udało się wyłączyć z użytku sale: " << getLogicManager()->getRoomManager()->
				get(roomNumber)->getInfo() << endl;
			return true;
		}
		catch (NoExistException& ee)
		{
			cerr << ee.what() << endl;
			return false;
		}
		catch (const ArchiveArchivedException& logicException)
		{
			cerr << logicException.what() << endl;
			return false;
		}
	}

	bool TerminalMenu::finishAppointment() const
	{
		string tmp;
		unsigned int appointmentId;

		cout << "Podaj unikalny parametr spotkania" << endl;
		getline(cin, tmp);
		if (!checkInt(tmp, appointmentId)) return false;
		try
		{
			int cost = getLogicManager()->getAppointmentManager()->finishAppointment(appointmentId);
			cout << "Sukces! Udało się zakończyć spotaknie" << endl;
			cout << "Suma do zapłaty wynosi: " << to_string(cost) << endl;
			return true;
		}
		catch (LogicException& de)
		{
			cerr << de.what() << endl;
			return false;
		}
	}

	bool TerminalMenu::cancelAppointment() const
	{
		string tmp;
		unsigned int appointmentId;

		cout << "Podaj unikalny parametr spotkania" << endl;
		getline(cin, tmp);
		if (!checkInt(tmp, appointmentId)) return false;
		try
		{
			getLogicManager()->getAppointmentManager()->cancelAppointment(appointmentId);
			cout << "Sukces! Udało się anulować spotkanie " << endl;
			return true;
		}
		catch (LogicException& de)
		{
			cerr << de.what() << endl;
			return false;
		}
	}

	bool TerminalMenu::arrangeAppointment() const
	{
		string personalId, date, hour, tmp;
		unsigned int appointmentId;
		boost::posix_time::ptime beginDate;
		vector<PersonnelPtr> personnel;

		cout << "Podaj odpowiednie unikalne wartości poszczególnych atrybutów spotkania." << endl;

		cout << "Podaj PESEL pacjenta: ";
		getline(cin, personalId);

		auto patient = getLogicManager()->getPatientManager()->get(personalId);
		if (!displaySpecific<PatientPtr>(patient, "pesel")) return false;

		cout << "Podaj unikalne parametry personelu, który chesz przypisać do wizyty" << endl;

		while (true)
		{
			PersonnelPtr searchedPersonnel;

			if (!isContinue()) break;

			if (!findByInt<PersonnelPtr>("specjalisty", getLogicManager()->getPersonnelManager(),
			                             &searchedPersonnel))
				continue;
			if (contains<PersonnelPtr>(personnel, searchedPersonnel, "specjalisty"))
			{
				if (!isContinue()) break;
				else continue;
			}
			personnel.push_back(searchedPersonnel);
		}

		RoomPtr searchedRoom;
		if (!findByInt<RoomPtr>("sali", getLogicManager()->getRoomManager(), &searchedRoom)) return false;

		ServicePtr searchedService;
		if (!findByInt<ServicePtr>("usługi", getLogicManager()->getServiceManager(), &searchedService)) return false;


		cout << "Podaj unikalny parametr spotkania" << endl;
		getline(cin, tmp);
		if (!checkInt(tmp, appointmentId)) return false;


		cout << "Podaj date rozpoczęcia spotkania (format: YYYY-MM-DD)" << endl;
		getline(cin, date);

		cout << "Podaj godzinę rozpoczęcia spotkania (format: HH:MM)" << endl;
		getline(cin, hour);

		if (!checkDate(date, hour, beginDate)) return false;

		try
		{
			getLogicManager()->getAppointmentManager()->arrangeAppointment(
				patient, searchedService, personnel, beginDate, searchedRoom, appointmentId);

			cout << "Sukces! Dodano nową wizytę: " << getLogicManager()->getAppointmentManager()->
			                                                             get(appointmentId)->getInfo() << endl;
			return true;
		}
		catch (LogicException& le)
		{
			cout << le.what() << endl;
			return false;
		}
		catch (DateException& de)
		{
			cout << de.what() << endl;
			return false;
		}
		catch (ActivityException& ae)
		{
			cout << ae.what() << endl;
			return false;
		}
	}

	bool TerminalMenu::changeAppointment() const
	{
		unsigned int appointmentId;
		string date, time, tmp;
		boost::posix_time::ptime beginDate;

		cout << "Podaj unikalny parametr spotkania" << endl;
		getline(cin, tmp);
		if (!checkInt(tmp, appointmentId)) return false;

		cout << "Podaj date rozpoczęcia spotkania (format - 'YYYY-MM-DD')" << endl;
		getline(cin, date);

		cout << "Podaj godzinę rozpoczęcia spotkania (format - 'HH:MM')" << endl;
		getline(cin, time);

		if (!checkDate(date, time, beginDate)) return false;

		try
		{
			getLogicManager()->getAppointmentManager()->changeAppointment(beginDate, appointmentId);
			cout << "Sukces! Zmieniono termin wizyty: " << getLogicManager()->getAppointmentManager()->
			                                                                  get(appointmentId)->getInfo() << endl;
			return true;
		}
		catch (DateException& de)
		{
			cerr << de.what() << endl;
			return false;
		}
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
					if (registerPatient()) break;
					continue;
				}
			case 2:
				{
					if (archivePatient()) break;
					continue;
				}
			case 3:
				{
					auto vector = getLogicManager()->getPatientManager()->findAll();
					displayAll<PatientPtr>(vector);

					break;
				}
			case 4:
				{
					string personalId;
					cout << "Podaj PESEL pacjenta: ";
					getline(cin, personalId);

					auto patient = getLogicManager()->getPatientManager()->get(personalId);
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
			cout << "<4> - zakończ spotkanie" << endl;
			cout << "<5> - wyświetl wszystkie wizyty konkretnego specjalisty" << endl;
			cout << "<6> - wyświetl wszystkie wizyty konkretnej sali" << endl;
			cout << "<7> - wyświetl wszystkie wizyty konkretnego pacjenta" << endl;
			cout << "<8> - wyświetl wszystkie wizyty konkretnej usługi" << endl;

			getline(cin, tmp);

			if (!isAmount(tmp, 1)) continue;
			input = isDigit(tmp[0], '8');

			switch (input)
			{
			case 0:
				exit = true;
				break;
			case 1:
				{
					if (arrangeAppointment()) break;
					continue;
				}
			case 2:
				{
					if (changeAppointment()) break;
					continue;
				}
			case 3:
				{
					if (cancelAppointment()) break;
					continue;
				}
			case 4:
				{
					if (finishAppointment()) break;
					continue;
				}
			case 5:
				{
					string personalId;
					cout << "Podaj PESEL pacjenta: ";
					getline(cin, personalId);

					auto& patient = getLogicManager()->getPatientManager()->get(personalId);
					if (!displaySpecific<PatientPtr>(patient, "pesel")) continue;

					auto appointments = getLogicManager()->getAppointmentManager()->getPatientAppointments(patient);
					displayAll(appointments);
					break;
				}
			case 6:
				{
					PersonnelPtr searchedPersonnel = nullptr;
					if (!findByInt<PersonnelPtr>("specjalisty", getLogicManager()->getPersonnelManager(),
					                             &searchedPersonnel))
						continue;
					auto appointments = getLogicManager()->getAppointmentManager()->getPersonnelAppointments(
						searchedPersonnel);
					displayAll(appointments);
					break;
				}
			case 7:
				{
					RoomPtr searchedRoom = nullptr;
					if (!findByInt<RoomPtr>("sali", getLogicManager()->getRoomManager(), &searchedRoom)) continue;
					auto appointments = getLogicManager()->getAppointmentManager()->getRoomAppointments(searchedRoom);
					displayAll(appointments);
					break;
				}
			case 8:
				{
					ServicePtr searchedService = nullptr;
					if (!findByInt<ServicePtr>("usługi", getLogicManager()->getServiceManager(), &searchedService))
						continue;
					auto appointments = getLogicManager()->getAppointmentManager()->getServiceAppointments(
						searchedService);
					displayAll(appointments);
					break;
				}
				continue;
			}
		}
	}

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
					if (addRehabilitationRoom()) break;
					continue;
				}
			case 2:
				{
					if (addConsultationRoom()) break;
					continue;
				}
			case 3:
				{
					if (deactivateRoom()) break;
					continue;
				}
			case 4:
				{
					auto w = getLogicManager()->getRoomManager()->findAll();
					displayAll<RoomPtr>(w);
					break;
				}
			case 5:
				{
					if (!findByInt<RoomPtr>("sali", getLogicManager()->getRoomManager())) continue;
					break;
				}
			default:
				continue;
			}
		}
	}

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
					if (addRehabilitationService()) break;
					continue;
				}
			case 2:
				{
					if (addConsultationService()) break;
					continue;
				}
			case 3:
				{
					if (deactivateService()) break;
					continue;
				}
			case 4:
				{
					auto w = getLogicManager()->getServiceManager()->findAll();
					displayAll<ServicePtr>(w);
					break;
				}
			case 5:
				{
					if (!findByInt<ServicePtr>("usługi", getLogicManager()->getServiceManager())) continue;
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
					if (addDoctor()) break;
					continue;
				}
			case 2:
				{
					if (addNurse()) break;
					continue;
				}
			case 3:
				{
					if (dismissPersonnel()) break;
					continue;
				}
			case 4:
				{
					auto w = getLogicManager()->getPersonnelManager()->findAll();
					displayAll<PersonnelPtr>(w);
					break;
				}
			case 5:
				{
					if (!findByInt<PersonnelPtr>("specialisty", getLogicManager()->getPersonnelManager())) continue;
					break;
				}
			default:
				continue;
			}
		}
	};
}
