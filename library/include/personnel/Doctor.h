#ifndef REHABILITATIONCENTRE_DOCTOR_H
#define REHABILITATIONCENTRE_DOCTOR_H

#include "personnel/Personnel.h"
#include <vector>

enum class Specialisation;

class Doctor : public Personnel
{
public:
    Doctor(const std::string& name, const std::string& last_name, const unsigned personnel_id,
        const std::vector<Specialisation>& specialisation, const unsigned int doctor_cost);
    ~Doctor() = default;

private:
    std::vector<Specialisation> specialisation;
    unsigned int doctorCost;
public:
    void setDoctorCost(const unsigned int doctor_cost);
    const std::vector<Specialisation>& getSpecialisation() const;
    unsigned int getDoctorCost() const;
    bool canConductTreatment(Specialisation specjalizacja) const override;
    const std::string getInfo() const override;
};


#endif //REHABILITATIONCENTRE_DOCTOR_H