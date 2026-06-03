#ifndef REHABILITATIONCENTRE_REHABILLITATION_H
#define REHABILITATIONCENTRE_REHABILLITATION_H

#include "rooms/Room.h"
#include <string>
#include <vector>

enum class Equipment;

class Rehabillitation : public Room
{
private:
    std::vector<Equipment> requiredEqupiment;
    unsigned int requiredNurseSize;

public:
    Rehabillitation(const unsigned room_number, const std::vector<Equipment>& required_equpiment,
        const unsigned int required_nurse_size);
    ~Rehabillitation() = default;
    const std::string getInfo() const override;
    bool canBeUsed(Equipment equipment) const override;
    const std::vector<Equipment>& getRequiredEqupiment() const;
    unsigned int getRequiredNurseSize() const;
};


#endif //REHABILITATIONCENTRE_REHABILLITATION_H