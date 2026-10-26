#include <stdio.h>
#include "contact.h"

int main() 
{
    AddressBook s;
    initialize(&s);
    int choice;

    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Save contact\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createContact(&s);
                break;
            case 2:
                searchContact(&s);
                break;
            case 3:
                editContact(&s);
                break;
            case 4:
                deleteContact(&s);
                break;
            case 5:
                listContacts(&s);
                break;
            case 6:
                saveContactsToFile(&s);
                break;
            case 7:
                Exit();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } 
    while (choice != 7);
     return 0;
}
