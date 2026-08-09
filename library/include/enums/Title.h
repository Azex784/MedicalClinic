#ifndef REHABILITATIONCENTRE_STATUS_H
#define REHABILITATIONCENTRE_STATUS_H

#include <string>

namespace RehabClinic
{
/**
 * Typ wyliczeniowy zawierajcy sprzet
 */
    enum class Status
    {
        AVAILABLE,
        UNAVAILABLE,
        ARCHIVED
    };

}

#endif //REHABILITATIONCENTRE_STATUS_H