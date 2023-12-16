
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtkx.h>
#include <gtk/gtk.h>
#include <math.h>
#include <ctype.h>

GtkWidget  *window;
GtkWidget   *fixed;

GtkWidget   *SubmitButton;
GtkWidget   *RegisterButton;
GtkWidget   *CustomerButton;
GtkWidget   *DasherButton;
GtkWidget   *RestaurantButton;
GtkWidget   *CustomerSubmitButton;
GtkWidget   *DasherSubmitButton;
GtkWidget   *RestaurantSubmitButton;


GtkWidget   *LoginField;
GtkWidget   *PasswordField;
GtkWidget   *NameField;
GtkWidget   *PhoneField;
GtkWidget   *DeliveryTypeField;
GtkWidget   *AddressField;
GtkWidget   *Password1Field;
GtkWidget   *Password2Field;

GtkBuilder   *builder;

void on_SubmitButton_activate()
{
    const gchar *login_text = gtk_entry_get_text(GTK_ENTRY(LoginField));
    const gchar *password_text = gtk_entry_get_text(GTK_ENTRY(PasswordField));

    g_print("Login: %s\n", login_text);
    g_print("Password: %s\n", password_text);    
}

void on_CustomerSubmitButton_activate()
{
    const gchar *name = gtk_entry_get_text(GTK_ENTRY(NameField));
    const gchar *phone = gtk_entry_get_text(GTK_ENTRY(PhoneField));
    const gchar *address = gtk_entry_get_text(GTK_ENTRY(AddressField));
    const gchar *password1 = gtk_entry_get_text(GTK_ENTRY(Password1Field));
    const gchar *password2 = gtk_entry_get_text(GTK_ENTRY(Password2Field));

    g_print("Name: %s\n", name);
    g_print("Phone: %s\n", phone);
    g_print("Address: %s\n",address);
    g_print("Password1: %s\n",password1);
    g_print("Password2: %s\n",password2);
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

    g_print("Name: %s\n", name);
    g_print("Phone: %s\n", phone);
    g_print("Address: %s\n",address);
    g_print("Delivery Type Field: %s\n", type);
    g_print("Password1: %s\n",password1);
    g_print("Password2: %s\n",password2);   
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

void on_RestaurantSubmitButton_activate()
{
    const gchar *name = gtk_entry_get_text(GTK_ENTRY(NameField));
    const gchar *phone = gtk_entry_get_text(GTK_ENTRY(PhoneField));
    const gchar *address = gtk_entry_get_text(GTK_ENTRY(AddressField));
    const gchar *type = gtk_entry_get_text(GTK_ENTRY(DeliveryTypeField));
    const gchar *password1 = gtk_entry_get_text(GTK_ENTRY(Password1Field));
    const gchar *password2 = gtk_entry_get_text(GTK_ENTRY(Password2Field));

    g_print("Name: %s\n", name);
    g_print("Phone: %s\n", phone);
    g_print("Address: %s\n",address);
    g_print("Delivery Type Field: %s\n", type);
    g_print("Password1: %s\n",password1);
    g_print("Password2: %s\n",password2);   
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
    DeliveryTypeField = GTK_WIDGET(gtk_builder_get_object(new_builder, "DeliveryTypeField"));
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


    SubmitButton = GTK_WIDGET(gtk_builder_get_object(builder, "SubmitButton"));
    g_signal_connect(SubmitButton, "clicked", G_CALLBACK(on_SubmitButton_activate), NULL);
    
    RegisterButton = GTK_WIDGET(gtk_builder_get_object(builder, "RegisterButton"));
    g_signal_connect(RegisterButton, "clicked", G_CALLBACK(on_RegisterButton_activate), NULL);

    gtk_builder_connect_signals(builder, NULL);

    fixed = GTK_WIDGET(gtk_builder_get_object(builder, "Fixed"));

    gtk_widget_show(window);

    gtk_main();

    return EXIT_SUCCESS;
}
