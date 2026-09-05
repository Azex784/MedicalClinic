//
// Created by azex on 8/9/26.
//

#include "Statusable.h"

namespace MedicalClinic
{
    Statusable::Statusable() : entityStatus(Status::AVAILABLE)
    {
    }

    Statusable::~Statusable()
    {
    }

    Status Statusable::getEntityStatus() const
    {
        return entityStatus;
    }

    void Statusable::setEntityStatus(Status entityStatus)
    {
        this->entityStatus = entityStatus;
    }

    bool Statusable::isAvailable() const
    {
        if(getEntityStatus() == Status::AVAILABLE)
        {
            return true;
        }
        return false;
    }
}

