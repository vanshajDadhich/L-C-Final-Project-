#ifndef TODAYMENUSERVICE_H
#define TODAYMENUSERVICE_H

#include "../DAO/ITodayMenuDAO.h"
#include "../DTO/menuItem.h"
#include <vector>
#include <memory>

class TodayMenuService {
public:
    TodayMenuService(std::unique_ptr<ITodayMenuDAO> todayMenuDAO);

    bool addTodayMenu(const std::vector<int>& todayDayMenuItemId);
    std::vector<MenuItem> getAllTodayMenuItem();
    bool deleteTodayMenu();

private:
    std::unique_ptr<ITodayMenuDAO> todayMenuDAO;
};

#endif
