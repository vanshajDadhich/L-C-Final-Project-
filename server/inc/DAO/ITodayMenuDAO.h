#ifndef ITodayMenuDAO_H
#define ITodayMenuDAO_H
#include <vector>
#include"../DTO/menuItem.h"

class ITodayMenuDAO {
public:

    virtual bool addTodayMenu(const std::vector<int>& todayDayMenuItemId) = 0;
    virtual std::vector<MenuItem> getAllTodayMenuItem() = 0;
    virtual bool deleteTodayMenu() = 0;
};

#endif // ITodayMenuDAO_H
