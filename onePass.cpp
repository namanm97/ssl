#include<iostream>
#include<cstring>
#include<cstdlib>
#include<fstream>

using namespace std;

int main(){

    ifstream input("onePassInput.txt");
    ofstream out("onePassOut.txt");
    ofstream symtab("onePassSymtab.txt");
    ifstream optab("onePassOptab.txt");
    string label, opcode, operand, code;
    int startAddress = 0, locationPointer;

    input >> label >> opcode >> operand;
    if(opcode == "START"){
        startAddress = stoi(operand,nullptr,16);
        input >> label >> opcode >> operand;
    }

    locationPointer = startAddress;

    while(opcode != "END"){
        out << hex << locationPointer << " "<< label << " " << opcode << " " << operand << endl;
        if(label != "-"){
            symtab << label << " " << hex << locationPointer << endl;
        }
        optab.clear();
        optab.seekg(0, ios::beg);
        optab >> code;
        while(code!="END"){
            if(opcode == code){
                locationPointer += 3;
                break;
            }
            optab >> code;
        }
        if(opcode == "RESB")
            locationPointer += stoi(operand);
        else if(opcode == "RESW")
            locationPointer += 3*stoi(operand);
        else if(opcode == "BYTE")
            locationPointer += operand.length()/2 - 3;
        else if(opcode == "WORD")
            locationPointer += 3;

        input >> label >> opcode >> operand;
    }
    return 0;
}
