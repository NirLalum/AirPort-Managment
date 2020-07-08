
#ifndef RUNWAY_H_
#define RUNWAY_H_

#include "flight.h"

// struct for the linked list of flights in each runway

typedef struct _Node {
	void* data; // a pointer (to a flight/runway struct)
	struct _Node* pNext; // pointer to the next node
} NODE, * pNODE;

typedef struct _runway {
	int runway_num;
	FlightType runway_type;
	pNODE flight_list;  // flight is a pointer to a linked list. need to make sure it points the head of the list
} RUNWAY, * pRUNWAY;



//***AUX FUNCTIONS***//

//* function name: createEmptyList
//* Description: create an emty node for the flight list
//* Parameters: None
//* return value: a pointer to the first flight node
pNODE createEmptyList();

//* function name: addNode
//* Description: adds node to linked list into given pointer (address) inside the list
//* Parameters: new_node_adress -  a pointer to the new node 
//*             p_Next_of_prior_NODE - pointer to a pointer to the prior node pNext
//* return value: succes if node added and faliure if not
Result addNode(pNODE new_node_address, pNODE* p_Next_of_prior_NODE);

//* function name: removeNode
//* Description: removes node from linked list
//* Parameters: prev -  a pointer to the prior node of the removed one 
//* return value: succes if node removed and faliure if not
Result removeNode(pNODE prev);

//* function name: flightSearch
//* Description: searchs a flight in flight list of a runway
//* Parameters: head - a pointer to the head of the list
//*				num - flight number of the wanted fligt
//*				pofPrevious - pointer to a pointer to the previous node
//* return value: a pointer to node with the wanted flight
pNODE flightSearch(pNODE head, int num, pNODE* previous);

//* function name: destSearch
//* Description: searchs a flight with a requierd destination
//* Parameters: head - a pointer to the head of the list
//*				dest - a pointer to the destination string
//* return value: a pointer to a node with the a flight with dest
pNODE destSearch(pNODE head, char* dest);

//* function name: runwaySearch
//* Description: searchs a runway
//* Parameters: head - a pointer to the head of the runways linked list
//*				num - a runway number
//* return value: a pointer to a node with the a flight with dest
pNODE runwaySearch(pNODE head, int num, pNODE* pOfPrevious);


//* function name: emergency_count
//* Description: counts emergency flights in a runway
//* Parameters: head - a pointer to the head of the flight list of a runway
//* return value: number of energency flights
int emergency_count(pNODE head);

//* function name: linksCounter
//* Description: counts number of nodes in a given linked list
//* Parameters: head - a pointer to the head of the linked list
//* return value: number of nodes in a linked list
//counts number of nodes in linked list
int linksCounter(pNODE head);

//* function name: EmergencyCounter
//* Description: counts emergency flights in a runway (auxilary function of getEmergencyNum)
//* Parameters: head - a pointer to the head of the flight list of a runway
//* return value: number of energency flights
int EmergencyCounter(pNODE head);

//* function name: listDestroyer
//* Description: frees the memory of the of the flight linked list in a destroyed runway.
//* Parameters: a ponter to the head of the flight linked list
//* return value: None
void listDestroyer(pNODE head);




//***RUNWAY FUNCTIONS***//

//* function name: createRunway
//* Description: creates a new runway
//* Parameters: num - the new runway number
//*				type - the runway type
//* return value: a pointer to the new runway
pRUNWAY createRunway(int num, FlightType type);

//* function name: destroyRunway
//* Description: free memory of a runway
//* Parameters: runwayToDestroy - a pointer to the runway that will be removed
//* return value: None
void destroyRunway(pRUNWAY);

//* function name: isFlightExists
//* Description: determines if a flight is on the wait list
//* Parameters: runway - a pointer to the runway where the flight will be searched
//*             flight_num - the number of the searched flight number.
//* return value: TRUE if the flight exist and FALSE if not
BOOL isFlightExists(pRUNWAY, int);

//* function name: getFlightNum
//* Description: counts the number of flight in a wating flight list
//* Parameters: runway - a pointer to the runway where the flights will be count
//* return value: number of flights in a wating list
int getFlightNum(pRUNWAY);

//* function name: getEmergencyNum
//* Description: counts emergency flights in a runway
//* Parameters: runway - a pointer to a runway where the emergency flights will be counted
//* return value: number of energency flights in the runway
int getEmergecyNum(pRUNWAY);

//* function name: addFlight
//* Description: adds a new flight to a runway by the given rules
//* Parameters: runway - a pointer to a runway where the emergency flights will be added
//*                flight_ptr - a pointer to the added flight
//* return value: succes if flight was added and flaiure if not
Result addFlight(pRUNWAY runway, pFLIGHT flight);

//* function name: removeFlight
//* Description: removes a flight from a runway
//* Parameters: runway - a pointer to a runway where a flight will be removed
//*                f_num - the number of the flight that will be removed
//* return value: succes if flight was removed and flaiure if not
Result removeFlight(pRUNWAY, int);

//* function name: depart
//* Description: removes the first flight in the runway
//* Parameters: runway - a pointer to a runway where a flight will be depart
//* return value: succes if flight was departed and flaiure if not
Result depart(pRUNWAY runway);

//* function name: printRunway
//* Description: prints the data of the runway and the flight wating in it
//* Parameters: runway - a pointer to a runway where a flight will be removed
//* return value: None
void printRunway(pRUNWAY);

#endif






