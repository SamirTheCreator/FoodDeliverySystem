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
GtkWidget   *LoginLabel;
GtkBuilder   *builder;

int main(int argc, char *argv[])
{
    g_print("Before gtk_init\n");
    gtk_init(&argc, &argv);
    g_print("After gtk_init\n");

    builder = gtk_builder_new();

    if (gtk_builder_add_from_file(builder, "DraftGlade.glade", NULL) == 0) {
        g_error("Error loading Glade file");
        return EXIT_FAILURE;
    }

    g_print("After loading Glade file\n");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "LoginWindow"));

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_builder_connect_signals(builder, NULL);

    fixed = GTK_WIDGET(gtk_builder_get_object(builder, "Fixed"));
    SubmitButton = GTK_WIDGET(gtk_builder_get_object(builder, "SubmitButton"));
    LoginLabel = GTK_WIDGET(gtk_builder_get_object(builder, "LoginLabel"));

    g_print("Before gtk_widget_show\n");
    gtk_widget_show(window);
    g_print("After gtk_widget_show\n");

    gtk_main();

    return EXIT_SUCCESS;
}

void on_SubmitButton_activate(GtkButton *b)
{
    gtk_label_set_text(GTK_LABEL(LoginLabel), "Your Data was Submitted.");
}
