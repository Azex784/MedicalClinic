#ifndef REHABILITATIONCENTRE_EQUIPMENT_H
#define REHABILITATIONCENTRE_EQUIPMENT_H

#include <string>

namespace RehabClinic
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
        INCUBATOR
    };

    //Konwersja do stringa
    const std::string equipmentToString(Equipment eq);
}

#endif //REHABILITATIONCENTRE_EQUIPMENT_H