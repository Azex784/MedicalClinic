#ifndef REHABILITATIONCENTRE_PERSONNEL_H
#define REHABILITATIONCENTRE_PERSONNEL_H

#include <string>
#include <vector>
#include "Person.h"

enum class Specialisation;

/**
 * Klasa reprezentująca personel
 */
class Personnel : public Person{
public:
    Personnel(const std::string& name, const std::string& last_name, const unsigned int personnel_id);
    ~Personnel() = default;

private:
    bool isActive;
    unsigned int personnelId;
public:
    void setIsActive(const bool is_active);
    bool getIsActive() const;
    unsigned int getPersonnelId() const;
    virtual bool canConductTreatment(Specialisation specjalizacja) const = 0;
    const std::string getInfo() const override;
};



#endif //REHABILITATIONCENTRE_PERSONNEL_H
