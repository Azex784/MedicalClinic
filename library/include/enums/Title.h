#ifndef MEDICALCLINIC_TITLE_H
#define MEDICALCLINIC_TITLE_H

#include <string>

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
        PROF
    };

    /**
     * Funckja przekształcająca do postaci stringa typ status
     * @param Title
     * @return
     */
    const std::string titleToString(Title Title);
}

#endif //MEDICALCLINIC_TITLE_H