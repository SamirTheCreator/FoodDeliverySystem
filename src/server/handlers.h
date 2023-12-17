#include "foodle_types.h"

struct fooodle_handler_t {
	enum foodle_event_type_e type;
	int (*handler)(struct foodle_event_t *);
	struct fooodle_handler_t* next;
};

struct fooodle_handler_t* initChainedHandler();
void addHandler(struct fooodle_handler_t *chain, enum foodle_event_type_e type, int (*handler)());

int handleEvent(struct fooodle_handler_t *chain, struct foodle_event_t *event);

int authenticateUser(struct foodle_event_t *event);
int getUserInfo(struct foodle_event_t *event);
int updateUserInfo(struct foodle_event_t *event);
int deleteUserInfo(struct foodle_event_t *event);

int addMeal(struct foodle_event_t *event);
int updateMeal(struct foodle_event_t *event);
int deleteMeal(struct foodle_event_t *event);

int getOrderList(struct foodle_event_t *event);
int selectOrder(struct foodle_event_t *event);
int finishOrder(struct foodle_event_t *event);

int getRestaurantList(struct foodle_event_t *event);
int getMenu(struct foodle_event_t *event);
int orderCart(struct foodle_event_t *event);

int getDeliveryList(struct foodle_event_t *event);
int chooseDelivery(struct foodle_event_t *event);
int withdrawDelivery(struct foodle_event_t *event);
int finishDelivery(struct foodle_event_t *event);

