#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include <string.h>
#include "foodle_db.h"
#include "foodle_types.h"

void finish_with_error(MYSQL *con) {
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

MYSQL* foodle_db_init(void) {
	MYSQL *con = mysql_init(NULL);
	if (con == NULL) {
      		fprintf(stderr, "%s\n", mysql_error(con));
      		exit(1);
  	}

	if (mysql_real_connect(con, FOODLE_DB_HOST, FOODLE_DB_USER, FOODLE_DB_PASS, FOODLE_DB_DATABASE, 0, NULL, 0) == NULL) {
		finish_with_error(con);
	}
    
    printf("Connected to database\n");

    return con;
}

void foodle_db_add_user(MYSQL *con, struct foodle_user_t *user) {
	char query[200];
	char u_type[50];
	if (user->user_type == Restaurant) strcpy(u_type, "Restaurant");
	else if (user->user_type == Dasher) strcpy(u_type, "Dasher");
	else strcpy(u_type, "Customer");

	sprintf(query, "INSERT INTO user VALUES(NULL, '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')", user->name, user->phone_number, user->email, user->password, user->address, u_type, user->region, user->image_path, user->delivery_type);

	if (mysql_query(con, query)) {
		finish_with_error(con);
	}
}

void foodle_db_add_item(MYSQL *con, struct foodle_item_t *item) {
	char query[200];
	char u_type[50];

	sprintf(query, "INSERT INTO menu VALUES(NULL, %d, %s, %f, %s)", item->itemID, item->name, item->price, item->image_path);

	if (mysql_query(con, query)) {
		finish_with_error(con);
	}
}

/*
* @desc Get user by email
* @param[in] MYSQL *con - connection to database
* @param[in] char *email - email of user
* @return foodle_user_t actual or user with userID = -1 if not found
*/
struct foodle_user_t foodle_db_get_user_byemail(MYSQL *con, char *email) {
	char query[200];
	struct foodle_user_t user;

	sprintf(query, "SELECT * FROM user WHERE email='%s'", email);
	if (mysql_query(con, query)) {
		finish_with_error(con);
	}

	MYSQL_RES *result = mysql_store_result(con);
	if (result == NULL) {
		finish_with_error(con);
	}

	MYSQL_ROW row = mysql_fetch_row(result);
    if (row) {
        user.userID = atoi(row[0]);
        strcpy(user.name, row[1]);
        strcpy(user.phone_number, row[2]);
        strcpy(user.email, row[3]);
        strcpy(user.password, row[4]);
        strcpy(user.address, row[5]);
        if (strcmp(row[6], "Restaurant") == 0) user.user_type = Restaurant;
        else if (strcmp(row[6], "Dasher") == 0) user.user_type = Dasher;
        else user.user_type = Customer;
        strcpy(user.region, row[7]);
        strcpy(user.image_path, row[8]);
        strcpy(user.delivery_type, row[9]);
    } else {
        user.userID = -1;
    }
	
	mysql_free_result(result);
    return user;
}

/*
* @desc Function to get restaurant menu by restaurant id
* Menu can consist of maximum 20 items
* @return A pointer to dynamically allocated (heap),
* DON'T FORGET TO FREE POINTER!
*/
struct foodle_item_t* foodle_db_get_menu(MYSQL *con, int id) {
	struct foodle_item_t *menu = malloc(20*sizeof(struct foodle_item_t));
	memset(menu, 0, 20*sizeof(struct foodle_item_t));
	char query[200];
	int i=0;

	sprintf(query, "SELECT * FROM menu WHERE restaurant_id=%d", id);
	if (mysql_query(con, query)) {
		finish_with_error(con);
	}

	MYSQL_RES *result = mysql_store_result(con);
	if (result == NULL) {
		finish_with_error(con);
	}

	MYSQL_ROW row;
	while ((row = mysql_fetch_row(result))) {
		menu[i].itemID = atoi(row[0]),
		strcpy(menu[i].name, row[2]),
		menu[i].price = atof(row[3]),
		strcpy(menu[i].image_path, row[4]),
		i++;
	}
	return menu;
}

// Main only for testing the library
int main (int argc, char **argv) {
	MYSQL *con = foodle_db_init();


	// How to get menu:
	// struct foodle_item_t *menu = foodle_db_get_menu(con, 239);
	// struct foodle_item_t *ptr;
	// for (ptr = menu; ptr->itemID != 0; ptr++) {
	// 	printf("%d, %s, %f, %s\n", ptr->itemID, ptr->name, ptr->price, ptr->image_path);
	// }
	// free(menu);

	mysql_close(con);
	exit(0);
}