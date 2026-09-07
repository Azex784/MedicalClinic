#include "rooms/Room.h"

namespace MedicalClinic
{
    using namespace std;


    Room::Room(const unsigned int roomNumber): roomNumber(roomNumber)
    {
    }

    const std::string Room::getInfo() const
    {
        string tmp;
        return "Pokój o numerze: " + to_string(getUniqueParameter()) + ", status: " + toString(getEntityStatus());
    }

    unsigned int Room::getUniqueParameter() const
    {
        return roomNumber;
    }
}
