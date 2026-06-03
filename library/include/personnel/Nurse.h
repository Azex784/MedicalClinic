#ifndef REHABILITATIONCENTRE_NURSE_H
#define REHABILITATIONCENTRE_NURSE_H

#include "personnel/Personnel.h"

class Nurse : public Personnel
{
public:
    Nurse(const std::string& name, const std::string& last_name, const unsigned personnel_id);
    ~Nurse() = default;
    //zakldam ze kazda pielgniarka nie ma specjalizacji neorolgozki
    //ewentualnie mozna poprawic
    bool canConductTreatment(Specialisation specjalizacja) const override;
    const std::string getInfo() const override;
};


#endif //REHABILITATIONCENTRE_NURSE_H