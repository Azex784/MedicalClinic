#ifndef REHABILITATIONCENTRE_APPOINTMENTMANAGER_H
#define REHABILITATIONCENTRE_APPOINTMENTMANAGER_H

#include <vector>
#include <boost/date_time/posix_time/ptime.hpp>
#include "typedefs.h"
#include "repositories/AppointmentRepository.h"

/**
 * Klasa reprezentująca zarządce wizyt
 */
class AppointmentManager
{
private:
	std::shared_ptr<AppointmentRepository> repository;
	std::shared_ptr<AppointmentRepository> archiveRepository;

public:
	/**
	 * Domyślny konstruktor menedżera wizyt.
	 * Inicjuje obiekt menedżera
	 */
	AppointmentManager(const PatientRepositoryPtr& patientRepository,
	                   const PersonnelRepositoryPtr& personnelRepository, const RoomRepositoryPtr& roomRepository,
	                   const ServiceRepositoryPtr& serviceRepository);

	/**
	 * Konstruktor menedżera wizyt z niestandardową ścieżką do pliku danych(głownie testy i do archive).
	 * @param fileName Ścieżka do pliku tekstowego.
	 */
	AppointmentManager(const std::string& fileName,const std::string& fileNameArchive, const PatientRepositoryPtr& patientRepository,
	                   const PersonnelRepositoryPtr& personnelRepository, const RoomRepositoryPtr& roomRepository,
	                   const ServiceRepositoryPtr& serviceRepository);

	/**
	 * Domyślny destruktor menedżera wizyt, które zapisuje dane na dysku.
	 */
	~AppointmentManager();

	/**
	* Zwraca obiekt repozytorium archiwalnego przypisany do tego menedżera.
	* @return Stała referencja do obiektu repozytorium.
	*/
	const std::shared_ptr<AppointmentRepository>& getArchiveRepository() const;

	/**
	 * Wyszukuje obiekty w repozytorium ARCHIWALNYM spełniające zadany warunek.
	 * @param up Predykat.
	 * @return Wektor zawierający obiekty spełniające kryteria predykatu.
	 */
	const std::vector<AppointmentPtr> findByArchive(AppointmentPredicate up) const;
	/**
	* Zwraca obiekt repozytorium przypisany do tego menedżera.
	* @return Stała referencja do obiektu repozytorium.
	*/
	const std::shared_ptr<AppointmentRepository>& getRepository() const;

	/**
	 * Zwraca pojedynczy obiekt z repozytorium na podstawie unikalnego parametru.
	 * @param up Unikalny parametr identyfikujący obiekt.
	 * @return Stała referencja do znalezionego obiektu.
	 */
	const AppointmentPtr get(const unsigned int up) const;

	/**
	 * Wyszukuje obiekty w repozytorium spełniające zadany warunek.
	 * @param up Predykat.
	 * @return Wektor zawierający obiekty spełniające kryteria predykatu.
	 */
	const std::vector<AppointmentPtr> findBy(AppointmentPredicate up) const;

	/**
	 * Zwraca wszystkie obiekty znajdujące się obecnie w repozytorium.
	 * @return Wektor zawierający wszystkie obiekty.
	 */
	const std::vector<AppointmentPtr> findAll() const;

	/**
	 * Metoda zwracająca wszystkie wizyty przypisane do danego pacjenta.
	 * @param patient Inteligentny wskaźnik na pacjenta.
	 * @return Wektor wskaźników na wizyty pacjenta.
	 */
	std::vector<AppointmentPtr> getPatientAppointments(const PatientPtr& patient) const;

	/**
	 * Metoda zwracająca wszystkie wizyty obsługiwane przez danego pracownika.
	 * @param personnel Inteligentny wskaźnik na członka personelu.
	 * @return Wektor wskaźników na wizyty przypisane do pracownika.
	 */
	std::vector<AppointmentPtr> getPersonnelAppointments(const PersonnelPtr& personnel) const;

	/**
	 * Metoda zwracająca wszystkie wizyty zaplanowane w ramach konkretnej usługi.
	 * @param service Inteligentny wskaźnik na usługę.
	 * @return Wektor wskaźników na wizyty powiązane z usługą.
	 */
	std::vector<AppointmentPtr> getServiceAppointments(const ServicePtr& service) const;

	/**
	 * Metoda zwracająca wszystkie wizyty zaplanowane w danym pokoju/sali.
	 * @param room Inteligentn wskaźnik na pokój.
	 * @return Wektor wskaźników na wizyty przypisane do pokoju.
	 */
	std::vector<AppointmentPtr> getRoomAppointments(const RoomPtr& room) const;

	/**
	 * Metoda obliczająca koszty wszystkich wizyt danego pacjenta.
	 * @param patient Inteligentny wskaźnik na pacjenta.
	 * @return Całkowita kwota do zapłaty.
	 */
	unsigned int getAppointmentsCost(const PatientPtr& patient) const;

	/**
	 * Metoda tworząca nową wizytę.
	 * @param patient Wskaźnik na pacjenta.
	 * @param service Wskaźnik na wybraną usługę.
	 * @param personnel Wskaźnik na pracowników obsługujących.
	 * @param appointmentBeginDate Czas rozpoczęcia wizyty (obiekt ptime).
	 * @param room sala w której odbedzie sie wizyta.
	 * @param appointmentId unikalny parametr.
	 * @return Inteligentny wskaźnik na nowo utworzoną wizytę.
	 */
	AppointmentPtr arrangeAppointment(const PatientPtr& patient, const ServicePtr& service,
	                                  const std::vector<PersonnelPtr>& personnel,
	                                  const boost::posix_time::ptime& appointmentBeginDate,
	                                  const RoomPtr& room, unsigned int appointmentId);

	/**
	 * Metoda kończąca trwającą wizytę i podsumowująca jej stan.
	 * Metoda ta może być użyta raz i sprawia, że wizyta staje się archiwalna,
	 * zwraca koszt wizyty.
	 * @param appointmentId Unikalny paramter.
	 * @return Koszt zakończonej wizyty.
	 */
	unsigned int finishAppointment(unsigned int appointmentId);

	/**
	 * Metoda zmieniająca datę wybranej wizyty.
	 * @param _date Nowy termin wizyty.
	 * @param appointmentId Nowy termin wizyty.
	 */
	void changeAppointment(const boost::posix_time::ptime& _date, const unsigned int appointmentId);

	/**
	 * Metoda anulująca wizytę zaplanowaną na dany termin.
	 * Usuwa ona ją z repozytrium(pliku).
	 * @param appointmentId Unikalny paramter spotkania.
	 */
	void cancelAppointment(const unsigned int appointmentId);

	/**
	 * Metoda sprawdzająca czy terminy danego spotkania nie kolidują ze spotkaniami np. personelu czy pacjenta
	 * @param appointments
	 * @param beginDate
	 * @param duration
	 * @return True jesli nie koliduje, false jesli koliduje
	 */
	bool isDate(std::vector<AppointmentPtr> appointments, const boost::posix_time::ptime beginDate, unsigned int duration) const;


	/**
	 * Zwraca wszystkie obiekty znajdujące się obecnie w repozytorium archive.
	 * @return Wektor zawierający wszystkie obiekty.
	 */
	const std::vector<AppointmentPtr> findAllArchive() const;
};


#endif //REHABILITATIONCENTRE_APPOINTMENTMANAGER_H
