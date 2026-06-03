#ifndef REHABILITATIONCENTRE_CONSULTATIONROOM_H
#define REHABILITATIONCENTRE_CONSULTATIONROOM_H

#include "rooms/Room.h"

class ConsultationRoom : public Room
{
public:
    ConsultationRoom(const unsigned room_number);
    ~ConsultationRoom() = default;
    const std::string getInfo() const override;
    bool canBeUsed(Equipment equipment) const override;
};


#endif //REHABILITATIONCENTRE_CONSULTATIONROOM_H