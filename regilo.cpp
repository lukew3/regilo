#include <iostream>
#include <thread>
#include <string>
#include <pthread.h>
#include "mongoose.h"

char* serve_dir = ".";

static void server_callback(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
	if (ev == MG_EV_HTTP_MSG) {
		struct mg_http_message *hm = (struct mg_http_message *) ev_data;
		if (mg_http_match_uri(hm, "/websocket")) {
			mg_ws_upgrade(c, hm, NULL);
		} else {
			struct mg_http_serve_opts opts = {.root_dir = serve_dir};   // Serve local dir
			mg_http_serve_dir(c, hm, &opts);
		}
	} else if (ev == MG_EV_WS_MSG) {
		struct mg_ws_message *wm = (struct mg_ws_message *) ev_data;    
		// Got websocket frame. Received data is wm->data. Echo it back!
		char exec_string[100] = "xdotool key ";
		std::cout << wm->data.ptr << std::endl;
		strcat(exec_string, wm->data.ptr);
		std::cout << exec_string << std::endl;
//		system("xdotool key ctrl+w");
		system(exec_string);
		mg_ws_send(c, wm->data.ptr, wm->data.len, WEBSOCKET_OP_TEXT);
	}
	(void) fn_data;
}

void *start_static_server(char* serve_dir) {
        struct mg_mgr mgr;
        mg_mgr_init(&mgr);                                        // Init manager
        mg_http_listen(&mgr, "http://localhost:8000", server_callback, NULL);  // Setup listener
	std::cout << "Serving from \"" << serve_dir << "\" on http://localhost:8000" << std::endl;
        for (;;) mg_mgr_poll(&mgr, 1000);                         // Event loop
        mg_mgr_free(&mgr);                                        // Cleanup
}

// Serve the directory or zip file passed as argument
int main(int argc, char **argv) {
	// If there are arguments, use the first as the serve directory
	if (argc > 1) serve_dir = argv[1];
        // Start static server in a new thread
	std::thread server_thread(&start_static_server, serve_dir);
	server_thread.join(); // join and block main thread

        return EXIT_SUCCESS;
}
