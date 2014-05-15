###########################################
# ut61e interpreter
#
# Rainer Wetzel
# 2011-02-18
###########################################

all: es51922

CC=gcc
CXX=g++
CPPOBJS=./timediff.o ./es51922.o ./main.o
OBJS=$(CPPOBJS)
CFLAGS+=-I./ -Wall -g -c `pkg-config libusb-1.0 --cflags`
LIBS=`pkg-config libusb-1.0 libudev --libs`


es51922: $(OBJS)
	g++ -Wall -g $^ $(LIBS) -o es51922

$(CPPOBJS): %.o: %.cpp
	$(CXX) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJS) es51922

.PHONY: clean
