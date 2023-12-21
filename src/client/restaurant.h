#ifndef RESTAURANT_H
#define RESTAURANT_H

int addMeal(const char *meal_name, const char *price, const char *time, const char *path, int restaurantID);
//Adds a meal to the menu of a given restaurant. Returns mealID if the meal is successfully added, 0 otherwise.

int getMeal(int mealID, int restaurantID);
//Gets a meal from the menu of a given restaurant. Returns 1 if the meal is successfully got, 0 otherwise.

int deleteMeal(int mealID, int restaurantID);
//Deletes a meal from the menu of a given restaurant. Returns 1 if the meal is successfully removed, 0 otherwise.

int updateMeal(int mealID, char* meal_name, float price, int restaurantID);
//Updates information about meals in the given menu. Returns 1 if the information is successfully updated in the menu, 0 otherwise.

int getOrderList(void);
//Retrieves a list of pending orders for the restaurant. Returns a pointer to the array of struct Order elements. Null on failure.

int selectOrder(int orderID);
//Selects a pending order to perform actions on. Returns Order if order is successfully selected, 0 otherwise.

int finishOrder(int orderID);
//Completes pending order. Returns 1 if the pending order is successfully finished, 0 otherwise.

#endif //RESTAURANT_H
