#ifndef REHABILITATIONCENTRE_EQUIPMENT_H
#define REHABILITATIONCENTRE_EQUIPMENT_H

#include <string>
/**
 * Typ wyliczeniowy zawierajcy sprzet
 */
enum class Equipment {
    NONE,
    PHYSICAL_THERAPY_DEVICE,
    KINESITHERAPY_SPACE,
    ROBOTIC_SYSTEM
};

//Konwersja do stringa
const std::string equipmentToString(Equipment eq);

#endif //REHABILITATIONCENTRE_EQUIPMENT_H