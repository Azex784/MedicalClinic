#include "rooms/Room.h"

namespace MedicalClinic
{

    using namespace std;

    void Room::setIsActive(const bool isActive1)
    {
        isActive = isActive1;
    }

    void Room::setIsArchive(const bool isArchive1)
    {
        isArchive = isArchive1;
    }

    Room::Room(const unsigned int roomNumber) : roomNumber(roomNumber)
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
        }
        else
        {
            tmp = "nieaktywna";
        }
        return "Pokoj o numerze pokoju: " + to_string(getUniqueParameter()) + ", dostepnosc: " + tmp;
    }

    unsigned int Room::getUniqueParameter() const
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
}
