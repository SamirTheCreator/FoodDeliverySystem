#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtkx.h>
#include <gtk/gtk.h>
#include <glib.h>
#include <math.h>
#include <ctype.h>

#include <stdio.h>      //printf()
#include <stdlib.h>     //exit()
#include <string.h>     //memset()
#include <unistd.h>     //close()

//inet_addr(), socket(), connect()
//struct sockaddr_in, AF_INET, SOCK_STREAM
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "foodle_types.h"
#include "../restaurant.h"
#include "../account.h"
#include "../customer.h"
#include "../dasher.h"

int server_socket;
struct foodle_event_t event;
union foodle_data_u data;
int userID;

GtkWidget   *window;
GtkWidget   *fixed;

GtkWidget   *StatusLabel;

GtkWidget   *SubmitButton;
GtkWidget   *RegisterButton;
GtkWidget   *CustomerButton;
GtkWidget   *DasherButton;
GtkWidget   *RestaurantButton;
GtkWidget   *CustomerSubmitButton;
GtkWidget   *DasherSubmitButton;
GtkWidget   *RestaurantSubmitButton;
GtkWidget   *ViewMenuButton;
GtkWidget   *AddMealButton;
GtkWidget   *DeleteMealButton;
GtkWidget   *UpdateMealButton;
GtkWidget	*AddMealSubmitButton;

GtkWidget   *LoginField;
GtkWidget   *PasswordField;
GtkWidget   *NameField;
GtkWidget   *PhoneField;
GtkWidget   *DeliveryTypeField;
GtkWidget   *AddressField;
GtkWidget   *Password1Field;
GtkWidget   *Password2Field;
GtkWidget   *MealNameField;
GtkWidget   *MealPriceField;
GtkWidget   *AddressField;
GtkWidget   *MealCookingTimeField;
GtkWidget   *MealImagePathField;

GtkBuilder  *builder;



void on_RegisterButton_activate();
void hide_status_label(GtkWidget *label);
void on_AddMealButton_activate();

void freeze_sleep(int s)
{
    struct timespec delay;
    delay.tv_sec = s;
    delay.tv_nsec = 0;
    nanosleep(&delay, NULL);
    return;
}


//void on_ViewMealButton_activate(){}

void on_AddMealSubmitButton_activate()
{
	const gchar *meal_name = gtk_entry_get_text(GTK_ENTRY(MealNameField));
	const gchar *meal_price = gtk_entry_get_text(GTK_ENTRY(MealPriceField));
	const gchar *cooking_time = gtk_entry_get_text(GTK_ENTRY(MealCookingTimeField));
	const gchar *image_path = gtk_entry_get_text(GTK_ENTRY(MealImagePathField));
	
	g_print("\n--- Add meal window ---\n");
    g_print("Meal name: %s\n", meal_name);
    g_print("Meal price: %s\n", meal_price);
    g_print("Cooking time: %s\n",cooking_time);
    g_print("Image path: %s\n",image_path);
    
    addMeal(meal_name, meal_price, cooking_time, image_path, userID);
    
    GtkBuilder *new_builder = gtk_builder_new();
    if (gtk_builder_add_from_file(new_builder, "RestaurantMenuPage.glade", NULL) == 0) {
        g_error("Error loading New Glade file");
        return;
    }
    
    GtkWidget *new_window = GTK_WIDGET(gtk_builder_get_object(new_builder, "RestaurantMenuWindow"));

    ViewMenuButton = GTK_WIDGET(gtk_builder_get_object(new_builder, "ViewMenuButton"));
    g_signal_connect(ViewMenuButton, "clicked", G_CALLBACK(on_AddMealButton_activate), NULL);
    
    AddMealButton = GTK_WIDGET(gtk_builder_get_object(new_builder, "AddMealButton"));
    g_signal_connect(AddMealButton, "clicked", G_CALLBACK(on_AddMealButton_activate), NULL);

    DeleteMealButton = GTK_WIDGET(gtk_builder_get_object(new_builder, "DeleteMealButton"));
    g_signal_connect(DeleteMealButton, "clicked", G_CALLBACK(on_AddMealButton_activate), NULL);
    
    UpdateMealButton = GTK_WIDGET(gtk_builder_get_object(new_builder, "UpdateMealButton"));
    g_signal_connect(UpdateMealButton, "clicked", G_CALLBACK(on_AddMealButton_activate), NULL);
    
    gtk_widget_hide(window);

    g_signal_connect(new_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(new_window);
    window = new_window;
    builder = new_builder;
}

void on_AddMealButton_activate()
{

    GtkBuilder *new_builder = gtk_builder_new();
    
    if (gtk_builder_add_from_file(new_builder, "AddMealPage.glade", NULL) == 0) {
        g_error("Error loading New Glade file");
        return;
    }
    
    GtkWidget *new_window = GTK_WIDGET(gtk_builder_get_object(new_builder, "AddMenuWindow"));

    gtk_widget_hide(window);

    g_signal_connect(new_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    AddMealSubmitButton = GTK_WIDGET(gtk_builder_get_object(new_builder, "AddMealSubmitButton"));
    g_signal_connect(AddMealSubmitButton, "clicked", G_CALLBACK(on_AddMealSubmitButton_activate), NULL);

    MealNameField = GTK_WIDGET(gtk_builder_get_object(new_builder, "MealNameField"));
    MealPriceField = GTK_WIDGET(gtk_builder_get_object(new_builder, "MealPriceField"));
    MealCookingTimeField = GTK_WIDGET(gtk_builder_get_object(new_builder, "MealCookingTimeField"));
    MealImagePathField = GTK_WIDGET(gtk_builder_get_object(new_builder, "MealImagePathField"));
    
    gtk_widget_show_all(new_window);
    window = new_window;
    builder = new_builder;
}

//void on_UpdateMealButton_activate(){}

//void on_DeleteMealButton_activate(){}

void on_SubmitButton_activate()
{
    const gchar *login_text = gtk_entry_get_text(GTK_ENTRY(LoginField));
    const gchar *password_text = gtk_entry_get_text(GTK_ENTRY(PasswordField));

	g_print("\n--- Registration window ---\n");
    g_print("Login: %s\n", login_text);
    g_print("Password: %s\n", password_text);
    
 
    authenticateUser(login_text, password_text);
    if (data.user.ID == -1) {
    	printf("\nAuthentication failed!\n");
    	return;
    }
    userID = data.user.ID;
    printf("\nAuthentication succeed!\n");
    
    
    if (data.user.type == Restaurant)
    {
	   GtkBuilder *new_builder = gtk_builder_new();
		if (gtk_builder_add_from_file(new_builder, "RestaurantMenuPage.glade", NULL) == 0) {
		    g_error("Error loading New Glade file");
		    return;
		}
    
		GtkWidget *new_window = GTK_WIDGET(gtk_builder_get_object(new_builder, "RestaurantMenuWindow"));

		ViewMenuButton = GTK_WIDGET(gtk_builder_get_object(new_builder, "ViewMenuButton"));
		g_signal_connect(ViewMenuButton, "clicked", G_CALLBACK(on_AddMealButton_activate), NULL);
		
		AddMealButton = GTK_WIDGET(gtk_builder_get_object(new_builder, "AddMealButton"));
		g_signal_connect(AddMealButton, "clicked", G_CALLBACK(on_AddMealButton_activate), NULL);

		DeleteMealButton = GTK_WIDGET(gtk_builder_get_object(new_builder, "DeleteMealButton"));
		g_signal_connect(DeleteMealButton, "clicked", G_CALLBACK(on_AddMealButton_activate), NULL);
		
		UpdateMealButton = GTK_WIDGET(gtk_builder_get_object(new_builder, "UpdateMealButton"));
		g_signal_connect(UpdateMealButton, "clicked", G_CALLBACK(on_AddMealButton_activate), NULL);
		
		gtk_widget_hide(window);

		g_signal_connect(new_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

		gtk_widget_show_all(new_window);
		window = new_window;
		builder = new_builder;
    }
}

void on_CustomerSubmitButton_activate()
{
    const gchar *name = gtk_entry_get_text(GTK_ENTRY(NameField));
    const gchar *phone = gtk_entry_get_text(GTK_ENTRY(PhoneField));
    const gchar *address = gtk_entry_get_text(GTK_ENTRY(AddressField));
    const gchar *password1 = gtk_entry_get_text(GTK_ENTRY(Password1Field));
    const gchar *password2 = gtk_entry_get_text(GTK_ENTRY(Password2Field));

	g_print("\n--- Customer Information ---\n");
    g_print("Name: %s\n", name);
    g_print("Phone: %s\n", phone);
    g_print("Address: %s\n",address);
    g_print("Password1: %s\n",password1);
    g_print("Password2: %s\n",password2);
    
    GtkBuilder *new_builder = gtk_builder_new();
    
    if (gtk_builder_add_from_file(new_builder, "LoginPage.glade", NULL) == 0) {
        g_error("Error loading New Glade file");
        return;
    }
    
    GtkWidget *new_window = GTK_WIDGET(gtk_builder_get_object(new_builder, "LoginWindow"));

    g_signal_connect(new_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    LoginField = GTK_WIDGET(gtk_builder_get_object(new_builder, "LoginField"));
    PasswordField = GTK_WIDGET(gtk_builder_get_object(new_builder, "PasswordField"));
    
    StatusLabel = GTK_WIDGET(gtk_builder_get_object(new_builder, "StatusLabel"));  

    SubmitButton = GTK_WIDGET(gtk_builder_get_object(new_builder, "SubmitButton"));
    g_signal_connect(SubmitButton, "clicked", G_CALLBACK(on_SubmitButton_activate), NULL);
    
    RegisterButton = GTK_WIDGET(gtk_builder_get_object(new_builder, "RegisterButton"));
    g_signal_connect(RegisterButton, "clicked", G_CALLBACK(on_RegisterButton_activate), NULL);
    
    char *col = "green";   
    gchar *new_text = "Registration Completed!";


    if ( !(strlen(name) && strlen(phone) && strlen(address) && strlen(password1) && strlen(password2))) {
    	new_text = "You have not been registered!";
        col = "red"; 
    }
    else if (strncmp(password1, password2, 20) != 0) {
    	new_text = "Passwords did not match!";
        col = "red"; 
    }
    else addUserInfo(Customer, name, phone, address, "", password1);

    GdkRGBA color;

    gtk_label_set_text(GTK_LABEL(StatusLabel), new_text);

    gdk_rgba_parse(&color, col);    
  
    gtk_widget_override_color(StatusLabel, GTK_STATE_FLAG_NORMAL, &color);

    PangoFontDescription *font_desc = pango_font_description_from_string("System-ui 20");
    gtk_widget_override_font(StatusLabel, font_desc);

    pango_font_description_free(font_desc);
    
    gtk_widget_show_all(new_window);
    gtk_widget_hide(window);

    g_timeout_add(4000, G_SOURCE_FUNC(hide_status_label), StatusLabel);

    window = new_window;
    builder = new_builder;
}

void on_CustomerButton_activate()
{
    GtkBuilder *new_builder = gtk_builder_new();
    
    if (gtk_builder_add_from_file(new_builder, "CustomerSignPage.glade", NULL) == 0) {
        g_error("Error loading New Glade file");
        return;
    }
    
    GtkWidget *new_window = GTK_WIDGET(gtk_builder_get_object(new_builder, "CustomerSignWindow"));

    gtk_widget_hide(window);

    g_signal_connect(new_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    CustomerSubmitButton = GTK_WIDGET(gtk_builder_get_object(new_builder, "CustomerSubmitButton"));
    g_signal_connect(CustomerSubmitButton, "clicked", G_CALLBACK(on_CustomerSubmitButton_activate), NULL);

    NameField = GTK_WIDGET(gtk_builder_get_object(new_builder, "NameField"));
    PhoneField = GTK_WIDGET(gtk_builder_get_object(new_builder, "PhoneField"));
    AddressField = GTK_WIDGET(gtk_builder_get_object(new_builder, "AddressField"));
    Password1Field = GTK_WIDGET(gtk_builder_get_object(new_builder, "Password1Field"));
    Password2Field = GTK_WIDGET(gtk_builder_get_object(new_builder, "Password2Field"));

    gtk_widget_show_all(new_window);
    window = new_window;
    builder = new_builder;
}

void on_DasherSubmitButton_activate()
{
    const gchar *name = gtk_entry_get_text(GTK_ENTRY(NameField));
    const gchar *phone = gtk_entry_get_text(GTK_ENTRY(PhoneField));
    const gchar *address = gtk_entry_get_text(GTK_ENTRY(AddressField));
    const gchar *type = gtk_entry_get_text(GTK_ENTRY(DeliveryTypeField));
    const gchar *password1 = gtk_entry_get_text(GTK_ENTRY(Password1Field));
    const gchar *password2 = gtk_entry_get_text(GTK_ENTRY(Password2Field));

	g_print("\n--- Dasher Information ---\n");
    g_print("Name: %s\n", name);
    g_print("Phone: %s\n", phone);
    g_print("Address: %s\n",address);
    g_print("Delivery Type Field: %s\n", type);
    g_print("Password1: %s\n",password1);
    g_print("Password2: %s\n",password2);
    
    GtkBuilder *new_builder = gtk_builder_new();
    
    if (gtk_builder_add_from_file(new_builder, "LoginPage.glade", NULL) == 0) {
        g_error("Error loading New Glade file");
        return;
    }
    
    GtkWidget *new_window = GTK_WIDGET(gtk_builder_get_object(new_builder, "LoginWindow"));

    g_signal_connect(new_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    StatusLabel = GTK_WIDGET(gtk_builder_get_object(new_builder, "StatusLabel"));

    LoginField = GTK_WIDGET(gtk_builder_get_object(new_builder, "LoginField"));
    PasswordField = GTK_WIDGET(gtk_builder_get_object(new_builder, "PasswordField"));  

    SubmitButton = GTK_WIDGET(gtk_builder_get_object(new_builder, "SubmitButton"));
    g_signal_connect(SubmitButton, "clicked", G_CALLBACK(on_SubmitButton_activate), NULL);
    
    RegisterButton = GTK_WIDGET(gtk_builder_get_object(new_builder, "RegisterButton"));
    g_signal_connect(RegisterButton, "clicked", G_CALLBACK(on_RegisterButton_activate), NULL);
    
    char *col = "green";   
    gchar *new_text = "Registration Completed!";


    if ( !(strlen(name) && strlen(phone) && strlen(address) && strlen(password1) && strlen(password2))) {
    	new_text = "You have not been registered!";
        col = "red"; 
    }
    else if (strncmp(password1, password2, 20) != 0) {
    	new_text = "Passwords did not match!";
        col = "red"; 
    }
    else addUserInfo(Dasher, name, phone, address, type, password1);

    GdkRGBA color;

    gtk_label_set_text(GTK_LABEL(StatusLabel), new_text);

    gdk_rgba_parse(&color, col);    
  
    gtk_widget_override_color(StatusLabel, GTK_STATE_FLAG_NORMAL, &color);

    PangoFontDescription *font_desc = pango_font_description_from_string("System-ui 20");
    gtk_widget_override_font(StatusLabel, font_desc);

    pango_font_description_free(font_desc);
    
    gtk_widget_show_all(new_window);
    gtk_widget_hide(window);

    g_timeout_add(4000, G_SOURCE_FUNC(hide_status_label), StatusLabel);

    window = new_window;
    builder = new_builder;
}

void on_DasherButton_activate()
{
    GtkBuilder *new_builder = gtk_builder_new();
    
    if (gtk_builder_add_from_file(new_builder, "DasherSignPage.glade", NULL) == 0) {
        g_error("Error loading New Glade file");
        return;
    }
    
    GtkWidget *new_window = GTK_WIDGET(gtk_builder_get_object(new_builder, "DasherSignWindow"));

    gtk_widget_hide(window);

    g_signal_connect(new_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    DasherSubmitButton = GTK_WIDGET(gtk_builder_get_object(new_builder, "DasherSubmitButton"));
    g_signal_connect(DasherSubmitButton, "clicked", G_CALLBACK(on_DasherSubmitButton_activate), NULL);

    NameField = GTK_WIDGET(gtk_builder_get_object(new_builder, "NameField"));
    PhoneField = GTK_WIDGET(gtk_builder_get_object(new_builder, "PhoneField"));
    AddressField = GTK_WIDGET(gtk_builder_get_object(new_builder, "AddressField"));
    DeliveryTypeField = GTK_WIDGET(gtk_builder_get_object(new_builder, "DeliveryTypeField"));
    Password1Field = GTK_WIDGET(gtk_builder_get_object(new_builder, "Password1Field"));
    Password2Field = GTK_WIDGET(gtk_builder_get_object(new_builder, "Password2Field"));

    gtk_widget_show_all(new_window);
    window = new_window;
    builder = new_builder;
}

void hide_status_label(GtkWidget *label) {
    gtk_widget_hide(label);
}

void on_RestaurantSubmitButton_activate()
{
    const gchar *name = gtk_entry_get_text(GTK_ENTRY(NameField));
    const gchar *phone = gtk_entry_get_text(GTK_ENTRY(PhoneField));
    const gchar *address = gtk_entry_get_text(GTK_ENTRY(AddressField));
    const gchar *password1 = gtk_entry_get_text(GTK_ENTRY(Password1Field));
    const gchar *password2 = gtk_entry_get_text(GTK_ENTRY(Password2Field));

	g_print("\n--- Restaurant Information ---\n");
    g_print("Name: %s\n", name);
    g_print("Phone: %s\n", phone);
    g_print("Address: %s\n",address);
    g_print("Password1: %s\n",password1);
    g_print("Password2: %s\n",password2);
    
    GtkBuilder *new_builder = gtk_builder_new();
    
    if (gtk_builder_add_from_file(new_builder, "LoginPage.glade", NULL) == 0) {
        g_error("Error loading New Glade file");
        return;
    }
    
    GtkWidget *new_window = GTK_WIDGET(gtk_builder_get_object(new_builder, "LoginWindow"));

    g_signal_connect(new_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    StatusLabel = GTK_WIDGET(gtk_builder_get_object(new_builder, "StatusLabel"));

    LoginField = GTK_WIDGET(gtk_builder_get_object(new_builder, "LoginField"));
    PasswordField = GTK_WIDGET(gtk_builder_get_object(new_builder, "PasswordField"));  

    SubmitButton = GTK_WIDGET(gtk_builder_get_object(new_builder, "SubmitButton"));
    g_signal_connect(SubmitButton, "clicked", G_CALLBACK(on_SubmitButton_activate), NULL);
    
    RegisterButton = GTK_WIDGET(gtk_builder_get_object(new_builder, "RegisterButton"));
    g_signal_connect(RegisterButton, "clicked", G_CALLBACK(on_RegisterButton_activate), NULL);
    
    char *col = "green";   
    gchar *new_text = "Registration Completed!";


    if ( !(strlen(name) && strlen(phone) && strlen(address) && strlen(password1) && strlen(password2))) {
    	new_text = "You have not been registered!";
        col = "red"; 
    }
    else if (strncmp(password1, password2, 20) != 0) {
    	new_text = "Passwords did not match!";
        col = "red"; 
    }
    else addUserInfo(Restaurant, name, phone, address, "", password1);

    GdkRGBA color;

    gtk_label_set_text(GTK_LABEL(StatusLabel), new_text);

    gdk_rgba_parse(&color, col);    
  
    gtk_widget_override_color(StatusLabel, GTK_STATE_FLAG_NORMAL, &color);

    PangoFontDescription *font_desc = pango_font_description_from_string("System-ui 20");
    gtk_widget_override_font(StatusLabel, font_desc);

    pango_font_description_free(font_desc);
    
    gtk_widget_show_all(new_window);
    gtk_widget_hide(window);

    g_timeout_add(4000, G_SOURCE_FUNC(hide_status_label), StatusLabel);

    window = new_window;
    builder = new_builder;
}

void on_RestaurantButton_activate()
{
    GtkBuilder *new_builder = gtk_builder_new();
    
    if (gtk_builder_add_from_file(new_builder, "RestaurantSignPage.glade", NULL) == 0) {
        g_error("Error loading New Glade file");
        return;
    }
    
    GtkWidget *new_window = GTK_WIDGET(gtk_builder_get_object(new_builder, "RestaurantSignWindow"));

    gtk_widget_hide(window);

    g_signal_connect(new_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    RestaurantSubmitButton = GTK_WIDGET(gtk_builder_get_object(new_builder, "RestaurantSubmitButton"));
    g_signal_connect(RestaurantSubmitButton, "clicked", G_CALLBACK(on_RestaurantSubmitButton_activate), NULL);

    NameField = GTK_WIDGET(gtk_builder_get_object(new_builder, "NameField"));
    PhoneField = GTK_WIDGET(gtk_builder_get_object(new_builder, "PhoneField"));
    AddressField = GTK_WIDGET(gtk_builder_get_object(new_builder, "AddressField"));
    Password1Field = GTK_WIDGET(gtk_builder_get_object(new_builder, "Password1Field"));
    Password2Field = GTK_WIDGET(gtk_builder_get_object(new_builder, "Password2Field"));

    gtk_widget_show_all(new_window);
    window = new_window;
    builder = new_builder;
}


void on_RegisterButton_activate()
{
    GtkBuilder *new_builder = gtk_builder_new();
    if (gtk_builder_add_from_file(new_builder, "RegistrationPage.glade", NULL) == 0) {
        g_error("Error loading New Glade file");
        return;
    }
    
    CustomerButton = GTK_WIDGET(gtk_builder_get_object(new_builder, "CustomerButton"));
    g_signal_connect(CustomerButton, "clicked", G_CALLBACK(on_CustomerButton_activate), NULL);
    
    DasherButton = GTK_WIDGET(gtk_builder_get_object(new_builder, "DasherButton"));
    g_signal_connect(DasherButton, "clicked", G_CALLBACK(on_DasherButton_activate), NULL);

    RestaurantButton = GTK_WIDGET(gtk_builder_get_object(new_builder, "RestaurantButton"));
    g_signal_connect(RestaurantButton, "clicked", G_CALLBACK(on_RestaurantButton_activate), NULL);
    
    GtkWidget *new_window = GTK_WIDGET(gtk_builder_get_object(new_builder, "RegistrationWindow"));

    gtk_widget_hide(window);

    g_signal_connect(new_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(new_window);
    window = new_window;
    builder = new_builder;
}

int main(int argc, char *argv[]) {

	int port = argc > 1 ? atoi(argv[1]) : 8080;
	char *ip = argc > 2 ? argv[2] : "127.0.0.1";
	
	struct sockaddr_in addr;
	
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket < 0) {
		perror("[!] Socket for server wasn't created");
		exit(1);
	}
	printf("[+] TCP socket for server was created.\n");

	memset(&addr, '\0', sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = port;
	addr.sin_addr.s_addr = inet_addr(ip);

	if (connect(server_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0)	{
		perror("[!] Failed to connect to the server");
		exit(1);
	}
	printf("[+] Connected to the server.\n");


    gtk_init(&argc, &argv);

    builder = gtk_builder_new();

    if (gtk_builder_add_from_file(builder, "LoginPage.glade", NULL) == 0) {
        g_error("Error loading Glade file");
        return EXIT_FAILURE;
    }

    window = GTK_WIDGET(gtk_builder_get_object(builder, "LoginWindow"));
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    LoginField = GTK_WIDGET(gtk_builder_get_object(builder, "LoginField"));
    PasswordField = GTK_WIDGET(gtk_builder_get_object(builder, "PasswordField"));  

    if (!GTK_IS_ENTRY(LoginField) || !GTK_IS_ENTRY(PasswordField)) {
        g_error("Error: Incorrect widget types");
        return EXIT_FAILURE;
    }

    StatusLabel = GTK_WIDGET(gtk_builder_get_object(builder, "StatusLabel"));
	
    SubmitButton = GTK_WIDGET(gtk_builder_get_object(builder, "SubmitButton"));
    g_signal_connect(SubmitButton, "clicked", G_CALLBACK(on_SubmitButton_activate), NULL);
    
    RegisterButton = GTK_WIDGET(gtk_builder_get_object(builder, "RegisterButton"));
    g_signal_connect(RegisterButton, "clicked", G_CALLBACK(on_RegisterButton_activate), NULL);

    gtk_builder_connect_signals(builder, NULL);

    fixed = GTK_WIDGET(gtk_builder_get_object(builder, "Fixed"));

    gtk_widget_show(window);

    gtk_main();
    
    if (close(server_socket) < 0) {
		perror("[!] Server socket was not closed");
		exit(1);
	}
	printf("[-] Disconnected from the server.\n");

	return 0;

    return EXIT_SUCCESS;
}
