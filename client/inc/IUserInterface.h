#ifndef IUSERINTERFACE_H
#define IUSERINTERFACE_H

#include "requestHandler.h"
#include "DTO/serializationUtility.h"

class IUserInterface {
    public:
        virtual void showMenu() = 0;
};

#endif