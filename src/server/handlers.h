#include "foodle_types.h"

struct foodle_handler_t {
	enum foodle_event_type_e type;
	int (*handler)(struct foodle_event_t *);
	struct foodle_handler_t* next;
};

struct foodle_handler_t* initHandlers(void);
void addHandler(struct foodle_handler_t *chain, enum foodle_event_type_e type, int (*handler)(struct foodle_event_t *event));

int handleEvent(struct foodle_handler_t *chain, struct foodle_event_t *event);

//handlers are mainly intended for calling certain function(s) from dbconnector
//and parse retreived table or json file to union data
int authenticateUser(struct foodle_event_t *event);
int addUserInfo(struct foodle_event_t *event);
int getUserInfo(struct foodle_event_t *event);

int addMeal(struct foodle_event_t *event);
int getMeal(struct foodle_event_t *event);
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

