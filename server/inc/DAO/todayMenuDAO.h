#ifndef TODAYMENUDAO_H
#define TODAYMENUDAO_H

#include "ITodayMenuDAO.h"
#include "databaseConnection.h"
#include <vector>
#include "../DTO/menuItem.h"

class TodayMenuDAO : public ITodayMenuDAO {
public:
    TodayMenuDAO();

    bool addTodayMenu(const std::vector<int>& todayDayMenuItemId) override;
    std::vector<MenuItem> getAllTodayMenuItem() override;
    bool deleteTodayMenu() override;

private:
    std::shared_ptr<DatabaseConnection> databaseConnection;
};

#endif