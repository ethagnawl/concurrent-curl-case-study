#include "helpers.h"
#include "urls.h"
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>

void *dispatch_request(char *url) {
    CURL *curl = curl_easy_init();
    int http_code = 0;

    if (!curl) {
        exit(EXIT_FAILURE);
    } 

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

    curl_easy_perform(curl);

    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

    print_response_status_code(url, http_code);

    curl_easy_cleanup(curl);
    
    return NULL;
}

int main() {
  int urls_length = (sizeof(urls) / sizeof(urls[0]));

  #pragma omp parallel for
  for (int i = 0; i < urls_length; i += 1) {
      dispatch_request(urls[i]);
  }
}
