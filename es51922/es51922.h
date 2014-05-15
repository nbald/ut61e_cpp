/*
 * es51922.h
 *
 * based on
 *     UT61E.h
 *
 *      Created on: 12.11.2009
 *          Author: steffen
 */

#ifndef es51922_H_
#define es51922_H_


class es51922 {
public:
	es51922();
	virtual ~es51922();
	bool check(char * data);
	void parse(char * data);
	const char* getMode();
	const char* getPower();
	const char* getRange();

	double value, max, min, average;
	long sample;
	char data[14];

	bool hold, rel, bat;

	enum { VOLTAGE, CURENT, RESISTANCE, DIODE, FREQUENCY, CAPACITANCE, INDUCTANCE, CONDUCTANCE } mode, lastmode;
	enum { DUTY, FREQUENCE } fmode;
	enum { AC, DC } power;
	enum { AUTO, MANUAL } range;
	enum { OVERLOAD, NORMAL, UNDERLOAD } load;
	enum { MAX, MIN } peak;

private:
	static const char* modelbl[];
	static const char* fmodelbl[];
	static const char*  powerlbl[];
	static const char* rangelbl[];
	static const char* loadlbl[];
	static const char* peaklbl[];
};

#endif /* es51922_H_ */
