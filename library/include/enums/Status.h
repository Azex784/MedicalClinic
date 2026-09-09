#ifndef MEDICALCLINIC_STATUS_H
#define MEDICALCLINIC_STATUS_H

#include <string>
#include "enums/EnumsOverloads.h"


namespace MedicalClinic
{
    /**
     * Typ wyliczeniowy zawierajcy status obiektu
     */
    enum class Status
    {
        AVAILABLE,
        UNAVAILABLE,
        ARCHIVED,
        LAST
    };

    /**
     * Funckja przekształcająca do postaci stringa typ status
     * @param status
     * @return
     */
    const std::string toString(Status status);
}

#endif //MEDICALCLINIC_STATUS_H