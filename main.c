#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "address_book.h"

int main()
{

    //setvbuf(stdout, NULL, _IONBF, 0);   //Turn off output buffering, used for automated testing

    Contact *head = {{NULL, NULL, NULL, NULL, NULL}};
    char command;                       //Char that hold the subsequent commands entered through standard input
    int index;                          //Index of selected contact
    char csv_contact[1025];             //Contact separated by commas
    char field[20];                     //Name of contact field(first name, last name,...)
    char value[257];                    //Value of field
    int field_index;                    //0: lastname, 1: firstname,...
    char path[257];                     //Path of file to read/write
    Contact *contact;                   //Pointer to the current contact to perform operation on

    printf("Ready\n");

    //Keep asking for commands until a quit command is entered
    while(command != 'q')
    {
        //Get the command
        scanf("%c", &command);
        //Check the command entered and execute the appropriate function
        switch(command)
        {
        case 'a':
            //Get index where to insert the new contact and the contact information
            scanf("%d", &index);
            scanf("%s", csv_contact);
            //Allocate memory for the new contact
            newContact(&contact);
            //Extract contact details from the csv contact
            extractContact(csv_contact, contact);
            //Add the contact to the linked list
            //If it is to be the first element in the list, make it the head
            if(index == 0)
            {
                contact->next = head;
                head = contact;
            }
            else
            {
                addContact(head, contact, index);
            }
            break;

        case 'd':
            //Get index of contact to delete
            scanf("%d", &index);
            //Remove node from linked list
            //If it is the first element, make the head the next element and free allocated memory
            if(index == 0)
            {
                contact = head;
                head = head->next;
                freeMem(contact);
            }
            else if(index < countContacts(head))
            {
                deleteContact(head, index);
            }
            break;

        case 'g':
            //Get the index of contact to retreive
            scanf("%d", &index);
            //Get the matching node
            contact = getContact(head, index);
            //Convert contact details to cvs
            char* str = compressContact(contact);
            printf("%s\n", str);
            //Free allocated memory for csv
            free(str);
            break;

        case 'f':
            //Get contact index and name of field to find in the contact
            scanf("%d", &index);
            scanf("%s", field);
            //Get the matching node
            contact = getContact(head, index);
            //Get the corresponding index of the field in the struct
            field_index = fieldToIndex(field);
            //Get the value of the field fro the node
            printf("%s\n", getField(contact, field_index));
            break;

        case 'n':
            //Count the number of nodes in linked list
            printf("%i\n", countContacts(head));
            break;

        case 'l':
            //Get path to read
            scanf("%s", path);
            //Read lines from path to linked list
            readFile(path, &head);
            break;

        case 's':
            //Get path to save contacts
            scanf("%s", path);
            //Save contacts from linked list in csv format to file
            saveFile(path, head);
            break;

        case 'e':
            //Get the contact to edit and the new value
            scanf("%d", &index);
            scanf("%s", field);
            scanf("%s", value);
            //Replace the value in the matching node with the new value
            editContact(head, index, field, value);

        case 'o':
            //Sort contacts ascendingly
            sortContacts(head);
            break;

        default:
            //Unknown command. Ignore
            break;
        }

    }

    //If a quit command is entered, print Complete and end
    if(command == 'q')
        printf("Complete\n");
    return 0;
}
