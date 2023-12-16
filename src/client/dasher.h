#ifndef DASHER_H
#define DASHER_H

struct foodle_delivery_t* getDeliveryList(void);
struct foodle_delivery_t chooseDelivery(int dasherID, int orderID);
//Selects a specific order delivery from a list of available order deliveries to perform actions on. Returns 1 on success, 0 otherwise.

int withdrawDelivery(int dasherID, int orderID);
//Withdraws an order delivery. Returns 1 on success, 0 otherwise.

int finishDelivery(int dasherID, int orderID);
//Marks an order delivery as finished. Returns 1 on success, 0 otherwise.

#endif
