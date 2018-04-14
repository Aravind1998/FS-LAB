#include <iostream>
#include<fstream>
#include<string.h>
#include <sstream>
#include <cstring>
#include <bits/stdc++.h>
using namespace std;

class Student {
    char usn[11],name[20],age[3];
    int n;
  public:
    string pack();
    void add();
    void unpack(char[]);
    void search();
    void modify();
};
void Student::unpack(char str[]){
    char *token = strtok(str, "|");
    strcpy(usn,token);
    token = strtok(NULL, "|");
    strcpy(name,token);
    token = strtok(NULL, "#");
    strcpy(age,token);
}
string Student::pack() {
  string finalstr="";
  finalstr = usn;
  finalstr = finalstr + "|" + string(name) + "|" + string(age) +"#";
  cout<<finalstr<<endl;
  return finalstr;
}
void Student :: add () {
   cout<<"Enter the number of Students you would like to enter : ";
   cin>>n;
   fstream myfile;
   myfile.open("studentdb.txt",ios::app);
   for(int i=0;i<n;i++) {
      cout<<"Enter USN of the Student : ";
      cin>>usn;
      cout<<"Enter Name : ";
      cin>>name;
      cout<<"Enter Age : ";
      cin>>age;
      string final = pack();
      myfile << final <<endl;
   }
   myfile.close();
}
void Student::search() {
  char key[11];
  char input[35];
  int flag=0;
  cout<<"Enter the USN to find : ";
  cin>>key;
  ifstream myfile;
  myfile.open("studentdb.txt",ios::in);
  while(!myfile.eof()) {
      myfile >> input;
      if( myfile.eof() ){
        flag=1;
        break;
      }
      unpack(input);
      if(string(key)==string(usn)){
          cout<<"\nRECORD FOUND !!"<<endl;
          cout<<"USN  : "<<usn<<endl;
          cout<<"NAME : "<<name<<endl;
          cout<<"AGE  : "<<age<<endl<<endl;
          break;
      }
   }
   if(flag==1) {
      cout<<"\nERROR : NO RECORD FOUND !!"<<endl<<endl;
   }
   myfile.close();
}
void Student::modify() {
   char key[11];
   char input[35];
   int flag=0;
   cout<<"Which record would you like to modify ? Enter USN : ";
   cin>>key;
   fstream myfile;
   myfile.open("studentdb.txt",ios::in);
   while(!myfile.eof()) {
      myfile >> input;
      if( myfile.eof() ){
        flag=1;
        break;
      }
      unpack(input);
      if(string(key)==string(usn)){
          cout<<"\n- RECORD DETAILS - "<<endl;
          cout<<"USN  : "<<usn<<endl;
          cout<<"NAME : "<<name<<endl;
          cout<<"AGE  : "<<age<<endl<<endl;
          break;
      }
   }
   if(flag==1) {
      cout<<"\neRROR : NO RECORD FOUND !!"<<endl<<endl;
      return;
   }
   cout<<"ENTER NEW DATA "<<endl;
   cout<<"Enter USN of the Student : ";
   cin>>usn;
   cout<<"Enter Name : ";
   cin>>name;
   cout<<"Enter Age : ";
   cin>>age;

}
int main () {   
  Student stu;
  int choice;
  while(true) {
      cout<<"1.Enter Records\n2.Modify Records\n3.Search Records\n4.Exit\nEnter your choice : ";
      cin>>choice;
      switch(choice) {
          case 1 : stu.add(); 
                   break;
          case 2 : stu.modify();
                   break;
          case 3 : stu.search();
                   break;
          case 4 : exit(1);
                   break;
          default : cout<<"Wrong Choice"<<endl;
      }
  }
  return 0;
}

