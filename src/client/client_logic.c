	struct foodle_user_t user;
	while (true) {
		printf("Enter username: ");
		scanf("%s", user.name);
		printf("Enter password: ");
		scanf("%s", user.password);

		authenticateUser(user);
		user = data.user;
		if (user.ID != -1) {
			printf("Authentication succeed.\n");
			break;
		}

		printf("\nAuthentication failed.\n\n");
		sleep(2);
	}

	struct foodle_meal_t meal;
	struct foodle_menu_t menu;
	
	int choice = -1;
	while (choice)
	{
		puts("\n");
		puts("1. Get User Information");
		puts("2. Update User Information");
		if (user.type == Restaurant) {
			puts("3. Get Menu");
			puts("4. Add Meal");
			puts("5. Get Meal");
			puts("6. Update Meal");
			puts("7. Delete Meal");		
		}

		printf("Enter your choice: ");
		scanf("%d", &choice);
		
		switch (choice)
		{
		case 1:
		{
			getUserInfo(user);
			user = data.user;
			printf("\n--- User Information ---\n");
			printf("User ID: %d\n", user.ID);
			printf("Email: %s\n", user.email);
			printf("Password: %s\n", user.password);
			printf("Type: %d\n", user.type);
			printf("Name: %s\n", user.name);
			printf("Phone number: %s\n", user.phone);
			printf("Address: %s\n", user.address);
			printf("Region: %s\n", user.region);
			break;
		}
		case 2:
		{
			printf("\n\n--- Update User Details ---\n");
			printf("Enter email: ");
			scanf("%s", user.email);
			printf("Enter password: ");
			scanf("%s", user.password);
			printf("Enter name: ");
			scanf("%s", user.name);
			printf("Enter phone number: ");
			scanf("%s", user.phone);
			printf("Enter address: ");
			scanf("%s", user.address);
			printf("Enter region: ");
			scanf("%s", user.region);
			updateUserInfo(user);
			user = data.user;
			break;
		}
		case 3:
		{
			int restaurantID;
			printf("Enter restaurantID: ");
			scanf("%d", &restaurantID);
			getMenu(restaurantID);
			menu = data.menu;
			printf("\n\n--- Menu ---\n");
			for (int i = 0; i < MAXSIZE; i++) {
				if (menu.meal[i].price == 0.0)
					break;
				printf("Meal ID: %d\n", menu.meal[i].ID);
				printf("Meal name: %s\n", menu.meal[i].name);
				printf("Meal price: %f\n\n", menu.meal[i].price);
			}
			break;
		}
		case 4:
		{
			printf("\n\n--- Add Meal ---\n");
			printf("Enter meal name: ");
			scanf("%s", meal.name);
			printf("Enter meal price: ");
			scanf("%f", &meal.price);
			addMeal(meal.name, meal.price, 0);
			meal = data.meal;
			break;
		}
		case 5:
		{
			printf("Enter meal ID: ");
			scanf("%d", &meal.ID);
			getMeal(meal.ID, 0);
			meal = data.meal;
			printf("\n\n--- Meal Info ---\n");
			printf("Meal ID: %d\n", meal.ID);
			printf("Meal name: %s\n", meal.name);
			printf("Meal price: %f\n", meal.price);
			break;
		}
		case 6:
		{
			printf("\n\n--- Update Meal ---\n");
			printf("Enter meal ID: ");
			scanf("%d", &meal.ID);
			printf("Enter meal name: ");
			scanf("%s", meal.name);
			printf("Enter meal price: ");
			scanf("%f", &meal.price);
			updateMeal(meal.ID, meal.name, meal.price, 0);
			meal = data.meal;
			break;
		}
		case 7:
		{
			printf("\n\n--- Delete Meal ---\n");
			printf("Enter meal ID: ");
			scanf("%d", &meal.ID);
			deleteMeal(meal.ID, 0);
			meal = data.meal;
			break;
		}
		}
	}

