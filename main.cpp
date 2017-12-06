#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <fstream>
using namespace std;

string to_string(int i)
{
    stringstream ss;
    ss << i;
    return ss.str();
}
string toBinary(int n,int bit)
{
    bool neg = false;
    if(n<0)neg=true;
    string r;
    do{
    r=(n%2==0 ?"0":"1")+r; n/=2;
    }while(n!=0);
    while(r.length()<bit){
        if(neg){
        r="1"+r;
        }
        else{
        r="0"+r;
        }
    }
    return r;
}
string removeSpace(string x){
    for(int i=0;i<x.length();i++){
        if(x[i]=='j' && x[i+1]==' ')x[i+1]='$';
        if(x[i]=='j' && x[i+1]=='a')x[i+3]='$';
        if(x[i]==' ')x.erase(i,1);
    }
    return x;
}

string get_op(string x){
    int start =0;
if(x.find(":")!=string::npos)start = x.find(":")+1;
string op = x.substr(start,x.find_first_of("$")-start);
    for(int i=0;i<op.length();i++){
        if(op[i]==' ')op.erase(i,1);
    }
    return op;
}
string get_label(string x){
string label ="";
string op = get_op(x);
if(x.find(",")!= string::npos){
   label = x.substr(x.find_last_of(",")+1);
}
else if(op=="j" || op=="jal"){
        label = x.substr(x.find_first_of("$")+1);
}
return label;
}
int label_loc(ifstream& y, string l){
string x="";
string label = get_label(l);
string op = get_op(l);
int posLB =0;
int posST =0;
int counter =0;
while(!y.eof()){
    getline(y,x);
    x=removeSpace(x);
    counter++;
    if(x==l){
       posST=counter;
    }
    else if(x.find(label)!= string::npos && x.find(":")!= string::npos ){
            posLB=counter;
    }
}
int pos=0;
if(op == "j"|| op =="jal"){
    pos = posLB;
}
else{
    pos = posLB-posST;
}
return pos;
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
else if(num==0){ //sp case for lw and sw
    reg=reg.substr(reg.find_first_of("(")+1,reg.find_first_of(")")-reg.find_first_of("(")-1);
}
return reg;
}
string get_16(string x){
    string immedAdd ="";
    if(x.find("(") != string::npos){
    immedAdd = x.substr(x.find_first_of(",")+1,x.find_first_of(")")-x.find_first_of(",")-1);
    }
    else{
    immedAdd = x.substr(x.find_last_of(",")+1);
    }
    return immedAdd;
}
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


string i_form(string y, int l){
    string x = get_op(y);
    int op=0;
    int rs =0;
    int rt=0;
    int immAdd =0;
    if(x=="addi"){
        op=8;
        rs=reg(get_reg(2,y));
        rt=reg(get_reg(1,y));
        immAdd=atoi(get_16(y).c_str());
    }
    else if(x=="andi"){
        op=12;
        rs=reg(get_reg(2,y));
        rt=reg(get_reg(1,y));
        immAdd=atoi(get_16(y).c_str());

    }
    else if(x=="ori"){
        op=13;
        rs=reg(get_reg(2,y));
        rt=reg(get_reg(1,y));
        immAdd=atoi(get_16(y).c_str());

    }
    else if(x=="slti"){
        op=10;
        rs=reg(get_reg(2,y));
        rt=reg(get_reg(1,y));
        immAdd=atoi(get_16(y).c_str());

    }
    else if(x=="lw"){
        op=35;
        rs=reg(get_reg(0,y));
        rt=reg(get_reg(1,y));
        immAdd=atoi(get_16(y).c_str());

    }
    else if(x=="sw"){
        op=43;
        rs=reg(get_reg(0,y));
        rt=reg(get_reg(1,y));
        immAdd=atoi(get_16(y).c_str());

    }
    else if(x=="lui"){
        op=15;
        rt=reg(get_reg(1,y));
        immAdd=atoi(get_16(y).c_str());

    }
    else if(x=="beq"){
        op=4;
        rs=reg(get_reg(2,y));
        rt=reg(get_reg(1,y));
        immAdd=l;

    }
    else if(x=="bne"){
        op=5;
        rs=reg(get_reg(2,y));
        rt=reg(get_reg(1,y));
        immAdd=l;

    }
 string machCode = toBinary(op,6)+toBinary(rs,5)+toBinary(rt,5)+toBinary(immAdd,16);
 return machCode;

}


string j_form(string y, int l){
string x = get_op(y);
int op=0;
int label=0;
if(x=="j"){
    op=2;
    label = l;
}
else if(x=="jal"){
    op=3;
    label = l;
}
string machCode = toBinary(op,6)+toBinary(label,26);
return machCode;
}


string operation(string y,ifstream& l){
    string x = get_op(y);
    string result ="";
if(x=="add" || x=="and" || x=="or" || x=="sub" || x=="nor" || x=="slt" || x=="sll" || x== "srl" || x=="jr"){
 result = r_form(y);
}
else if(x=="addi" || x=="andi" || x=="ori" || x=="slti" || x=="lw" || x=="sw"||x=="lui"||x=="beq" || x=="bne"){
 int label = label_loc(l,y);
 result = i_form(y,label);
}
else if(x=="j" || x=="jal"){
int label = label_loc(l,y);
result = j_form(y,label);
}

return result;
}


int main()
{
    string input ="";
    ifstream inputfile ("input.txt");
    ofstream outputfile ("output.txt");
    if(inputfile.is_open()){
          while(!inputfile.eof()){
            getline(inputfile,input,'\n');
            input=removeSpace(input);
            ifstream test ("input.txt");
            outputfile<<operation(input,test)<<"\n";
            test.close();
          }
          outputfile.close();
    }
    else
    {
        cout<<"can't open file"<<endl;
    }
    inputfile.close();
    return 0;
}
