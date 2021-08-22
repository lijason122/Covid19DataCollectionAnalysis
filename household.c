/*
 * File name: household.c
 * Name: Jason Li
 * Start coding date: July 7th, 2021
 * Last revision date: July 26th, 2021
 */

#include "household.h"

/**
 * printList prints data of a linked list passed to the function.
 * @param ptr name of the linked list of Node pointer
 */
void printList(Node* ptr) {
    if(ptr == NULL){
        puts("Empty list");
        return;
    }

    int ctr = 0;
    puts("S.no\t Size\t Total Tested\t Total tested positive\t\t\tRace\t Region\t\t Town");
    while(ptr != NULL) {
        ctr++;
        printRecords(ptr, ctr);
        ptr = ptr->next; }
    puts("");
}

/**
 * printRecords prints data of a linked list passed to the function.
 * @param client name of the linked list of Node pointer
 * @param number the index of the linked list
 */
void printRecords(NodePtr client, int number)
{
    printf("%4d %8d %15d %24d %21s %10s %13s\n", number, client->info.familySize, client->info.covidTested, client->info.covidPositive, client->info.race, client->info.region, client->info.town);
}

/**
 * addNode adds a record to the linked list passed to the function.
 * @param clientPtr name of the linked list of NodePtr pointer
 * @param num the record from the Household
 */
void addNode(NodePtr* clientPtr, Household num){
    NodePtr ptr = malloc(sizeof(*ptr));
    ptr->info.familySize = num.familySize;
    ptr->info.covidTested = num.covidTested;
    ptr->info.covidPositive = num.covidPositive;
    strcpy(ptr->info.race, num.race);
    strcpy(ptr->info.region, num.region);
    strcpy(ptr->info.town, num.town);
    ptr->next = *clientPtr;
    *clientPtr = ptr;
}

/**
 * makeNode creates a pointer to a node on the heap and sets top's data to the record from the Household
 * @param num the record from the Household
 * @return a pointer to a node on the heap
 */
NodePtr makeNode(Household num){
    NodePtr ptr = malloc(sizeof(*ptr));
    if(ptr == NULL){
        puts("Memory allocation failure");
        return NULL;
    }

    ptr->info.familySize = num.familySize;
    ptr->info.covidTested = num.covidTested;
    ptr->info.covidPositive = num.covidPositive;
    strcpy(ptr->info.race, num.race);
    strcpy(ptr->info.region, num.region);
    strcpy(ptr->info.town, num.town);
    ptr->next = NULL;
    return ptr;
}

/**
 * makeHousehold creates a structure of Household that has data stored inside
 * @params data from the Household
 * @return the structure of Household that has data stored inside
 */
Household makeHousehold(int familySize, int covidTested, int covidPositive, char race[], char region[], char town[]){
    Household temp;
    strcpy(temp.region, region);
    strcpy(temp.town, town);
    strcpy(temp.race, race);
    temp.familySize = familySize;
    temp.covidTested = covidTested;
    temp.covidPositive = covidPositive;
    return temp;
}

/**
 * deleteNodesWithOptions removes records from the linked list passed to the function according to user's options.
 * @param top name of the linked list of NodePtr pointer
 * @params options from the user
 */
void deleteNodesWithOptions(NodePtr* top, int regionOption, int townOption, int raceOption) {

    char regions[3][20] = {"Durham", "Peel", "York"};
    char towns[3][2][20] = {{"Whitby", "Oshawa"}, {"Brampton", "Mississauga"}, {"Maple", "Vaughan"}};
    char race[5][20] = {"Indigenous", "Caucasian", "African_American", "Asian", "Other"};

    NodePtr prev = NULL;
    NodePtr current = *top;
    if (*top == NULL) {
        puts("No matching records found");
        return;
    }
    int ctr = 0;
    while (*top != NULL && strcmp((*top)->info.region, regions[regionOption]) == 0 &&
        strcmp((*top)->info.town, towns[regionOption][townOption]) == 0 &&
        strcmp((*top)->info.race, race[raceOption]) == 0) {
        current = *top;
        *top = (*top)->next;
        free(current);
        ctr++;
    }
    prev = current = *top;
    // if the top does not hold the key
    while (current != NULL) {
        while (current != NULL && (strcmp(current->info.region, regions[regionOption]) != 0 ||
            strcmp(current->info.town, towns[regionOption][townOption]) != 0 ||
            strcmp(current->info.race, race[raceOption]) != 0)) {
            prev = current;
            current = current->next;
        }
        if (current == NULL) { // if the while loop terminated because it hit the end of the list
            if (ctr == 0) {
                puts("No matching records found");
            }
            else {
                printf("%d matching records deleted\n", ctr);
            }
            return;
        }
        // the loop terminated because the key was found
        prev->next = current->next;
        free(current);
        current = prev->next;
        ctr++;
    } // outer while loop ends
    if (ctr == 0) {
        puts("No matching records found");
    }
    else {
        printf("%d matching records deleted\n", ctr);
    }
}

/**
 * Validate user's file name with extension
 * @return user's file name with extension
 */
char* fileNameValidation()
{
    int n = 0;
    static char fileName[40];
    char temp[40];
    while (1)
    {
        fgets(temp, sizeof(temp), stdin);
        n = sscanf(temp, "%s", fileName);
        char *extension = strrchr(fileName, '.');

        if (extension == NULL) {
            printf("Invalid file name with extension: %s . Try again\n", fileName);
            continue;
        }
        if(strcmp(extension, ".txt") == 0 && n == 1) return fileName;
        else {
            printf("Invalid file name with extension: %s . Try again\n", fileName);
            continue;
        }
    }
}

/**
 * Prompt the user for three integers, validate the number of members, and display it to the user if it is not valid
 * The three positive integers must be in descending order respectively
 * If valid, update the three integers
 * @param familySize is the number of people in the household and it must be an integer greater than 0
 * @param covidTested or covidPositive is the number of household members tested (or tested positive) for Covid-19
 * and it must be an integer greater than or equal to 0
 */
void numOfMembersValidation(int *familySize, int *covidTested, int *covidPositive)
{
    int n = 0;
    char temp[40];
    int overAgeFifty;
    int underAgeFifty;

    while (1)
    {
        puts("Please enter");
        puts("1-total people in the household,");
        puts("2-people over the age of 50,");
        puts("3-people under 50 with chronic diseases separated by space/tab and make sure all of these are valid integers");
        fgets(temp, sizeof(temp), stdin);
        n = sscanf(temp, "%d%d%d", familySize, &overAgeFifty, &underAgeFifty);
        if(*familySize > 0 && *familySize < 21 && *familySize >= (overAgeFifty+underAgeFifty) && *familySize >= overAgeFifty && *familySize >= underAgeFifty && overAgeFifty >= 0 && underAgeFifty >= 0 && n == 3);
        else if(*familySize <= 0 || *familySize >= 21)
        {
            puts("Total people in the household must be an integer greater than 0 and less than 21, try again");
            continue;
        }
        else if(*familySize < (overAgeFifty+underAgeFifty)) {
            puts("Total people in the household can't be less than the people over 50 or people under 50 with chronic diseases");
            puts(" or even their sum! Kindly re-enter the data");
            continue;
        }
        else
        {
            puts("Make sure you enter three positive integers and total people must be greater than or equal to the other two integers");
            continue;
        }

        int bool = 1;
        while (bool)
        {
            puts("Enter total number of people in the household who were tested for Covid and those who were tested positive separated by space or tab.");
            fgets(temp, sizeof(temp), stdin);
            n = sscanf(temp, "%d%d", covidTested, covidPositive);
            if(*familySize >= *covidTested && *covidTested >= *covidPositive && *covidTested >= 0 && *covidPositive >= 0 && n == 2) return;
            else if(*familySize < *covidTested || *covidTested < *covidPositive)
            {
                puts("Total people in the household can't be less than the total members tested for Covid.");
                puts("Similarly total tested can't be less than total tested positive.");
                puts("Enter 'Y' if you want to re-enter/correct household numbers or");
                puts(" 'F' if you want to re-enter only Covid test figures.");
                while(1){
                    char response;
                    fgets(temp, sizeof(temp), stdin);
                    n = sscanf(temp, " %c", &response);
                    if (response == 'y' || response == 'Y') {
                        bool = 0;
                        break;
                    }
                    else if (response == 'f' || response == 'F') {
                        break;
                    }
                    else if (n <= 1){
                        puts("Wrong input, please");
                        puts("Enter 'Y' if you want to re-enter/correct household numbers or");
                        puts(" 'F' if you want to re-enter only Covid test figures.");
                        continue;
                    }
                }

            }
            else
            {
                puts("Make sure you enter two positive integers in descending order, try again");
                continue;
            }
        }
    }
}

/**
 * Validate the number of tested positive from the user
 * @param testedPositive is the number of household members tested positive for Covid-19
 * and it must be an integer greater than or equal to 0
 */
void numOfTestedPositiveValidation(int *testedPositive)
{
    int n = 0;
    char temp[40];
    while (1)
    {
        fgets(temp, sizeof(temp), stdin);
        n = sscanf(temp, "%d", testedPositive);
        if(*testedPositive >= 0 && n == 1) return;
        else if(*testedPositive < 0)
        {
            puts("The number of tested positive must be an integer greater than or equal to 0, try again");
            continue;
        }
        else
        {
            puts("Make sure you enter one positive integer, try again");
            continue;
        }
    }
}

/**
 * generateRandomRecords generates random data to a file.
 */
void generateRandomRecords() {

    FILE *cfPtr; /* cfPtr = clients.dat file pointer */
    char filename[] = "..//data//clients.txt";
    NodePtr top;

    int regionOption; // this is used to match the region with the correct town
    char regions[3][20] = {"Durham", "Peel", "York"};
    char towns[3][2][20] = {{"Whitby", "Oshawa"}, {"Brampton", "Mississauga"}, {"Maple", "Vaughan"}};
    char race[5][20] = {"Indigenous", "Caucasian", "African_American", "Asian", "Other"};

    char rndRace[20];
    char rndRegion[20];
    char rndTown[20];
    int rndFamilySize;
    int rndCovidTested;
    int rndCovidPositive;

    // fopen opens file. Exit program if unable to create file
    if ((cfPtr = fopen(filename, "w")) == NULL) {
        printf("File could not be opened\n");
    }
    else {
        srand(time(NULL));

        for (int dex = 0; dex < SIZE; dex++) {
            strcpy(rndRace, race[rand() % 5]);
            regionOption = rand() % 3;
            strcpy(rndRegion, regions[regionOption]);
            strcpy(rndTown, towns[regionOption][rand() % 2]); // Match the region with the correct town
            rndFamilySize = rand() % 20 + 1; // Maximum 20 and Minimum 1
            rndCovidTested = rand() % 21; // Maximum 20 and Minimum 0
            while (rndFamilySize < rndCovidTested) { // Covid tested must be less than or equal to family size
                rndCovidTested = rand() % 21;
            }
            rndCovidPositive = rand() % 21; // Maximum 20 and Minimum 0
            while (rndCovidTested < rndCovidPositive) { // Covid positive must be less than or equal to Covid tested
                rndCovidPositive = rand() % 21;
            }
            addNode(&top, makeHousehold(rndFamilySize, rndCovidTested, rndCovidPositive, rndRace, rndRegion, rndTown));
            fprintf(cfPtr, "%d %d %d %s %s %s\n", rndFamilySize, rndCovidTested, rndCovidPositive, rndRace, rndRegion, rndTown);
        }
        addNode(&top, makeHousehold(0, 0, 0, "End of the list", "", ""));
        fprintf(cfPtr, "%d %d %d %s %s %s\n", 0, 0, 0, "End of the list", "", "");
        fclose(cfPtr); /* fclose closes file */
    } /* end else */
    printf("%d records written successfully as the text file:  %s\n", SIZE, filename);
}

/**
 * readRecordsFromClients stores the records from clients.txt to a linked list and then displays them.
 * @param top name of the linked list of NodePtr pointer
 */
void readRecordsFromClients(NodePtr *top) {
    char rndRace[20];
    char rndRegion[20];
    char rndTown[20];
    int rndFamilySize;
    int rndCovidTested;
    int rndCovidPositive;

    FILE *cfPtr; /* cfPtr = clients.dat file pointer */

    /* fopen opens file; exits program if file cannot be opened */
    if ( ( cfPtr = fopen( "..//data//clients.txt", "r" ) ) == NULL ) {
        printf( "File could not be opened\n" );
        exit(1);
    } /* end if */
    else { /* read Household records from file */
        fscanf( cfPtr, "%d%d%d%s%s%s", &rndFamilySize, &rndCovidTested, &rndCovidPositive, rndRace, rndRegion, rndTown); // read first record
        Household household = makeHousehold(rndFamilySize, rndCovidTested, rndCovidPositive, rndRace, rndRegion, rndTown); // making a household
        *top = makeNode(household); // adding household as a node to the list

        while ( !feof( cfPtr ) ) { /* reading rest of the records i.e. while not end of file */
            fscanf( cfPtr, "%d%d%d%s%s%s", &rndFamilySize, &rndCovidTested, &rndCovidPositive, rndRace, rndRegion, rndTown);
            if(rndFamilySize == 0) break; //sentinel control
            addNode(top, makeHousehold(rndFamilySize, rndCovidTested, rndCovidPositive, rndRace, rndRegion, rndTown));
        } /* end while */

        fclose( cfPtr ); /* fclose closes the file */
        printList(*top);
    } /* end else */
}

/**
 * writeRecordsToFile adds the records to a file.
 * @param top name of the linked list of Node pointer
 * @param fileName name of the file pointer
 */
void writeRecordsToFile(NodePtr top, char *fileName) {

    char path[40] = "..//data//";
    strcat(path, fileName);
    FILE *cfPtr;
    int ctr = 0;

    // fopen opens file. Exit program if unable to create file
    if ((cfPtr = fopen(path, "w")) == NULL) {
        printf("File could not be opened\n");
    }
    else {

        while (top != NULL) {
            fprintf(cfPtr, "%d %d %d %s %s %s\n", top->info.familySize, top->info.covidTested, top->info.covidPositive, top->info.race, top->info.region, top->info.town);
            ctr++;
            top = top->next;
        }

        fprintf(cfPtr, "%d %d %d %s %s %s\n", 0, 0, 0, "End of the list", "", "");
        fclose(cfPtr); /* fclose closes file */
    } /* end else */
    printf("%d records and the sentinel record were written to %s successfully.\n", ctr, path);
}

/**
 * readRecordsFromFile displays the records from a file.
 * @param top name of the linked list of NodePtr pointer
 * @param fileName name of the file pointer
 */
void readRecordsFromFile(NodePtr *top, char *fileName) {
    char rndRace[20];
    char rndRegion[20];
    char rndTown[20];
    int rndFamilySize;
    int rndCovidTested;
    int rndCovidPositive;

    char path[40] = "..//data//";
    strcat(path, fileName);
    FILE *cfPtr;

    /* fopen opens file; exits program if file cannot be opened */
    if ( ( cfPtr = fopen(path, "r" ) ) == NULL ) {
        printf( "File does not exist\n" );
        return;
    } /* end if */
    else { /* read Household data from file */
        fscanf( cfPtr, "%d%d%d%s%s%s", &rndFamilySize, &rndCovidTested, &rndCovidPositive, rndRace, rndRegion, rndTown); // read first record
        Household household = makeHousehold(rndFamilySize, rndCovidTested, rndCovidPositive, rndRace, rndRegion, rndTown); // making a household
        *top = makeNode(household); // adding household as a node to the list

        if (rndFamilySize == 0) {
            puts("Empty list");
            return;
        }

        while ( !feof( cfPtr ) ) { /* reading rest of the records i.e. while not end of file */
            fscanf( cfPtr, "%d%d%d%s%s%s", &rndFamilySize, &rndCovidTested, &rndCovidPositive, rndRace, rndRegion, rndTown);
            if(rndFamilySize == 0) break; //sentinel control
            addNode(top, makeHousehold(rndFamilySize, rndCovidTested, rndCovidPositive, rndRace, rndRegion, rndTown));
        } /* end while */

        fclose( cfPtr ); /* fclose closes the file */
        printList(*top);
    } /* end else */
}

/**
 * Prompt the user for an integer, validate user's option, and display it to the user if it is not valid
 * @param upperbound is the highest integer acceptable as one of the menu options, it must NOT be 0
 * @return is one of the valid options or 0 if the user wants to exit or go back to a previous menu
 */
int menuValidation(int upperbound)
{
    int n = 0, num;
    char temp[40];
    while (1)
    {
        fgets(temp, sizeof(temp), stdin);
        n = sscanf(temp, "%d", &num);
        if (num == 0) break;
        else if(num > 0 && num <= upperbound && n == 1) return num;
        else
        {
            printf("Invalid data, Enter an integer 1 through %d or enter 0 to exit the main menu. Try again\n", upperbound);
            continue;
        }
    }
}

/**
 * Prompt the user for an integer, validate user's option, and display it to the user if it is not valid
 * @param upperbound is the highest integer acceptable as one of the menu options, it must NOT be 9
 * @return is one of the valid options or 9 if the user wants to exit or go back to a previous menu
 */
int menu2Validation(int upperbound)
{
    int n = 0, num;
    char temp[40];
    while (1)
    {
        fgets(temp, sizeof(temp), stdin);
        n = sscanf(temp, "%d", &num);
        if (num == 9) break;
        else if(num >= 0 && num <= upperbound && n == 1) return num;
        else
        {
            printf("Invalid data, Enter an integer 0 through %d or enter 9 to return to the main menu. Try again\n", upperbound);
            continue;
        }
    }
}

/**
 * printSpecificRecords prints data of a linked list passed to the function according to user's choices.
 * @param top name of the linked list of Node pointer
 * @param menuOption first choice from the user
 * @param userOption second choice from the user
 * @param testedPositive number of tested positive
 */
void printSpecificRecords(NodePtr top, int menuOption, int userOption, int testedPositive)
{
    int i = 1;
    char race[5][20] = {"Indigenous", "Caucasian", "African_American", "Asian", "Other"};
    char regions[3][20] = {"Durham", "Peel", "York"};
    char towns[6][20] = {"Whitby", "Oshawa", "Brampton", "Mississauga", "Maple", "Vaughan"};

    puts("S.no\t Size\t Total Tested\t Total tested positive\t\t\tRace\t Region\t\t Town");

    while (top != NULL)
    {
        if (menuOption == 1) {
            if (strcmp(top->info.region, regions[userOption]) == 0) {
                printf("%4d %8d %15d %24d %21s %10s %13s\n", i++, top->info.familySize, top->info.covidTested, top->info.covidPositive, top->info.race, top->info.region, top->info.town);
            }
        }
        else if (menuOption == 2) {
            if (strcmp(top->info.town, towns[userOption]) == 0) {
                printf("%4d %8d %15d %24d %21s %10s %13s\n", i++, top->info.familySize, top->info.covidTested, top->info.covidPositive, top->info.race, top->info.region, top->info.town);
            }
        }
        else if (menuOption == 3) {
            if (strcmp(top->info.race, race[userOption]) == 0) {
                printf("%4d %8d %15d %24d %21s %10s %13s\n", i++, top->info.familySize, top->info.covidTested, top->info.covidPositive, top->info.race, top->info.region, top->info.town);
            }
        }
        else if (menuOption == 4) {
            if (strcmp(top->info.region, regions[userOption]) == 0 && testedPositive <= top->info.covidPositive) {
                printf("%4d %8d %15d %24d %21s %10s %13s\n", i++, top->info.familySize, top->info.covidTested, top->info.covidPositive, top->info.race, top->info.region, top->info.town);
            }
        }
        top = top->next;
    }

}

/**
 * sortCategoryDesc sorts a list of Category ranking in descending order
 * @param list name of the array
 * @param len size of the array
 */
void sortCategoryDesc(Category list[80], int len)
{
    int i, j;
    Category temp;

    for (i = 0; i < len - 1; i++)
    {
        for (j = 0; j < (len - 1-i); j++)
        {
            if (list[j].value < list[j + 1].value)
            {
                temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
}

/**
 * printRegionTownRanking prints specific data of a linked list passed to the function.
 * @param top name of the linked list of Node pointer
 */
void printRegionTownRanking(NodePtr top)
{
    char regions[3][20] = {"Durham", "Peel", "York"};
    char towns[6][20] = {"Whitby", "Oshawa", "Brampton", "Mississauga", "Maple", "Vaughan"};
    int totalCases;
    Category regionRank[3];
    Category townRank[6];

    NodePtr temp = top; // For resetting the top

    for (int i = 0; i < 3; i++) {
        top = temp; // Reset top
        totalCases = 0;
        strcpy(regionRank[i].type, regions[i]);
        while (top != NULL) {
            if (strcmp(top->info.region, regions[i]) == 0) {
                totalCases += top->info.covidPositive;
            }
            top = top->next;
        }
        regionRank[i].value = totalCases;
    }

    for (int i = 0; i < 6; i++) {
        top = temp; // Reset top
        totalCases = 0;
        strcpy(townRank[i].type, towns[i]);
        while (top != NULL) {
            if (strcmp(top->info.town, towns[i]) == 0) {
                totalCases += top->info.covidPositive;
            }
            top = top->next;
        }
        townRank[i].value = totalCases;
    }

    sortCategoryDesc(regionRank, 3);
    sortCategoryDesc(townRank, 6);

    puts("Tested Positive Covid-19 cases:");
    puts("Region-wise ranking:");
    for (int i = 0; i < 3; i++) {
        printf("%19s : %d\n", regionRank[i].type, regionRank[i].value);
    }
    puts("Town-wise ranking:");
    for (int i = 0; i < 6; i++) {
        printf("%19s : %d\n", townRank[i].type, townRank[i].value);
    }
}