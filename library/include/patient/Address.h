#ifndef REHABILITATIONCENTRE_ADDRESS_H
#define REHABILITATIONCENTRE_ADDRESS_H

#include <string>

/**
 * Klasa reprezentująca adres
 */
class Address
{
public:
    Address(const std::string& city, const std::string& street, const std::string& number);
    ~Address() = default;

private:
    std::string city;
    std::string street;
    std::string number;
public:
    const std::string getInfo() const;
    const std::string& getCity() const;
    const std::string& getStreet() const;
    const std::string& getNumber() const;
};


#endif //REHABILITATIONCENTRE_ADDRESS_H