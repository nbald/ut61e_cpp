/*
 * main.cpp
 * 
 * 
 * based on
 *     main.cpp
 *
 *      Created on: 12.11.2009
 *          Author: steffen
 */
#include "es51922.h"
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include "timediff.h"
#include <unistd.h>

int main(int argc, char *argv[]) {

        timediff td;

	es51922 * dmm = new es51922();

	char buf[14];

	while (true) {
    
                // read carefully and detect bad data faster
                buf[13]=0; // make buffer data invalid
                for(int i=0;i<14;i++)
                {
                    std::cin.read(buf+i,1);
                    if(buf[i] == 0x0a) break; // sync immediately to src
                }

 
                if(std::cin.gcount()>0) // data read
                {

                    if (dmm->check(buf))
                    {
			dmm->parse(buf);

			if (!dmm->hold)
				std::cout << td.get() << ";" <<  dmm->sample << ";" << dmm->value << ";" << dmm->max << ";" << dmm->min << ";" << dmm->average << ";" << dmm->getMode() << ";" << dmm->getPower() << ";" << dmm->getRange() << std::endl <<  "" ;
                                fflush(stdout); // cout << fflush; works but returns also an 1 o0
		    }
                    else
                    {
			std::cerr << "Invalid data!" << std::endl;

                        // read bytes until there was a 0x0a to sync to source stream (this trashes 1 packet!)
                        //char c=0;
                        //while(c!=0x0a) std::cin.read(&c,1);
		    }
                }
                else // no data read
                {
                    usleep(1000*250);
                }

	}


}
