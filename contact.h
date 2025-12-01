#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[100];
    int contactCount;
} AddressBook;

int createContact(AddressBook *addressBook);
int searchContact(AddressBook *addressBook);
int editContact(AddressBook *addressBook);
int deleteContact(AddressBook *addressBook);
int validate_name(char name[]);
int validate_phone(char phone[],AddressBook *addressBook);
int validate_email(char email[],AddressBook *addressBook);
void listContacts(AddressBook *addressBook, int sortCriteria);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);
void saveAndExit(AddressBook *addressBook);

#endif
