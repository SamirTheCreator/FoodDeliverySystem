#include "data_structures.h"

struct Handler {
	enum event_type type;
	int (*handler)(struct Event *);
	struct Handler* next;
};

struct Handler* initChainedHandler();
void addHandler(struct Handler *chain, enum event_type type, int (*handler)());

void handleEvent(struct Handler *chain, struct Event *event);

int authenticateAccount(struct Event *event);
int getAccount(struct Event *event);
int updateAccount(struct Event *event);
int deleteAccount(struct Event *event);

int getOrderList(struct Event *event);
int selectOrder(struct Event *event);
int finishOrder(struct Event *event);

int getMenu(struct Event *event);
int addMeal(struct Event *event);
int updateMeal(struct Event *event);
int deleteMeal(struct Event *event);

int getRestaurantList(struct Event *event);
int viewCart(struct Event *event);
int addItem(struct Event *event);
int updateItem(struct Event *event);
int deleteItem(struct Event *event);
int orderCart(struct Event *event);

int getDeliveryList(struct Event *event);
int chooseDelivery(struct Event *event);
int withdrawDelivery(struct Event *event);
int finishDelivery(struct Event *event);

