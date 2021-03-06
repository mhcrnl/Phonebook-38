// READ readme.txt

#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<chrono>
#include<ctime>
#include<stdio.h>
#include<cstring>
#include<unistd.h>

using namespace std;

void create();
void view();
void search();
void delete_contact();
void initialize_time();
void insert_into_file();

struct
{
  char phone_no[20];
  char name[30];
  char email[50];
  char *create_time;
  char create_time1[30];
}contact;

fstream phonebook;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
  phonebook.open("phonebook.txt",ios::app);
  phonebook.close();
  int ch;
  while(1)
  {
    system("tput reset");
    cout<<"\n\tPHONE BOOK APP";
    cout<<"\n\n\t1.CREATE NEW CONTACT";
    cout<<"\n\t2.VIEW CONTACT";
    cout<<"\n\t3.SEARCH CONTACT";
    cout<<"\n\t4.DELETE CONTACT";
    cout<<"\n\n\tEnter your choice: ";
    cin>>ch;

    switch(ch)
    {
      case 1:create();
      break;
      case 2:view();
      break;
      case 3:search();
      break;https://github.com/Girish2015/Phonebook
      case 4:delete_contact();
      break;
      default:return 0;
    }
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void initialize_time()
{
  std::chrono::time_point<std::chrono::system_clock> t;
  t=std::chrono::system_clock::now();
  std::time_t current_time = std::chrono::system_clock::to_time_t(t);
  contact.create_time=std::ctime(&current_time);
  contact.create_time[strlen(contact.create_time)-1]='\0';
}

void insert_into_file()
{
  phonebook.open("phonebook.txt",ios::app);
  if(phonebook.fail())
    cout<<"File open FAIL!";
  char buf[500];
  sprintf(buf,"%s|%s|%s|%s|",contact.phone_no,contact.name,contact.email,contact.create_time);
  strcat(buf,"\n");
  phonebook.write(buf,strlen(buf));
  cout<<"\n\tThe contact has been created";
  cout<<"\n\n\tPress any key for menu";
  flush(cout);
  system("bash pause.sh");
  phonebook.close();
}
void create()
{
  system("tput reset");
  cout<<"\n\tEnter the contact name: ";
  cin>>contact.name;
  cout<<"\n\tEnter the contact number: ";
  cin>>contact.phone_no;
  cout<<"\n\tEnter the email ID of contact: ";
  cin>>contact.email;
  initialize_time();
  insert_into_file();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void view()
{
  system("tput reset");
  phonebook.open("phonebook.txt",ios::in);
  if(phonebook.fail())
    cout<<"File open FAIL!";
  cout<<"\n\tALL CONTACTS\n\n";
  char buf[500];
  int i=0;
  while(phonebook.getline(buf,500,'\n'))
  {
    ++i;
    sscanf(buf,"%[^|]|%[^|]|%[^|]|%[^|]",contact.phone_no,contact.name,contact.email,contact.create_time1);
    cout<<"\n"<<i<<".";
    cout<<"\tNAME : "<<contact.name;
    cout<<"\n\tPHONE NUMBER : "<<contact.phone_no;
    cout<<"\n\tE-MAIL : "<<contact.email;
    cout<<"\n\tDATE/TIME ADDED : "<<contact.create_time1;
    cout<<"\n";
  }
  cout<<"\n\tPress any key for Main Menu";
  flush(cout);
  system("bash pause.sh");
  phonebook.close();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void search()
{
  system("tput reset");
  phonebook.open("phonebook.txt",ios::in);
  if(phonebook.fail())
    cout<<"File open FAIL!";
  char key[20],buf[500],ch;
  int flag;
  cout<<"\n\tPHONEBOOK SEARCH";
  cout<<"\n\n\tEnter the Name or Phone Number: ";
  cin>>key;
  while(phonebook.getline(buf,500,'\n'))
  {
    sscanf(buf,"%[^|]|%[^|]|%[^|]|%[^|]",contact.phone_no,contact.name,contact.email,contact.create_time1);
    if(strcmp(contact.phone_no,key)==0||strcmp(contact.name,key)==0)
    {
      cout<<"\n\tNAME : "<<contact.name;
      cout<<"\n\tPHONE NUMBER : "<<contact.phone_no;
      cout<<"\n\tE-MAIL : "<<contact.email;
      cout<<"\n\tDATE/TIME ADDED : "<<contact.create_time1;
      flag=1;
      cout<<"\n\n\tEnter any key for Main Menu ";
      flush(cout);
      system("bash pause.sh;");
      break;
    }
  }
    if(flag==0)
    {
      cout<<"\n\tContact not FOUND!";
      cout<<"\n\n\tEnter any key for Main Menu ";
      flush(cout);
      system("bash pause.sh;");
    }
    phonebook.close();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void delete_contact()
{
  system("tput reset");
  phonebook.open("phonebook.txt",ios::in|ios::out);
  if(phonebook.fail())
    cout<<"File open FAIL!";
  char key[20],buf[500],ch;
  int flag =0;
  cout<<"\n\tDELETE CONTACT";
  cout<<"\n\n\tEnter the Name or Phone Number: ";
  cin>>key;
  while(phonebook.getline(buf,500,'\n'))
  {
    sscanf(buf,"%[^|]|%[^|]|%[^|]|%[^|]",contact.phone_no,contact.name,contact.email,contact.create_time1);
    if(strcmp(contact.phone_no,key)==0||strcmp(contact.name,key)==0)
    {
      cout<<"\n\tNAME : "<<contact.name;
      cout<<"\n\tPHONE NUMBER : "<<contact.phone_no;
      cout<<"\n\tE-MAIL : "<<contact.email;
      cout<<"\n\tDATE/TIME ADDED : "<<contact.create_time1;
      flag=1;
      break;
    }
  }
  phonebook.close();
  if(flag==0)
  {
    cout<<"\n\tContact not FOUND!";
    cout<<"\n\n\tEnter any key for Main Menu ";
    flush(cout);
    system("bash pause.sh;");
    return;
  }
  else
  {
    cout<<"\n\n\tDo you want this CONTACT to be DELETED ?";
    cin>>ch;
    if(ch=='y'||ch=='Y')
    {
      char cmd[100];
      sprintf(cmd,"awk -F \"|\" '!($1 == \"%s\"||$2==\"%s\")' phonebook.txt>phonebook1.txt",key,key);
      system(cmd);
      system("mv phonebook1.txt phonebook.txt");
      cout<<"\n\tDELETED!";
      cout<<"\n\n\tEnter any key for Main Menu ";
      flush(cout);
      system("bash pause.sh;");
    }
  }
}
