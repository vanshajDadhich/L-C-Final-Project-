#ifndef TODAYMENUSERVICE_H
#define TODAYMENUSERVICE_H

#include "../DAO/ITodayMenuDAO.h"
#include "../DTO/menuItem.h"
#include <vector>
#include <memory>

class TodayMenuService {
public:
    TodayMenuService(std::shared_ptr<ITodayMenuDAO> todayMenuDAO);

    bool addTodayMenu(const std::vector<int>& todayDayMenuItemId);
    std::vector<MenuItem> getAllTodayMenuItem();
    bool deleteTodayMenu();

private:
    std::shared_ptr<ITodayMenuDAO> todayMenuDAO;
};

#endif // TODAYMENUSERVICE_H
