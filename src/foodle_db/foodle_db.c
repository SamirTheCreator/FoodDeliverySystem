





/*

get menu from Aziz meals: 

SELECT * FROM menu WHERE menu_id = 1;

struct foodle_menu_t {
    char *name;
    char *description;
    foodle_menu_item_t *items;
};

foodle_menu_t foodle_db_get_menu_by_name(char *name) {
    table = mysql_query("SELECT * FROM menu WHERE name = %s", name);

    foodle_menu_t menu;
    menu.name = table[0][0];
    menu.description = table[0][1];
    menu.items = foodle_db_get_menu_items_by_menu_id(table[0][2]);
    

    return foodle_menu_t;

}


*/