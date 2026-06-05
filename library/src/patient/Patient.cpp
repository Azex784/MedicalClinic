#include "patient/Patient.h"
#include "patient/Address.h"

const AddressPtr& Patient::getAddress() const
{
    return address;
}

Patient::Patient(const std::string& name, const std::string& lastName, const std::string& personalNumber,
                 const AddressPtr& address) : Person(name, lastName),
                                              personalNumber(personalNumber),
                                              address(address)
{
}

const std::string& Patient::getUniqueParameter() const
{
    return personalNumber;
}

const std::string Patient::getInfo() const
{
    return Person::getInfo() + " pacjent o adresie: \n" + getAddress()->getInfo();
}
