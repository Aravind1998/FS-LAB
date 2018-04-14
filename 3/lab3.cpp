#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

using namespace std;

class Student{
	private:
		char usn[11], name[21], age[3], buffer[37];
		fstream f;

	public:
		void pack();
		void unpack();
		void display();
		int displayAll();
		void read();
		void addRecord();
		void modify(char u[]);
		int search(char u[], int );
};

void Student::pack(){
	strcpy(buffer, usn);
	strcat(buffer, "|");
	strcat(buffer, name);
	strcat(buffer, "|");
	strcat(buffer, age);
	strcat(buffer, "#");
}

void Student::unpack(){
	strcpy(usn, strtok(buffer, "|"));
	strcpy(name, strtok(NULL, "|"));
	strcpy(age, strtok(NULL, "#"));
}

void Student::display(){
	cout << "  USN: " << usn << endl;
	cout << "  Name: " << name << endl;
	cout << "  Age: " << age << endl;
}

int Student::displayAll(){
	ifstream f;
	f.open("student.txt");
	int s_count = 0;
	while(!f.eof()){
		f.getline(buffer, sizeof(buffer), '#');
		if(f.fail())
			break;
		unpack();
		if(s_count < 1)
			cout << "\nRecords Present in File\n";
		cout << "\n Student " << ++s_count << ":-\n";
		display();
	}
	return s_count;
}

void Student::read(){
	cout << " USN: ";
	cin >> usn;
	cout << " Name: ";
	cin >> name;
	cout << " Age: ";
	cin >> age;
}

void Student::addRecord(){
	fstream f;
	f.open("student.txt", ios::in | ios::out | ios::ate);
	read();
	pack();
	f.write(buffer, strlen(buffer));
}

int Student::search(char u[], int mode = 0){
	ifstream f;
	f.open("student.txt");
	int index = -1, pos = 0, b_len;
	while(!f.eof()){
		f.getline(buffer, sizeof(buffer), '#');
		if(f.fail())
			break;
		pos += b_len = (strlen(buffer) + 1);
		unpack();
		if(strcmp(u, usn) == 0){
			index = pos - b_len;
			if(mode == 0){
				cout << "\nRecord Found\n\nRecord Details:-\n";
				display();
			}
			break;
		}
	}
	f.close();
	return index;
}

void Student::modify(char u[]){
	fstream fin;
	fin.open("student.txt", ios::in);
	int index = search(u, 1);
	if(index == -1){
		cout << "\nRecord Not Present\n";
		return ;
	}
	cout << "\nEnter Updated Details:-\n";
	read();
	pack();
	fstream fout;
	fout.open("tempStudent.txt", ios::out);
	Student temp;
	while(!fin.eof()){
		if((int )fin.tellg() == index){
			fout.write(buffer, strlen(buffer));
			fin.getline(temp.buffer, sizeof(temp.buffer), '#');
		}
		else{
			fin.getline(temp.buffer, sizeof(temp.buffer), '#');
			if(fin.fail())
				break;
			strcat(temp.buffer, "#");
			fout.write(temp.buffer, strlen(temp.buffer));
		}
	}
	fin.close();
	fout.close();
	remove("student.txt");
	rename("tempStudent.txt", "student.txt");	
}

int main(){
	int choice;
	Student s;
	char u[11];
	while(true){
		cout << "\nMENU:\n1  Add Record\n2  Show Records\n3  Search Record\n";
		cout << "4  Modify Records\n5  Exit\n\nYour Choice: ";
		cin >> choice;
		switch(choice){
			case 1: cout << "\nProvide Following Student Details:-\n";
				s.addRecord();
				break;

			case 2: if(s.displayAll() == 0)
					cout << "\nStudent File is Empty\n";
				break;

			case 3: cout << "\nEnter the USN to search for the record: ";
				cin >> u;
				if(s.search(u) == -1)
					cout << "\nRecord Not Present\n";
				break;

			case 4: cout << "\nEnter the USN to modify the specified record: ";
				cin >> u;
				s.modify(u);
				break;

			case 5: cout << "\nTHE END\n";
				exit(0);
				break;

			default: cout << "\nInvalid Input!\nPlease try again.\n";
		}
	}
	return 0;
}

