#ifndef FOODLE_DB_H__
#define FOODLE_DB_H__

#include "../foodle_types/foodle_types.h"

enum foodle_db_request_type_e {
    REQUEST_GET,
    REQUEST_UPDATE,
};

typedef struct foodle_db_request_t {
    foodle_db_request_type_e request_type;
    
} foodle_db_request_t;

void foodle_db_restaurant_save(foodle_restaurant_t rest);
foodle_restaurant_t foodle_db_restaurant_get(void);

void foodle_db_order_save(foodle_order_t order);
foodle_order_t foodle_db_order_save(void);

void foodle_db_dasher_save(foodle_dasher_t dasher);
foodle_dasher_t foodle_db_dasher_get(void);

void foodle_db_customer_save(foodle_customer_t customer);
foodle_customer_t foodle_db_customer_get(void);

#endif FOODLE_DB_H_