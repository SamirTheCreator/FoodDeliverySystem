#ifndef ACCOUNT_H
#define ACCOUNT_H

//Authenticates the user account credentials using username and password. Uses the single-factor authentication.
//Retreives userID andfrom database with to data.user.ID 
int authenticateUser(struct foodle_user_t user);

int addUserInfo(struct foodle_user_t user);

//Retrieves account information with specific phone.
int getUserInfo(struct foodle_user_t user);

#endif //ACCOUNT_H

