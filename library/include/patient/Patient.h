#ifndef REHABILITATIONCENTRE_PATIENT_H
#define REHABILITATIONCENTRE_PATIENT_H

#include "string"
#include "Person.h"
#include "typedefs.h"

/**
 * Klasa reprezentująca pacjenta
 */
class Patient : public Person{
public:
    Patient(const std::string& name, const std::string& last_name, const std::string& personal_number,
        const AddressPtr& address);
    ~Patient() = default;

private:
    std::string personalNumber;
    AddressPtr address;

public:
    const std::string& getPersonalNumber() const;
    const AddressPtr& getAddress() const;
    const std::string getInfo() const override;
};


#endif //REHABILITATIONCENTRE_PATIENT_H