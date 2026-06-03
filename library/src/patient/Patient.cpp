#include "patient/Patient.h"
#include "patient/Address.h"

const AddressPtr& Patient::getAddress() const
{
    return address;
}

Patient::Patient(const std::string& name, const std::string& last_name, const std::string& personal_number,
                 const AddressPtr& address) : Person(name, last_name),
                                              personalNumber(personal_number),
                                              address(address)
{
}

const std::string& Patient::getPersonalNumber() const
{
    return personalNumber;
}

const std::string Patient::getInfo() const
{
    return Person::getInfo() + " pacjent o adresie: \n" + getAddress()->getInfo();
}
