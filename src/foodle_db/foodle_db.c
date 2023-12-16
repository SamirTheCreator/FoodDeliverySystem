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

MYSQL* foodle_db_init (void) {
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

// Does not work
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

	int num_fields = mysql_num_fields(result);

	MYSQL_ROW row = mysql_fetch_row(result);

	memset(&user, 0, sizeof user);
	printf("%d\n", sizeof user);

	user.userID = atoi((char*)&row[0]);
	strcpy(user.name, row[1]);
	strcpy(user.phone_number, row[2]);
	strcpy(user.email, row[3]);
	strcpy(user.password, row[4]);
	user.user_type = strcmp(row[5], "Restaurant") == 0 || strcmp(row[5], "Dasher") == 0? (strcmp(row[5], "Restaurant") == 0 ? Restaurant : Dasher) : Customer;
	strcpy(user.region, row[6]);
	strcpy(user.image_path, row[7]);
	strcpy(user.delivery_type, row[8]);
	
	mysql_free_result(result);
}

// Main only for testing the library
int main (int argc, char **argv) {
	MYSQL *con = foodle_db_init();
	
	struct foodle_user_t user = foodle_db_get_user_byemail(con, "john@doe");

	printf("%d\n%s\n%s\n%s\n%s\n%s\n%d\n%s\n%s\n%s", user.userID, user.name, user.phone_number, user.email, user.password, user.address, user.user_type, user.region, user.image_path, user.delivery_type);
	
	mysql_close(con);
	exit(0);
}