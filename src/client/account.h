#ifndef ACCOUNT_H
#define ACCOUNT_H

//Authenticates the user account credentials using username and password. Uses the single-factor authentication.
//Retreives userID andfrom database with to data.user.ID 
int authenticateUser(const char *phone, const char *password);

int addUserInfo(enum foodle_user_type_e user_type, const char *name, const char *phone, const char *address, const char *delivery_type, const char *password);

//Retrieves account information with specific phone.
int getUserInfo(struct foodle_user_t user);

#endif //ACCOUNT_H
