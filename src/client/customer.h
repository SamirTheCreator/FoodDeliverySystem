#ifndef MAIN_CUSTOMER_H
#define MAIN_CUSTOMER_H

/* manageCart functions */

//Displays the contents of the user's cart.
void viewCart(void);

//Adds a meal(s) to the user’s cart.
//Returns 1 if the meal successfully added to the cart, 0 otherwise.
int addItem(int itemID, int quantity);

//Deletes a meal from the user's cart.
//Returns 1 if the meal successfully deleted from the cart, 0 otherwise.
int deleteItem(int itemID);

//Updates the quantity of a meal in the user's cart.
//Returns 1 if the meal successfully updated in the cart, 0 otherwise.
int updateItem(int itemID, int quantity);

//Places an order using the items in the user's cart.
//Returns a pointer to the order information if the order successfully placed, NULL otherwise.
struct foodle_order_t* orderCart(int customerID, struct foodle_order_t order, char *address);

//Retrieves the list of available order deliveries.
//Returns a pointer to the array of struct Delivery, NULL otherwise.
struct foodle_delivery_t* getDeliveryList(void);

//Retrieves the list of available restaurants from the database by category (cuisine type).
//Returns a pointer to the array of struct Restaurant, NULL otherwise.
struct foodle_restaurant_t* getRestaurantList(void);

//Displays the menu of a given restaurant.
//Returns a pointer to the struct Menu with list of Meals, or Null in failure.
struct foodle_menu_t* getMenu(int restaurantID);

#endif //MAIN_CUSTOMER_H

