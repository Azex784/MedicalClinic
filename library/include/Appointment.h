#ifndef REHABILITATIONCENTRE_APPOINTMENT_H
#define REHABILITATIONCENTRE_APPOINTMENT_H

#include <boost/date_time.hpp>
#include <string>
#include <vector>
#include "typedefs.h"

/**
 * Klasa reprezentująca spotkanie
 */
class Appointment
{
private:
    boost::posix_time::ptime appointmentBeginDate;
    boost::posix_time::ptime appointmentEndDate = boost::posix_time::not_a_date_time;
    unsigned int appointmentId;
    unsigned int appointmentCost;
    std::vector<PersonnelPtr> personnel;
    PatientPtr patient;
    ServicePtr service;
    RoomPtr room;

public:
    /**
     * Konstruktor tworzący nowy obiekt spotkania i wylicza odrazu date zakonczenia
     * @param appointmentBeginDate Data i czas rozpoczęcia wizyty.
     * @param appointmentId Unikalny identyfikator przypisany do wizyty.
     * @param personnel Wektor wskaźników na personel przypisany do realizacji usługi.
     * @param patient Wskaźnik na pacjenta biorącego udział w wizycie.
     * @param service Wskaźnik na realizowaną usługę.
     * @param room Wskaźnik na przypisaną salę.
     */
    Appointment(const boost::posix_time::ptime& appointmentBeginDate, const unsigned int appointmentId,
                const std::vector<PersonnelPtr>& personnel, const PatientPtr& patient, const ServicePtr& service,
                const RoomPtr& room);

    /**
     * Domyślny destruktor klasy.
     */
    ~Appointment() = default;

    /**
     * Setter appointment beginDate
     * @param appointmentBeginDate
     */
    void setAppointmentBeginDate(const boost::posix_time::ptime& appointmentBeginDate);

    /**
     * Metoda zwracająca informacje o klasie.
     * @return Sformatowany łańcuch znaków zawierający szczegóły wizyty.
     */
    const std::string getInfo() const;

    /**
     * Pobiera datę i czas rozpoczęcia wizyty.
     * @return Referencja do obiektu ptime z datą rozpoczęcia.
     */
    const boost::posix_time::ptime& getAppointmentBeginDate() const;

    /**
     * Pobiera datę i czas zakończenia wizyty.
     * @return Referencja do obiektu ptime z datą zakończenia.
     */
    const boost::posix_time::ptime& getAppointmentEndDate() const;

    /**
     * Pobiera unikalny identyfikator wizyty.
     * @return ID wizyty jako int
     */
    unsigned int getUniqueParameter() const;

    /**.
     * @return Koszt wizyty.
     */
    unsigned int getAppointmentCost() const;

    /**
     * Pobiera listę(vector) personelu przypisanego do wizyty.
     * @return Stała referencja do wektora personelu.
     */
    const std::vector<PersonnelPtr>& getPersonnel() const;

    /**
     * Pobiera pacjenta przypisanego do wizyty.
     * @return Stała referencja na wskaźnik pacjenta.
     */
    const PatientPtr& getPatient() const;

    /**
     * @return Stała referencja na wskaźnik usługi.
     */
    const ServicePtr& getService() const;

    /**
     * @return Stała referencja na wskaźnik sali.
     */
    const RoomPtr& getRoom() const;

    /**
     * Ustawia  czasu zakończenia wizyty
     * Automatycznie wylicza tą datę
     */
    void setAppointmentEndDate();

    /**
     * Przelicza całkowity koszt wizyty dodajc koszt prestizu lekarzy i uslugi
     * Można tyko raz tego uzyc
     * @return Zwraca ostateczny koszt po przeliczeniu.
     */
    const unsigned int setAppointmentCost();
};


#endif //REHABILITATIONCENTRE_APPOINTMENT_H
