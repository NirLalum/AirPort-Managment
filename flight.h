
#ifndef FLIGHT_H_
#define FLIGHT_H_

#include "ex2.h"

//defining flight struct
typedef struct _FLIGHT {
	int f_Num;
	FlightType f_Type;
	char* f_dest; //check
	BOOL f_Emergency;
} FLIGHT, * pFLIGHT;

//* function name: createFlight
//* Description: checks if given parameters a valid
//* Parameters: flight_Num - flight number
//*             flight_Type - flight type
//*				flight_dest - flight destination
//*				flight_Emergency - parameter for the kind of flight (Emergency or regular)
//* return value: TRUE if all tests are good and FALSE if not
pFLIGHT creatFlight(int flight_Num, FlightType flight_Type, char* flight_dest, BOOL flight_Emergency);

//* function name: fparamcheck
//* Description: checks if given parameters a valid
//* Parameters: flight_Num - flight number
//*             flight_Type - flight type
//*				flight_dest - flight destination
//*				flight_Emergency - parameter for the kind of flight (Emergency or regular)
//* return value: TRUE if all tests are good and FALSE if not
BOOL fParamCheck(int flight_Num, FlightType flight_Type, char* flight_dest, BOOL flight_Emergency);

//* function name: destroyFlight
//* Description: removes flight memory
//* Parameters: flightpointer - a pointer to the flight that will be removed
//* return value: None
void destroyFlight(pFLIGHT flightPointer);

//* function name: printFlight
//* Description: prints flight data
//* Parameters: flightpointer - a pointer to the flight that will be printed
//* return value: None
void printFlight(pFLIGHT flightPointer);

//* function name: isDestValid
//* Description: checks if the flight destination name is valid
//* Parameters: dest - a pointer to the destination name
//* return value: TRUE if valid FALSE if not
BOOL isDestValid(char*);

#endif