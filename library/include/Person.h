#ifndef REHABILITATIONCENTRE_PERSON_H
#define REHABILITATIONCENTRE_PERSON_H

#include <string>

/**
 * Klasa reprezentująca człowieka
 */
class Person
{
private:
    std::string name;
    std::string lastName;
    bool isArchive;
public:
    virtual const std::string getInfo() const;
    Person(const std::string& name, const std::string& last_name);
    ~Person(){};
    const std::string& getName() const;
    void setName(const std::string& name);
    void setLastName(const std::string& last_name);
    void setIsArchive(const bool is_archive);
    const std::string& getLastName() const;
    bool getArchive() const;
};


#endif //REHABILITATIONCENTRE_PERSON_H