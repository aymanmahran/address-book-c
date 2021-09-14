#include "address_book.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void setField(Contact *contact, int field_index, char* value)
{
    //Based on field index, copy the value to the field in the node
    switch(field_index)
    {
    case 0:
        strcpy(contact->last_name, value);
        break;
    case 1:
        strcpy(contact->first_name, value);
        break;
    case 2:
        strcpy(contact->email, value);
        break;
    case 3:
        strcpy(contact->phone_number, value);
        break;
    }
    return;
}

char *getField(Contact *contact, int field_index)
{
    //Based on field index, return the field value of a node
    switch(field_index)
    {
    case 0:
        return contact->last_name;
        break;
    case 1:
        return contact->first_name;
        break;
    case 2:
        return contact->email;
        break;
    case 3:
        return contact->phone_number;
        break;
    }
}

void addContact(Contact *head, Contact *new_contact, int position)
{
    Contact *traverse;
    traverse = head;
    int count = 0;
    //Skip first "position" nodes and insert after
    while(count < position - 1)
    {
        traverse = traverse->next;
        count++;
    }
    //Insert new_contact after node at index position by making it point
    //to the node after that at index position
    //and making the node at index position point to the new node
    new_contact->next = traverse->next;
    traverse->next = new_contact;
    return;
}

void deleteContact(Contact *head, int position)
{
    Contact *traverse;
    Contact *delete_contact;
    traverse = head;
    int count = 0;
    //Traverse to node at index position - 1
    while(count < position - 1)
    {
        traverse = traverse->next;
        count++;
    }

    //Delete node at index position by making the previous node point
    //to the node after that at index position
    //and freeing memory allocated for node at index position
    delete_contact = traverse->next;
    traverse->next = traverse->next->next;
    freeMem(delete_contact);
    return;
}

Contact* getContact(Contact *head, int position)
{
    Contact *traverse;
    traverse = head;
    int count = 0;
    //Traverse to node at index position
    while(count < position)
    {
        traverse = traverse->next;
        count++;
    }
    //Return that node
    return traverse;
}

int countContacts(Contact *head)
{
    Contact *traverse;
    traverse = head;
    int count = 0;
    //Traverse through all nodes and add one each time until a null pointer is reached(end of list)
    while(traverse != NULL)
    {
        traverse = traverse->next;
        count++;
    }
    //Return number of nodes
    return count;
}

void editContact(Contact *head, int position, char *field, char *value)
{
    Contact *traverse;
    traverse = head;
    int count = 0;
    //Traverse to node at index position
    while(count < position)
    {
        traverse = traverse->next;
        count++;
    }
    //Get the field index from its name
    int field_index = fieldToIndex(field);
    //Update field with the new value
    setField(traverse, field_index, value);

    return;
}

void freeMem(Contact *delete_contact)
{
    //Free memory for the node and its data
    free(delete_contact->first_name);
    free(delete_contact->last_name);
    free(delete_contact->email);
    free(delete_contact->phone_number);
    free(delete_contact);
    return;
}

char *compressContact(Contact *contact)
{
    //Allocate maximum length for csv line
    char *csv_contact = malloc(1025);
    for(int i=0; i<4; i++)
    {
        //Append each field to the csv string, adding comma after each one except for the last field
        strcat(csv_contact, getField(contact, i));
        if(i != 3) strcat(csv_contact, ",");
    }
    return csv_contact;
}

void extractContact(char *input, Contact *new_contact)
{
    //Split csv string using comma delimiter
    char *value = strtok(input, ",");
    char *field;
    for(int i=0; i<4; i++)
    {
        //Update each field with the values extracted from csv string
        setField(new_contact, i, value);
        value = strtok(NULL, ",");
    }
    return;
}

int fieldToIndex(char *field)
{
    //Return index of each field based on its name. Makes it easier to iterate through fields
    int index = -1;
    if(strcmp(field, "lastName") == 0)
    {
        index = 0;
    }
    else if(strcmp(field, "firstName") == 0)
    {
        index = 1;
    }
    else if(strcmp(field, "email") == 0)
    {
        index = 2;
    }
    else if(strcmp(field, "phoneNumber") == 0)
    {
        index = 3;
    }
    return index;
}

void newContact(Contact **new_contact)
{
    //Allocate memory for the node and each field with the maximum string length
    Contact *contact = malloc(sizeof(*contact));
    contact->first_name = malloc(257);
    contact->last_name = malloc(257);
    contact->email = malloc(257);
    contact->phone_number = malloc(257);
    contact->next = NULL;

    *new_contact = (Contact *) contact;
    return;
}

void readFile(char *path, Contact **head){
    //Open file at path to read it
    FILE *stream = fopen(path, "r");

    char line[1025];
    char *tmp;
    Contact *contact;
    int n = countContacts(*head);
    //Flag to skip the first record (column headers)
    int flag = false;
    //Read each line into buffer
    while (fgets(line, 1025, stream))
    {
        //Remove \n newline from the end of the line
        char* record = strdup(strtok(line, "\n"));
        //Skip column headers
        if(!flag){
            flag = true;
            continue;
        }
        //Allocate memory for a new contact node
        newContact(&contact);
        //Extract data from csv line and insert it into the new node
        extractContact(record, contact);
        //Add the node to the end of the linked list at position n
        //If list is already empty, make the new node the head
        if(n == 0)
        {
            contact->next = *head;
            *head = contact;
        }
        else
        {
            addContact(*head, contact, n);
        }

        n++;
        //Free memory for the line read
        free(tmp);
    }
    return;
}

void saveFile(char *path, Contact *head)
{
    Contact *traverse;
    traverse = head;

    //Open file to write to it
    FILE *file;
    file = fopen(path, "w");

    //Write column headers
    fprintf(file, "lastName,firstName,email,phoneNumber\n");
    //Traverse through the list passing though every node
    while(traverse != NULL)
    {
        //Convert the data in a node into csv string
        char *str = compressContact(traverse);
        //Write the csv string to the file
        fprintf(file, str);
        fprintf(file, "\n");
        traverse = traverse->next;
        //Free memory for csv string as it is not needed
        free(str);
    }
    //Close the file to save changes
    fclose(file);
    return;
}

void swapStrings(char **string1, char **string2){
    //Swap strings
    //Store pointer of string1, let the string1 hold pointer of string1, put string1 pointer int string2
    char *tmp = *string1;
    *string1 = *string2;
    *string2 = tmp;
    return;
}

void sortContacts(Contact *head){

    Contact *traverse = head, *node;

    //Create a list of pointers to the csv strings of all the nodes to compare them
    int n = countContacts(head);
    char *contacts[n+1];
    int index = 0;

    //Generate and store csv string for each not into the pointer array
    while(traverse != NULL){
        contacts[index] = compressContact(traverse);
        index++;
        traverse = traverse->next;
    }

    //Sort the pointer array using bubble sort
    for(int i=0; i<n-1; i++){
        node = head;
        for(int j=0; j<n-i-1; j++){
            if(strcmp(contacts[j], contacts[j+1]) > 0){
                swapStrings(&contacts[j], &contacts[j+1]);
                //When swapping array elements, swap the corresponding node values
                //Thus the linked list is sorted
                swapStrings(&node->last_name, &node->next->last_name);
                swapStrings(&node->first_name, &node->next->first_name);
                swapStrings(&node->email, &node->next->email);
                swapStrings(&node->phone_number, &node->next->phone_number);

            }
            node = node->next;
        }
    }

    return;
}
