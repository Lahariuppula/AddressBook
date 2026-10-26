#include <stdio.h>
#include <string.h>
#include "contact.h"

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contacts.txt", "w");
    if (!fp)
    {
        printf("Error opening contacts.txt for writing!\n");
        return;
    }

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%s %s %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }

    fclose(fp);
    printf("Contacts saved successfully.\n");
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contacts.txt", "r");
    if (!fp)
    {
        addressBook->contactCount = 0;
        return;
    }

    addressBook->contactCount = 0;

    while (fscanf(fp, "%s %s %s",addressBook->contacts[addressBook->contactCount].name,addressBook->contacts[addressBook->contactCount].phone,addressBook->contacts[addressBook->contactCount].email) == 3)
    {
        addressBook->contactCount++;

        if (addressBook->contactCount >= MAX_CONTACTS)
            break;
    }

    fclose(fp);
}
