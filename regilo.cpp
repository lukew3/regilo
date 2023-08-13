#include <iostream>
#include <thread>
#include <string>
#include <pthread.h>
#include "mongoose.h"

char* serve_dir = ".";

static void server_callback(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
        struct mg_http_serve_opts opts = {.root_dir = serve_dir};   // Serve local dir
        if (ev == MG_EV_HTTP_MSG) {
		struct mg_http_message *hm = (struct mg_http_message *) ev_data;
		mg_http_serve_dir(c, hm, &opts);
	}	
}

void *start_static_server(char* serve_dir) {
        struct mg_mgr mgr;
        mg_mgr_init(&mgr);                                        // Init manager
        mg_http_listen(&mgr, "http://localhost:8000", server_callback, &mgr);  // Setup listener
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
