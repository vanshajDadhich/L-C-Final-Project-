#ifndef IUSERINTERFACE_H
#define IUSERINTERFACE_H

#include "requestHandler.h"
#include "DTO/SerializationUtility.h"

class IUserInterface {
    public:
        virtual void showMenu() = 0;
};

#endif