#include <iostream>
#include <fstream>

using namespace std;

int main()
{
  ofstream myfile;
  myfile.open("dude.txt");
  for(unsigned x=0;x<1000000;x++)
    myfile << "hello" << endl;
  myfile.close();
}
