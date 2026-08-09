//
// Created by azex on 8/9/26.
//

#include "Statusable.h"

namespace MedicalClinic
{
    Status Statusable::getEntityStatus() const
    {
        return entityStatus;
    }

    void Statusable::setEntityStatus(Status entityStatus_)
    {
        entityStatus = entityStatus_;
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

