#include "Person.h"


Person::Person(const std::string& name, const std::string& last_name) : name(name),
                                                                        lastName(last_name)
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

void Person::setLastName(const std::string& last_name)
{
    lastName = last_name;
}

void Person::setIsArchive(const bool is_archive)
{
    isArchive = is_archive;
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
    return "Osoba: " + getName() + " " + getLastName();
}
