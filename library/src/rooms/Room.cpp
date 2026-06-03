#include "rooms/Room.h"


using namespace std;

Room::Room(const unsigned int room_number): roomNumber(room_number)
{
}

const std::string Room::getInfo() const
{
    return "Pokoj o numerze pokoju: " + to_string( getRoomNumber()) + ", dostepnosc: " + to_string(getIsActive());
}

unsigned int Room::getRoomNumber() const
{
    return roomNumber;
}

bool Room::getIsActive() const
{
    return isActive;
}

bool Room::getIsArchive() const
{
    return isArchive;
}
