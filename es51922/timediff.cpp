#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include "timediff.h"

timediff::timediff(){rst();}

long timediff::get()
{
    struct timeval now;
    gettimeofday(&now, NULL); 

    long sec_diff = now.tv_sec - start.tv_sec;

    long msec_diff = ((now.tv_usec/1000+1000 ) - (start.tv_usec/1000+0 ) );
    if(msec_diff >= 1000) msec_diff-=1000;


    return sec_diff*1000 + msec_diff;
}

void timediff::rst()
{
    gettimeofday(&start, NULL); 
}
