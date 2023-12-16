	char username[16];
	char password[16];

	printf("Enter username: ");
	scanf("%s", username);
	printf("Enter password: ");
	scanf("%s", password);

	int clientID = authenticateAccount(username, password);
	if (clientID)
	{
		struct foodle_account_t account;
		
		account = getAccount(clientID);
		printf("\nAccount Information:\n");
		printf("Client ID: %d\n", account.clientID);
		printf("Email: %s\n", account.email);
		printf("Password: %s\n", account.password);
		printf("Type: %d\n", account.type);
		printf("Name: %s\n", account.name);
		printf("Phone: %s\n", account.phone);
		printf("Address: %s\n", account.address);

		printf("\n\n--- Update Account Details ---\n");
		printf("Enter email: ");
		scanf("%s", account.email);
		printf("Enter password: ");
		scanf("%s", account.password);
		printf("Enter name: ");
		scanf("%s", account.name);
		printf("Enter phone: ");
		scanf("%s", account.phone);
		printf("Enter address: ");
		scanf("%s", account.address);
		
		updateAccount(account);
		account = data.account;
		printf("\n\nAccount Information:\n");
		printf("Client ID: %d\n", account.clientID);
		printf("Email: %s\n", account.email);
		printf("Password: %s\n", account.password);
		printf("Type: %d\n", account.type);
		printf("Name: %s\n", account.name);
		printf("Phone: %s\n", account.phone);
		printf("Address: %s\n", account.address);
	}
	else
		printf("Authentication failed. Exiting...\n");

