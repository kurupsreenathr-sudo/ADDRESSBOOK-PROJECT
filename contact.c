#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#define BOLD  "\033[1m"
#define RESET   "\033[0m"

//#include "populate.h"

void listContacts(AddressBook *addressBook, int sortCriteria) 
{  
     // Sort contacts based on the chosen criteria
      printf("-------------------------------------------------------------------------------\n");
      printf("| %-5s | %-20s | %-15s | %-26s |\n","SL.no","Name","PhoneNo.","Email id.");
      printf("-------------------------------------------------------------------------------\n");
    for(int i=0;i<addressBook->contactCount;i++)
    {
        printf("| %-5d | %-20s | %-15s | %-26s |\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    printf("-------------------------------------------------------------------------------\n");
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);          //load from file
    //populateAddressBook(addressBook);
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook);
    printf("\n**********CONTACTS ARE SAVED AND EXITED**********\n"); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}
// function for creating contact//
int createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    char name[30];
    char phone[11];
    char email[20];
    a://label
    printf("Enter the name : ");
    scanf(" %[^\n]",name);   //read name from the user
    if(validate_name(name)) //function call
    {
       strcpy(addressBook->contacts[addressBook->contactCount].name,name);//copy the name given by the user to the new contact structure
    }
    else
    {
        printf("Please enter a valid name\n");  //invalid prompt message
        goto a;  //goto the label for re entering the name
    }
    b:      //label
    printf("Enter the phone number : ");
    scanf(" %s",phone);                  //read phone number from the user
    if(validate_phone(phone,addressBook))  //function call
    {
        strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);//copy the phone number given by the user to the new contact structure
    }
    else{
        printf("Please enter a valid phone number\n");   //invalid prompt message
        goto b;         //goto the label for re entering the phone number
    }
    c:   //label
    printf("Enter the email id : ");
    scanf(" %s",email);           //read email id from the user
    if(validate_email(email,addressBook))  //function call
    {
        strcpy(addressBook->contacts[addressBook->contactCount].email,email);//copy the email id given by the user to the new contact structure
    }
    else{
        printf("\nPlease enter a valid Email id\n");    //invalid prompt message
        goto c;   //goto the label for re entering the mail id
    }
    addressBook->contactCount++;  //increment the contact count after adding a new contact
    printf("\nContact saved successfully!\n");   //prompt message
    return 1;
}
//function for search contact
int searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int choice,flag=0;
    char name[30];
    char phone[11];
    char email[40];
do
{
    printf("\nEnter search by : \n");  //prompt message for the user
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("4. Exit\n");
    scanf("%d",&choice);  //get the option from the user
    switch(choice)    //switch case
    {
        case 1:  //search by name
        {
            int arr[40];//declaring the array to store the index value of occurance
            int size=0;
            getchar();    //clear the input buffer
            printf("\nEnter the name: ");
            scanf(" %[^\n]",name);  //read the name from the user for search
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strcasestr(addressBook->contacts[i].name,name)!=NULL)  //check the entered name is present in the contacts name
                
                {
                   arr[size]=i;// store the index value inside the array
                   size++;//increment the size counter
                }         
            }
            if(size>=1)//if the size count is greater than 0
            {
                printf(BOLD"\n*************CONTACT FOUND*************\n"RESET);//prompt message of contact is found
                printf("------------------------------------------------------------------------------\n");
                printf("| %-5s | %-20s | %-15s | %-25s |\n","SL.no","Name","PhoneNo.","Email id.");
                printf("------------------------------------------------------------------------------\n");
                for(int k=0;k<size;k++)
                {
                    printf("| %-5d | %-20s | %-15s | %-25s |\n",k+1,addressBook->contacts[arr[k]].name,addressBook->contacts[arr[k]].phone,addressBook->contacts[arr[k]].email);
                }
                printf("------------------------------------------------------------------------------\n");
            }
            else 
            {
              printf(BOLD"\n**********CONTACT NOT FOUND**********\n"RESET);  //if not found that contact
            }
        break;
        }
        case 2:  //search by phone number
        {
            getchar();//clear the input buffer
            printf("Enter the phone number: "); //prompt message
            scanf("%s",phone);  //read a phone number from the user to be searched
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strcmp(phone,addressBook->contacts[i].phone)==0)  //compare the two string
                {
                    flag=1;//if contact is found
                   printf("\n*************CONTACT FOUND*************\n");//prompt message to the user
                   printf("----------------------------------------------------------------------\n");
                   printf("| %-20s | %-15s | %-25s |\n","Name","PhoneNo.","Email id.");
                   printf("----------------------------------------------------------------------\n");                   
                   printf("| %-20s | %-15s | %-25s |\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                   printf("----------------------------------------------------------------------\n");
                }  
            }
            if(flag==0)//if no contact is found
            printf(BOLD"\n*************CONTACT NOT FOUND*************\n"RESET);
        break;
        }
        case 3: //search by email id
        {
            getchar();  //clear the input buffer
            printf("Enter the email id : ");
            scanf("%s",email);  //read email id from the user
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strcmp(email,addressBook->contacts[i].email)==0)//compare the two string
                     
                {
                    flag=1; //if contact is found
                   printf(BOLD"\n*************CONTACT FOUND*************\n"RESET);  //prompt message to the user
                   printf("----------------------------------------------------------------------\n");
                   printf("| %-20s | %-15s | %-25s |\n","Name","PhoneNo.","Email id.");
                   printf("----------------------------------------------------------------------\n");                   
                   printf("| %-20s | %-15s | %-25s |\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                   printf("----------------------------------------------------------------------\n");                
                }  
            }
            if(flag==0)   //if not found a contact
            printf("\n*************CONTACT NOT FOUND*************\n");
        break;
        }
        case 4: //exit from the search
        {
            printf(BOLD"Redirecting to main menu...\n\n"RESET);// exit message
            return 0;
        }
        default:
        {
            printf("Enter a valid selection\n");
            while(getchar()!='\n');
            //fflush(stdout);
        }
    }
}while(1);// Infinite loop to keeps running until select a valid selection
}
//function for edit contact//
int editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int choice,flag=0;
    char name[30];         //declaring strings for new name
    char phone[11];        //declaring strings for new phone number
    char email[40];        //declaring strings for new email id
do
{
    na://label
    ph://label
    em://label
    printf(BOLD"\nChoose an option to search for edit : \n"RESET);  //prompt message
    printf("\n");
    printf("1. Search by Name\n");
    printf("2. Search by Phone Number\n");
    printf("3. Search by Email Address\n");
    printf("4. Exit from Edit\n");
    scanf("%d",&choice);  //read a option from the user
    int arr[40];           //array to store the index of occurance 
    int size=0;
    int i,serial;
    switch(choice)
    {
        case 1:      //search by name for edit
        {
            getchar();
            printf("Enter the name: ");
            scanf(" %[^\n]",name);  //read the name to be edited from the user
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strcasestr(addressBook->contacts[i].name,name)!=NULL)  //compare the name entered by the user within the struture array
                {
                   arr[size]=i;   //store that index to the array
                   size++;  //increment the contact counter
                }         
            }
            if(size>=1)//if size is greater than 0,contact found
            {
                printf("\n*************CONTACT FOUND*************\n");  //prompt message
                 printf("------------------------------------------------------------------------------\n");
                printf("| %-5s | %-20s | %-15s | %-25s |\n","SL.no","Name","PhoneNo.","Email id.");
                printf("------------------------------------------------------------------------------\n");
                for(int k=0;k<size;k++)
                {
                    printf("| %-5d | %-20s | %-15s | %-25s |\n",k+1,addressBook->contacts[arr[k]].name,addressBook->contacts[arr[k]].phone,addressBook->contacts[arr[k]].email);
                }
                printf("------------------------------------------------------------------------------\n");
                do
                {
                    printf("\nSelect the serial number you want to edit : ");
                    scanf("%d",&serial);    //read a serial number which user want to edit
                    if(serial>size||serial<1)  //if the entered serial number is not in the range
                    {
                        printf("\nPlease enter a valid selection\n");    //invalid ,prompt message
                        while(getchar()!='\n');
                    }
                }while(serial>size||serial<1); //for the run the loop infinitly untill user enter a valid serial number
                 char m;
                do
                {
                    g:  //label
                    printf("\nENTER THE OPTION YOU WANT TO EDIT : \n");//prompt message
                    printf("1. Edit by Name\n");
                    printf("2. Edit by Phone Number\n");
                    printf("3. Edit by Email Address\n");
                    printf("4. Exit Editing this Contact\n");
                    int option,i;
                    scanf("%d",&option);  //read a option from the user
                    switch(option)
                    { 
                        case 1:  //edit by name
                      {
                        char new_name[40];
                        a1:
                        printf("Enter the new name : ");
                        getchar(); //clear the input buffer
                        scanf("%[^\n]",new_name);  //read a new name from the user to replace the old one
                         if(validate_name(new_name))  //validate the new name
                            {
                                strcpy(addressBook->contacts[arr[serial-1]].name,new_name);//copy the new name
                                printf("\nContact updated successfully!\n");//success message
                                printf("\n");
                            }
                            else{
                                printf("\nPLEASE ENTER A VALID NAME\n");//invalid prompt message
                                goto a1;//goto label a1
                            }                       
                         break;
                      }
                        case 2: //edit by number
                        {
                             char new_number[20];
                             p://label
                            printf("\nEnter the new mobile number : ");
                            scanf("%s",new_number);//read a new phone number from the user to replace the old one
                            if(validate_phone(new_number,addressBook)) //validate the new phone number
                            {
                            strcpy(addressBook->contacts[arr[serial-1]].phone,new_number);//copy the new phone number
                            printf("\nContact updated successfully!\n");//success message
                            }
                            else{
                                printf("\nPLEASE ENTER A UNIQUE AND VALID PHONE NUMBER\n");//invalid prompt message
                                goto p;  //goto to the label to re enter the mobile number again
                            }
                            break;
                        }
                        case 3:
                        {
                            char new_mail[20];//edit by email
                            q://label
                             printf("\nEnter the new mail id : ");
                             scanf("%s",new_mail);//read a new mail id from the user to replace the old one
                             if(validate_email(new_mail,addressBook))//validate the new email id
                             {
                                strcpy(addressBook->contacts[arr[serial-1]].email,new_mail);//copy the new email id
                                printf("\nContact updated successfully!\n");//success message
                                printf("\n");
                             }
                             else{
                                printf("\nPLEASE ENTER A VALID EMAIL ID\n");
                                goto q;//goto to the label to re enter the email id again
                             }
                 
                            break;
                        }
                        case 4:
                        {
                            printf("\nExiting edit for this contact.\n");
                            goto na;//goto label 
                            return 0;
                            break;
                        }
                        default:
                        {
                            printf("\nInvalid selection \n");//invalid prompt message
                            while(getchar()!='\n');
                            goto g;//goto g label to re enter a valid selection
                            break;
                        }
                    }
                    printf("Do you want to edit this same contact again? (Y/N)");//edit the same contact again
                    getchar();  //clear the input buffer
                    scanf("%c",&m);//read y or n from the user
                }while(m=='Y'||m=='y');//infinite loop untill a break is executed
            }
            else 
            {
              printf("\n**********CONTACT NOT FOUND**********\n");  
            }
            
        break;
        }
        case 2:
        {   
            getchar();
            printf("Enter the phone number: ");
            scanf("%s",phone); //search by phone number for edit
            char m;
            for(i=0;i<addressBook->contactCount;i++)
            {
                if(strcmp(phone,addressBook->contacts[i].phone)==0) //compare the entered phone by the user within the structure array            
                {
                    flag=1;//contact is found
                    printf("\n***************CONTACT FOUND***************\n");//prompt message
                   printf("----------------------------------------------------------------------\n");
                   printf("| %-20s | %-15s | %-25s |\n","Name","PhoneNo.","Email id.");
                   printf("----------------------------------------------------------------------\n");                   
                   printf("| %-20s | %-15s | %-25s |\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                   printf("----------------------------------------------------------------------\n");                
                    do
                    { 
                        h://label
                        printf("\nENTER THE OPTION YOU WANT TO EDIT : \n");
                        printf("1. Edit by Name\n");
                        printf("2. Edit by Phone Number\n");
                        printf("3. Edit by Email Address\n");
                        printf("4. Exit Editing this Contact \n");
                        int option;
                        scanf("%d",&option);//read the option from the user
                        switch(option)
                        { 
                            case 1:  //edit by name
                            {
                                char new_name[40];
                                a2:  //label
                                printf("Enter the new name : ");
                                getchar(); //clear the input buffer
                                scanf("%[^\n]",new_name);//read new name from the user
                                if(validate_name(new_name))//validate the name
                                {
                                  strcpy(addressBook->contacts[i].name,new_name); //copy the new name to the old one
                                  printf("\nContact updated successfully!\n");//success message
                                }
                                else{
                                    printf("\nPLEASE ENTER A VALID NAME\n");
                                    goto a2;//goto label to re enter the new name
                                }
                                break;
                            }
                                case 2: //edit by phone number
                            {
                                char new_number[20];
                                p1://label
                                printf("\nEnter the new mobile number : ");
                                scanf("%s",new_number);//read new number from the user
                                if(validate_phone(new_number,addressBook))//validate new phone number
                                {
                                  strcpy(addressBook->contacts[i].phone,new_number);//copy the new number to the old one
                                  printf("\nContact updated successfully!\n");//success message
                                }
                                else
                                {
                                printf("\nPLEASE ENTER A UNIQUE AND VALID PHONE NUMBER\n");
                                goto p1;//goto label to re enter the new phone number
                               }
                                break;
                            }
                                case 3:
                            {
                                char new_mail[20];
                                p4://label
                                printf("\nEnter the new mail id : ");
                                scanf("%s",new_mail);//read new mail id from the user
                                if(validate_email(new_mail,addressBook))//validate the new mail id
                                {
                                  strcpy(addressBook->contacts[i].email,new_mail);//copy the new mail id to the old one
                                  printf("\nContact updated successfully!\n");
                                }
                                else{
                                printf("\nPLEASE ENTER A VALID EMAIL ID\n");
                                goto p4;//goto label to re enter the new email id
                            }
                                break;
                            }
                                case 4:
                            {
                                printf("\nExiting edit for this contact.\n");//prompt message
                                goto ph;//goto label to ph
                                return 0;
                                break;
                            }
                            default:
                            {
                                printf("\nInvalid selection \n");//invalid message
                                while(getchar()!='\n');
                                goto h;//goto h label re enter the selection again
                                break;
                            }
                        }
                        printf("Do you want to edit this same contact again? (Y/N)");
                        getchar();//clear the input buffer
                        scanf("%c",&m);//read y or n from the user
                    } while(m=='y'||m=='Y'); //infinite loop untill a break is executed
                } 
            }
            if(flag==0)//contact is not found
            {
            printf("\n**********CONTACT NOT FOUND**********\n");
             break;
            }
            break;
        }
        case 3://search by email for edit
        {
            getchar();//clear the input buffer
            printf("Enter the email id : ");
            scanf("%s",email);//read the mail id
            char m;
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strcmp(email,addressBook->contacts[i].email)==0)    //compare the entered mail id is present within the struture array      
                {
                    flag=1;//if a contact is found,make the flag variable as 1 
                   printf("\n**********CONTACT FOUND**********\n");//prompt message
                   printf("----------------------------------------------------------------------\n");
                   printf("| %-20s | %-15s | %-25s |\n","Name","PhoneNo.","Email id.");
                   printf("----------------------------------------------------------------------\n");                   
                   printf("| %-20s | %-15s | %-25s |\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                   printf("----------------------------------------------------------------------\n");                
                    do
                    {
                        k: //label
                    printf("ENTER THE OPTION YOU WANT TO EDIT : \n");
                    printf("1. Edit by Name\n");
                    printf("2. Edit by Phone Number\n");
                    printf("3. Edit by Email Address\n");
                    printf("4. Exit Editing this Contact\n");
                    int option;
                    scanf("%d",&option);//read option from the user
                    switch(option)
                 {  
                    case 1://edit by name
                    {
                        char new_name[40];
                        a3://label
                        printf("Enter the new name : ");
                        getchar();//clear the input buffer
                        scanf("%[^\n]",new_name);//read a new name from the user
                        if(validate_name(new_name))//validate the new name
                        {
                            strcpy(addressBook->contacts[i].name,new_name);//copy the new name to the old one
                            printf("\nContact updated successfully!\n");//success message
                        }
                        else
                        {
                            printf("\nPLEASE ENTER A VALID NAME\n");//invalid message
                            goto a3;//goto label a3 to re enter the new name again
                        }
                        break;
                    }
                    case 2://edit by number
                    {
                        char new_number[20];
                        p2://label
                        printf("\nEnter the new mobile number : ");
                        scanf("%s",new_number);//read a new number from the user
                        if(validate_phone(new_number,addressBook))//validate the new number
                        {
                            strcpy(addressBook->contacts[i].phone,new_number);//copy the new number to the old one
                            printf("\nContact updated successfully!\n");//success message
                        }
                        else{
                                printf("\nPLEASE ENTER A UNIQUE AND VALID PHONE NUMBER\n");//invalid message
                                goto p2;//goto label p2 to re enter the new number again
                            }
                        break;
                    }
                    case 3://edit by mail id
                    {
                        char new_mail[20];
                        p3://label
                        printf("\nEnter the new mail id : ");
                        scanf("%s",new_mail);//read a new mail id from the user
                        if(validate_email(new_mail,addressBook))//validate the new mail
                        {
                            strcpy(addressBook->contacts[i].email,new_mail);//copy the new mail to the old one
                             printf("\nContact updated successfully!\n");//success message
                        }
                        else{
                            printf("\nPLEASE ENTER A VALID EMAIL ID\n");//invalid message 
                            goto p3;//goto label p3 to re enter the new email id again
                        }
                        break;
                    }
                    case 4:
                    {
                        printf("\nExiting edit for this contact.\n");//exit
                        goto em;//goto label em for editing another contact
                        return 0;
                        break;
                    }
                    default: {
                        printf("\n!.. Invalid selection ..!\n");//invalid message
                        goto k;//goto label k to re enter the valid option
                        break;
                    }
                 }
                     printf("Do you want to edit this same contact again? (Y/N)");
                     getchar();//clear the input buffer
                    scanf("%c",&m);//read y or n from the user
                  }while(m=='y'||m=='Y');//infinite loop untill a break is executed
                }  
            }
            if(flag==0)//flag is 0 ,if the contact is not found
            printf("\n**********CONTACT NOT FOUND**********\n");
        break;
        }
        case 4: 
        {
            printf("\nExisting form Editing....\n");
            return 0;
        }
        default:
        {   
            printf("\nEnter a valid selection\n");
            while(getchar()!='\n');
        }
    }
}while(1);//infinite loop untill a break is executed
}
    //function to delete contact
int deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */

    int choice,i,k;  //declaration
    int num;        
    char c;
    char name[30];  //declare string for new name
    char phone[11];  //declare string for new phone
    char email[40];  //declare string for new email
do
{
    printf("Enter search by : \n");  //message prompt for the user
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("4. Exit\n");
    scanf("%d",&choice);
    switch(choice)  //switch case
    {
        case 1://search by name to delete contact
        {
            int flag=0;
            int arr[40];  //declare an array to store the occurance of contact
            int size=0;
            getchar();  //clear the input buffer
            printf("Enter the name: ");
            scanf(" %[^\n]",name); //read name to be deleted from the user
            for(i=0;i<addressBook->contactCount;i++)
            {
                if(strcasestr(addressBook->contacts[i].name,name)!=NULL) //check the name is present in the struture array   
                {
                   arr[size]=i;  //copy the index value to the array
                   size++;//increment the size counter
                }         
            }
            if(size>=1)   //contact is found
            {
                printf("\n**********CONTACT FOUND**********\n");
                printf("------------------------------------------------------------------------------\n");
                printf("| %-5s | %-20s | %-15s | %-25s |\n","SL.NO","Name","PhoneNo.","Email id.");
                printf("------------------------------------------------------------------------------\n");
                for(k=0;k<size;k++)
                {
                    printf("| %-5d | %-20s | %-15s | %-25s |\n",k+1,addressBook->contacts[arr[k]].name,addressBook->contacts[arr[k]].phone,addressBook->contacts[arr[k]].email);
                }
                printf("------------------------------------------------------------------------------\n");
                 
                 do{
                printf("Selected the serial number of contact to DELETE: ");
                scanf("%d",&num);  //read a serial number to be edited from the user
                if(num<=0||num>size)//check the user entered serial number is belongs to the range
                {
                    printf("\n--Enter a valid SL.No--\n");
                    while(getchar()!='\n');
                }
                }while(num<=0||num>size);//make the loop run untill you enter a valid serial number
                printf("Do you want to delete... (Y/N)");//confirmation prompt message
                getchar();//clear the input buffer
                scanf(" %c",&c);//read y or n from the user
                if(c=='Y'||c=='y')//if y is enter
                {
                  for(k=arr[num-1];k<addressBook->contactCount;k++)
                    {
                      addressBook->contacts[k]=addressBook->contacts[k+1];//shifting one place left for performing deletion
                
                    }
                    addressBook->contactCount--;//decrementing the contact count
                    printf("\nContact deleted successfully\n");//delete success message
                }
                
                else
                {
                      printf("\nDeletion canceled.\n");
                }
                break;      
            }
            else 
            {
              printf("\n**********CONTACT NOT FOUND**********\n");  
            }
        break;
        }
        case 2:  //search by phone number to delete the contact
        {
            int flag=0;
            getchar();  //clear the input buffer
            printf("Enter the phone number: ");
            scanf("%s",phone);  //read phone number from the user
            int s=0; 
            for(i=0;i<addressBook->contactCount;i++)
            {
                if(strcmp(phone,addressBook->contacts[i].phone)==0) //check the user entered number is present in addressbook
                     
                {
                    flag=1;
                    s=i;//copy the i value to s
                   printf("\n*************CONTACT FOUND*************\n"); 
                   printf("----------------------------------------------------------------------\n");
                   printf("| %-20s | %-15s | %-25s |\n","Name","PhoneNo.","Email id.");
                   printf("----------------------------------------------------------------------\n");                   
                   printf("| %-20s | %-15s | %-25s |\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                   printf("----------------------------------------------------------------------\n");                
                    break;
                }         
            }
                if(flag==0)//no contact is found
                {
                 printf("\n*************CONTACT NOT FOUND*************\n");
                 break;
                }    
              printf("Do you want to delete... (Y/N)");
                getchar();//clear the input buffer
                scanf(" %c",&c);//read y or n from the user
                if(c=='Y'||c=='y')//if user is input y
                {
                for(k=s;k<addressBook->contactCount;k++)//for loop
                {
                addressBook->contacts[k]=addressBook->contacts[k+1];//shifting one place left for performing deletion
                }
                addressBook->contactCount--;  //decrementing the contact count
                printf("\nContact deleted successfully\n");
              }  
                else
                {
                      printf("\nDeletion canceled.\n");//cancellation message
                }
                break;    
        }
        case 3: //search by email to delete the contact
        {
            int flag=0;
            getchar();//clear the input buffer
            printf("Enter the email id : ");
            scanf("%s",email); //read email from the user
            int s;
            for(i=0;i<addressBook->contactCount;i++)
            {
                if(strcmp(email,addressBook->contacts[i].email)==0) //check the user entered number is present in addressbook          
                {
                    flag=1;
                    s=i;  //copy the index value to variable s
                   printf("\n*************CONTACT FOUND*************\n");
                    
                   printf("----------------------------------------------------------------------\n");
                   printf("| %-20s | %-15s | %-25s |\n","Name","PhoneNo.","Email id.");
                   printf("----------------------------------------------------------------------\n");                   
                   printf("| %-20s | %-15s | %-25s |\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                   printf("----------------------------------------------------------------------\n");                
                }  
            }  
             if(flag==0)//if not found
             {
             printf("\n*************CONTACT NOT FOUND*************\n");
             }
             else
             {
                printf("Do you want to delete... (Y/N)");  //confirmation message 
                getchar();
                scanf(" %c",&c);//read y or n from the user
                if(c=='Y'||c=='y')  //if user input is y
                {
                for(k=s;k<addressBook->contactCount;k++)//for loop
                {
                addressBook->contacts[k]=addressBook->contacts[k+1];//shifting one place left for performing deletion
                }
                addressBook->contactCount--;//decrementing the contact count
                printf("\nContact deleted successfully\n");
                }
                else
                {
                      printf("\nDeletion canceled.\n");
                }
             }
         break;
        }
        case 4:   //exit from delete
        {
            return 0;
        }
        default:
        {
            printf("\nEnter a valid selection\n");
            while(getchar()!='\n');
        }
    }
  }while(1);
}

//function for name validation
int validate_name(char name[])
{
    int i=0;
    if (strlen(name) < 3)//check the name entered has contain greater than 3 character
        return 0;
    while(name[i]!='\0')
    {
       if(!((name[i]>='a'&&name[i]<='z')||(name[i]>='A'&&name[i]<='Z')||(name[i]==' ')))//the name must contain only uppercase,lowercase or space
       {
        printf("---INVALID NAME---The name must contain uppercase,lowercase and space\n");
        return 0;//invalid character found
       }
       i++;//move to next character
    }
    return 1;
}
//function for phone validation
int validate_phone(char phone[],AddressBook *addressBook)
{
    int i=0,j=0;
    if(!((strlen(phone)==10)&&(phone[0]>='6'&&phone[0]<='9')))//check the number has 10 digits and start with 6,7,8,9
    {
    printf("Invalid Number\nPLEASE ENTER A 10 DIGIT NUMBER STARTING WITH 6,7,8,9\n");
        return 0;//invalid number
    }
    for(j=0;j<addressBook->contactCount;j++)//for loop
    {
    if(strcmp(phone,addressBook->contacts[j].phone)==0)//check the number is already exist in the contacts
    {
        printf("\nNumber already exist\n");//already exist prompt message
         return 0;
    }
   
    }
    while(phone[i]!='\0')//while loop
    {
        if(!(phone[i]>='0'&&phone[i]<='9'))//check the number should contain only digits
        {
            printf("Invalid Number\nPHONE NUMBER SHOULD BE CONTAIN ONLY DIGITS\n");//invalid prompt message
            return 0;
        }
        i++;
    }
    return 1;//valid
}
//function for email validation
    int validate_email(char email[],AddressBook *addressBook)
     {
    int at=0;                              // position of '@'
    int dot=0;                             // position of '.'
    int count=0;                          
    for(int i=0;email[i]!='\0';i++)//loop
    {
        if(email[i] == '@')                 //validating @ is present in email id
        {                             
            at = i;                        //if present copy that position to a variable
            count++;
        }
        if(email[i] == '.')             //validating . is present in email id
        {
            dot = i;                    //if present copy that index position to the dot variable
            count++;
        }
        else if(email[i]=='@' && email[i+1]=='.')//checking for character present between the @ and .
        {
            printf("There should be something between @ and . \n");
            return 0; //invalid
        }         
    }
    for(int i=at+1;i<dot;i++)
    {
        if(!(email[i]>='a' && email[i]<='z'))  //also check the character present between the @ and .
        {
            printf("only lowercase alphabets are permitted between @ and . \n");//invalid prompt message
            return 0;//invalid
        }
       
    }
    if(at > 0 && dot > at && dot < strlen(email) - 1 && count == 2)//check the @ and . are present pn;y once and . will be present after @
    {
        if(!(email[0] >= 'a' && email[0] <= 'z'))//check the first letter is lower case or not
        {
            printf("INVALID!!..First letter should be lower case alphabet\n");
            return 0;
        }
        return 1;
    } 
    else if(count>2)//check multiple occurence of @ and .
    {
        printf("\nINVALID!!..Multiple @ or . character is found\n");
        return 0;//invalid
    } 
    return 0;
    
}