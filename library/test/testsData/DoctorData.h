//
// Created by azex on 9/7/26.
//

#ifndef MEDICALCLINIC_DOCTORDATA_H
#define MEDICALCLINIC_DOCTORDATA_H

#include <vector>

#include "enums/Specialisation.h"
#include "enums/Title.h"

using namespace MedicalClinic;

namespace data
{
    const std::vector<Title> titles = {
        Title::MD,
        Title::DR_MED,
        Title::DR_HAB_MED,
        Title::PROF,
        Title::MD,
        Title::DR_MED,
        Title::DR_HAB_MED,
        Title::PROF,
        Title::MD,
        Title::DR_MED
    };

    const std::vector<std::vector<Specialisation>> specialisations = {
        {Specialisation::ANESTHESIOLOGIST, Specialisation::GENERAL_SURGEON},
        {Specialisation::CARDIOLOGIST},
        {Specialisation::NEUROLOGIST, Specialisation::PSYCHIATRIST, Specialisation::INTERNIST},
        {Specialisation::ORTHOPEDIST, Specialisation::PEDIATRICIAN},
        {Specialisation::DERMATOLOGIST},
        {Specialisation::UROLOGIST, Specialisation::ONCOLOGIST, Specialisation::RADIOLOGIST, Specialisation::LARYNGOLOGIST},
        {Specialisation::GYNECOLOGIST, Specialisation::ENDOCRINOLOGIST},
        {Specialisation::EMERGENCY_PHYSICIAN},
        {Specialisation::PULMONOLOGIST, Specialisation::GASTROENTEROLOGIST, Specialisation::INTERNIST},
        {Specialisation::OPHTHALMOLOGIST, Specialisation::NEPHROLOGIST}
    };

}


#endif //MEDICALCLINIC_DOCTORDATA_H
