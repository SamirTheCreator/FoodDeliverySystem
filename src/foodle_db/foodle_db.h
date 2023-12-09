#ifndef FOODLE_DB_H__
#define FOODLE_DB_H__

#include "../foodle_types/foodle_types.h"

void foodle_db_dasher_save(char *name, char *address, char *phone, char *email, char *car_model, char *car_color, char *car_plate);
foodle_dasher_t foodle_db_dasher_get_byid(int id);
foodle_dasher_t foodle_db_dasher_get_byname(char *name);
foodle_dasher_t foodle_db_dasher_get_byemail(char *email);
foodle_dasher_t foodle_db_dasher_get_byphone(char *phone);

void foodle_db_restaurant_save(char *name, char *address, char *phone, char *password);
foodle_restaurant_t foodle_db_restaurant_get_byid(int id);
foodle_restaurant_t foodle_db_restaurant_get_byname(char *name);
foodle_restaurant_t foodle_db_restaurant_get__byphone(char *phone);

void foodle_db_order_save(int restaurant_id, int customer_id, char *address, char *date, char *status);
foodle_order_t foodle_db_order_get_byid(int id);
/*
 * Functions below are used to display the history of orders
 * for a restaurant, customer, or dasher. The functions return
 * a pointer to an array of foodle_order_t structs.
 * param [in] id: the id of the restaurant, customer, or dasher
 * return: a pointer to an array of foodle_order_t structs
 *        NULL if no orders are found
 * note: the array of foodle_order_t structs is dynamically allocated
 *      and must be freed by the caller
 * note: the array of foodle_order_t structs is NULL terminated
 *     (the last element of the array is NULL)
 * note: the array of foodle_order_t structs is sorted by date
 *    (the first element of the array is the oldest order)
*/
foodle_order_t* foodle_db_order_get_byrestaurant(int restaurant_id);
foodle_order_t* foodle_db_order_get_bycustomer(int customer_id);
foodle_order_t* foodle_db_order_get_bydasher(int dasher_id);

void foodle_db_customer_save(foodle_customer_t customer);
foodle_customer_t foodle_db_customer_get_byid(int id);
foodle_customer_t foodle_db_customer_get_byname(char *name);
foodle_customer_t foodle_db_customer_get_byemail(char *email);
foodle_customer_t foodle_db_customer_get_byphone(char *phone);

#endif FOODLE_DB_H_ // FOODLE_DB_H__