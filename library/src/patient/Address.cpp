#include "patient/Address.h"

namespace RehabClinic
{
    const std::string& Address::getCity() const
    {
        return city;
    }

    const std::string& Address::getStreet() const
    {
        return street;
    }

    const std::string& Address::getNumber() const
    {
        return number;
    }

    Address::Address(const std::string& city, const std::string& street, const std::string& number) : city(city),
        street(street),
        number(number)
    {
    }

    const std::string Address::getInfo() const
    {
        return "Miasto: " + getCity() + ", ulica: " + getStreet() + " " + getNumber();
    }
}
