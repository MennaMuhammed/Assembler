#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;


string get_op(string x){

}
string get_func(string x){

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

}
string get_26(string x){

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
string r_form(string x){
int op =0;
int func = 0;
if(x=="add"){
       func = 32;
}
else if(x=="and"){
        func =36;
}
else if(x=="or"){
    func =37;
}
else if(x=="sub"){
       func =34;
}
else if(x=="nor"){
    func =39;
}
else if(x=="slt"){
    func =42;
}
else if(x=="sll"){
    func =0;
}
else if (x== "srl"){
    func =2;
}
else if(x=="jr"){
    func =8;
}
return x;
}
string operation(string x){
if(x=="add" || x=="and" || x=="or" || x=="sub" || x=="nor" || x=="slt" || x=="sll" || x== "srl" || x=="jr"){
 x = r_form(x);
}
else if(x=="addi" || x=="andi" || x=="ori" || x=="slti" || x=="lw" || x=="sw"||x=="lui"||x=="beq" || x=="bne"){

}
else if(x=="j"){

}
}


int main()
{
    //string input ="";
    //cin>>input;
    cout<<get_reg(1,"$s3, $s4, $s2")<<endl;
    cout<<get_reg(2,"$s3, $s4, $s2")<<endl;
    cout<<get_reg(3,"$s3, $s4, $s2")<<endl;
    return 0;
}
