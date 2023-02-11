#include <gtk/gtk.h>
#include <pthread.h>
#include "mongoose.h"


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
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, start_static_server, NULL);
	//pthread_join(thread_id, NULL);

	// Run gtk app
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
