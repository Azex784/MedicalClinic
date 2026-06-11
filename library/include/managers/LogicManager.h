#ifndef REHABILITATIONCENTRE_LOGICMANAGER_H
#define REHABILITATIONCENTRE_LOGICMANAGER_H

#include "managers/PatientManager.h"
#include "managers/PersonnelManager.h"
#include "managers/ServiceManager.h"
#include "managers/AppointmentManager.h"
#include "managers/RoomManager.h"

/**
 * Klasa reprezentująca zarządce logiki aplikacji
 */
class LogicManager
{
private:
	std::shared_ptr<PersonnelManager> personnelManager;
	std::shared_ptr<PatientManager> patientManager;
	std::shared_ptr<ServiceManager> serviceManager;
	std::shared_ptr<RoomManager> roomManager;
	std::shared_ptr<AppointmentManager> appointmentManager;

public:
	/**
	 * Konstruktor domyślny
	 */
	LogicManager();

	/**
	 * Konstruktor do testów
	 * @param fileName1
	 * @param fileName2
	 * @param fileName3
	 * @param fileName4
	 * @param fileName5
	 */
	LogicManager(const std::string& fileName1, const std::string& fileName2, const std::string& fileName3,
	             const std::string& fileName4, const std::string& fileName5,
	             const std::string& fileName6);

	/**
	 * Domyślny destruktor
	 */
	~LogicManager() = default;

	/**
	 * Zwraca zarządcę personelu.
	 * @return Stała referencja do wskaźnika zarządzającego obiektem PersonnelManager.
	 */
	const std::shared_ptr<PersonnelManager>& getPersonnelManager() const;

	/**
	 * Zwraca zarządcę pacjentów.
	 * @return Stała referencja do wskaźnika zarządzającego obiektem PatientManager.
	 */
	const std::shared_ptr<PatientManager>& getPatientManager() const;

	/**
	 * @brief Zwraca zarządcę usług medycznych.
	 * @return Stała referencja do wskaźnika zarządzającego obiektem ServiceManager.
	 */
	const std::shared_ptr<ServiceManager>& getServiceManager() const;

	/**
	 * Zwraca zarządcę wizyt.
	 * @return Stała referencja do wskaźnika zarządzającego obiektem AppointmentManager.
	 */
	const std::shared_ptr<AppointmentManager>& getAppointmentManager() const;

	/**
	 * Zwraca zarządcę pomieszczeń.
	 * @return Stała referencja do wskaźnika zarządzającego obiektem RoomManager.
	 */
	const std::shared_ptr<RoomManager>& getRoomManager() const;

	/**
	 * Sprawia, że osoba z personelu staje się archiwalna,
	 * anuluje wszystkie spotkania tej osoby i staje się ona nieaktywna.
	 * @param personnelId
	 */
	void removePersonnel(unsigned int personnelId);

	/**
	 * Sprawia, że pacjent staje się archiwalny, JEŚLI nie ma żadnych spotkań.
	 * @param personalID
	 */
	void unregisterPatient(const std::string& personalID);

	/**
	 * Sprawia, że pokój staje się nieaktywny, archiwalny i anuluje
	 * wszystkie spotkania przypisane do tego pokoju.
	 * @param roomNumber
	 */
	void removeRoom(unsigned int roomNumber);

	/**
	 * Sprawia, że dana usługa staje się niedostępna i archiwalna,
	 * JEŚLI nie ma zaplanowanych już terminów związanych z tą usługą.
	 * @param serviceID
	 */
	void removeService(unsigned int serviceID);
};


#endif //REHABILITATIONCENTRE_LOGICMANAGER_H
