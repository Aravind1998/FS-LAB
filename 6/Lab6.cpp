#include<iostream>
#include<string>
#include<fstream>
#include<stdlib.h>
using namespace std;
class student
{
	public:
		string usn, name, sem;
		void enter_data();		
		void pack();			
}s1;
struct sec_index
{
	string usn, name;
	int addr;
}i2[100], found[20];
int cnt, find_cnt;
fstream fp;
int indexnums[20];
void create_index();				
void sort_index();
void search();
void lin_search(string);
void del();
int main()
{
	int choice;
	fp.open("lol.txt", ios::out|ios::app);
	fp.close();
	create_index();	
	while(1)
	{
		cout<<"1.Add Record\n2.Search for a record\n3.Delete a record\n4.Exit\n\nEnter choice : ";
		cin>>choice;
		switch(choice)
		{
			case 1: s1.enter_data();
				fp.open("lol.txt",ios::out|ios::app);
				if(!fp)
					cout<<"Error";
				s1.pack();
				fp.close();
				break;
			case 2:	search();
				break;
			case 3: del();
				break;
			default: exit(0);
		}
	}
}
void create_index()
{
	int pos, i;
	string seg, usnbuf, namebuf;
	cnt = -1;
	fp.open("lol.txt", ios::in);
	if(!fp)
		cout<<"Error";
	while(fp)
	{
		usnbuf.erase();
		namebuf.erase();
		pos = fp.tellg();
		getline(fp, usnbuf, '|');
		getline(fp, namebuf, '|');
		getline(fp,seg);
		if(usnbuf[0] == '*'||usnbuf.length()==0||namebuf.length()==0)
			continue;
		cnt++;
		i2[cnt].usn = usnbuf;
		i2[cnt].name = namebuf;
		i2[cnt].addr = pos;
	}
	fp.close();
	sort_index();	
}
void sort_index()
{
	struct sec_index temp;	
	for(int i=0; i<=cnt; i++)
	{	
		for(int j=i+1; j<=cnt; j++)
		if(i2[i].name>i2[j].name)
		{
			temp.usn = i2[i].usn;
			temp.name = i2[i].name;
			temp.addr = i2[i].addr;
			i2[i].usn = i2[j].usn;
			i2[i].name = i2[j].name;
			i2[i].addr = i2[j].addr;
			i2[j].usn = temp.usn;
			i2[j].name = temp.name;
			i2[j].addr = temp.addr;
		}	
	}
}
void student::enter_data()
{
	cout<<"\nEnter USN: ";
	cin>>usn;
	cout<<"\nEnter Name: ";
	cin>>name;
	cout<<"\nEnter Sem: ";
	cin>>sem;
}
void student::pack()
{
	int pos = fp.tellp();
	string buf = usn + "|" + name + "|" + sem + "|";	
	fp<<buf<<endl;
	cnt++;
	i2[cnt].addr =pos;
	i2[cnt].usn = usn;
	i2[cnt].name = name;
	sort_index();
}
void lin_search(string name_search)
{
	find_cnt = 0;
	int j=0;
	for(int i = 0; i<=cnt; i++)
	{
		if(i2[i].name == name_search)
		{
			indexnums[j++]=i;
			found[find_cnt].usn = i2[i].usn;
			found[find_cnt].name = i2[i].name;
			found[find_cnt].addr = i2[i].addr;
			find_cnt++;
		} 	
	}
}
void search()
{
	string name_search, buf;
	int ch;
	cout<<"\nEnter the Name of The student to be searched : ";
	cin>>name_search;
	lin_search(name_search);
	if(find_cnt == 0)
	{
		cout<<"\nRecord Not Found!\n";
		return;
	}
	if(find_cnt == 1)
	{
		cout<<"\n1 Record Found\n";
		ch = 0;
	}
	if(find_cnt>1)
	{
		cout<<"\nMultiple Records Found!\n";
		for(int i = 0; i< find_cnt; i++)
		cout<<i<<". Usn = "<<found[i].usn<<endl;
		cout<<"\nEnter choice: ";
		cin>>ch;
		if(ch>find_cnt)
		{
			cout<<"Invalid Range\n";
			return;
		}
	}
	cout<<"\nUsn|Name|Sem"<<endl;
	fp.open("lol.txt",ios::in);
	if(!fp)
		cout<<"Error";
	fp.seekg(found[ch].addr, ios::beg);
	getline(fp,buf);
	fp.close();
	cout<<buf<<endl;
}
void del()
{
	string name_search;
	int ch;
	cout<<"\nEnter the Name of The student to be deleted : ";
	cin>>name_search;
	lin_search(name_search);
	if(find_cnt == 0)
	{
		cout<<"\nRecord Not Found!\n";
		return;
	}
	if(find_cnt == 1)
	{
		cout<<"\n1 Record Found\n";
		ch = 0;
	}
	if(find_cnt>1)
	{
		cout<<"\nMultiple Records Found!\n";
		for(int i = 0; i< find_cnt; i++)
		cout<<i<<". "<<found[i].usn<<endl;
		cout<<"\nEnter choice: \n";
		cin>>ch;
		if(ch>find_cnt)
		{
			cout<<"Invalid Range\n";
			return;
		}
	}
	cout<<"\nRecord Deleted\n\n";
	fp.open("lol.txt",ios::out|ios::in);
	if(!fp)
		cout<<"Error";
	fp.seekp(found[ch].addr, ios::beg);
	fp.put('*');
	fp.close();
	for(int i=indexnums[ch]; i<cnt;i++)
	{
		i2[i].usn = i2[i+1].usn;
		i2[i].name = i2[i+1].name;
		i2[i].addr = i2[i+1].addr;
	}
	cnt--;	
}
