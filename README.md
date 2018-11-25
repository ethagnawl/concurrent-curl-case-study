# About
I recently finished reading [21st Century C](http://shop.oreilly.com/product/0636920033677.do), by Ben Klemens, which provided 
the motivation for revisiting and releasing this demo. (Originally, it was just 
going to be a few examples covering how to use libcurl in a C program, but I'd 
abandoned it a while back.)

The included programs are my attempts at exploring some of the various ways you 
can make concurrent/parallel Curl requests using common C libraries and 
patterns. The programs don't do a whole lot -- they make concurrent/parallel 
requests to each of a list of URLs and report the response status code of each 
request -- but they were complicated enough that I was forced to reacquaint 
myself with C and its ecosystem and I learned quite a bit about Curl, OpenMP 
and POSIX threads.

The current examples cover:

- OpenMP (concurrent-curl-openmp)
- pthreads (concurrent-curl-pthreads)
- libcurl's multi interface (concurrent-curl-multi)

# Dependencies
- libcurl (all)
- C11 (concurrent-curl-pthreads)
- GNU_SOURCE (concurrent-curl-pthreads)
- openmp (concurrent-curl-openmp)

# Run
Each program can be built and run using: `make $DEMO && ./$DEMO`

# Conclusions
TODO

# Resources
- [21st Century C](http://shop.oreilly.com/product/0636920033677.do)
- https://curl.haxx.se/libcurl/c/10-at-a-time.html
- [OpenMP API](https://docs.oracle.com/cd/E19059-01/stud.10/819-0501/1_Summary.html)
- [pthreads - Linux man page](https://linux.die.net/man/7/pthreads)
