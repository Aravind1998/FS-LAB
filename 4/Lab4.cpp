#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

using namespace std;

int r2a_map[20], rrn_counter = 0;

class Student{
	private:
		char rrn[3], usn[11], name[21], age[3], buffer[37];
	public:
		Student(){
			char buf[40];
			fstream f;
			f.open("student.txt", ios::in | ios::out);
			f.getline(buf, sizeof(buf), '#');
			while(!f.fail()){
				r2a_map[rrn_counter++] = (int )f.tellg() - strlen(buf) - 1;
				f.getline(buf, sizeof(buf), '#');
			}
		}
		void pack();
		void unpack();
		void display();
		void search(int r, int );
		int displayAll();
		void read();
		void addRecord();
};

void Student::pack(){
	strcpy(buffer, rrn);
	strcat(buffer, "|");
	strcat(buffer, usn);
	strcat(buffer, "|");
	strcat(buffer, name);
	strcat(buffer, "|");
	strcat(buffer, age);
	strcat(buffer, "#");
}

void Student::unpack(){
	strcpy(rrn, strtok(buffer, "|"));
	strcpy(usn, strtok(NULL, "|"));
	strcpy(name, strtok(NULL, "|"));
	strcpy(age, strtok(NULL, "#"));
}

void Student::display(){
	cout << "  RRN: " << rrn << endl;
	cout << "  USN: " << usn << endl;
	cout << "  Name: " << name << endl;
	cout << "  Age: " << age << endl;
}

void Student::search(int r, int mode = 0){
	if(r >= rrn_counter){
		cout << "\nRecord Not Present\n";
		return ;
	}
	ifstream f;
	f.open("student.txt");
	f.seekg(r2a_map[r], ios::beg);
	f.getline(buffer, sizeof(buffer), '#');
	unpack();
	if(mode == 0){
		cout << "\nRecord Found\n\nRecord Details:-\n";
	}
	display();
	f.close();
}

int Student::displayAll(){
	int s_count = 0;
	while(s_count < rrn_counter){
		if(s_count < 1)
			cout << "\nRecords Present in File\n";
		cout << "\n Student " << s_count + 1 << ":-\n";
		search(s_count++, 1);
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

char* conv(int num){
	int n = num;
	int d_count = 0;
	do{
		n = n / 10;
		d_count++;
	}while(n > 0);
	char *s_num = new char[d_count + 1];
	n = num;
	s_num[d_count--] = '\0';
	do{
		int d = n % 10;
		n = n/10;
		s_num[d_count--] = (char )(d + 48);
	}while(n > 0);
	return s_num;
}

void Student::addRecord(){
	fstream f;
	f.open("student.txt", ios::in | ios::out | ios::ate);
	read();
	strcpy(rrn, conv(rrn_counter));
	r2a_map[rrn_counter++] = (int )f.tellg();
	pack();
	f.write(buffer, strlen(buffer));
}

int main(){
	int choice;
	Student s;
	int rrn;
	while(true){
		cout << "\nMENU:\n1  Add Record\n2  Show Records\n3  Search Record\n";
		cout << "4  Exit\n\nYour Choice: ";
		cin >> choice;
		switch(choice){
			case 1: cout << "\nProvide Following Student Details:-\n";
				s.addRecord();
				break;

			case 2: if(s.displayAll() == 0)
					cout << "\nStudent File is Empty\n";
				break;

			case 3: cout << "\nEnter RRN to Search: ";
				cin >> rrn;
				s.search(rrn);
				break;

			case 4: cout << "\nUntil next time!\n";
				exit(0);
				break;

			default: cout << "\nInvalid Input!\nTry Again.\n";
		}
	}
	return 0;
}
