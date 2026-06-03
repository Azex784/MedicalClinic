#include "rooms/ConsultationRoom.h"
#include "enums/Equipment.h"

using namespace std;

ConsultationRoom::ConsultationRoom(const unsigned room_number): Room(room_number)
{
}

const std::string ConsultationRoom::getInfo() const
{
    return Room::getInfo() + " pokoj do przeprowadzania konsultacji";
}

bool ConsultationRoom::canBeUsed(Equipment equipment) const
{
    if (equipment == Equipment::NONE)
    {
        return true;
    }
    return false;
}
