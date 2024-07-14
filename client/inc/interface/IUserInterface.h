#ifndef IUSERINTERFACE_H
#define IUSERINTERFACE_H

#include "../communication/requestHandler.h"
#include "../../../common/DTO/serializationUtility.h"

class IUserInterface {
public:
    virtual void showMenu() = 0;
};

#endif