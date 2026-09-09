#ifndef MEDICAL_CLINIC_EQUIPMENT_H
#define MEDICAL_CLINIC_EQUIPMENT_H

#include <string>
#include "enums/EnumsOverloads.h"

namespace MedicalClinic
{
    /**
     * Typ wyliczeniowy zawierajcy sprzet
     */
    enum class Equipment
    {
        NONE,
        DEFIBRILLATOR,
        ECG_MACHINE,
        PATIENT_MONITOR,
        VENTILATOR,
        INFUSION_PUMP,
        ULTRASOUND_MACHINE,
        X_RAY_MACHINE,
        CT_SCANNER,
        MRI_SCANNER,
        ANESTHESIA_MACHINE,
        SURGICAL_TABLE,
        INCUBATOR,
        LAST
    };

    /**
     * Funckja przekształcająca do postaci stringa typ status
     * @param eq
     * @return
     */
    const std::string toString(Equipment eq);
}

#endif //MEDICAL_CLINIC_EQUIPMENT_H