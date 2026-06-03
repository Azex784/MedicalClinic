#include "rooms/Room.h"

using namespace std;

void Room::setIsActive(const bool is_active)
{
    isActive = is_active;
}

void Room::setIsArchive(const bool is_archive)
{
    isArchive = is_archive;
}

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
