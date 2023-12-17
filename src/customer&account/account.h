//
// Created by mumu.
//

#ifndef UNTITLED_ACCOUNT_H
#define UNTITLED_ACCOUNT_H

//Authenticates the user account credentials using name and password. Uses the single-factor authentication.
//Returns 1 if authentication is successful, 0 otherwise.
int authenticateAccount(char *name, char *password);

/* manageAccount functions */

//Retrieves and displays the account information with specific userID.
//Returns a pointer to the data structure containing account information, NULL otherwise.
struct foodle_user_t* getAccount(int userID);

//Allows the user to modify their account information.
//Returns 1 on success, 0 otherwise.
int updateAccount(struct foodle_user_t account);

//Deletes the user account with a specific userID.
//Returns 1 on success, 0 otherwise.
int deleteAccount(int userID);

#endif //UNTITLED_ACCOUNT_H

