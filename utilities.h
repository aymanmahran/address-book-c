void setField(Contact *contact, int field_index, char* value)
{
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

void freeMem(Contact *delete_contact)
{
    free(delete_contact->first_name);
    free(delete_contact->last_name);
    free(delete_contact->email);
    free(delete_contact->phone_number);
    free(delete_contact);
    return;
}

char *compressContact(Contact *contact)
{
    char *csv_contact = malloc(1025);
    for(int i=0; i<4; i++)
    {
        strcat(csv_contact, getField(contact, i));
        //printf("%s", getField(contact, i));
        if(i != 3) strcat(csv_contact, ",");
            //printf(",");
    }
    //printf("\n");
    return csv_contact;
}

void extractContact(char *input, Contact *new_contact)
{
    char *value = strtok(input, ",");
    char *field;
    for(int i=0; i<4; i++)
    {
        setField(new_contact, i, value);
        //strcpy(new_contact->first_name, value);
        value = strtok(NULL, ",");
    }
    return;
}

int fieldToIndex(char *field)
{
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

    FILE *stream = fopen(path, "r");

    char line[1025];
    char *tmp;
    Contact *contact;
    int n = countContacts(*head);
    int flag = false;
    while (fgets(line, 1025, stream))
    {
        char* record = strdup(strtok(line, "\n"));
        if(!flag){
            flag = true;
            continue;
        }
        newContact(&contact);
        extractContact(record, contact);

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
        free(tmp);
    }
    return;
}

void saveFile(char *path, Contact *head)
{
    Contact *traverse;
    traverse = head;

    FILE *file;
    file = fopen(path, "w");

    fprintf(file, "lastName,firstName,email,phoneNumber\n");
    while(traverse != NULL)
    {
        char *str = compressContact(traverse);
        fprintf(file, str);
        fprintf(file, "\n");
        traverse = traverse->next;
        free(str);
    }

    fclose(file);
    return;
}

void swapStrings(char **string1, char **string2){
    char *tmp = *string1;
    *string1 = *string2;
    *string2 = tmp;
    return;
}

void swapFields(char* field1, char* field2)
{
    char tmp[257] = "";
    strcpy(tmp,field1);
    strcpy(field1,field2);
    strcpy(field2,tmp);
    return;
}
