#ifndef FOODLE_TYPES_H__
#define FOODLE_TYPES_H__

struct foodle_restaurant_t {
    char *name;
    char *address;
    char *phone_number;
    foodle_menu_t *menu;
};

struct foodle_order_t {
    char *name;
    char *address;
    char *phone_number;
    char *email;
    foodle_menu_item_t *items;
};

struct foodle_dasher_t {
    char *name;
    char *address;
    char *phone_number;
    char *email;
    char *car_make;
    char *car_model;
    char *car_color;
    char *car_plate;
};

struct foodle_customer_t {
    char *name;
    char *address;
    char *phone_number;
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