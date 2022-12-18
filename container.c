#include <gtk/gtk.h>

int main(int argc, char **argv) {
	gtk_init(&argc, &argv);
	GtkWidget *window;

	GtkWidget *box;

	GtkWidget *button1;
	GtkWidget *button2;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	button1 = gtk_button_new_with_label("button1");
	button2 = gtk_button_new_with_label("button2");

	gtk_container_add(GTK_CONTAINER(window), box);

	gtk_box_pack_start(GTK_BOX(box), button1, TRUE, TRUE, 50);
	gtk_box_pack_start(GTK_BOX(box), button2, TRUE, FALSE, 50);

	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
