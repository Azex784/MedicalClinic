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
    const std::string toString(Status status);

    /**
     * Operator przeciązaenia.
     * Podczas wypisywania wywołuje funkcje statusToString.
     * @param os
     * @param status
     * @return
     */
    std::ostream& operator<<(std::ostream& os, const Status& status);
}

#endif //MEDICALCLINIC_STATUS_H