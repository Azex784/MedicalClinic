#ifndef MEDICALCLINIC_TITLE_H
#define MEDICALCLINIC_TITLE_H

#include <string>
#include "enums/EnumsOverloads.h"


namespace MedicalClinic
{
    /**
     * Typ wyliczeniowy zawierajcy tytuły naukowe lekarza
     */
    enum class Title
    {
        MD,
        DR_MED,
        DR_HAB_MED,
        PROF,
        LAST
    };

    /**
     * Funckja przekształcająca do postaci stringa typ status
     * @param Title
     * @return
     */
    const std::string toString(Title Title);
}

#endif //MEDICALCLINIC_TITLE_H