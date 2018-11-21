// _heavily_ inspired by: https://curl.haxx.se/libcurl/c/10-at-a-time.html

#include "helpers.h"
#include "urls.h"
#include <curl/multi.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void init(CURLM *cm, const char *url, Callback callback) {
    CURL *curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_PRIVATE, url);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

    curl_multi_add_handle(cm, curl);
}

int main(void) {
    long urls_length = (sizeof(urls) / sizeof(urls[0]));
    CURLM *cm = curl_multi_init();
    int U = -1;
    CURLMsg *msg;
    long L;
    int M, Q;
    fd_set R, W, E;
    struct timeval T;

    curl_global_init(CURL_GLOBAL_ALL);

    curl_multi_setopt(cm, CURLMOPT_MAXCONNECTS, urls_length);

    while (urls_length--) {
        init(cm, urls[urls_length], callback);
    }

    while (U) {
        curl_multi_perform(cm, &U);

        if (U) {
            FD_ZERO(&R);
            FD_ZERO(&W);
            FD_ZERO(&E);

            if (curl_multi_fdset(cm, &R, &W, &E, &M)) {
                fprintf(stderr, "E: curl_multi_fdset\n");
                return EXIT_FAILURE;
            }

            if (curl_multi_timeout(cm, &L)) {
                fprintf(stderr, "E: curl_multi_timeout\n");
                return EXIT_FAILURE;
            }

            if (L == -1) {
                L = 100;
            }

            if (M == -1) {
                sleep((unsigned int)L / 1000);
            } else {
                T.tv_sec = L/1000;
                T.tv_usec = (L%1000)*1000;

                if (0 > select(M + 1, &R, &W, &E, &T)) {
                    fprintf(stderr, "E: select(%i,,,,%li): %i: %s\n", M + 1, L, errno, strerror(errno));
                    return EXIT_FAILURE;
                }
            }
        }

        while ((msg = curl_multi_info_read(cm, &Q))) {
            if (msg->msg == CURLMSG_DONE) {
                int http_code = 0;
                char *url;
                CURL *e = msg->easy_handle;

                curl_easy_getinfo(e, CURLINFO_PRIVATE, &url);
                curl_easy_getinfo(e, CURLINFO_RESPONSE_CODE, &http_code);

                print_response_status_code(url, http_code);

                curl_multi_remove_handle(cm, e);
                curl_easy_cleanup(e);
            } else {
                fprintf(stderr, "E: CURLMsg (%d)\n", msg->msg);
            }
        }
    }

    curl_multi_cleanup(cm);
    curl_global_cleanup();
}
