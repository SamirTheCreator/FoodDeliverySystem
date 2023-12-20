#ifndef CUSTOMER_H
#define CUSTOMER_H

//Retrieves list of restaurants.
int getRestaurantList(void);

//Displays the menu of a given restaurant.
int getMenu(int restaurantID);

//Places an order using the items in the user's cart.
int orderCart(struct foodle_order_t order);

#endif //CUSTOMER_H
