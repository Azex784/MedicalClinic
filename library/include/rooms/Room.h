#ifndef REHABILITATIONCENTRE_ROOM_H
#define REHABILITATIONCENTRE_ROOM_H
#include <string>

enum class Equipment;

class Room
{
private:
        unsigned int roomNumber;
        bool isActive;
        bool isArchive;
public:
        Room(const unsigned int room_number);
        ~Room() = default;
        virtual const std::string getInfo() const ;
        virtual bool canBeUsed(Equipment equipment) const = 0;
        unsigned int getRoomNumber() const;
        bool getIsActive() const;
        bool getIsArchive() const;
};


#endif //REHABILITATIONCENTRE_ROOM_H