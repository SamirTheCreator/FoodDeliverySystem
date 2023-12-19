	struct foodle_user_t user;
	
	strcpy(user.phone, "+998 71 200 73 73");
	strcpy(user.password, "password");
	authenticateUser(user);
	user = data.user;
	
	if (user.ID == -1) {
		printf("\nAuthentication failed.\n\n");
		goto LABEL;
	}

	printf("\nAuthentication succeed.\n\n");

	
	
	struct foodle_meal_t meal;
	struct foodle_menu_t menu;
	getMenu(user.ID);
	memset(&menu, 0, sizeof menu);
	menu = data.menu;
	printf("\n\n--- Menu %s ---\n", user.name);
	for (int i = 0; i < 20; i++) {
		if (menu.meal[i].ID == 0.0)
			break;
		printf("Meal ID: %d\n", menu.meal[i].ID);
		printf("Meal name: %s\n", menu.meal[i].name);
		printf("Meal price: %f\n\n", menu.meal[i].price);
	}

	puts("--- Get Meal ---");
	printf("Enter meal ID: ");
	scanf("%d", &meal.ID);
	getMeal(meal.ID, user.ID);
	meal = data.meal;
	printf("\n\n--- Meal Info ---\n");
	printf("Meal ID: %d\n", meal.ID);
	printf("Meal name: %s\n", meal.name);
	printf("Meal price: %f\n", meal.price);
	
	
	printf("\n\n--- Delete Meal ---\n");
	deleteMeal(meal.ID, user.ID);

	puts("--- Get Menu ---");
	getMenu(user.ID);
	memset(&menu, 0, sizeof menu);
	menu = data.menu;
	printf("\n\n--- Menu ---\n");
	for (int i = 0; i < 20; i++) {
		if (menu.meal[i].ID == 0.0)
			break;
		printf("Meal ID: %d\n", menu.meal[i].ID);
		printf("Meal name: %s\n", menu.meal[i].name);
		printf("Meal price: %f\n\n", menu.meal[i].price);
	}

/*
	printf("\n\n--- Update Meal ---\n");
	printf("Enter meal ID: ");
	scanf("%d", &meal.ID);
	printf("Enter meal name: ");
	scanf("%s", meal.name);
	printf("Enter meal price: ");
	scanf("%f", &meal.price);
	updateMeal(meal.ID, meal.name, meal.price, 0);
	meal = data.meal;

	printf("\n\n--- Delete Meal ---\n");
	printf("Enter meal ID: ");
	scanf("%d", &meal.ID);
	deleteMeal(meal.ID, 0);
	meal = data.meal;
	break;
	*/

LABEL:
