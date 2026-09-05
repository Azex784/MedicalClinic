//
// Created by azex on 8/9/26.
//

#ifndef MEDICALCLINIC_STATUSABLE_H
#define MEDICALCLINIC_STATUSABLE_H

#include "enums/Status.h"

namespace MedicalClinic
{
    /**
     * Klasa przedstawiajca status danego obiektu
     */
    class Statusable
    {
    private:
        Status entityStatus;

    public:
        /**
         * Konstruktor, który automatycznie zmienia status usługi na AVAILABLE
         */
        Statusable();

        /**
         *
         */
        virtual ~Statusable() = 0;

        /**
         * Getter entityStatus
         * @return
         */
        Status getEntityStatus() const;

        /**
         * Setter paramtetru entityStatus
         * @param entityStatus_
         */
        void setEntityStatus(Status entityStatus);

        /**
         * Zwraca prawdę gdy wartość EntityStatus to AVAILABLE
         * @return BOOL
         */
        bool isAvailable() const;
    };

}

#endif //MEDICALCLINIC_STATUSABLE_H
