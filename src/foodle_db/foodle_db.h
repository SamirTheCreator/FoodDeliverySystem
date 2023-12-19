#ifndef FOODLE_DB_H
#define FOODLE_DB_H

#include "foodle_types.h"
#include "mysql.h"

#define FOODLE_DB_HOST "localhost"
#define FOODLE_DB_USER "root"
#define FOODLE_DB_PASS "1234"
#define FOODLE_DB_DATABASE "Foodle_DB"

MYSQL* foodle_db_init(void);

struct foodle_user_t* foodle_db_get_user_byphone(MYSQL *con, char *phone);

struct foodle_user_t* foodle_db_get_user_byid(MYSQL *con, int userID);

int foodle_db_add_user(MYSQL *con, struct foodle_user_t *user);

int foodle_db_add_meal(MYSQL *con, struct foodle_meal_t *meal, int restaurantID);

int foodle_db_update_meal_bystruct(MYSQL *con, struct foodle_meal_t *meal);

int foodle_db_delete_meal_byid(MYSQL *con, int id);

struct foodle_meal_t* foodle_db_get_meal_byid(MYSQL *con, int id);

struct foodle_restaurant_t* foodle_db_get_restaurants(MYSQL* con);

struct foodle_menu_t* foodle_db_get_menu(MYSQL *con, int id);

#endif // FOODLE_DB_H
