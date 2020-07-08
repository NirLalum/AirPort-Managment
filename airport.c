#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "airport.h"


pNODE airport;

//* function name: addRunway
//* Description: adds a new runway to the airport
//* Parameters: runwayNum - int parameter for the desired runway number
//*             runwayType - parameter for the desired flight type
//* return value: succes(1) if runway was added or faliure(0) if not
Result addRunway(int runwayNum, FlightType runwayType) {
	pNODE previous = NULL;
	if (runwaySearch(airport, runwayNum, &previous) != NULL) return FAILURE; //if runway exists, return from func
	pRUNWAY newRunway;
	if (!(newRunway = createRunway(runwayNum, runwayType))) return FAILURE; // creating a new runway
	if (airport->data == NULL) { // if there are no runways at all
		airport->data = newRunway;
		return SUCCESS;
	}
	pNODE current = airport;
	while (current->pNext != NULL) { // serching the end of the runway linked list.
		current = current->pNext;
	}
	pNODE new_RUNWAY_NODE = createEmptyList();
	new_RUNWAY_NODE->data = newRunway;
	addNode(new_RUNWAY_NODE, &(current->pNext));
	return SUCCESS;
}

//* function name: removeRunway
//* Description: removes runway from airport
//* Parameters: runwayNum - int parameter for the desired runway number to remove
//* return value: succes(1) or faliure(0)
Result removeRunway(int runwayNum) {
	pNODE runWayToRemove = airport;
	pNODE previous = NULL;
	if (!(runWayToRemove = runwaySearch(runWayToRemove, runwayNum, &previous))) return FAILURE; // if the is no matching runway or no runways at all return FAILURE
		//previous contains pointer to link prior to the one we are looking for
	destroyRunway(runWayToRemove->data);
	if ((airport->pNext == NULL) && (previous == NULL)) {	//ONLY the case of one node only
		airport->data = NULL;
		airport->pNext = NULL;
		return SUCCESS;
	}
	if (previous == NULL) {	// ONLY the case of first node out of multiple nodes
		pNODE tmp = airport;
		airport = airport->pNext;
		free(tmp);
		return SUCCESS;
		return SUCCESS;

	}
	return removeNode(previous);
}

//* function name: whichRunway_add
//* Description: auxilary function for addFlight. determines to which runway to add a given flight
//* Parameters: type - flight type
//*             emergency - emergency or not
//* return value: the number of the runway to add the flight to. 
int whichRunway_add(FlightType type, BOOL emergency) {
	int min_ID = -1;
	if (emergency) { // in case the flight is emergency
		int T_flights, E_flights, T_flights_MIN = -1, E_flights_MIN = -1;
		pRUNWAY cp;

		pNODE current_airport_node = airport;
		while (current_airport_node) {
			cp = (pRUNWAY)(current_airport_node->data);
			if (cp->runway_type != type) {
				current_airport_node = current_airport_node->pNext;
				continue;
			}
			E_flights = emergency_count(cp->flight_list);
			T_flights = linksCounter(cp->flight_list);
			if (E_flights_MIN == -1) {//first runway checked
				E_flights_MIN = E_flights;
				T_flights_MIN = T_flights;
				min_ID = cp->runway_num;
				current_airport_node = current_airport_node->pNext;
				continue;
			}


			if (E_flights < E_flights_MIN) {
				E_flights_MIN = E_flights;
				T_flights_MIN = T_flights;
				min_ID = cp->runway_num;
			}

			if (E_flights == E_flights_MIN) {
				if (T_flights < T_flights_MIN) {
					min_ID = cp->runway_num;
				}
			}

			if (E_flights == E_flights_MIN) {
				if (T_flights == T_flights_MIN) {
					if ((cp->runway_num) < min_ID) {
						min_ID = cp->runway_num;
					}
				}
			}
			current_airport_node = current_airport_node->pNext;
		}
	}

	if (!emergency) { // in case the flight is not an emergency
		int T_flights, T_flights_MIN = -1;
		pRUNWAY cp;

		pNODE current_airport_node = airport;
		while (current_airport_node) {
			cp = (pRUNWAY)(current_airport_node->data);
			if (cp->runway_type != type) { //runway type doesnt match flight type
				current_airport_node = current_airport_node->pNext;
				continue;
			}
			T_flights = linksCounter(cp->flight_list);
			if (T_flights_MIN == -1) { //first runway to be checked
				T_flights_MIN = T_flights;
				min_ID = cp->runway_num;
				current_airport_node = current_airport_node->pNext;
				continue;
			}
			if (T_flights < T_flights_MIN) {
				T_flights_MIN = T_flights;
				min_ID = cp->runway_num;
			}

			if (T_flights == T_flights_MIN) {
				if ((cp->runway_num) < min_ID) {
					min_ID = cp->runway_num;
				}
			}
			current_airport_node = current_airport_node->pNext;

		}
	}

	return min_ID;
}


//* function name: addFlightToAirport
//* Description: add a flight to the airport by the given rules of assigning a new flight.
//* Parameters: f_num - flight number
//*             f_type - flight type
//*             f_dest - a pointer to the destination of the flight
//*             f_Emergency - emergency flight or regular
//* return value: succes if flight added or faliure if not
Result addFlightToAirport(int f_num, FlightType f_type, char* f_dest, BOOL f_Emergency) {

	if (!fParamCheck(f_num, f_type, f_dest, f_Emergency)) return FAILURE; // parameters check
	pNODE current_node = airport;
	pRUNWAY cp2;
	while (current_node) {	// search for a flight with identical flight number 
		cp2 = (pRUNWAY)(current_node->data);
		if (cp2 == NULL) return FAILURE;
		pNODE previous = NULL;
		if (flightSearch(cp2->flight_list, f_num, &previous)) return FAILURE;
		current_node = current_node->pNext;
	}

	int thisRunway = whichRunway_add(f_type, f_Emergency); // check which runway to add flight to
	if (thisRunway == -1) return FAILURE;
	pFLIGHT flight_ptr;
	if ((flight_ptr = creatFlight(f_num, f_type, f_dest, f_Emergency)) == NULL) return FAILURE;
	pNODE prev = NULL;
	pNODE RUNWAY_NODE = runwaySearch(airport, thisRunway, &prev);
	Result res = addFlight(RUNWAY_NODE->data, flight_ptr);
	if (!res) {
		destroyFlight(flight_ptr);

	}
	return SUCCESS;
}

//* function name: whichRunway_depart
//* Description: auxilary function for depart. determines from which runway to depart a given flight
//* Parameters: None
//* return value: the number of the runway to depart a flight from.
int whichRunway_depart() {
	int max_E = 0, max_T = 0, curr_E, curr_T, runway_num = 0;
	pNODE current_node = airport;
	pRUNWAY cp;
	if (airport->data == NULL) return FALSE;
	while (current_node) {
		cp = (pRUNWAY)(current_node->data);
		curr_E = EmergencyCounter(cp->flight_list);
		curr_T = linksCounter(cp->flight_list);
		if (runway_num == 0) { //first runway to be checked
			max_E = curr_E;
			max_T = curr_T;
			runway_num = cp->runway_num;
			current_node = current_node->pNext;
			continue;
		}

		if (curr_E > max_E) {	//if runway contains max emergency flight - update max Emergency Runway
			max_E = curr_E;
			max_T = curr_T;
			runway_num = cp->runway_num;
		}
		if (curr_E == max_E) {	//if runway E = max E, check number of all flights in runway
			if (curr_T > max_T) {
				max_T = curr_T;
				runway_num = cp->runway_num;
			}
		}
		if (curr_E == max_E) {	//if runway E = max E and T = max T, check runway number
			if (curr_T == max_T) {
				if ((cp->runway_num) < runway_num) {
					runway_num = cp->runway_num;
				}
			}
		}
		current_node = current_node->pNext;

	}
	return runway_num;
}


//* function name: departAirport
//* Description: depart a flight from the airport according to the rules given
//* Parameters: None
//* return value: succes for departing or faliure for not.
Result departAirport() {
	if (airport->data == NULL) return FAILURE;
	pNODE tmp = airport;
	int flag = 1;
	// check if all runways are empty
	while (flag && (tmp != NULL)) {
		pRUNWAY cp1 = (pRUNWAY)(tmp->data);
		if (cp1->flight_list->data != NULL) flag = 0;
		tmp = tmp->pNext;
	}
	if (flag == 1) return FAILURE;
	int runway_ID = whichRunway_depart();
	pNODE prev = NULL;
	pNODE runway_NODE = runwaySearch(airport, runway_ID, &prev);
	pRUNWAY cp = (pRUNWAY)(runway_NODE->data);
	return depart(cp);
}

//* function name: changeDest
//* Description: changes flights destination
//* Parameters: originalDest - a pointer to the destination we want to change.
//*             newDest - a pointer to the desired destination
//* return value: succes for changing or faliure for not.
Result changeDest(char* originalDest, char* newDest) {
	if (!(isDestValid(newDest))) return FAILURE; // checks if destination is valid
	if (strlen(originalDest) != 3 || strlen(newDest) != 3)
		return FAILURE;
	pNODE current = airport, toBeChangedFlight = airport;
	pRUNWAY cp;
	pFLIGHT cp2;
	Result flag = SUCCESS;
	while (current) { // searching all runways
		cp = (pRUNWAY)(current->data);
		if (cp->flight_list->data == NULL) {
			current = current->pNext;
			continue;
		}
		toBeChangedFlight = current;
		while (toBeChangedFlight != NULL) {
			toBeChangedFlight = destSearch(cp->flight_list, originalDest);
			if (toBeChangedFlight != NULL) { // searching all flights
				cp2 = (pFLIGHT)(toBeChangedFlight->data);
				strcpy(cp2->f_dest, newDest); // changing destination
				flag = SUCCESS;
			}
		}
		current = current->pNext;
	}
	return flag;
}

//* function name: delay_RUNWAY
//* Description: delays flights in input runway by the given rules
//* Parameters: RUNWAY_NODE - pointer to node containing runway
//*				delayed_dest - a pointer to the destination of flights we want to delay
//* return value: success for delaying or faliure for not.
Result delay_RUNWAY(pNODE RUNWAY_NODE, char* delayed_dest) { //delay per runway
	pRUNWAY RUNWAY = (pRUNWAY)(RUNWAY_NODE->data);
	if (RUNWAY == NULL) return SUCCESS;
	pNODE f_list = (pNODE)(RUNWAY->flight_list);
	if (f_list->data == NULL) return SUCCESS;
	pNODE curr = f_list;
	int R_num, E_num;
	E_num = EmergencyCounter(f_list); //holds number of emergency flights
	R_num = (linksCounter(f_list) - E_num); //holds number of total flights

	int i = 0, j, k = 0;
	//pFLIGHT curr_flight = (pFLIGHT)(f_list->data);
	if (E_num != 0) {//delay for emergency flights
		while (i < (E_num)) {
			pFLIGHT curr_flight = (pFLIGHT)(curr->data);
			if (!strcmp(curr_flight->f_dest, delayed_dest)) {
				pFLIGHT tmp = curr_flight;
				pNODE curr_E = curr, next_E = curr_E->pNext;
				for (j = 0; j < (E_num - i + k -1); j++) {
					curr_E->data = next_E->data;
					curr_E = curr_E->pNext;
					next_E = curr_E->pNext;
				}
				/*if ((E_num - 1 - i) == 0) {//last flight to be checked
					for (j = 0; j < k; j++) {
						curr_E->data = next_E->data;
						curr_E = curr_E->pNext;
						next_E = curr_E->pNext;
					}
				}*/
				curr_E->data = tmp;
				k++;
			}

			else {
				curr = curr->pNext;
			}
			i++;
			}
		}

	pFLIGHT f_RoE = (pFLIGHT)(f_list->data);
	curr = f_list;
	while (f_RoE->f_Emergency) {
		curr = curr->pNext;
		if (curr == NULL) break;
		f_RoE = curr->data;
	}

	if (R_num != 0) {//delay for regular flights
		i = 0;
		k = 0;
		while (i < R_num) {
			pFLIGHT curr_flight = (pFLIGHT)(curr->data);
			if (!strcmp(curr_flight->f_dest, delayed_dest)) {
				pFLIGHT tmp = curr_flight;
				pNODE curr_R = curr, next_R = curr_R->pNext;
				for (j = 0; j < (R_num - i + k -1); j++) {
					curr_R->data = next_R->data;
					curr_R = curr_R->pNext;
					next_R = curr_R->pNext;
				}
				curr_R->data = tmp;
				//printf("TESTING: %d\n", );
				k++;
			}
			else {
				curr = curr->pNext;
			}
			i++;
			}
		}
	return SUCCESS;
}



//* function name: delay
//* Description: delays flights by the given rules
//* Parameters: delayed_dest - a pointer to the destination of flights we want to delay.
//* return value: success for delaying or faliure for not.
Result delay(char* delayed_dest) {
	if (!isDestValid(delayed_dest)) return FAILURE;
	pNODE AP_current_node = airport;
	while (AP_current_node) {
		if (!delay_RUNWAY(AP_current_node, delayed_dest)) return FAILURE;
		AP_current_node = AP_current_node->pNext;
	}
	return SUCCESS;
}

//* function name: printAirport
//* Description: prints all runways and waiting flights in the airport
//* Parameters: None
//* return value: None
void printAirport() {
	pNODE next = airport;
	pRUNWAY cp;

	printf("Airport status:\n");
	while (next != NULL) {
		if (next->data == NULL) {
			printf("\n");
			return;
		}
		cp = (pRUNWAY)(next->data);
		printRunway(cp);
		next = next->pNext;
	}
	printf("\n");
	return;
}

//* function name: destroyAirport
//* Description: deletes airport, runways and flights.
//* Parameters: None
//* return value: None
void destroyAirport() {
	pNODE current = airport, next;
	pRUNWAY cp;
	while (current) {
		next = current->pNext;
		cp = (pRUNWAY)(current->data);
		destroyRunway(cp);
		free(current);
		current = next;
	}
//	free(airport);
	return;
}
