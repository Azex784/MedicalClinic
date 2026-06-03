#ifndef REHABILITATIONCENTRE_REHABILLITATIONROOM_H
#define REHABILITATIONCENTRE_REHABILLITATIONROOM_H

#include "rooms/Room.h"
#include <vector>

enum class Equipment;

class RehabillitationRoom : public Room
{
private:
    std::vector<Equipment> accessibleEqupiment;
    unsigned int maxCapacity;
public:
    //ewentualnie dodac do info equpiment
    RehabillitationRoom(const unsigned room_number, const std::vector<Equipment>& accessible_equpiment,
        const unsigned int max_capacity);
    ~RehabillitationRoom() = default;
    bool canBeUsed(Equipment equipment) const override;
    const std::string getInfo() const override;
    const std::vector<Equipment>& getAccessibleEqupiment() const;
    unsigned int getMaxCapacity() const;

};


#endif //REHABILITATIONCENTRE_REHABILLITATIONROOM_H