#include<iostream>
#include<cstring>
#include<fstream>

using namespace std;
int m,n;


void write()
{
  fstream out1,out2;
  int i;
  char name[20];
  out1.open("a.txt",ios::out);
  out2.open("b.txt",ios::out);
  cout<<"Enter no of names in file1:";
  cin >> m;
  cout << "Enter the names in ascending order:\n";
  for(i=0;i<m;i++)
  {
    cin >> name;
    out1 << name << "\n";
  }
  cout << "Enter no of names in file2:";
  cin >> n;
  cout << "Enter names in ascending order\n";
  for(i=0;i<n;i++)
  {
    cin >> name;
    out2 << name << "\n";
  }
}

void match()
{
  char list1[50][50],list2[50][50];
  int i,j;
  fstream out1,out2,out3;
  out1.open("a.txt",ios::in);
  out2.open("b.txt",ios::in);
  out3.open("c.txt",ios::out);

  i=0;
  out1.getline(list1[i],30,'\n');
  cout<<"Names in file1 are:\n";
  while(!out1.eof())
  {
    cout << list1[i] << endl;
    i++;
    out1.getline(list1[i],30,'\n');
  }
  i=0;
  cout<<"Names in file2 are:\n";
  out2.getline(list2[i],30,'\n');
  while(!out2.eof())
  {
    cout << list2[i] << endl;
    i++;
    out2.getline(list2[i],30,'\n');
  }

  cout << "\nCommon names are:\n";
  i = j = 0;
  while(i<m && j<n)
  {
    if(strcmp(list1[i],list2[j]) == 0)
    {
      cout << list1[i] << "\n";
      out3 << list1[i] << '\n';
      i++;
      j++;
    }
    else if(strcmp(list1[i],list2[j]) < 0)
      i++;
    else
      j++;
  }
}

int main()
{
  write();
  match();
  return 0;
}
