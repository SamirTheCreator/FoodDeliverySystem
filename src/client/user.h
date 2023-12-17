#ifndef USER_H
#define USER_H

//Authenticates the user account credentials using username and password. Uses the single-factor authentication.
//Returns 1 if authentication is successful, 0 otherwise.
int authenticateUser(char *name, char *password);

/* manageUser functions */

//Retrieves and displays the account information with specific clientID.
//Returns a pointer to the data structure containing account information, NULL otherwise.
struct foodle_user_t getUserInfo(int userID);

//Allows the user to modify their account details with specific clientID.
//Returns 1 on success, 0 otherwise.
int updateUserInfo(struct foodle_user_t user);

//Deletes the user account with a specific clientID.
//Returns 1 on success, 0 otherwise.
int deleteUserInfo(int userID);

#endif //ACCOUNT_H

