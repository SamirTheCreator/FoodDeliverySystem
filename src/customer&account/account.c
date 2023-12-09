//
// Created by mumu.
//

#include <stdio.h>
#include <string.h>             // for strlen(), strcmp()
#include <sys/socket.h>         // for socket(), connect(), send(), and recv()

#include "data_structures.h"    // This is the header file for the structures used in the program.
#include "account.h"            // This is the header file for the Account API endpoints.


int authenticateAccount(char *username, char *password) {

    //preparing event to be sent to the event handler
    event.type = AUTHENTICATE_ACCOUNT;
    strcpy(event.data.account.username, username);
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
    return data.account.clientID;

}


struct Account* getAccount(int clientID) {

    //preparing event to be sent to the event handler
    event.type = GET_ACCOUNT;
    event.data.account.clientID = clientID;

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


int updateAccount(struct Account account) {

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


int deleteAccount(int clientID) {

    //preparing event to be sent to the event handler
    event.type = DELETE_ACCOUNT;
    event.data.account.clientID = clientID;

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


