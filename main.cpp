#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
using namespace std;

string to_string(int i)
{
    stringstream ss;
    ss << i;
    return ss.str();
}
string toBinary(int n,int bit)
{
    string r;
    do{
    r=(n%2==0 ?"0":"1")+r; n/=2;
    }while(n!=0);
    while(r.length()<bit){
        r="0"+r;
    }
    return r;
}


string get_op(string x){
string op = x.substr(0,x.find_first_of("$"));
    for(int i=0;i<op.length();i++){
        if(op[i]==' ')op.erase(i,1);
    }
    return op;
}
string removeSpace(string x){
    for(int i=0;i<x.length();i++){
        if(x[i]==' ')x.erase(i,1);
    }
    return x;
}
string get_reg(int num,string x){
string reg = x.substr(x.find_first_of("$"));
if(num==1){
    reg=reg.substr(0,reg.find_first_of(","));
    for(int i=0;i<reg.length();i++){
        if(reg[i]==' ')reg.erase(i,1);
    }
}
else if(num==2){
    reg=reg.substr(reg.find_first_of(",")+1,reg.find_last_of(",")-reg.find_first_of(",")-1);
    for(int i=0;i<reg.length();i++){
        if(reg[i]==' ')reg.erase(i,1);
    }
}
else if(num==3){
    reg=reg.substr(reg.find_last_of(",")+1);
    for(int i=0;i<reg.length();i++){
        if(reg[i]==' ')reg.erase(i,1);
    }
}
return reg;
}
string get_16(string x){
    string immedAdd = x.substr(x.find_last_of(","));
    return immedAdd;
}
/*string get_26(string x){
    string bit26Add =
}*/
string get_shamt(string x){
    string shamt = x.substr(x.find_last_of(",")+1);
    return shamt;
}


string numReg(string x){
string y ="";
if(x.find("0") != string::npos){
    y="0";
}
else if(x.find("1") != string::npos){
    y="1";
}
else if(x.find("2") != string::npos){
    y="2";
}
else if(x.find("3") != string::npos){
    y="3";
}
else if(x.find("4") != string::npos){
    y="4";
}
else if(x.find("5") != string::npos){
    y="5";
}
else if(x.find("6") != string::npos){
    y="6";
}
else if(x.find("7") != string::npos){
    y="7";
}
else if(x.find("8") != string::npos){
    y="8";
}
else if(x.find("9") != string::npos){
    y="9";
}
return y;
}
int reg(string x){
int r =0;
string y = x;
if(y == "$zero"){
    r = 0;
}
else if(y == "$at"){
    r = 1;
}
else if(y == "$gp"){
    r = 28;
}
else if(y == "$sp"){
    r = 29;
}
else if(y == "$fp"){
    r = 30;
}
else if(y == "$ra"){
    r = 31;
}
else if(y.find("$v") != string::npos){
   if (numReg(y)!="" && atoi(numReg(y).c_str())<2){
        r = 2 + atoi(numReg(y).c_str());
   }
}
else if(y.find("$a") != string::npos){
   if (numReg(y)!="" && atoi(numReg(y).c_str())<4){
        r = 4 + atoi(numReg(y).c_str());
   }
}
else if(y.find("$t") != string::npos){
   if (numReg(y)!="" && atoi(numReg(y).c_str())<10){
        if(atoi(numReg(y).c_str())<8){
           r = 8 + atoi(numReg(y).c_str());
        }
        else if(atoi(numReg(y).c_str())<10 && atoi(numReg(y).c_str())>7){
           r = 24 + atoi(numReg(y).c_str());
        }

   }
}
else if(y.find("$s") != string::npos){
   if (numReg(y)!="" && atoi(numReg(y).c_str())<8){
        r = 16 + atoi(numReg(y).c_str());
   }
}
else if(y.find("$k") != string::npos){
   if (numReg(y)!="" && atoi(numReg(y).c_str())<2){
        r = 26 + atoi(numReg(y).c_str());
   }
}
return r;
}
string r_form(string y){
string x = get_op(y);
int op=0;
int rs=0;
int rt=0;
int rd=0;
int shamt=0;
int func=0;
if(x=="add"){
       func = 32;
       rs = reg(get_reg(2,y));
       rt = reg(get_reg(3,y));
       rd = reg(get_reg(1,y));
}
else if(x=="sub"){
       func =34;
       rs = reg(get_reg(2,y));
       rt = reg(get_reg(3,y));
       rd = reg(get_reg(1,y));
}
else if(x=="and"){
       func =36;
       rs = reg(get_reg(2,y));
       rt = reg(get_reg(3,y));
       rd = reg(get_reg(1,y));
}
else if(x=="or"){
    func =37;
       rs = reg(get_reg(2,y));
       rt = reg(get_reg(3,y));
       rd = reg(get_reg(1,y));
}
else if(x=="nor"){
    func =39;
       rs = reg(get_reg(2,y));
       rt = reg(get_reg(3,y));
       rd = reg(get_reg(1,y));
}
else if(x=="slt"){
    func =42;
       rs = reg(get_reg(2,y));
       rt = reg(get_reg(3,y));
       rd = reg(get_reg(1,y));
}
else if(x=="sll"){
    func =0;
       rd = reg(get_reg(1,y));
       rt = reg(get_reg(2,y));
       shamt = atoi(get_shamt(y).c_str());
}
else if (x== "srl"){
    func =2;
       rd = reg(get_reg(1,y));
       rt = reg(get_reg(2,y));
       shamt = atoi(get_shamt(y).c_str());
}
else if(x=="jr"){
    func =8;
    rs = reg(get_reg(1,y));
}
string machCode = toBinary(op,6)+toBinary(rs,5)+toBinary(rt,5)+toBinary(rd,5)+toBinary(shamt,5)+toBinary(func,6);
return machCode;
}
string operation(string y){
    string x = get_op(y);
if(x=="add" || x=="and" || x=="or" || x=="sub" || x=="nor" || x=="slt" || x=="sll" || x== "srl" || x=="jr"){
  r_form(y);
}
else if(x=="addi" || x=="andi" || x=="ori" || x=="slti" || x=="lw" || x=="sw"||x=="lui"||x=="beq" || x=="bne"){

}
else if(x=="j"){

}
}


int main()
{
    bool run =true;
    while(run){
    string input ="";
    getline(cin,input);
    input = removeSpace(input);
    cout<<r_form(input)<<endl;
    }
    return 0;
}
