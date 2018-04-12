#include<iostream>
#include<fstream>
#include<string>
#include<bitset>
using namespace std;

int main(){
    int a;
    string s;
    cout<<"Enter the starting address";
    cin >> s;
    a = stoi(s,nullptr,16);
    fstream input("relocInput.txt");
    fstream out("relocOutput.txt");
    string x;
    input >> x;

    while(x!="E"){
        if(x=="H"){
            input >> x >> x >> x;
        }
        else if(x=="T")
        {
            input >> x;
            int address = stoi(x, nullptr, 16) + a;
            input >> x >> x;
            string b = bitset<12>(stoi(x, nullptr, 16)).to_string();
            input >> x;
            int i = 0;
            while(!(x=="T" || x=="E")){
                if(b[i]=='1'){
                    int direct = stoi(x.substr(x.length()-4), nullptr, 16) + a;
                    out << hex << address << " " << x.substr(0,2) << direct << endl;
                }
                else{
                    out<< hex << address << " " << x << endl;
                }
                address += x.length()/2;
                input >> x;
                i++;
            }
        }
    }
    return  0;
}
