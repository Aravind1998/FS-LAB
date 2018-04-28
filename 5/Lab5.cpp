#include<iostream>
#include<cstring>
#include<fstream>
#include<cstdlib>

using namespace std;

class student
{
  public:
          string usn,name,sem;
          void enter_data();
          void pack();
}s1;

struct index
{
  string usn;
  int addr;
}i1[100],temp;

int cnt;
fstream fp;

void create_index();
void sort_index();
void search();
int bin_search(string);
void del();
// void error(int);

int main()
{
  int choice;
  fp.open("student.txt",ios::out|ios::app);
  fp.close();
  create_index();

  while(1)
  {
    cout << "************************************\n";
    cout <<"1.Add Record\n2.Search Record\n3.Delete Record\n4.Exit\n";
    cout << "Please Enter your choice\n";
    cout << "************************************\n";
    cin >> choice;
    switch (choice) {
      case 1: s1.enter_data();
              fp.open("student.txt",ios::out|ios::app);
              if(!fp)
                cout<<"Error";
              s1.pack();
              fp.close();
              break;

      case 2: search();
              break;
      case 3 : del();
               break;

      default : exit(0);
    }
  }
  return 0;
}

void create_index()
{
  int pos,i;
  string seg,usnbuf;
  cnt = -1;
  fp.open("student.txt",ios::in);
  if(!fp)
      cout << "Error";
  while (fp) {
      pos = fp.tellg();
      getline(fp,usnbuf,'|');
      getline(fp,seg);
      if(usnbuf[0] == '*' || usnbuf.length()==0)
      {
        continue;
      }
      cnt++;
      i1[cnt].usn = usnbuf;
      i1[cnt].addr = pos;
  }
  fp.close();
  sort_index();
}

void sort_index()
{
  for(int i=0;i<=cnt;i++)
  {
    for(int j=i+1;j<=cnt;j++)
    {
      if(i1[i].usn > i1[j].usn)
      {
        temp.usn = i1[i].usn;
        temp.addr = i1[i].addr;

        i1[i].usn = i1[j].usn;
        i1[i].addr = i1[j].addr;

        i1[j].usn = temp.usn;
        i1[j].addr = temp.addr;
      }
    }
  }
}

void student::enter_data()
{
  cout << "Enter the USN\n";
  cin >> usn;
  cout << "Enter the Name\n";
  cin >> name;
  cout << "Enter the Sem\n";
  cin >> sem;
}

void student::pack()
{
  int pos = fp.tellg();
  string buf = usn + "|" + name + "|" + sem;
  fp << buf <<endl;
  cnt++;
  i1[cnt].usn = usn;
  i1[cnt].addr = pos;
  sort_index();
}

int bin_search(string usn_search)
{
  int l=0,h=cnt,mid;
  while(l<=h)
  {
    mid = (l+h)/2;
    if(i1[mid].usn == usn_search)
      return mid;
    if(i1[mid].usn < usn_search)
      l = mid+1;
    if(i1[mid].usn > usn_search)
      h = mid-1;
  }
  return -1;
}

void search()
{
  string usn_search,buf;
  cout << "Enter USN of student to be searched\n";
  cin >> usn_search;
  int pos = bin_search(usn_search);
  if(pos == -1)
  {
    cout << "Record not found\n";
    return;
  }
  cout << "Record found\n";
  cout << "USN|NAME|SEM"<<endl;
  fp.open("student.txt",ios::in);
  if(!fp)
    cout << "Error";
  fp.seekg(i1[pos].addr,ios::beg);
  getline(fp,buf);
  fp.close();
  cout << buf << endl;
}

void del()
{
  string usn_search;
  cout << "Enter the USN of student to be deleted\n";
  cin >> usn_search;
  int pos = bin_search(usn_search);
  if(pos == -1)
  {
    cout << "Record Not Found\n";
    return;
  }
  cout << "Record found and deleted\n";
  fp.open("student.txt",ios::out|ios::in);
  fp.seekp(i1[pos].addr,ios::beg);
  fp.put('*');
  fp.close();

  for(int i=pos;i<cnt;i++)
  {
    i1[i].usn = i1[i+1].usn;
    i1[i].addr = i1[i+1].addr;
  }
  cnt--;
}
