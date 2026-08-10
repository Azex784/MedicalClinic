#ifndef MEDICALCLINIC_STATUS_H
#define MEDICALCLINIC_STATUS_H

#include <string>

namespace MedicalClinic
{
    /**
     * Typ wyliczeniowy zawierajcy status obiektu
     */
    enum class Status
    {
        AVAILABLE,
        UNAVAILABLE,
        ARCHIVED
    };

    /**
     * Funckja przekształcająca do postaci stringa typ status
     * @param status
     * @return
     */
    const std::string statusToString(Status status);
}

#endif //MEDICALCLINIC_STATUS_H