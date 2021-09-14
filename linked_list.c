typedef struct node
{
    char *first_name;
    char *last_name;
    char *email;
    char *phone_number;
    struct node *next;
} Contact;

void addContact(Contact *head, Contact *new_contact, int position)
{
    Contact *traverse;
    traverse = head;
    int count = 0;

    while(count < position - 1)
    {
        traverse = traverse->next;
        count++;
    }
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

    while(count < position - 1)
    {
        traverse = traverse->next;
        count++;
    }

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

    while(count < position)
    {
        traverse = traverse->next;
        count++;
    }

    return traverse;
}

int countContacts(Contact *head)
{
    Contact *traverse;
    traverse = head;
    int count = 0;
    while(traverse != NULL)
    {
        traverse = traverse->next;
        count++;
    }
    return count;
}

void editContact(Contact *head, int position, char *field, char *value)
{
    Contact *traverse;
    traverse = head;
    int count = 0;

    while(count < position)
    {
        traverse = traverse->next;
        count++;
    }

    int field_index = fieldToIndex(field);
    setField(traverse, field_index, value);

    return;
}

void sortContacts(Contact *head){

    Contact *traverse = head, *node;

    int n = countContacts(head);
    char *contacts[n+1];
    int index = 0;

    while(traverse != NULL){
        contacts[index] = compressContact(traverse);
        index++;
        traverse = traverse->next;
    }

    for(int i=0; i<n-1; i++){
        node = head;
        for(int j=0; j<n-i-1; j++){
            if(strcmp(contacts[j], contacts[j+1]) > 0){
                /*printf("%d %d\n", i, j);
                printf("%10s\n", contacts[j]);
                printf("%10s\n", contacts[j+1]);
                printf("%s\n", node2->last_name);
                printf("%s\n", node2->next->last_name);*/
                swapStrings(&contacts[j], &contacts[j+1]);
                swapStrings(&node->last_name, &node->next->last_name);
                swapStrings(&node->first_name, &node->next->first_name);
                swapStrings(&node->email, &node->next->email);
                swapStrings(&node->phone_number, &node->next->phone_number);

            }
            node = node->next;
        }
    }

    /*node = head;
    for(int i=0; i<n; i++){
    printf("%s\n", contacts[i]);
    }

    while(node != NULL){
        printf("%s\n", compressContact(node));
        node = node->next;
    }*/

    return;
}
