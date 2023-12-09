//
// Created by mumu.
//

#include <stdio.h>
#include <string.h>             // for strlen(), strcmp()
#include <sys/socket.h>         // for socket(), connect(), send(), and recv()

#include "customer.h"           // This is the header file for the Customer API endpoints.
#include "data_structures.h"    // This is the header file for the structures used in the program.


void viewCart(void){

    //preparing event to be sent to the event handler
    event.type = VIEW_CART;

    //sending event to the event handler
    if((send(server_socket, &event, sizeof(event), 0)) == 0) {

        //error sending event
        return;
    }

    //receiving data from the server
    if ((recv(server_socket, &data, sizeof(data), 0)) == 0) {

        //error receiving data
        return;
    }

    //printing the cart
    printf("Cart:\n");
    for(int i = 0; i < data.cart.item[i].quantity; i++){

        printf("%d. %s\n", i+1, data.cart.item[i].name);
    }

}


int addItem(int itemID, int quantity){

        //preparing event to be sent to the event handler
        event.type = ADD_ITEM;
        event.data.item.itemID = itemID;
        event.data.item.quantity = quantity;

        //sending event to the event handler
        if((send(server_socket, &event, sizeof(event), 0)) == 0) {

            //error sending event
            return 0;
        }

    //receiving data from the server
    if ((recv(server_socket, &data, sizeof(data), 0)) == 0) {

        //error receiving data
        return 0;
    }

        //returning result
        return 1;

}


int deleteItem(int itemID){

    //preparing event to be sent to the event handler
    event.type = DELETE_ITEM;
    event.data.item.itemID = itemID;

    //sending event to the event handler
    if((send(server_socket, &event, sizeof(event), 0)) == 0) {

        //error sending event
        return 0;
    }

   //receiving data from the server
   if ((recv(server_socket, &data, sizeof(data), 0)) == 0) {

       //error receiving data
       return 0;
   }

    //returning result
    return 1;
}


int updateItem(int itemID, int quantity){

    //preparing event to be sent to the event handler
    event.type = UPDATE_ITEM;
    event.data.item.itemID = itemID;
    event.data.item.quantity = quantity;

    //sending event to the event handler
    if((send(server_socket, &event, sizeof(event), 0)) == 0) {

        //error sending event
        return 0;
    }

   //receiving data from the server
   if ((recv(server_socket, &data, sizeof(data), 0)) == 0) {

       //error receiving data
       return 0;
   }

    //returning result
    return 1;
}


struct Order* orderCart(int customerID, struct Order order, char *address){

    //preparing event to be sent to the event handler
    event.type = ORDER_CART;
    event.data.order.customerID = customerID;
    event.data.order.cart = order.cart;
    strcpy(event.data.order.address, address);

    //sending event to the event handler
    if((send(server_socket, &event, sizeof(event), 0)) == 0) {

        //error sending event
        return NULL;
    }

   //receiving data from the server
   if ((recv(server_socket, &data, sizeof(data), 0)) == 0) {

       //error receiving data
       return NULL;
   }

    //returning result
    return &data.order;
}


struct Delevery* getDeliveryList(void){

    //preparing event to be sent to the event handler
    event.type = GET_DELIVERY_LIST;

    //sending event to the event handler
    if((send(server_socket, &event, sizeof(event), 0)) == 0) {

        //error sending event
        return NULL;
    }

   //receiving data from the server
   if ((recv(server_socket, &data, sizeof(data), 0)) == 0) {

       //error receiving data
       return NULL;
   }

    //returning result
    return data.delivery_list;
}


struct Restaurant* getRestaurantList(void){

    //preparing event to be sent to the event handler
    event.type = GET_RESTAURANTS_LIST;

    //sending event to the event handler
    if((send(server_socket, &event, sizeof(event), 0)) == 0) {

        //error sending event
        return NULL;
    }

   //receiving data from the server
   if ((recv(server_socket, &data, sizeof(data), 0)) == 0) {

       //error receiving data
       return NULL;
   }

    //returning result
    return data.restaurant_list;
}


struct Menu* getMenu(int restaurantID){

    //preparing event to be sent to the event handler
    event.type = GET_MENU;
    event.data.restaurant.restaurantID = restaurantID;

    //sending event to the event handler
    if((send(server_socket, &event, sizeof(event), 0)) == 0) {

        //error sending event
        return NULL;
    }

   //receiving data from the server
   if ((recv(server_socket, &data, sizeof(data), 0)) == 0) {

       //error receiving data
       return NULL;
   }

    //returning result
    return &data.menu;
}





