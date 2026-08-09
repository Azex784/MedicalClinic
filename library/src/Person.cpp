#include "Person.h"

namespace MedicalClinic
{

    Person::Person(const std::string& name, const std::string& lastName) : name(name),
                                                                           lastName(lastName)
    {
        setIsArchive(false);
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

    void Person::setIsArchive(const bool isArchive1)
    {
        isArchive = isArchive1;
    }


    const std::string& Person::getLastName() const
    {
        return lastName;
    }

    bool Person::getIsArchive() const
    {
        return isArchive;
    }

    const std::string Person::getInfo() const
    {
        std::ostringstream oss;
        oss << "Osoba: " + getName() + " " + getLastName();
        if (getIsArchive())
        {
            oss << ", archiwalna";
        }
        else
        {
            oss << ", niearchiwalna";
        }
        return oss.str();
    }
}
