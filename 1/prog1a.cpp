#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int main()
{
  char test[25];
  int n=0,x=0,j=0;
  cout<<"Enter no of names:\n";
  cin >> n;
  for(int i=1;i<=n;i++)
  {
    cout<<"Enter name "<<i << ":\n";
    cin >> test;
    x = strlen(test);
    cout<<"Reversed name "<< i << ":\n";

    for(j=x-1;j>=0;j--)
      cout << test[j];
      cout<<"\n";
  }
  return 0;
}
