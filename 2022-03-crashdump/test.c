#include <stdio.h>
#include <stdlib.h>
#ifdef SENTRY
#include "test_sentry.h"
#endif

void bar() 
{
    abort();
}

void foo() 
{
    bar();
}

void main(int argc, char *argv[]) 
{
#ifdef SENTRY
    atexit(cleanup);
    test_sentry_init();
    foo();
    test_sentry_fini();
#else
    foo();
#endif
}


