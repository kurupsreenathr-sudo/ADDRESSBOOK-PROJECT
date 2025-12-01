/*
NAME           :SREENATH R KURUP
REG_NO         :25026_066
START DATE     :16/10/2025
END DATE       :29/10/2025
DESCRIPTION    :The Address Book Management System is a C-based console application that allows users to create, search, edit, delete, and list contacts efficiently.
                It ensures data validation through name, phone, and email verification while storing contact details persistently using file handling.
                The project showcases structured programming, string manipulation, and user-friendly menu-driven interaction.
*/

#include <stdio.h>
#include "contact.h"
#include <unistd.h>
#define BOLD  "\033[1m"
#define RESET   "\033[0m"


int main() {
    int choice,sortChoice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        printf(BOLD "\nADDRESS BOOK MENU:\n" RESET);
       // printf("==================\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save contacts\n");		
        printf("7. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:          
                listContacts(&addressBook, sortChoice);
                break;
            case 6:
                printf(BOLD"Saving and Exiting...\n"RESET);
                saveContactsToFile(&addressBook);
                saveAndExit(&addressBook);
                break;
            case 7:
            printf("Exiting...\n ");
            sleep(2);
            printf(BOLD"\n---------------EXITED---------------\n"RESET);
            break;

            default:
                printf("Invalid choice. Please try again.\n");
                while(getchar()!='\n');
        }
    } while (choice != 7);
    
       return 0;
}
