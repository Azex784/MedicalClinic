#ifndef MEDICALCLINIC_STATUS_H
#define MEDICALCLINIC_STATUS_H

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
}

#endif //MEDICALCLINIC_STATUS_H