//send a number to tcp server and receive a square back
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <uv.h>

//vars for on client read, wont be declared every function call
int i;
int val;
char *next;

void on_new_connection(uv_stream_t *server, int status);
void on_client_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf);
void on_client_write(uv_write_t *req, int status);
void on_client_close(uv_handle_t* handle);
void alloc_buffer(uv_handle_t *handle, size_t size, uv_buf_t *buf);


int main(int argc, char** argv) {
    uv_loop_t *loop = uv_default_loop();

    uv_tcp_t server;
    uv_tcp_init(loop, &server);

    struct sockaddr_in bind_addr;
    uv_ip4_addr("0.0.0.0", 8080, &bind_addr);

    uv_tcp_bind(&server, (const struct sockaddr*)&bind_addr, 0);
    int r = uv_listen((uv_stream_t*) &server, 128, on_new_connection);
    if (r) {
        fprintf(stderr, "error... %s\n", uv_strerror(r));
        return 1;
    }

    printf("Server is listening... port 8080\n");

    return uv_run(loop, UV_RUN_DEFAULT);
}

void on_new_connection(uv_stream_t *server, int status) {
    if (status < 0) {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        return;
    }

    uv_tcp_t *client = malloc(sizeof(uv_tcp_t));    //user connection
    uv_tcp_init(uv_default_loop(), client);

    if (uv_accept(server, (uv_stream_t*) client) == 0) {
        uv_read_start((uv_stream_t*) client, alloc_buffer, on_client_read);     //reading data from the user
    } else {
        uv_close((uv_handle_t*) client, on_client_close);
    }
}

void on_client_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf) { 
    int response_len;   //nisam deklarirao donje varijable koje se koriste u else if iz razloga da se vidi koja je deklaracija istih

    if (nread < 0) {
        if (nread != UV_EOF) {
            fprintf(stderr, "reading error %s\n", uv_err_name(nread));
        }
        uv_close((uv_handle_t*) client, on_client_close);
        free (buf->base); //free memory!!!
        return;
    }
    if (nread > 0) {
        val = atoi(buf->base);
        if (val > 0) {      //check if imput is number, not fully correct, still can pass number+{some char} but OK
            val = val * val;
            //send square back to client

            // uv_buf_t response = uv_buf_init((char*)&val, sizeof(val));       //ways to send data 
            // uv_write_t *req = (uv_write_t*) malloc(sizeof(uv_write_t));
            // uv_write(req, client, &response, 1, on_client_write);
            char square[128];
            response_len = snprintf(square, sizeof(square), "%d\n", val);
            uv_buf_t response_buf = uv_buf_init(square, response_len);
            uv_write_t* req = (uv_write_t*)malloc(sizeof(uv_write_t));  //handler to keep the track of writing progress, used for sending data over TCP
            uv_write(req, client, &response_buf, 1, on_client_write);   //send back request
        }
        else{       //ako nije broj posalji poruku
            char message [40] = "You can enter only numerical values!\n";
            uv_buf_t response_buf = uv_buf_init(message, 40);
            uv_write_t* req = (uv_write_t*)malloc(sizeof(uv_write_t));
            uv_write(req, client, &response_buf, 1, on_client_write);
        }   
        
    }
    free(buf->base);
}

void on_client_write(uv_write_t *req, int status) {     //sending data to client
    if (status < 0) {
        fprintf(stderr, "Write error %s\n", uv_strerror(status));
    }
    free(req); //free uv_write_t handler
}

void on_client_close(uv_handle_t* handle) {
    free(handle);
}
void alloc_buffer(uv_handle_t *handle, size_t size, uv_buf_t *buf) {    //alloc buffer that will be used for reading data from user connection
    buf->base = (char*) malloc(size);
    buf->len = size;
}