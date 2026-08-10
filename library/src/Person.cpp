#include "Person.h"
#include <sstream>
#include "enums/Status.h"

namespace MedicalClinic
{

    Person::Person(const std::string& name, const std::string& lastName) : name(name),
                                                                           lastName(lastName)
    {
    }

    Person::~Person()
    {
    }

    const std::string& Person::getName() const
    {
        return name;
    }

    void Person::setName(const std::string& name)
    {
        this->name = name;
    }

    void Person::setLastName(const std::string& lastName1)
    {
        lastName = lastName1;
    }

    const std::string& Person::getLastName() const
    {
        return lastName;
    }

    const std::string Person::getInfo() const
    {
        std::ostringstream oss;

        oss << "Osoba, imię: " + getName() + ", nazwisko: " + getLastName()+ ", status: " + statusToString(getEntityStatus());
       
        return oss.str();
    }
}
