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
GtkWidget   *LoginField;
GtkWidget   *PasswordField;
GtkBuilder   *builder;


void on_RegisterButton_activate(GtkButton *b)
{
    g_print("Register Button was pressed.\n");
}

void on_SubmitButton_activate(GtkButton *b)
{
    g_print("Login:");
    const gchar *login_text = gtk_entry_get_text(GTK_ENTRY(LoginField));
    const gchar *password_text = gtk_entry_get_text(GTK_ENTRY(PasswordField));

    g_print("Login: %s\n", login_text);
    g_print("Password: %s\n", password_text);    
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

