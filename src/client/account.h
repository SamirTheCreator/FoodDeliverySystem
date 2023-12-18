#ifndef ACCOUNT_H
#define ACCOUNT_H

//Authenticates the user account credentials using username and password. Uses the single-factor authentication.
//Retreives userID andfrom database with to data.user.ID 
int authenticateUser(struct foodle_user_t user);

//Retrieves  account information with specific userID.
int getUserInfo(struct foodle_user_t user);

//Allows the user to modify their account details with specific userID.
int updateUserInfo(struct foodle_user_t user);

//Deletes the user account with a specific clientID.
int deleteUserInfo(struct foodle_user_t user);

#endif //ACCOUNT_H

