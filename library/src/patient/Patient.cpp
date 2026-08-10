#include "patient/Patient.h"
#include "Exceptions.h"
#include "patient/Address.h"

namespace MedicalClinic
{
    const AddressPtr& Patient::getAddress() const
    {
        if (address == nullptr)
        {
            throw NullPointerException("adres");
        }
        return address;
    }

    Patient::Patient(const std::string& name, const std::string& lastName, const std::string& personalNumber,
                     const AddressPtr& address) : Person(name, lastName),
                                                  personalNumber(personalNumber),
                                                  address(address)
    {
        if (address == nullptr)
        {
            throw NullPointerException("adres");
        }
    }

    const std::string& Patient::getUniqueParameter() const
    {
        return personalNumber;
    }

    const std::string Patient::getInfo() const
    {
        return Person::getInfo() + ", pacjent, pesel: " + personalNumber + ", " + getAddress()->getInfo();
    }
}
