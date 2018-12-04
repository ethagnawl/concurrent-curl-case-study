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
- base case (single-threaded-curl)
- OpenMP (concurrent-curl-openmp)
- pthreads (concurrent-curl-pthreads)
- libcurl's multi interface (concurrent-curl-multi)

# Dependencies
- libcurl (all)
- C11 (concurrent-curl-pthreads)
- GNU_SOURCE (concurrent-curl-pthreads)
- OpenMP (concurrent-curl-openmp)

# Run
Each program can be built and run using: `make $DEMO && ./$DEMO`

# Conclusions

I was very surprised by two things:

## How little code was required to parallelize the base demo using OpenMP and pthreads

Parallelizing the single threaded base program was _shockingly_ easy. The program is very simple, but the OpenMP version only required _one_ additional line of code and one additional compiler flag; the pthreads version required seven new lines of code (including the pthreads header, defining GNU_SOURCE) and an additional compiler flag. Now, these programs weren't doing anything complicated like orchestrating access to shared memory, but IMO, these solutions are still much simpler than analogous solutions in other languages I've worked with. (This may/may not be a good thing, as those other languages may provide additional safeguards which C does not.)

## How much more code was required by the Curl multi interface example

To be fair, this program was very heavily inspired by a pre-existing program, so the solution wasn't as tidy as the others written for the purposes of this case study. However, there does seem to be quite a bit more orchestration/bookkeeping code required by the multi interface program (writing/reading file descriptors, sleeps, Curl cleanup utilities, etc.). This program did include some error handling that the threaded programs didn't, but this only accounted for ~10 of the additional ~60 lines of code in the multi example. There's likely good reason for the additional code in this program and since curl works everywhere, this example is probably more portable than the others. It may also be more performant than the other examples -- I haven't done any benchmarking.

If I was to pick one of these solutions to use in a production application, I'd probably pick the pthreads version. It is simple enough (despite requiring more code than the OpenMP version), should be more future proof (pthreads are part of the modern C standard) and there's no non-standard compiler feature dependency (OpenMP). Of course, this hypothetical choice would also depend on the target environment, as an application using OpenMP or Curl's multi interface would likely have a much wider reach than one relying on features in C11.

# Future Work
- benchmarks
- stress tests

# Resources
- [21st Century C](http://shop.oreilly.com/product/0636920033677.do)
- https://curl.haxx.se/libcurl/c/10-at-a-time.html
- [OpenMP API](https://docs.oracle.com/cd/E19059-01/stud.10/819-0501/1_Summary.html)
- [pthreads - Linux man page](https://linux.die.net/man/7/pthreads)
