//
// Created by mumu.
//

#include <stdio.h>
#include <string.h>                 // for strlen(), strcmp()
#include <sys/socket.h>             // for socket(), connect(), send(), and recv()

#include "customer.h"               // This is the header file for the Customer API endpoints.
#include "foodle_types.h"    // This is the header file for the structures used in the program.


void viewCart(void){

    //preparing event to be sent to the event handler
    event.type = VIEW_CART;

    //sending event to the event handler
    if((send(server_socket, &event, sizeof(event), 0)) == 0) {

        //error sending event
        printf("Error sending event\n");
    }

    //receiving data from the server
    if ((recv(server_socket, &data, sizeof(data), 0)) == 0) {

        //error receiving data
        printf("Error receiving data\n");
    }

}


int addItem(int itemID){

        //preparing event to be sent to the event handler
        event.type = ADD_ITEM;
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


int updateItem(int itemID){

    //preparing event to be sent to the event handler
    event.type = UPDATE_ITEM;
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


struct foodle_order_t* orderCart(int customerID, struct foodle_order_t order, char *address){

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


struct foodle_delivery_t* getDeliveryList(void){

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
    return &data.delivery_list[0]; // address of the first element of the array
}


struct foodle_restaurant_t* getRestaurantList(void){

    //preparing event to be sent to the event handler
    event.type = GET_RESTAURANT_LIST;

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
    return &data.restaurant_list[0]; // address of the first element of the array
}


struct foodle_menu_t* getMenu(int restaurantID){

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





