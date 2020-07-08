
#ifndef AIRPORT_H_
#define AIRPORT_H_

#include "runway.h"

// global variable for the head of the list of runways

extern pNODE airport;

// adds a new runway to the airport
Result addRunway(int runwayNum, FlightType runwayType);

// removes runway from airport
Result removeRunway(int runwayNum);

//* function name: addFlightToAirport
//* Description: add a flight to the airport by the given rules of assigning a new flight.
//* Parameters: f_num - flight number
//*             f_type - flight type
//*             f_dest - a pointer to the destination of the flight
//*             f_Emergency - emergency flight or regular
//* return value: succes if flight added or faliure if not
Result addFlightToAirport(int f_num, FlightType f_type, char* f_dest, BOOL f_Emergency);

//* function name: departAirport
//* Description: depart a flight from the airport according to the rules given
//* Parameters: None
//* return value: succes for departing or faliure for not.
Result departAirport();

//* function name: changeDest
//* Description: changes flights destination
//* Parameters: originalDest - a pointer to the destination we want to change.
//*             newDest - a pointer to the desired destination
//* return value: succes for changing or faliure for not.
Result changeDest(char* originalDest, char* newDest);

//* function name: delay
//* Description: delays flights by the given rules
//* Parameters: delayed_dest - a pointer to the destination of flights we want to delay.
//* return value: success for delaying or faliure for not.
Result delay(char* delayed_dest);

//* function name: printAirport
//* Description: prints all runways and waiting flights in the airport
//* Parameters: None
//* return value: None
void printAirport();

//* function name: destroyAirport
//* Description: deletes airport, runways and flights.
//* Parameters: None
//* return value: None
void destroyAirport();

#endif

