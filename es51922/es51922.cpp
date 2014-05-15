/*
 * es51922.cpp
 * 
 * based on
 *     UT61E.cpp
 *
 *      Created on: 12.11.2009
 *          Author: steffen
 */


#include "es51922.h"
#include <exception>
#include <cstdlib>
#include <sys/time.h>
#include <time.h>

const char* es51922::modelbl[] = { "V", "A", "Ohm", "-|>-", "Hz", "F", "H", "-/ -" };
const char* es51922::fmodelbl[] = { "Duty" , "Frequence" };
const char* es51922::powerlbl[] = {"AC", "DC" };
const char* es51922::rangelbl[] = { "Auto", "Manual" };
const char* es51922::loadlbl[] = { "Overload", "Normal", "Underload" };
const char* es51922::peaklbl[] = { "Maximum", "Minimum" };

es51922::es51922() {
	mode = VOLTAGE;
}

es51922::~es51922() {}

const char* es51922::getMode() {
	return es51922::modelbl[mode];
}

const char* es51922::getPower() {
	return es51922::powerlbl[power];
}

const char* es51922::getRange() {
	return es51922::rangelbl[range];
}

bool es51922::check(char * data) {
	if ((data[0] & 0x30) == 0x30 && data[12] == 0x0d && data[13] == 0x0a) {
		return true;
	} else {
		return false;
	}
}

void es51922::parse(char * data) {

	char digits[] = { data[1], data[2], data[3], data[4], data[5] }; // directly holds the digits as ascii chars
	value = atof(digits);

	lastmode = mode;

        // flags
	bat = (data[7] & 2)>0;
	rel = (data[8] & 2)>0;
	hold = (data[11] & 2)>0;


	if (data[7] & 0x04) // negative
		value *= -1;

	if (data[10] & 8)
		power = DC;
	else if (data[10] & 4)
		power = AC;

	if (data[10] & 2)
		range = AUTO;
	else
		range = MANUAL;

	if (data[7] & 1)
		load = OVERLOAD;
	else if (data[9] & 8)
		load = UNDERLOAD;
	else
		load = NORMAL;

	if (data[9] & 4)
		peak = MAX;
	else if (data[9] & 2)
		peak = MIN;

	if (data[10] & 1)
		fmode = FREQUENCE;

	if (data[7] & 8)
		fmode = DUTY;

	double multp = 1;
	switch (data[6]) {
	case '1':
		mode = DIODE;
		break;

	case '2':
		mode = FREQUENCY;

		switch (data[0]) {
		case '0':
			multp = 1e-2;
			break;
		case '1':
			multp = 1e-1;
			break;
		case '3':
			multp = 1;
			break;
		case '4':
			multp = 1e1;
			break;
		case '5':
			multp = 1e2;
			break;
		case '6':
			multp = 1e3;
			break;
		case '7':
			multp = 1e4;
			break;
		default:
			throw std::exception();
		}
		break;

	case '3':
		mode = RESISTANCE;

		switch (data[0]) {
		case '0':
			multp = 1e-2;
			break;
		case '1':
			multp = 1e-1;
			break;
		case '2':
			multp = 1;
			break;
		case '3':
			multp = 1e1;
			break;
		case '4':
			multp = 1e2;
			break;
		case '5':
			multp = 1e3;
			break;
		case '6':
			multp = 1e4;
			break;
		default:
			throw std::exception();
		}
		break;

	case '5':
		mode = CONDUCTANCE;
		break;

	case '6':
		mode = CAPACITANCE;

		switch (data[0]) {
		case '0':
			multp = 1e-12;
			break;
		case '1':
			multp = 1e-11;
			break;
		case '2':
			multp = 1e-10;
			break;
		case '3':
			multp = 1e-9;
			break;
		case '4':
			multp = 1e-8;
			break;
		case '5':
			multp = 1e-7;
			break;
		case '6':
			multp = 1e-6;
			break;
		case '7':
			multp = 1e-5;
			break;
		default:
			throw std::exception();
		}
		break;

	case 0x3b: // V
		mode = VOLTAGE;

		switch (data[0]) {
		case '0':
			multp = 1e-4;
			break;
		case '1':
			multp = 1e-3;
			break;
		case '2':
			multp = 1e-2;
			break;
		case '3':
			multp = 1e-1;
			break;
		case '4':
			multp = 1e-5;
			break;
		default:
			throw std::exception();
		}
		break;

	case '0': // A
		mode = CURENT;
		if (data[0] == '0')
			multp = 1e-3;
		else {
			throw std::exception();
		}
		break;

	case 0x3d: // uA
		mode = CURENT;

		switch (data[0]) {
		case '0':
			multp = 1e-8;
			break;
		case '1':
			multp = 1e-7;
			break;
		default:
			throw std::exception();
		}

		break;
	case 0x3f: // mA
		mode = CURENT;

		switch (data[0]) {
		case '0':
			multp = 1e-6;
			break;
		case '1':
			multp = 1e-5;
			break;
		default:
			throw std::exception();
		}

		break;
	default:
		throw std::exception();
	}

	value *= multp;

	if (mode != lastmode) {
		max = value; // max=0 -> bug
		min = value; // min=0 -> bug
		sample = 0;
		average = value;
	}

	if (value > max)
		max = value;

	if (value < min)
		min = value;

	average = (sample * average + value) / ++sample;
}
