P=$%
OBJECTS=
CFLAGS=-Wall -O3 -fopenmp
LDLIBS=-lcurl

single-threaded-curl: single-threaded-curl.c
	gcc single-threaded-curl.c -o single-threaded-curl -Wall -O3 -lcurl 

concurrent-curl-openmp: concurrent-curl-openmp.c
	gcc concurrent-curl-openmp.c -o concurrent-curl-openmp -Wall -O3 -fopenmp -lcurl

concurrent-curl-pthreads: concurrent-curl-pthreads.c
	gcc concurrent-curl-pthreads.c -o concurrent-curl-pthreads -Wall -O3 -lcurl -pthread

concurrent-curl-multi: concurrent-curl-multi.c
	gcc concurrent-curl-multi.c -o concurrent-curl-multi -Wall -O3 -lcurl 

all: single-threaded-curl concurrent-curl-multi concurrent-curl-pthreads concurrent-curl-openmp
