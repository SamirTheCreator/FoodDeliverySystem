//
// Created by mumu.
//

#include <stdio.h>
#include <string.h>             // for strlen(), strcmp()
#include <sys/socket.h>         // for socket(), connect(), send(), and recv()

#include "foodle_types.h"    // This is the header file for the structures used in the program.
#include "account.h"            // This is the header file for the Account API endpoints.

int authenticateAccount(char *name, char *password) {

    //preparing event to be sent to the event handler
    event.type = AUTHENTICATE_ACCOUNT;
    strcpy(event.data.account.name, name);
    strcpy(event.data.account.password, password);

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
    return data.account.userID;

}


struct foodle_user_t* getAccount(int userID) {

    //preparing event to be sent to the event handler
    event.type = GET_ACCOUNT;
    event.data.account.userID = userID;

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
    return &data.account;

}


int updateAccount(struct foodle_user_t account) {

    //preparing event to be sent to the event handler
    event.type = UPDATE_ACCOUNT;
    event.data.account = account;

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


int deleteAccount(int userID) {

    //preparing event to be sent to the event handler
    event.type = DELETE_ACCOUNT;
    event.data.account.userID = userID;

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


