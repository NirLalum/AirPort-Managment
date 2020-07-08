#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "flight.h"


//* function name: fparamcheck
//* Description: checks if given parameters a valid
//* Parameters: flight_Num - flight number
//*             flight_Type - flight type
//*				flight_dest - flight destination
//*				flight_Emergency - parameter for the kind of flight (Emergency or regular)
//* return value: TRUE if all tests are good and FALSE if not
BOOL fParamCheck(int flight_Num, FlightType flight_Type, char* flight_dest, BOOL flight_Emergency) {

	if (flight_Num >= 1 && flight_Num <= MAX_ID) {
		if (strlen(flight_dest) == 3) {
			if ((flight_Type == 0) || (flight_Type == 1)) {
				if ((flight_Emergency == 0) || (flight_Emergency == 1)) {
					if (isDestValid(flight_dest)) {
						return TRUE;
					}
				}
			}
		}
	}
	return FALSE;
}

//* function name: createFlight
//* Description: checks if given parameters a valid
//* Parameters: flight_Num - flight number
//*             flight_Type - flight type
//*				flight_dest - flight destination
//*				flight_Emergency - parameter for the kind of flight (Emergency or regular)
//* return value: TRUE if all tests are good and FALSE if not
pFLIGHT creatFlight(int flight_Num, FlightType flight_Type, char* flight_dest, BOOL flight_Emergency) {

	pFLIGHT flight_ptr = (pFLIGHT)malloc(sizeof(FLIGHT));
	if (flight_ptr == NULL || !fParamCheck(flight_Num, flight_Type, flight_dest, flight_Emergency)) {
		return NULL;
	}
	char* dest = malloc(sizeof(flight_dest)); //--------- we need to make sure to freeee
	if (dest == NULL) return NULL;
	flight_ptr->f_Num = flight_Num;
	flight_ptr->f_Type = flight_Type;
	strcpy(dest, flight_dest);
	flight_ptr->f_dest = dest;
	flight_ptr->f_Emergency = flight_Emergency;

	return flight_ptr;
}

//* function name: destroyFlight
//* Description: removes flight memory
//* Parameters: flightpointer - a pointer to the flight that will be removed
//* return value: None
void destroyFlight(pFLIGHT flightPointer) {

	if (flightPointer == NULL) return;
	free(flightPointer->f_dest); // free dest memory that we got from strcpy in createflight
	free(flightPointer);
}

//* function name: printFlight
//* Description: prints flight data
//* Parameters: flightpointer - a pointer to the flight that will be printed
//* return value: None
void printFlight(pFLIGHT flightPointer) {

	if (flightPointer == NULL) return;
	char type = 'D';
	if (flightPointer->f_Type)
		type = 'I';
	char emergency = 'R';
	if (flightPointer->f_Emergency)
		emergency = 'E';
	printf("Flight %d %c %s %c\n", flightPointer->f_Num, type, flightPointer->f_dest, emergency);
}

//* function name: isDestValid
//* Description: checks if the flight destination name is valid
//* Parameters: dest - a pointer to the destination name
//* return value: TRUE if valid FALSE if not
BOOL isDestValid(char* dest) {
	if (strlen(dest) != 3) {
		return FALSE;
	}
	int i = 0;
	while (dest[i] != '\0') {
		if (dest[i] < 'A' || dest[i] > 'Z') return FALSE;
		i++;
	}
	return TRUE;
}