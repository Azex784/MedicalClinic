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
    setIsActive(true);
    setIsArchive(false);
}

const std::string Room::getInfo() const
{
    string tmp;
    if (getIsActive())
    {
        tmp = "aktywna";
    }else
    {
        tmp = "nieaktywna";
    }
    return "Pokoj o numerze pokoju: " + to_string( getRoomNumber()) + ", dostepnosc: " + tmp;
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
