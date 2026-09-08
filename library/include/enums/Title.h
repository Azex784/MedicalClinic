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
        PROF,
        LAST
    };

    /**
     * Funckja przekształcająca do postaci stringa typ status
     * @param Title
     * @return
     */
    const std::string toString(Title Title);

    /**
     * Operator przeciązaenia.
     * Podczas wypisywania wywołuje funkcje toString.
     * @param os
     * @param t
     * @return
     */
    std::ostream& operator<<(std::ostream& os, const Title& t);
}

#endif //MEDICALCLINIC_TITLE_H