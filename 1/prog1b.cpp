#include<iostream>
#include<cstring>
#include<fstream>

using namespace std;
int main()
{
  char s1[25];
  fstream f1,f2;
  char fname1[25],fname3[25];
  int x =0;
  cout<<"Enter input file\n";
  cin >> fname1;
  cout<<"Enter output file\n";
  cin >> fname3;

  f1.open(fname1,ios::in);
  f2.open(fname3,ios::out);

  if(!f1)
  {
    cerr<<"File doesn't exist: "<<fname1;
    return -1;
  }

  if(!f2)
  {
    cerr << "File doesn't exist:" << fname3;
    return -1;
  }
  while(1)
  {
    f1.getline(s1,25);
    if(f1.fail())
      break;
    x = strlen(s1);
    for(int i=x-1;i >=0;i--)
    f2 << s1[i];
      f2<<endl;
  }

  f1.close();
  f2.close();
    return 0;
}
