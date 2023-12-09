//
// Created by mumu.
//

#ifndef UNTITLED_ACCOUNT_H
#define UNTITLED_ACCOUNT_H


//Authenticates the user account credentials using username and password. Uses the single-factor authentication.
//Returns 1 if authentication is successful, 0 otherwise.
int authenticateAccount(char *username, char *password);

/* manageAccount functions */

//Retrieves and displays the account information with specific clientID.
//Returns a pointer to the data structure containing account information, NULL otherwise.
struct Account* getAccount(int clientID);

//Allows the user to modify their account details with specific clientID.
//Returns 1 on success, 0 otherwise.
int updateAccount(struct Account account);

//Deletes the user account with a specific clientID.
//Returns 1 on success, 0 otherwise.
int deleteAccount(int clientID);

#endif //UNTITLED_ACCOUNT_H

