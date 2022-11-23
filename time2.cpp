#include <stdio.h>
#include <time.h>
#include <math.h>

int main( void) {
    struct timespec specific_time;
    struct tm *now;
    int millsec;
    clock_gettime( CLOCK_REALTIME, &specific_time);
    now = localtime(&specific_time.tv_sec);
    millsec = specific_time.tv_nsec;

    millsec = floor (specific_time.tv_nsec/1.0e6);


    printf("[%04d/%02d/%02d] %02d:%02d:%02d msec : %d\n", 1900 + now->tm_year, 
        now->tm_mon + 1, now->tm_mday, now->tm_hour, 
        now->tm_min, now->tm_sec, millsec);

    return 0;
}


//gcc test.c -lm

/*
struct timespec {
    time_t tv_sec
    long tv_nsec
}
*/