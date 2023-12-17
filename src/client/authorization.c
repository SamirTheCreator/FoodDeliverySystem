	int userID;
	while (true) {
		char username[16];
		char password[16];

		printf("Enter username: ");
		scanf("%s", username);
		printf("Enter password: ");
		scanf("%s", password);

		userID = authenticateUser(username, password);
		if (userID != -1) {
			printf("Authentication succeed.\n");
			break;
		}

		printf("\nAuthentication failed.\n\n");
		sleep(2);
	}
	
	struct foodle_user_t user;
	struct foodle_meal_t meal;
	
	int choice = -1;
	while (choice)
	{
		puts("1. Get User Information");
		puts("2. Update User Information");
		puts("3. Add Meal");
		puts("4. Update Meal");
		puts("5. Delete Meal");
		puts("6. View Meal");
		
		printf("Enter your choice: ");
		scanf("%d", &choice);
		
		switch (choice)
		{
		case 1:
		{
			user = getUserInfo(userID);
			printf("\n--- User Information ---\n");
			printf("User ID: %d\n", user.userID);
			printf("Email: %s\n", user.email);
			printf("Password: %s\n", user.password);
			printf("Type: %d\n", user.type);
			printf("Name: %s\n", user.name);
			printf("Phone number: %s\n", user.phone_number);
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
			scanf("%s", user.phone_number);
			printf("Enter address: ");
			scanf("%s", user.address);
			printf("Enter region: ");
			scanf("%s", user.region);
			updateUserInfo(user);
			break;
		}
		case 3:
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
		case 4:
		{
			printf("\n\n--- Update Meal ---\n");
			printf("Enter meal name: ");
			scanf("%s", meal.name);
			printf("Enter meal price: ");
			scanf("%f", &meal.price);
			updateMeal(meal.mealID, meal.name, meal.price, 0);
			meal = data.meal;
			break;
		}
		case 5:
		{
			printf("\n\n--- Delete Meal ---\n");
			printf("Enter meal ID: ");
			scanf("%d", &meal.mealID);
			deleteMeal(meal.mealID, 0);
			meal = data.meal;
			break;
		}
		case 6:
		{
			printf("\n\n--- Meal Info ---\n");
			printf("Meal ID: %d\n", meal.mealID);
			printf("Meal name: %s\n", meal.name);
			printf("Meal price: %f\n", meal.price);
			break;
		}
		}
	}

