#include <stdio.h>

void print_response_status_code(char *url, int response_status_code) {
  printf("HTTP Response Status Code for GET request to %s: %d\n", url, response_status_code);
}

void callback(void *ptr, size_t size, size_t nmemb, void *stream) { }

typedef void (*Callback)(void *ptr, size_t size, size_t nmemb, void *stream);
