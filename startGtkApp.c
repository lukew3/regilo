#include <gtk/gtk.h>

static void activate (GtkApplication *app, gpointer user_data) {
	GtkWidget *window;
	window = gtk_application_window_new(app);
	gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
	GtkApplication *app;
	int ret;

	app = gtk_application_new("com.regilo", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	ret = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	return ret;
}
/*
int main (int argc, char **argv) {
	const char *title;

	gtk_init (&argc, &argv);
	GtkWidget *window;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Regilo");
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

	title = gtk_window_get_title(GTK_WINDOW(window));
	printf("Your title is: %s\n", title);

	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
*/
