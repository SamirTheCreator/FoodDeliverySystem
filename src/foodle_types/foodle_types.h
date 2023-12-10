#ifndef FOODLE_TYPES_H__
#define FOODLE_TYPES_H__

struct foodle_restaurant_t {
    int restaurant_id;
    char *name;
    char *address;
    char *phone_number;
    char *password;
    foodle_menu_t *menu;
};

struct foodle_order_t {
    int order_id;
    int restaurant_id;
    int customer_id;
    int dasher_id;
    char *address;
    char *date;
    char *status;
    foodle_menu_item_t *items;
};

struct foodle_dasher_t {
    int dasher_id;
    char *name;
    char *address;
    char *phone_number;
    char *email;
    char *car_model;
    char *car_color;
    char *car_plate;
};

struct foodle_customer_t {
    int customer_id;
    char *name;
    char *address;
    char *phone_number;
    char *password;
    char *email;
};

struct foodle_menu_t {
    char *name;
    char *description;
    foodle_menu_item_t *items;
};

struct foodle_menu_item_t {
    char *name;
    char *description;
    double price;
};

#endif FOODLE_TYPES_H__ // FOODLE_TYPES_H__