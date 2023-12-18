#ifndef FOODLE_DB_H
#define FOODLE_DB_H

#include <mysql.h>
#include <foodle_types.h>

#define FOODLE_DB_HOST "localhost"
#define FOODLE_DB_USER "root"
#define FOODLE_DB_PASS "1234"
#define FOODLE_DB_DATABASE "Foodle_DB"


MYSQL* foodle_db_init(void);

/*
* @desc Function to initialize database connection
* @return A pointer to MYSQL connection
*/
void foodle_db_add_user(MYSQL *con, struct foodle_user_t *user);

/*
* @desc Function to initialize database connection
* @return A pointer to MYSQL connection
*/
void foodle_db_add_meal(MYSQL *con, struct foodle_meal_t *meal);

/*
* @desc Get user by email
* @param[in] MYSQL *con - connection to database
* @param[in] char *email - email of user
* @return foodle_user_t actual or user with userID = -1 if not found
*/
struct foodle_user_t foodle_db_get_user_byemail(MYSQL *con, char *email);

/*
* @desc Function to get restaurant menu by restaurant id
* Menu can consist of maximum 20 items
* @return A pointer to dynamically allocated (heap),
* DON'T FORGET TO FREE POINTER!
*/
int foodle_db_get_menu(MYSQL *con, int id);


#endif //FOODLE_DB_H
