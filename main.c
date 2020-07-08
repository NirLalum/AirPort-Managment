#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "airport.h"


#define MAX_LINE_SIZE 256 
#define COMMAND_NUM 8

//* function name: paramAmout
//* Description: checks if the number of parameters is correct.
//* Parameters: pAmount - the required number of parameters
//*				arr[] - a pointer tothe parameters array
//* return value: true or false.

bool paramAmount(int pAmount, char* arr[]) {
	int i = 0;
	while ((arr[i] != NULL) && i < 5) {
		if (i == 4) {
			i++;
			break;
		}
		i++;
	}
	if (i >= pAmount) return true;
	else return false;
}

//* function name: commandID
//* Description: interpreting which command the user used
//* Parameters: input - a pointer to a parameter given by user
//* return value: the "ID" of the command

int commandID(char* input) {
	int i = 0;
	char* C1 = "Insert";
	char* C2 = "Remove";
	char* C3 = "Add";
	char* C4 = "Depart";
	char* C5 = "Change";
	char* C6 = "Delay";
	char* C7 = "Print";
	char* C8 = "Exit";
	char* commands[8] = { C1, C2 , C3 , C4 , C5 , C6, C7, C8};
	for (i = 0; i < COMMAND_NUM; i++) {
		if (!strcmp(input, (commands[i]))) {
			return i;
		}
	}
	return i++;
}
//* function name: type_decoder
//* Description: determines which type of flight/runway (international or domestic) is given by the user
//* Parameters: param - a pointer to the parameter given by user
//* return value: internaional or domestic

FlightType type_decoder(char* param) {
	char* D = "D";
	if (!strcmp(D, param)) return DOMESTIC;
	return INTERNATIONAL;
}

//* function name: emergency_decoder
//* Description: determines which type of flight/runway (emergency or regular) is given by the user
//* Parameters: param - a pointer to the parameter given by user
//* return value: 0 or 1 for regular or emergency

BOOL emergency_decoder(char* param) {
	char* R = "R";
	if (!strcmp(R, param)) return FALSE;
	return TRUE;
}

//* function name: type_bad_input
//* Description: checks if the input for flight type is valid
//* Parameters: param - a pointer to the parameter given by user
//* return value: true of false

bool type_bad_input(char param) {
	if ((param != 'D') && (param != 'I')) return true;
	return false;
}

//* function name: emergency_bad_input
//* Description: checks if the input for emergency or regular is valid
//* Parameters: param - a pointer to the parameter given by user
//* return value: true of false
bool emergency_bad_input(char param) {
	if ((param != 'E') && (param != 'R')) return true;
	return false;
}

//* function name: num_bad_input
//* Description: makes the flight number char input a int and test if its valid
//* Parameters: c_num - a pointer to the flight number
//* return value: the flight number as a int type or 0 if the input is nut a number.
int num_bad_input(char* c_num) {
	return (!atoi(c_num));
}

//* main function
//* gets the user input and calls to relavent function according to the input.
int main() {
	pNODE AIRPORT = createEmptyList();
	airport = AIRPORT;
	char inputLine[MAX_LINE_SIZE];	//array for storing input line from standard input which will later be analyzed
	char* Word;
	char* delimiters = " ";		//space is the only delimeter
	char* params[5] = { NULL, NULL, NULL, NULL, NULL };

	int i = 1;

	while (fgets(inputLine, MAX_LINE_SIZE, stdin)) {
		Word = strtok(inputLine, delimiters);
		//char* newline = strchr(Word, '\n');
		char* newline;
		char* backup = Word;
		params[0] = Word; //word will contain name of command
		i = 1;
		while ((Word != NULL) && (i < 5)) {	//params will contain name of command and the rest of the parmeters for the command
			backup = Word;
			Word = strtok(NULL, delimiters);
			if (!Word) break;
			params[i] = Word;
			i++;
		}
		if (i == 5) newline = strchr(Word, '\n');
		else newline = strchr(backup, '\n');
		if (newline && *newline == '\n') *newline = '\0';
		int ID = commandID(params[0]);

		//running commad according to command ID:
		//insert runway
		if (ID == 0) {
			if (!paramAmount(3, params)) fprintf(stderr, "Insert failed: not enough parameters.\n");
			else if ((num_bad_input(params[1])) || (type_bad_input(*params[2])) || (!addRunway(atoi(params[1]), type_decoder(params[2])))) fprintf(stderr, "Insert execution failed.\n");
		}

		//remove runway
		if (ID == 1) {
			if (!paramAmount(2, params)) fprintf(stderr, "Remove failed: not enough parameters.\n");
			else if ((num_bad_input(params[1])) || (!removeRunway(atoi(params[1])))) fprintf(stderr, "Remove execution failed.\n");
		}

		//add flight
		if (ID == 2) {
			if (!paramAmount(5, params)) fprintf(stderr, "Add failed: not enough parameters.\n");
			else if ((num_bad_input(params[1])) || (type_bad_input(*params[2])) || (emergency_bad_input(*params[4])) || (!addFlightToAirport(atoi(params[1]), type_decoder(params[2]), params[3], emergency_decoder(params[4]))))fprintf(stderr, "Add execution failed.\n");
		}

		//depart
		if (ID == 3) {
			if (!departAirport()) fprintf(stderr, "Depart execution failed.\n");
		}

		//change destination
		if (ID == 4) {
			if (!paramAmount(3, params)) fprintf(stderr, "Change Destination failed: not enough parameters.\n");
			else if (!changeDest(params[1], params[2])) fprintf(stderr, "Change Destination execution failed.\n");
		}

		//delay
		if (ID == 5) {
			if (!paramAmount(2, params)) fprintf(stderr, "Delay failed: not enough parameters.\n");
			else if (!delay(params[1])) fprintf(stderr, "Delay execution failed.\n");
		}

		//print airport
		if (ID == 6) {
			printAirport();
		}

		//destroy airport
		if (ID == 7) {
			destroyAirport();
			return 0;
		}

		//command not found
		if (ID == 8) {
			fprintf(stderr, "Command not found.\n");
		}
		int j;
		for (j = 0; j < 5; j++) {
			params[j] = NULL;
		}

	}
	destroyAirport();
  return 0;
}

