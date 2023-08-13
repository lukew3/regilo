#include <gtk/gtk.h>
#include <pthread.h>
#include "mongoose.h"

GtkBuilder *builder;
GtkWidget *window;

static void server_callback(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
	struct mg_http_serve_opts opts = {.root_dir = "."};   // Serve local dir
	if (ev == MG_EV_HTTP_MSG) mg_http_serve_dir(c, ev_data, &opts);
}

void *start_static_server(void *vargp) {
	struct mg_mgr mgr;
	mg_mgr_init(&mgr);                                        // Init manager
	mg_http_listen(&mgr, "http://localhost:8000", server_callback, &mgr);  // Setup listener
	for (;;) mg_mgr_poll(&mgr, 1000);                         // Event loop
	mg_mgr_free(&mgr);                                        // Cleanup
}

int main(int argc, char **argv) {
	// Start static server in a new thread
	pthread_t server_thread;
	pthread_create(&server_thread, NULL, start_static_server, NULL);
	// pthread_join(server_thread, NULL); // Wait for termination of server_thread

	// Run gtk app in main thread
	gtk_init(&argc, &argv);

	builder = gtk_builder_new_from_file("regilo.glade");

	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	// gtk_widget_show_all(window);
	gtk_widget_show(window);
	gtk_main();

	return EXIT_SUCCESS;
}