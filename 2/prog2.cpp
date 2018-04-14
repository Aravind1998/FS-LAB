#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>

using namespace std;

class Student{
	private:
		char usn[10], name[20], age[2], buffer[35];

		void pack();
		void unpack();
		void read();

	public:
		void addRecord();
		void display();
		bool displayAll();
		int search(char [], int );
		void modify(char []);
};

void Student::pack(){
	strcpy(buffer, usn);
	strcat(buffer, "|");
	strcat(buffer, name);
	strcat(buffer, "|");
	strcat(buffer, age);
	for(int i = strlen(buffer); i < 35; i++)
		buffer[i] = '#';
}

void Student::unpack(){
	strcpy(usn, strtok(buffer, "|"));
	strcpy(name, strtok(NULL, "|"));
	strcpy(age, strtok(NULL, "#"));
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
	f.open("student.txt", ios::in|ios::out|ios::ate);
	read();
	pack();
	f.write(buffer, sizeof(buffer));
	f.close();
}

void Student::display(){
	cout << "Enter the USN: " << usn << endl;
	cout << "Enter the Name: " << name << endl;
	cout << "Enter the Age: " << age << endl;
}

bool Student::displayAll(){
	ifstream f;
	f.open("student.txt");
	bool flag = false;
	int s_count = 1;
	while(!f.eof()){
		f.read(buffer, sizeof(buffer));
		if(f.fail())
			break;
		if(flag == false)
			cout << "\nThe contents of the Student File\n";
		unpack();
		cout << "\n Studuent " << s_count++ << ":-\n";
		display();
		flag = true;
	}
	f.close();
	return flag;
}

int Student::search(char u[], int mode = 0){
	ifstream f;
	f.open("student.txt");
	int index = -1, count = 0;
	while(!f.eof()){
		f.read(buffer, sizeof(buffer));
		if(f.fail())
			break;
		unpack();
		if(strcmp(u, usn) == 0){
			if(mode == 0){
				cout << "\nStudent Record Found\n";
				display();
			}
			index = count;
			break;
		}
		count++;
	}
	f.close();
	return index;
}

void Student::modify(char u[]){
	fstream f;
	f.open("student.txt", ios::in | ios::out);
	int index = search(u, 1);
	if(index == -1){
		cout << "\nRecord Not Available\n";
		return ;
	}
	cout << "\nEnter Updated Student Details:-\n";
	read();
	f.seekp(index * sizeof(buffer), ios::beg);
	pack();
	f.write(buffer, sizeof(buffer));
	cout << "\nRecord Updated Successfully\n";
	f.close();
}

int main(){
	int choice;
	char usn[10];
	Student s;
	while(true){
		cout << "\nMENU:\n1  Add Record\n2  Show Records\n3  Search Record\n";
		cout << "4  Modify Record\n5  Exit\n\nYour Choice: ";
		cin >> choice;
		switch(choice){
			case 1: cout << "\nInput Student Details:-\n";
				s.addRecord();
				break;

			case 2: if(!s.displayAll())
					cout << "\nStudent File is Empty\n";
				break;

			case 3: cout << "\nEnter the USN to be searched ";
				cin >> usn;
				if(s.search(usn) == -1){
					cout << "\nThe record is not available\n";
				}
				break;

			case 4: cout << "\nEnter the USN to modify the specified record: ";
				cin >> usn;
				s.modify(usn);
				break;

			case 5: cout << "\nTHE END\n";
				exit(0);
				break;

			default: cout << "\nInvalid Input!\nPlease try again.\n";	 
		}
	}
	return 0;
}

