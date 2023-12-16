#ifndef ACCOUNT_H
#define ACCOUNT_H

//Authenticates the user account credentials using username and password. Uses the single-factor authentication.
//Returns 1 if authentication is successful, 0 otherwise.
int authenticateAccount(char *name, char *password);

/* manageAccount functions */

//Retrieves and displays the account information with specific clientID.
//Returns a pointer to the data structure containing account information, NULL otherwise.
struct foodle_account_t getAccount(int clientID);

//Allows the user to modify their account details with specific clientID.
//Returns 1 on success, 0 otherwise.
int updateAccount(struct foodle_account_t account);

//Deletes the user account with a specific clientID.
//Returns 1 on success, 0 otherwise.
int deleteAccount(int clientID);

#endif //ACCOUNT_H

