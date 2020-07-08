#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "runway.h"


//* function name: createEmptyList
//* Description: create an emty node for the flight list
//* Parameters: None
//* return value: a pointer to the first flight node
pNODE createEmptyList() {
	pNODE head; // head is a ponter to an empty node. the haed of the linked list for start
	head = (pNODE)malloc(sizeof(NODE));
	if (head == NULL) {
		return NULL;
	}
	head->pNext = NULL;
	head->data = NULL;
	return head;
}

//* function name: listDestroyer
//* Description: frees the memory of the of the flight linked list in a destroyed runway.
//* Parameters: a ponter to the head of the flight linked list
//* return value: None
void listDestroyer(pNODE head) {
	pNODE next, current = head;
	if (head == NULL) return;
	while (current) {
		next = current->pNext;
		destroyFlight(current->data);
		free(current);
		current = next;
	}
}

//* function name: addNode
//* Description: adds node to linked list into given pointer (address) inside the list
//* Parameters: new_node_adress -  a pointer to the new node 
//*             p_Next_of_prior_NODE - pointer to a pointer to the prior node pNext
//* return value: succes if node added and faliure if not
Result addNode(pNODE new_node_address, pNODE* p_Next_of_prior_NODE) { //new_node_address is the address of the node being added, p_next is the location new_node is being added
	if (p_Next_of_prior_NODE == NULL) {
		*p_Next_of_prior_NODE = new_node_address;
		return SUCCESS;
	}
	pNODE tmp = *p_Next_of_prior_NODE;
	new_node_address->pNext = tmp;
	*p_Next_of_prior_NODE = new_node_address;
	return SUCCESS;
}


//* function name: removeNode
//* Description: removes node from linked list
//* Parameters: prev -  a pointer to the prior node of the removed one 
//* return value: succes if node removed and faliure if not
Result removeNode(pNODE prev) {
	if (prev == NULL) return FAILURE;
	pNODE tmp = prev->pNext; //backup for node that we want to remove
	prev->pNext = tmp->pNext;
	free(tmp);
	return SUCCESS;
}


//* function name: flightSearch
//* Description: searchs a flight in flight list of a runway
//* Parameters: head - a pointer to the head of the list
//*				num - flight number of the wanted fligt
//*				pofPrevious - pointer to a pointer to the previous node
//* return value: a pointer to node with the wanted flight
pNODE flightSearch(pNODE head, int num, pNODE* pOfPrevious) {
	pNODE current = head;
	// while head is not NULL continue
	while (current) {
		if (current->data == NULL) return NULL;
		pFLIGHT cp = (pFLIGHT)(current->data);
		if (cp->f_Num == num) {
			return (current); // return the node which contains the given flight
		}
		*pOfPrevious = current;
		current = current->pNext;
	}
	return NULL; // list is empty or flight number was not found
}

//* function name: destSearch
//* Description: searchs a flight with a requierd destination
//* Parameters: head - a pointer to the head of the list
//*				dest - a pointer to the destination string
//* return value: a pointer to a node with the a flight with dest
pNODE destSearch(pNODE head, char* dest) {
	pNODE current, next = head;
	// while head is not NULL continue
	while (next) {
		current = next;
		next = next->pNext;
		pFLIGHT cp = (pFLIGHT)(current->data);
		if (!strcmp(cp->f_dest, dest))
			return (current); // return the node which contains the given flight
	}
	return NULL; // list is empty or flight number was not found
}

//* function name: runwaySearch
//* Description: searchs a runway
//* Parameters: head - a pointer to the head of the runways linked list
//*				num - a runway number
//* return value: a pointer to a node with the a flight with dest
pNODE runwaySearch(pNODE head, int num, pNODE* pOfPrevious) {
	pNODE prev = NULL, current = head;
	// while head is not NULL continue
	if (current->data == NULL) return NULL; //no runways in airport
	while (current) {
		pRUNWAY cp = (pRUNWAY)(current->data);
		if (cp->runway_num == num) {
			*pOfPrevious = prev;
			return current; // there's a runway with this number already
		}
		prev = current;
		current = current->pNext;

	}
	return NULL; // no runway with this number
}


//* function name: emergency_count
//* Description: counts emergency flights in a runway
//* Parameters: head - a pointer to the head of the flight list of a runway
//* return value: number of energency flights
int emergency_count(pNODE head) {
	pNODE current = head;
	pFLIGHT cp;
	cp = (pFLIGHT)(head->data);
	int count = 0;
	if ((current->data) == NULL) return count;
	while (current) {
		cp = (pFLIGHT)(current->data);
		if (cp->f_Emergency == TRUE) count++;
		current = current->pNext;
	}
	return count;
}

//* function name: linksCounter
//* Description: counts number of nodes in a given linked list
//* Parameters: head - a pointer to the head of the linked list
//* return value: number of nodes in a linked list
//counts number of nodes in linked list
int linksCounter(pNODE head) {
	pNODE current = head;
	int count = 0;
	if ((current->data) == NULL) return count;
	while (current) {
		current = current->pNext;
		count++;
	}
	return count;
}

//* function name: EmergencyCounter
//* Description: counts emergency flights in a runway (auxilary function of getEmergencyNum)
//* Parameters: head - a pointer to the head of the flight list of a runway
//* return value: number of energency flights
int EmergencyCounter(pNODE head) {
	pNODE current, next = head;
	int count = 0;
	while (next) {
		current = next;
		next = next->pNext;
		pFLIGHT cp = (pFLIGHT)(current->data);
		if (cp == NULL) return count;
		if (cp->f_Emergency) {
			count++;
		}
	}
	return count;
}

//* function name: printlist
//* Description: auxilary fuction for printRunway
//* Parameters: head - a pointer to the head of the linked list
//* return value: None
static void printList(pNODE head) {
	if (head->data == NULL) return;
	pNODE current = head;
	while (current) {
		printFlight(current->data);
		current = current->pNext;
	}
}


//* function name: createRunway
//* Description: creates a new runway
//* Parameters: num - the new runway number
//*				type - the runway type
//* return value: a pointer to the new runway
pRUNWAY createRunway(int num, FlightType type) {
	pRUNWAY newRunway;
	if (num > MAX_ID || num < 1) {
		return NULL;
	}
	newRunway = (pRUNWAY)malloc(sizeof(RUNWAY)); //malloc for RUNWAY struct
	if (newRunway == NULL) {
		return NULL;
	}
	newRunway->runway_num = num;
	newRunway->runway_type = type;
	newRunway->flight_list = createEmptyList(); //CEL has malloc for flight list
	return newRunway;
}

//* function name: destroyRunway
//* Description: free memory of a runway
//* Parameters: runwayToDestroy - a pointer to the runway that will be removed
//* return value: None
void destroyRunway(pRUNWAY runwayToDestroy) {
	if (runwayToDestroy == NULL) return;
	listDestroyer(runwayToDestroy->flight_list);
	free(runwayToDestroy);
}

//* function name: isFlightExists
//* Description: determines if a flight is on the wait list
//* Parameters: runway - a pointer to the runway where the flight will be searched
//*             flight_num - the number of the searched flight number.
//* return value: TRUE if the flight exist and FALSE if not
BOOL isFlightExists(pRUNWAY runway, int flight_num) {
	if (runway == NULL || flight_num < 1 || flight_num > MAX_ID) return FALSE;
	pNODE previous = NULL;
	if (flightSearch(runway->flight_list, flight_num, &previous)) return TRUE;
	else return FALSE;
}

//* function name: getFlightNum
//* Description: counts the number of flight in a wating flight list
//* Parameters: runway - a pointer to the runway where the flights will be count
//* return value: number of flights in a wating list
int getFlightNum(pRUNWAY runway) {
	pNODE listOfFlights = runway->flight_list;
	int flight_amount = 0;
	if (runway == NULL) {
		return -1;
	}
	return (flight_amount = linksCounter(listOfFlights));
}

//* function name: getEmergencyNum
//* Description: counts emergency flights in a runway
//* Parameters: runway - a pointer to a runway where the emergency flights will be counted
//* return value: number of energency flights in the runway
int getEmergencyNum(pRUNWAY runway) {
	pNODE listOfFlights = runway->flight_list;
	listOfFlights = runway->flight_list;
	int flight_amount = 0;
	if (runway == NULL) {
		return -1;
	}
	return (flight_amount = EmergencyCounter(listOfFlights)); // sending the head of the wating list to the counter.
}

//* function name: addFlight
//* Description: adds a new flight to a runway by the given rules
//* Parameters: runway - a pointer to a runway where the emergency flights will be added
//*                flight_ptr - a pointer to the added flight
//* return value: succes if flight was added and flaiure if not
Result addFlight(pRUNWAY runway, pFLIGHT flight_ptr) {
	pNODE previous = NULL;
	pNODE prev = NULL;
	pFLIGHT cp = NULL;
	// check if a flight with the same flight number allready exist
	if ((flightSearch(runway->flight_list, flight_ptr->f_Num, &previous)) || (flight_ptr->f_Type != runway->runway_type) || (runway == NULL))
		return FAILURE;
	pNODE curr_node = runway->flight_list;
	if (curr_node->data == NULL) {
		if (flight_ptr == NULL) return FAILURE;
		curr_node->data = flight_ptr;
		return SUCCESS;
	}
	// if the flght is a regular flight case
	if (!(flight_ptr->f_Emergency)) {
		while (curr_node->pNext != NULL) {
			curr_node = curr_node->pNext;
		}
	}
	// if the flght is an emergency flight case
	if (flight_ptr->f_Emergency) {
		prev = curr_node;
		cp = (pFLIGHT)(curr_node->data);
		if (!(cp->f_Emergency)) { //if first flight is R
			pNODE newFlightNode = createEmptyList();
			newFlightNode->data = flight_ptr;
			newFlightNode->pNext = curr_node;
			runway->flight_list = newFlightNode;
			return SUCCESS;
		}
		// if there are no regular flights
		while (cp->f_Emergency) {
			if (curr_node->pNext == NULL) break;
			prev = curr_node;
			curr_node = curr_node->pNext;
			cp = (pFLIGHT)(curr_node->data);
		}
	}
	if (prev != NULL && !(cp->f_Emergency)) curr_node = prev;
	pNODE newFlightNode = createEmptyList();
	newFlightNode->data = flight_ptr;
	return addNode(newFlightNode, &curr_node->pNext);
}

//* function name: removeFlight
//* Description: removes a flight from a runway
//* Parameters: runway - a pointer to a runway where a flight will be removed
//*                f_num - the number of the flight that will be removed
//* return value: succes if flight was removed and flaiure if not
Result removeFlight(pRUNWAY runway, int f_num) {
	pNODE address;
	pNODE previous = NULL;
	address = (flightSearch((runway->flight_list), f_num, &previous));
	if (address) return FAILURE;
	return removeNode(address);
}

//* function name: depart
//* Description: removes the first flight in the runway
//* Parameters: runway - a pointer to a runway where a flight will be depart
//* return value: succes if flight was departed and flaiure if not
Result depart(pRUNWAY runway) {
	if (runway == NULL) return FAILURE; //the test if the flight list is empty is made in removeNode
	pNODE tmp = (pNODE)(runway->flight_list); //backup for NODE that is being removed
	if (runway->flight_list->pNext == NULL) { //meaning only flight in this runway
		pFLIGHT cp2 = (pFLIGHT)(tmp->data); //accesing pointer to flight
		destroyFlight(cp2); //deleting flight
		runway->flight_list->data = NULL;
		return SUCCESS;
	}
	runway->flight_list = runway->flight_list->pNext; //moving one NODE forward
	pFLIGHT cp2 = (pFLIGHT)(tmp->data); //accesing pointer to flight
	destroyFlight(cp2); //deleting flight
	free(tmp); //deleting NODE
	return SUCCESS;
}

//* function name: printRunway
//* Description: prints the data of the runway and the flight wating in it
//* Parameters: runway - a pointer to a runway where a flight will be removed
//* return value: None
void printRunway(pRUNWAY runway) {
	int flight_num = 0;
	printf("Runway %d ", runway->runway_num);
	if (runway->runway_type) { printf("international\n"); }
	else printf("domestic\n");
	if (runway->flight_list->data == NULL) flight_num = 0;
	else flight_num = linksCounter(runway->flight_list);
	printf("%d flights are waiting:\n", flight_num);
	printList(runway->flight_list);
	return;
}
