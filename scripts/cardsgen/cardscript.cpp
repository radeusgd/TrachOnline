#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

string combineFile(fstream & file)
{
  string txt="";
  while(!file.eof())
  {
    string temp;
    getline(file, temp);
    txt+=temp;
    txt+="\n";
  }
  return txt;
}

void updateWord(string & str, string current, string wanted)
{
  int pos=str.find(current);
  while(pos!=string::npos)
  {
    str.erase(pos, current.length());
    str.insert(pos,wanted);
    pos=str.find(current, pos+wanted.length());
  }
}

int main(int argc, char *argv[])
{
  string type=argv[1];  //a or n (abstract or normal)
  string namec=argv[2]; //Name
  string name=namec;    //name
  string nameh=namec;   //NAME
  string content;
  transform(name.begin(), name.end(), name.begin(), ::tolower);
  transform(nameh.begin(), nameh.end(), nameh.begin(), ::toupper);

  if(type=="a")
  {
    fstream a_in;
    ofstream a_out;
    string source=namec+".hpp";

    a_in.open("Abstract.hpp", ios::in);
    content=combineFile(a_in);
    updateWord(content,"#name#", name);
    updateWord(content,"#Name#", namec);
    updateWord(content,"#NAME#", nameh);
    a_in.close();
    a_out.open(source.c_str());
    a_out<<content;
    a_out.close();
  }
  if(type=="n")
  {
    fstream nc_in, nh_in;
    ofstream nc_out, nh_out;

    string source=namec+".cpp";
    nc_in.open("Normal.cpp", ios::in);
    content=combineFile(nc_in);
    updateWord(content,"#name#", name);
    updateWord(content,"#Name#", namec);
    updateWord(content,"#NAME#", nameh);
    nc_in.close();
    nc_out.open(source.c_str());
    nc_out<<content;
    nc_out.close();

    source=namec+".hpp";
    nh_in.open("Normal.hpp", ios::in);
    content=combineFile(nh_in);
    updateWord(content,"#name#", name);
    updateWord(content,"#Name#", namec);
    updateWord(content,"#NAME#", nameh);
    nh_in.close();
    nh_out.open(source.c_str());
    nh_out<<content;
    nh_out.close();
  }

  return 0;
}
