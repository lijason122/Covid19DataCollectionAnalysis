/*
 * File name: household.h
 * Name: Jason Li
 * Start coding date: July 7th, 2021
 * Last revision date: July 26th, 2021
 */

#ifndef JASONLIASSIGN3_HOUSEHOLD_H
#define JASONLIASSIGN3_HOUSEHOLD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#define SIZE 100

typedef struct {
    char region[20];
    char town[20];
    char race[20];
    unsigned int familySize;
    unsigned int covidTested;
    unsigned int covidPositive;
}Household; // end struct Household definition

typedef struct node { // Set up the self-referential structure
    Household info;
    struct node* next;
}Node, *NodePtr;

typedef struct { // This is for ordering the ranking for each category from the Household
    char type[20];
    int value;
}Category; // end struct Category definition

void printList(Node *);

void printRecords(NodePtr, int);

void addNode(NodePtr *, Household);

NodePtr makeNode(Household);

Household makeHousehold(int, int, int, char [], char [], char []);

void numOfMembersValidation(int *, int *, int *);

void numOfTestedPositiveValidation(int *);

void generateRandomRecords();

void readRecordsFromClients(NodePtr *);

void writeRecordsToFile(NodePtr, char *);

void readRecordsFromFile(NodePtr *, char *);

char* fileNameValidation();

int menuValidation(int);

int menu2Validation(int);

void printSpecificRecords(NodePtr, int, int, int);

void printRegionTownRanking(NodePtr);

void deleteNodesWithOptions(NodePtr *, int, int, int);

#endif //JASONLIASSIGN3_HOUSEHOLD_H
