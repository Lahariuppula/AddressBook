#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "populate.h"

void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
    if(addressBook->contactCount == 0)
    {
        printf("No contacts available.\n");
        return;
    }
    printf("\nContact list\n");
    printf("%-20s %-15s %-30s\n", "Name", "Phone Number", "Mail Id");
    printf("-----------------------------------------------------------------\n");
    for(int i=0;i<addressBook -> contactCount;i++)
    {
       printf("%-20s %-15s %-30s\n",addressBook-> contacts[i].name,addressBook-> contacts[i].phone,addressBook-> contacts[i].email);
    }
}

void initialize(AddressBook *addressBook) 
{
    populateAddressBook(addressBook);
    loadContactsFromFile(addressBook);
}


void createContact(AddressBook *addressBook)
{
    /* Define your logic for create contact*/
    char name[50], phone[20], email[50], choice;

    printf("Enter Name (Mandatory): ");
    scanf(" %[^\n]", name);

    printf("Enter Phone no.: ");
    scanf(" %s", phone);

    if (strlen(phone) != 10)
    {
        printf("Phone number must contain exactly 10 digits!\n");
        return;
    }

    for (int i = 0; phone[i] != '\0'; i++)
    {
        if (!isdigit(phone[i]))
        {
            printf("Phone number should contain digits only!\n");
            return;
        }
    }

    printf("Enter Email Id: ");
    scanf(" %s", email);

    char gmail[] = "@gmail.com";
    if (strlen(email) < strlen(gmail) ||
        strcmp(email + strlen(email) - strlen(gmail), gmail) != 0)
    {
        printf("Only @gmail.com email IDs are allowed!\n");
        return;
    }

    printf("Save contact? (y/n): ");
    scanf(" %c", &choice);

    if (choice != 'y' && choice != 'Y')
    {
        printf("Contact not saved.\n");
        return;
    }

    strcpy(addressBook->contacts[addressBook->contactCount].name, name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email, email);
    addressBook->contactCount++;

    printf("Contact created successfully.\n");
}


void searchContact(AddressBook *addressBook) 
{
  /* Define the logic for search contact*/
    char find[50];
    int count = 0,index = -1;
    
    if (addressBook->contactCount == 0)
    {
        printf("No contacts available.\n");
        return;
    }
    printf("Enter Name/Phone no./Email to search: ");
    scanf(" %[^\n]", find);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(find, addressBook->contacts[i].name) == 0)
        {
            count++;
            index = i;
        }
    }

    if (count > 1)
    {
        printf("Name already exists.\n");
        printf("Please search using Phone number or Email ID.\n");

        printf("Enter Phone no./Email to search: ");
        scanf(" %[^\n]", find);

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(find, addressBook->contacts[i].phone) == 0 ||
                strcmp(find, addressBook->contacts[i].email) == 0)
            {
                printf("\nName  : %s", addressBook->contacts[i].name);
                printf("\nPhone : %s", addressBook->contacts[i].phone);
                printf("\nEmail : %s\n", addressBook->contacts[i].email);
                return;
            }
        }

        printf("Contact not found.\n");
        return;
    }

    if (count == 1)
    {
        printf("\nName  : %s", addressBook->contacts[index].name);
        printf("\nPhone : %s", addressBook->contacts[index].phone);
        printf("\nEmail : %s\n", addressBook->contacts[index].email);
        return;
    }

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(find, addressBook->contacts[i].phone) == 0 ||
            strcmp(find, addressBook->contacts[i].email) == 0)
        {
            printf("\nName  : %s", addressBook->contacts[i].name);
            printf("\nPhone : %s", addressBook->contacts[i].phone);
            printf("\nEmail : %s\n", addressBook->contacts[i].email);
            return;
        }
    }

    printf("Contact not found.\n");
}

void editContact(AddressBook *addressBook)
{
    /* Define the logic for edit */
    char Detailtobeedited[50],Newdetail[50];
    int choice,found = 0;

    printf("Enter Name / Phone / Email to edit: ");
    scanf(" %s", Detailtobeedited);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(Detailtobeedited, addressBook->contacts[i].name) == 0 ||
            strcmp(Detailtobeedited, addressBook->contacts[i].phone) == 0 ||
            strcmp(Detailtobeedited, addressBook->contacts[i].email) == 0)
        {
            found = 1;
            printf("Enter what you want to edit:\n");
            printf("1. Name\n");
            printf("2. Phone no.\n");
            printf("3. Email\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            if (choice == 1)
            {
                printf("Enter new Name: ");
                scanf(" %[^\n]", Newdetail);
                strcpy(addressBook->contacts[i].name, Newdetail);
            }
            else if (choice == 2)
            {
                printf("Enter new Phone no.: ");
                scanf(" %s", Newdetail);

                if (strlen(Newdetail) != 10)
                {
                   printf("Invalid phone number! Must be exactly 10 digits.\n");
                   return;
                }

                for (int k = 0; Newdetail[k] != '\0'; k++) 
                {
                    if (!isdigit(Newdetail[k])) 
                    {
                        printf("Invalid phone number! Digits only.\n");
                        return;
                    }
                }

                for (int j = 0; j < addressBook->contactCount; j++)
                {
                   if (j != i && strcmp(Newdetail, addressBook->contacts[j].phone) == 0)
                    {
                      printf("This phone number already exists!\n");
                      return;
                    }
                }

                strcpy(addressBook->contacts[i].phone, Newdetail);
            }
            else if (choice == 3)
            {
                printf("Enter new Email: ");
                scanf(" %s", Newdetail);

                if (strchr(Newdetail, '@') == NULL || strchr(Newdetail, '.') == NULL) 
                {
                    printf("Invalid email format!\n");
                    return;
                }
                  
                for (int j = 0; j < addressBook->contactCount; j++)
                {
                   if (j != i && strcmp(Newdetail, addressBook->contacts[j].email) == 0)
                    {
                      printf("This email ID already exists!\n");
                      return;
                    }
                }

                strcpy(addressBook->contacts[i].email, Newdetail);
            }
            else
            {
                printf("Invalid choice\n");
            }
            printf("Contact edited successfully.\n");
        }
    }
    if(!found)
    printf("Contact not found.\n");
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    char Find[50];
    int found = 0;
    printf("Enter Name/Phone no./Email of the contact to be deleted: ");
    scanf(" %s", Find);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(Find, addressBook->contacts[i].name) == 0 ||
            strcmp(Find, addressBook->contacts[i].phone) == 0 ||
            strcmp(Find, addressBook->contacts[i].email) == 0)
        {
            found = 1;
            char confirm;
            printf("Are you sure you want to delete this contact? (y/n): ");
            scanf(" %c", &confirm);

            if(confirm != 'y' && confirm != 'Y') 
            {
                printf("Delete cancelled.\n");
                return;
            }
            for (int j = i; j < addressBook->contactCount - 1; j++)
            {
                addressBook->contacts[j] = addressBook->contacts[j + 1];
            }

            addressBook->contactCount--; 
            printf("Contact deleted successfully.\n");
            break;
        }
    }

    if (!found)
    {
        printf("Contact not found.\n");
    }
}

void Exit()
{
    printf("Exiting the application...\n");
    exit(0);
}