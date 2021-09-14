#ifndef ADDRESS_BOOK_H
#define ADDRESS_BOOK_H

//Contact node with contact details and pointer to the next contact node in the list
typedef struct node
{
    char *first_name;
    char *last_name;
    char *email;
    char *phone_number;
    struct node *next;
} Contact;

//Set the value of a  field in a specific node
void setField(Contact *contact, int field_index, char* value);

//Get the value of a field in a specific node
char *getField(Contact *contact, int field_index);

//Add new node after node at new_contact
void addContact(Contact *head, Contact *new_contact, int position);

//Delete node at index position
void deleteContact(Contact *head, int position);

//Get the node at index position
Contact *getContact(Contact *head, int position);

//Count nodes
int countContacts(Contact *head);

//Update field at node position with value
void editContact(Contact *head, int position, char *field, char *value);

//Free allocated memory by a node
void freeMem(Contact *delete_contact);

//Convert contact information to csv value
char *compressContact(Contact *contact);

//Convert csv value to contact information
void extractContact(char *input, Contact *new_contact);

//Convert field name to field index
int fieldToIndex(char *field);

//Allocate memory for a new contact
void newContact(Contact **new_contact);

//Read content of a file, process it and add it to linked list
void readFile(char *path, Contact **head);

//Save linked list as csv file
void saveFile(char *path, Contact *head);

//Swap value of two char arrays
void swapStrings(char **string1, char **string2);

//Sort nodes in linked list ascendingly
void sortContacts(Contact *head);

#endif
