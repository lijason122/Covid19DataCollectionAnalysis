/*
 * Name: Jason Li
 * Start coding date: July 7th, 2021
 * Last revision date: July 26th, 2021
 * covid19InfoLL.c stores, analyzes, and updates Covid-19 information about Greater Toronto Area (GTA) for the health ministry of Ontario.
 */

#include "household.h"

int main() {

    // Generate the records to clients.txt
    generateRandomRecords();

    // Store the records from clients.txt to a linked list called top and display them
    NodePtr top;
    readRecordsFromClients(&top);

    puts("-------------------This program analyzes and stores information related to Covid-19 cases-------------------");
    puts("-------------------------and its impact on various races, regions and towns of GTA--------------------------");

    // Category of data that will be collected
    char regions[3][20] = {"Durham", "Peel", "York"};
    char towns[3][2][20] = {{"Whitby", "Oshawa"}, {"Brampton", "Mississauga"}, {"Maple", "Vaughan"}};
    char race[5][20] = {"Indigenous", "Caucasian", "African_American", "Asian", "Other"};

    // Show the text-based menu driven interface
    while(1) {
        // Number of options from specific choice that the user will be choosing
        int menuOption;
        int userOption;
        int testedPositive;
        int regionOption;
        int townOption;
        int raceOption;

        // Display the choices to the user
        puts("Menu:");
        puts("Enter your choice to");
        puts("1. display households of a region");
        puts("2. display households of a town");
        puts("3. display households of a race");
        puts("4. display households of a region with a given minimum number of people tested positive for Covid-19");
        puts("5. display the regions town-wise ranking of number of people tested positive for Covid-19");
        puts("6. add a record");
        puts("7. delete all records of a region, town and race triplet");
        puts("8. display updated data");
        puts("9. store data to a file");
        puts("10. display data from file");
        puts("0. exit the program");

        // Prompt the user to enter their choices, validate user's choices, and display the data information accordingly
        menuOption = menuValidation(10);
        if (menuOption == 0) { // Exit the application
            printf("\nThank you");
            break;
        }
        else if (menuOption == 1) {
            puts("Enter an integer for region: Durham(0), Peel(1), and York(2):");
            userOption = menu2Validation(2);
            if (userOption == 9) {
                continue;
            }
            // Print the records according to the choices from the user
            printSpecificRecords(top, menuOption, userOption, 0);
        }
        else if (menuOption == 2) {
            puts("Enter an integer for town: Whitby(0), Oshawa(1), Brampton(2), Mississauga(3), Maple(4), Vaughan(5):");
            userOption = menu2Validation(5);
            if (userOption == 9) {
                continue;
            }
            // Print the records according to the choices from the user
            printSpecificRecords(top, menuOption, userOption, 0);
        }
        else if (menuOption == 3) {
            puts("Enter an integer for race: Indigenous(0), Caucasian(1), African_American(2), Asian(3), Other(4):");
            userOption = menu2Validation(4);
            if (userOption == 9) {
                continue;
            }
            // Print the records according to the choices from the user
            printSpecificRecords(top, menuOption, userOption, 0);
        }
        else if (menuOption == 4) {
            puts("Enter an integer for region: Durham(0), Peel(1), and York(2):");
            userOption = menu2Validation(2);
            if (userOption == 9) {
                continue;
            }
            puts("Enter lowerbound of number of Covid-19 positive cases per household in the region");
            // Validate the number from the user
            numOfTestedPositiveValidation(&testedPositive);

            // Print the records according to the choices from the user
            printSpecificRecords(top, menuOption, userOption, testedPositive);
        }
        else if (menuOption == 5) {
            // Print the records according to the choices from the user
            printRegionTownRanking(top);
        }
        else if (menuOption == 6) {
            puts("Enter region: 0 for Durham, 1 for Peel, 2 for York");
            regionOption = menu2Validation(2);
            if (regionOption == 9) {
                continue;
            }
            printf("Enter town: 0 for %s, 1 for %s\n", towns[regionOption][0], towns[regionOption][1]);
            townOption = menu2Validation(1);
            if (townOption == 9) {
                continue;
            }
            puts("Enter race: 0 for indigenous, 1 for Caucasian, 2 for African_American, 3 for Asian, 4 for Other");
            raceOption = menu2Validation(4);
            if (raceOption == 9) {
                continue;
            }

            int familySize;
            int covidTested;
            int covidPositive;

            // Validate the numbers from the user
            numOfMembersValidation(&familySize, &covidTested, &covidPositive);

            // Add the record to the top of the linked list
            addNode(&top, makeHousehold(familySize, covidTested, covidPositive, race[raceOption], regions[regionOption], towns[regionOption][townOption]));

        }
        else if (menuOption == 7) {
            puts("Enter region: 0 for Durham, 1 for Peel, 2 for York");
            regionOption = menu2Validation(2);
            if (regionOption == 9) {
                continue;
            }
            printf("Enter town: 0 for %s, 1 for %s\n", towns[regionOption][0], towns[regionOption][1]);
            townOption = menu2Validation(1);
            if (townOption == 9) {
                continue;
            }
            puts("Enter race: 0 for indigenous, 1 for Caucasian, 2 for African_American, 3 for Asian, 4 for Other");
            raceOption = menu2Validation(4);
            if (raceOption == 9) {
                continue;
            }

            // Delete the records that match the choices from the user
            deleteNodesWithOptions(&top, regionOption, townOption, raceOption);

        }
        else if (menuOption == 8) {
            // Display the updated data
            printList(top);
        }
        else if (menuOption == 9) {
            puts("Enter file name with extension, for example clients.txt");
            char *fileName = fileNameValidation(); // Validate file name with extension from the user
            writeRecordsToFile(top, fileName); // Add the records to the file
        }
        else {
            puts("Enter file name with extension, for example clients.txt");
            char *fileName = fileNameValidation(); // Validate file name with extension from the user
            readRecordsFromFile(&top, fileName); // Display the records from the file
        }
    } // End of while loop for the text-based menu driven interface

    return 0;
}
