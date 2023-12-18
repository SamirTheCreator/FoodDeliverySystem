#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include <string.h>
#include "foodle_db.h"

extern union foodle_data_u data;

void finish_with_error(MYSQL *con) {
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

MYSQL* foodle_db_init(void)
{
	MYSQL *con = mysql_init(NULL);
	if (con == NULL) {
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}

	if (mysql_real_connect(con, FOODLE_DB_HOST, FOODLE_DB_USER, FOODLE_DB_PASS, FOODLE_DB_DATABASE, 0, NULL, 0) == NULL)
		finish_with_error(con);
	printf("Connected to database\n");

	return con;
}

void foodle_db_add_user(MYSQL *con, struct foodle_user_t *user) {
	char query[255];
	char u_type[50];
	if (user->type == Restaurant)
		strcpy(u_type, "Restaurant");
	else if (user->type == Dasher)
		strcpy(u_type, "Dasher");
	else
		strcpy(u_type, "Customer");

	sprintf(query, "INSERT INTO user VALUES(NULL, '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')", user->name, user->phone, user->email, user->password, user->address, u_type, user->region, user->image_path, user->delivery_type);

	if (mysql_query(con, query))
		finish_with_error(con);
}

void foodle_db_add_meal(MYSQL *con, struct foodle_meal_t *meal)
{
	char query[255];
	char u_type[50];

	sprintf(query, "INSERT INTO menu VALUES(NULL, %d, %s, %f, %s)", meal->ID, meal->name, meal->price, meal->image_path);

	if (mysql_query(con, query))
		finish_with_error(con);
}

struct foodle_user_t foodle_db_get_user_byemail(MYSQL *con, char *email) {
	char query[255];
	struct foodle_user_t user;

	sprintf(query, "SELECT * FROM user WHERE email='%s'", email);
	if (mysql_query(con, query)) 
		finish_with_error(con);

	MYSQL_RES *result = mysql_store_result(con);
	if (result == NULL)
		finish_with_error(con);

	MYSQL_ROW row = mysql_fetch_row(result);
	if (row) {
		user.ID = atoi(row[0]);
		strcpy(user.name, row[1]);
		strcpy(user.phone, row[2]);
		strcpy(user.email, row[3]);
		strcpy(user.password, row[4]);
		strcpy(user.address, row[5]);
		
		if (strcmp(row[6], "Restaurant") == 0) user.type = Restaurant;
		else if (strcmp(row[6], "Dasher") == 0) user.type = Dasher;
		else user.type = Customer;
	
		strcpy(user.region, row[7]);
		strcpy(user.image_path, row[8]);
		strcpy(user.delivery_type, row[9]);
	}
	else {
		user.ID = -1;
	}
	mysql_free_result(result);
	return user;
}

int foodle_db_get_menu(MYSQL *con, int id) {
	char query[255];
	int i = 0;

	sprintf(query, "SELECT * FROM menu WHERE restaurant_id = %d", id);
	if (mysql_query(con, query))
		finish_with_error(con);

	MYSQL_RES *result = mysql_store_result(con);
	if (result == NULL)
		finish_with_error(con);

	MYSQL_ROW row;
	while (row = mysql_fetch_row(result)) {
		data.menu.meal[i].ID = atoi(row[0]);
		strcpy(data.menu.meal[i].name, row[2]);
		data.menu.meal[i].price = atof(row[3]);
		strcpy(data.menu.meal[i].image_path, row[4]);
		i++;
	}
	
	return 1;
}

/*
// Main only for testing the library
int main (int argc, char **argv) {
	MYSQL *con = foodle_db_init();
	// How to get menu:
	 struct foodle_item_t *menu = foodle_db_get_menu(con, 2);
	 struct foodle_item_t *ptr;
	 for (ptr = menu; ptr->itemID != 0; ptr++) {
	 	printf("%d, %s, %f, %s\n", ptr->itemID, ptr->name, ptr->price, ptr->image_path);
	 }
	 free(menu);
	mysql_close(con);
	exit(0);
}
*/
