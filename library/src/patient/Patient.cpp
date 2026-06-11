#include "patient/Patient.h"
#include "Exceptions.h"
#include "patient/Address.h"

namespace RehabClinic
{

    const AddressPtr& Patient::getAddress() const
    {
        if (address == nullptr)
        {
            throw NullPointerException("archiveRepository");
        }
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
        return Person::getInfo() + " pacjent o peselu: " + personalNumber + ", adresie: " + getAddress()->getInfo();
    }
}
