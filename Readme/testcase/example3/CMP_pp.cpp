#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <bitset>
#include <sstream>
#include <math.h>
#include <fstream>
using namespace std;
vector<long long> reg;
vector<string >d_mem;
#define mult_sign 9223372036854775807
#define mult_unsign 18446744073709551615
int lock_num = 0;
int lock = 0;
int safe_H = 0;//use for mult
int safe_L = 0;
int cycle = 0;
ofstream fout1 , fout3;
string to_str(int &i){
  string s;
  stringstream ss(s);
  ss << i;
  return ss.str();
}
string str_cut(string str , int i , int j)
{
    int len = str.size();
    string after_str = "";
    for(int sratt = i ; i <= j ; i++)
        after_str = after_str + str[i];
    return after_str;
}
int row_2(int i)
{
    int num = 0;
    while(i != 1)
    {
        i = i / 2;
        num++;
    }
    return num;
}
long long convert_dex(string str_bin)
{
    int str_size = str_bin.size();
    long long dec = 0;
    int bin_pow = 0;
    for(int i = (str_size-1) ; i>=0 ; i--)
    {
        int num = 0;
        //cost ~0.017sec
        stringstream temp_num;
        temp_num << str_bin[i];
        temp_num >> num;
        long long temp = num * pow(2,bin_pow);
        dec += temp;
        bin_pow++;
        // cost ~0.024sec
        /*
        if(str_bin[i] == '1') num = 1;
        int temp = num * pow(2,bin_pow);
        dec += temp;
        bin_pow++;*/
    }
    return dec;
}
string convert_bin(long long num)
{
    if(num < 0)//avoid data is signed
    {
        num = num & 4294967295;
    }
    string temp = "";
    while(true)
    {
        if(num % 2 == 0)
        {
            temp += "0";
            num = num/2;
        }
        else if(num % 2 == 1)
        {
            temp += "1";
            num = num/2;
        }
        if(num == 0)
            break;
    }
    string output = "";
    int s_num = temp.size();
    for(int i = 31; i >= 0 ; i--)
    {
        if(i >= s_num)
            output += "0";
        else
            output += temp[i];
    }
    return output;
}
string convert_hex(long long num)
{
    if(num < 0)//avoid data is signed
    {
        num = num & 4294967295;
    }
    string temp = "";
    while(true)
    {
        if(num % 16 == 0)
        {
            temp += "0";
            num = num/16;
        }
        else if(num % 16 == 1)
        {
            temp += "1";
            num = num/16;
        }
        else if(num % 16 == 2)
        {
            temp += "2";
            num = num/16;
        }
        else if(num % 16 == 3)
        {
            temp += "3";
            num = num/16;
        }
        else if(num % 16 == 4)
        {
            temp += "4";
            num = num/16;
        }
        else if(num % 16 == 5)
        {
            temp += "5";
            num = num/16;
        }
        else if(num % 16 == 6)
        {
            temp += "6";
            num = num/16;
        }
        else if(num % 16 == 7)
        {
            temp += "7";
            num = num/16;
        }
        else if(num % 16 == 8)
        {
            temp += "8";
            num = num/16;
        }
        else if(num % 16 == 9)
        {
            temp += "9";
            num = num/16;
        }
        else if(num % 16 == 10)
        {
            temp += "A";
            num = num/16;
        }
        else if(num % 16 == 11)
        {
            temp += "B";
            num = num/16;
        }
        else if(num % 16 == 12)
        {
            temp += "C";
            num = num/16;
        }
        else if(num % 16 == 13)
        {
            temp += "D";
            num = num/16;
        }
        else if(num % 16 == 14)
        {
            temp += "E";
            num = num/16;
        }
        else
        {
            temp += "F";
            num = num/16;
        }
        if(num == 0)
            break;
    }
    string output = "0x";
    int s_num = temp.size();
    for(int i = 7; i >= 0 ; i--)
    {
        if(i >= s_num)
            output += "0";
        else
            output += temp[i];
    }
    return output;

}
int ins_add(char *rs , char *rt , char *rd) // sign +-
{
    int booling = 0;
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = convert_dex(rd);
    long long temp_1 = 0;
    long long temp_2 = 0;
    long long temp = reg[t3];
    if(reg[t1] > 2147483647) //from overflow error
        temp_1 = int32_t(reg[t1]);
    else if(reg[t1] < int(-2147483648))
        temp_1 = (reg[t1]) & 2147483647;
    else
        temp_1 = reg[t1];
    if(reg[t2] > 2147483647)
        temp_2 = int32_t(reg[t2]);
    else if(reg[t2] < int(-2147483648))
        temp_2 = (reg[t2]) & 2147483647;
    else
        temp_2 = reg[t2];
    reg[t3] = temp_1 + temp_2;
    fout1 << "cycle " << cycle << endl;
    if(t3 == 0){
        //fout2 << "In cycle " << cycle << ": " << "Write $0 Error" << endl;
        booling = 1;
    }
    //system("PAUSE");
    int no_double = 0;
    if((reg[t3]) > 2147483647 || (reg[t3]) < int(-2147483648) )
    {
        //fout2 << "In cycle " << cycle << ": " << "Number Overflow" << endl;
        no_double = 1;
    }
    /*if((reg[t1] < 0 && reg[t2] < 0 && reg[t3] > 0) ||(reg[t1] > 0 && reg[t2] > 0 && reg[t3] < 0))
    {


    }*/
    if(booling == 1)
        reg[t3] = 0;
    if(convert_bin(reg[t3]) != convert_bin(temp)){
        if(t3 < 10)
            fout1 << "$0" <<t3 << ": " << convert_hex(reg[t3]) << endl;
        else
            fout1 << "$" << t3 << ": " << convert_hex(reg[t3]) << endl;
    }
    reg[34] = reg[34] + 4;
    fout1 << "PC: " << convert_hex(reg[34]) << endl;
    return 0;

}
int ins_addu(char *rs , char *rt , char *rd)
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = convert_dex(rd);
    unsigned long long temp = reg[t3];
    unsigned int temp_num_1 = 0;
    unsigned int temp_num_2 = 0;
    if(reg[t1] < 0 && reg[t2] >0)
    {
        temp_num_1 = reg[t1]& 4294967295;
        reg[t3] = temp_num_1 + reg[t2];
    }
    else if (reg[t1] > 0 && reg[t2] < 0)
    {
        temp_num_2 = reg[t2]& 4294967295;
        reg[t3] = temp_num_2 + reg[t1];
    }
    else if(reg[t1] < 0 && reg[t2] < 0)
    {
        temp_num_1 = reg[t1]& 4294967295;
        temp_num_2 = reg[t2]& 4294967295;
        reg[t3] = temp_num_1 + temp_num_2;
    }
    else
        reg[t3] = reg[t1] + reg[t2];
    fout1 << "cycle " << cycle << endl;
    if(t3 == 0){
//        fout2 << "In cycle " << cycle << ": " << "Write $0 Error" << endl;
        reg[t3] = 0;
    }
    if(reg[t3] > 4294967295)
    {
        reg[t3] = reg[t3] & 4294967295;
    }
    if(convert_bin(reg[t3]) != convert_bin(temp)){
        if(t3 < 10)
            fout1 << "$0" <<t3 << ": " << convert_hex(reg[t3]) << endl;
        else
            fout1 << "$" <<t3 << ": " << convert_hex(reg[t3]) << endl;
    }
    reg[34] = reg[34] + 4;
    fout1 << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_sub(char *rs , char *rt , char *rd)// sign +-
{
    int booling = 0;
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = convert_dex(rd);
    //cout << reg[t1] << endl;
    //cout << reg[t2] << endl;
    long long temp = reg[t3];
    long long temp_1 = 0;
    long long temp_2 = 0;
    if(reg[t1] > 2147483647)
        temp_1 = int32_t(reg[t1]);
    else if(reg[t1] < int(-2147483648))
        temp_1 = (reg[t1]) & 2147483647;
    else
        temp_1 = reg[t1];
    if(reg[t2] > 2147483647)
        temp_2 = int32_t(reg[t2]);
    else if(reg[t2] < int(-2147483648))
        temp_2 = (reg[t2]) & 2147483647;
    else
        temp_2 = reg[t2];
    reg[t3] = (temp_1 - temp_2);
    //cout << reg[t1] << endl;
    //cout << reg[t2] << endl;
    //cout << reg[t3] << endl;
    //system("PAUSE");
    fout1 << "cycle " << cycle << endl;
    if(t3 == 0){
        //fout2 << "In cycle " << cycle << ": " << "Write $0 Error" << endl;
        booling = 1;
    }
    int no_double = 0;
    if((reg[t3]) > 2147483647 || (reg[t3]) < int(-2147483648))
    {
        //fout2 << "In cycle " << cycle << ": " << "Number Overflow" << endl;
        no_double = 1;
    }
    /*if((reg[t1] < 0 && reg[t2] < 0 && reg[t3] > 0) ||(reg[t1] > 0 && reg[t2] > 0 && reg[t3] < 0))
    {

    }
    if(reg[t1] == int(-2147483648) && reg[t2]== int32_t(-2147483648))
    {

    }*/
    //cout << reg[t3] << endl;
    if(booling == 1)
        reg[t3] = 0;
    if(convert_bin(reg[t3]) != convert_bin(temp)){
        if(t3 < 10)
            fout1 << "$0" <<t3 << ": " << convert_hex(reg[t3]) << endl;
        else
            fout1 << "$"<<t3 << ": " << convert_hex(reg[t3]) << endl;
    }
    reg[34] = reg[34] + 4;
    fout1 << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_and(char *rs , char *rt , char *rd)// sign +-
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = convert_dex(rd);
    long long temp = reg[t3];
    reg[t3] = (reg[t1]) & (reg[t2]);
    fout1 << "cycle " << cycle << endl;
    if(t3 == 0){
//        fout2 << "In cycle " << cycle << ": " << "Write $0 Error" << endl;
        reg[t3] = 0;
    }
    if(convert_bin(reg[t3]) != convert_bin(temp)){
        if(t3 < 10)
            fout1 << "$0" <<t3 << ": " << convert_hex(reg[t3]) << endl;
        else
            fout1 << "$"<<t3 << ": " << convert_hex(reg[t3]) << endl;
    }
    reg[34] = reg[34] + 4;
    fout1 << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_or(char *rs , char *rt , char *rd)// sign +-
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = convert_dex(rd);
    long long temp = reg[t3];
    reg[t3] = (reg[t1]) | (reg[t2]);
    fout1 << "cycle " << cycle << endl;
    if(t3 == 0){
//        fout2 << "In cycle " << cycle << ": " << "Write $0 Error" << endl;
        reg[t3] = 0;
    }
    if(convert_bin(reg[t3]) != convert_bin(temp)){
        if(t3 < 10)
            fout1 << "$0" <<t3 << ": " << convert_hex(reg[t3]) << endl;
        else
            fout1 << "$"<<t3 << ": " << convert_hex(reg[t3]) << endl;
    }
    reg[34] = reg[34] + 4;
    fout1 << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_xor(char *rs , char *rt , char *rd)// sign +-
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = convert_dex(rd);
    long long temp = reg[t3];
    reg[t3] = (reg[t1]) ^ (reg[t2]);
    //cout << "xor-t3 = " << t3 << endl;
    fout1 << "cycle " << cycle << endl;
    if(t3 == 0){
//        fout2 << "In cycle " << cycle << ": " << "Write $0 Error" << endl;
        reg[t3] = 0;
    }
    if(convert_bin(reg[t3]) != convert_bin(temp)){
        if(t3 < 10)
            fout1 << "$0" <<t3 << ": " << convert_hex(reg[t3]) << endl;
        else
            fout1 << "$"<<t3 << ": " << convert_hex(reg[t3]) << endl;
    }
    reg[34] = reg[34] + 4;
    fout1 << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_nor(char *rs , char *rt , char *rd)// sign +-
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = convert_dex(rd);
    long long temp = reg[t3];
    reg[t3] = ~((reg[t1]) | (reg[t2]));
    fout1 << "cycle " << cycle << endl;
    //cout << "nor-t3 = " << t3 << endl;
    //cout << reg[t3] << endl;
    if(t3 == 0){
 //       fout2 << "In cycle " << cycle << ": " << "Write $0 Error" << endl;
        reg[t3] = 0;
    }
    if(convert_bin(reg[t3]) != convert_bin(temp)){
        if(t3 < 10)
            fout1 << "$0" <<t3 << ": " << convert_hex(reg[t3]) << endl;
        else
            fout1 << "$"<<t3 << ": " << convert_hex(reg[t3]) << endl;
    }
    reg[34] = reg[34] + 4;
    fout1 << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_nand(char *rs , char *rt , char *rd)// sign +-
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = convert_dex(rd);
    long long temp = reg[t3];
    reg[t3] = ~((reg[t1]) & (reg[t2]));
    //cout << "nand-t3 = " << t3 << endl;
    fout1 << "cycle " << cycle << endl;
    if(t3 == 0){
//        fout2 << "In cycle " << cycle << ": " << "Write $0 Error" << endl;
        reg[t3] = 0;
    }
    if(convert_bin(reg[t3]) != convert_bin(temp)){
        if(t3 < 10)
            fout1 << "$0" <<t3 << ": " << convert_hex(reg[t3]) << endl;
        else
            fout1 << "$"<<t3 << ": " << convert_hex(reg[t3]) << endl;
    }
    reg[34] = reg[34] + 4;
    fout1 << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_slt(char *rs , char *rt , char *rd)
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = convert_dex(rd);
    long long temp = reg[t3];
    long long comp_1 = 0;
    long long comp_2 = 0;
    fout1 << "cycle " << cycle << endl;
    //cout << "xor-t1 = " << t1 << endl;
    //cout << "xor-t2 = " << t2 << endl;
    if(reg[t1] > 2147483647 )
        comp_1 = int32_t(reg[t1]);
    else if(reg[t1] < int(-2147483648))
        comp_1 = (reg[t1]) & 2147483647;
    else
        comp_1 = reg[t1];
    if(reg[t2] > 2147483647)
        comp_2 = int32_t(reg[t2]);
    else if(reg[t2] < int(-2147483648))
        comp_2 = (reg[t2]) & 2147483647;
    else
        comp_2 = reg[t2];
    //cout << t1 <<endl;
    //cout << reg[t2] <<endl;
    if(int(comp_1) < int(comp_2))
        reg[t3] = 1;
    else
        reg[t3] = 0;
    //cout << reg[t3] <<endl;
    if(t3 == 0){
 //       fout2 << "In cycle " << cycle << ": " << "Write $0 Error" << endl;
        reg[t3] = 0;
    }
    if(convert_bin(reg[t3]) != convert_bin(temp)){
        if(t3 < 10)
            fout1 << "$0" <<t3 << ": " << convert_hex(reg[t3]) << endl;
        else
            fout1 << "$"<<t3 << ": " << convert_hex(reg[t3]) << endl;
    }
    reg[34] = reg[34] + 4;
    fout1 << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_sll(char *rt , char *rd , char *shamt)//+ ~ -
{
    int booling = 0;
    int t1 = convert_dex(rt);
    int t2 = convert_dex(rd);
    int t3 = convert_dex(shamt);
    long long use_1 = 0;
    if(reg[t1] > 2147483647)
        use_1 = int32_t(reg[t1]);
    else if(reg[t1] < int(-2147483648))
        use_1 = (reg[t1]) & 2147483647;
    else
        use_1 = (reg[t1]);
    long long temp = reg[t2];
    fout1 << "cycle " << cycle << endl;
    int spec = 0;
    if(t2 == 0 && t1 == 0 && t3 == 0)
        spec = 1;
    if((t2 == 0) && (spec != 1)){
//        fout2 << "In cycle " << cycle << ": " << "Write $0 Error" << endl;
        booling = 1;
    }
    //cout << t2 << endl;
    //cout << t1 << endl;
    //cout << "reg[t2] = "<< reg[t2] << endl;
    //cout << "reg[t1] = "<< reg[t1] << endl;
    //cout << "t3 = "<< t3 << endl;
    reg[t2] = (use_1) << t3;
    //cout << "reg[t2] = "<< convert_hex(reg[t2]) << endl;
    //system("PAUSE");
    /*
    if((reg[t2]) > 4294967295 || (reg[t2]) < int(-2147483648))
    {
        reg[t2] = 0;
    }*/
    if(booling == 1)
        reg[t2] = 0;
    //cout << "reg[t2] = "<< reg[t2] << endl;
    if(convert_bin(reg[t2]) != convert_bin(temp)){
        if(t2 < 10)
            fout1 << "$0" << t2 << ": " << convert_hex(reg[t2]) << endl;
        else
            fout1 << "$"<<t2 << ": " << convert_hex(reg[t2]) << endl;
    }
    reg[34] = reg[34] + 4;
    fout1 << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}

int ins_srl(char *rt , char *rd , char *shamt)//+ ~ -
{
    int t1 = convert_dex(rt);
    int t2 = convert_dex(rd);
    int t3 = convert_dex(shamt);
    long long temp = reg[t2];
    long long temp_1 = 0;
    if(reg[t1] > 2147483647)
        temp_1 = int32_t(reg[t1]);
    else if(reg[t1] < int(-2147483648))
        temp_1 = (reg[t1]) & 2147483647;
    else
        temp_1 = reg[t1];
    //cout << "reg[t1] = "<< reg[t1] << endl;
    //cout << "reg[t2] = "<< reg[t2] << endl;
    //cout << "t3 = " << t3 << endl;
    fout1 << "cycle " << cycle << endl;
    if(temp_1 < 0)
    {
        long long temp_num = temp_1 >> t3;
        int ppow = pow(2,(32-t3)) - 1;
        reg[t2] = (temp_num & ppow);
    }
    else
        reg[t2] = temp_1 >> t3;
    //cout << "reg[t2] = "<< reg[t2] << endl;
    if(t2 == 0){
//        fout2 << "In cycle " << cycle << ": " << "Write $0 Error" << endl;
        reg[t2] = 0;
    }
    if(convert_bin(reg[t2]) != convert_bin(temp)){
        if(t2 < 10)
            fout1 << "$0" << t2 << ": " << convert_hex(reg[t2]) << endl;
        else
            fout1 << "$" << t2 << ": " << convert_hex(reg[t2]) << endl;
    }
    reg[34] = reg[34] + 4;
    fout1 << "PC: " <<convert_hex(reg[34]) << endl;
    return 0;
}

int ins_sra(char *rt , char *rd , char *shamt)//+~- sign extend
{
    int t1 = convert_dex(rt);
    int t2 = convert_dex(rd);
    int t3 = convert_dex(shamt);
    long long temp = reg[t2];
    long long temp_1 = 0;
    if(reg[t1] > 2147483647)
        temp_1 = int32_t(reg[t1]);
    else if(reg[t1] < int(-2147483648))
        temp_1 = (reg[t1]) & 2147483647;
    else
        temp_1 = reg[t1];
    reg[t2] = temp_1 >> t3;
    fout1 << "cycle " << cycle << endl;
    if(t2 == 0){
//        fout2 << "In cycle " << cycle << ": " << "Write $0 Error" << endl;
        reg[t2] = 0;
    }
    if((reg[t2]) > 4294967295 || (reg[t2]) < int(-2147483648))
    {
        reg[t2] = 0;
    }
    if(convert_bin(reg[t2]) != convert_bin(temp)){
        if(t2 < 10)
            fout1 << "$0" << t2 << ": " << convert_hex(reg[t2]) << endl;
        else
            fout1 << "$"<<t2 << ": " << convert_hex(reg[t2]) << endl;
    }
    reg[34] = reg[34] + 4;
    fout1 << "PC: " <<convert_hex(reg[34]) << endl;
    return 0;
}

int ins_jr(char *rs)
{
    int t1 = convert_dex(rs);
    int temp_add;
    fout1 << "cycle " << cycle << endl;
    temp_add = reg[34];
    temp_add = (temp_add-reg[t1])/4;
    reg[34] = reg[t1];
    //fout1 << "temp_add = " << temp_add << endl;
    fout1 << "PC: " << convert_hex(reg[34]) << endl;
    //system("PAUSE");
    //cout << temp_add << endl;
    return temp_add;
}

int ins_mult(char *rs , char *rt)
{
    long long result_1 = 0;
    long long result_2 = 0;
    long long result = 0;
    long long temp = 0;
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    long long temp_HI = reg[32];
    long long temp_LO = reg[33];
    result = int32_t(reg[t1]) * int32_t(reg[t2]);
    fout1 << "cycle " << cycle << endl;
    //fout1 << result << endl;
    //cout << "reg[t1] = " << reg[t1] << endl;
    //cout << "reg[t2] = " << reg[t2] << endl;
    //system("PAUSE");
    //cout << "result = " << result << endl;
    //cout << mul_num << endl;
    if(result < 0)
    {
        result = result & mult_unsign;
    }
    //cout << "result = " << result << endl;
    //system("PAUSE");
    result_1 = result/pow(2,32);
    //if(result_1 != 0)
    reg[32] = result_1 ;
    temp = result_1 * pow(2,32);
    result_2 = result - temp;
    reg[33]  = result_2 ;
    //reg[32] = int32_t(reg[32]);
    //cout << "HI = " << reg[32] << endl;
    //cout << "LO = " << reg[33] << endl;
    if((reg[t1] < 0 && reg[t2] > 0) || (reg[t1] > 0 && reg[t2] < 0))
    {
        unsigned long long ind_result = int32_t(reg[t1]) * int32_t(reg[t2]);
        reg[32] = ind_result/pow(2,32);
        long long ind_temp = reg[32] * pow(2,32);
        reg[33] = ind_result - ind_temp;
    }
    //system("PAUSE");
    if(reg[32] > 4294967295)
        reg[32] = 4294967295;
    if(reg[33] > 4294967295)
        reg[33] = 4294967295;
//    if((reg[32]) > 4294967295 || (reg[33]) > 4294967295)
//        fout2 << "In cycle " << cycle << ": " << "Number Overflow" << endl;
    //cout << "reg[32] = " << reg[32] << endl;
    //cout << "reg[33] = " << reg[33] << endl;
    int no_double = 0;
    /*
    if(safe_H == 1)
    {

        if(convert_bin(reg[32]) != convert_bin(temp_HI))
        {
            fout2 << "In cycle " << cycle << ": " << "Overwrite HI-LO registers" << endl;
            no_double = 1;
        }
    }
    if(safe_L == 1 && no_double == 0)
    {
        fout2 << "In cycle " << cycle << ": " << "Overwrite HI-LO registers" << endl;
    }*/
    if(safe_H == 1 && safe_L == 1)
    {
        if(convert_bin(reg[32]) != convert_bin(temp_HI))
        {
//            fout2 << "In cycle " << cycle << ": " << "Overwrite HI-LO registers" << endl;
            no_double = 1;
        }
  //      if(convert_bin(reg[33]) != convert_bin(temp_LO) && no_double == 0)
 //           fout2 << "In cycle " << cycle << ": " << "Overwrite HI-LO registers" << endl;
    }
    if(convert_bin(reg[32]) != convert_bin(temp_HI))
        fout1 << "$HI: " << convert_hex(reg[32]) << endl;
    if(convert_bin(reg[33]) != convert_bin(temp_LO))
        fout1 << "$LO: " << convert_hex(reg[33]) << endl;
    safe_H = 1;
    safe_L = 1;
    reg[34] = reg[34] + 4;
    fout1 << "PC: " << convert_hex(reg[34]) << endl;
    return 0;

}
int ins_multu(char *rs , char *rt)
{
    unsigned long long result = 0;
    unsigned long long temp = 0;
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    long long temp_1 = 0;
    long long temp_2 = 0;
    fout1 << "cycle " << cycle << endl;
    if(reg[t1] < 0 && reg[t2] > 0)
    {
        temp_1 = reg[t1] &4294967295;
        result = temp_1 * reg[t2];
    }

    else if(reg[t2] < 0 && reg[t1] > 0)
    {
        temp_2 = reg[t2] &4294967295;
        result = reg[t1] * temp_2;
    }
    else if(reg[t2] < 0 && reg[t1] < 0)
    {
        temp_1 = reg[t1] &4294967295;
        temp_2 = reg[t2] &4294967295;
        result = temp_1 * temp_2;
    }
    else
        result = reg[t1] * reg[t2];
    long long temp_HI = reg[32];
    long long temp_LO = reg[33];
    //cout << result << endl;
    result = (result&mult_unsign);
    //cout << "HI = " << reg[32] << endl;
    //cout << "LO = " << reg[33] << endl;
    //cout << result << endl;
    reg[32] = result/pow(2,32);
    if(reg[32] > 4294967295)
        reg[32] = reg[32] & 4294967295;
    temp = reg[32] * pow(2,32);
    reg[33] = result - temp ;
    //cout << "HI = " << reg[32] << endl;
    //cout << "LO = " << reg[33] << endl;
    //system("PAUSE");
//    if((reg[32]) > 4294967295 || (reg[33]) > (4294967295))
//        fout2 << "In cycle " << cycle << ": " << "Number Overflow" << endl;
    int no_double = 0;
/*    if(safe_H == 1)
    {
        if(convert_bin(reg[32]) != convert_bin(temp_HI))
        {
            cout << "YY" << endl;
            fout2 << "In cycle " << cycle << ": " << "Overwrite HI-LO registers" << endl;
            no_double = 1;
        }
    }
    if(safe_H == 1 && no_double == 0)
    {
        if(convert_bin(reg[33]) != convert_bin(temp_LO))
        fout2 << "In cycle " << cycle << ": " << "Overwrite HI-LO registers" << endl;
    }*/
    if(safe_H == 1 && safe_L == 1)
    {
        if(convert_bin(reg[32]) != convert_bin(temp_HI))
        {
//            fout2 << "In cycle " << cycle << ": " << "Overwrite HI-LO registers" << endl;
            no_double = 1;
        }
 //       if(convert_bin(reg[33]) != convert_bin(temp_LO) && no_double == 0)
 //           fout2 << "In cycle " << cycle << ": " << "Overwrite HI-LO registers" << endl;
    }
    if(convert_bin(reg[32]) != convert_bin(temp_HI))
        fout1 << "$HI: " << convert_hex(reg[32]) << endl;
    if(convert_bin(reg[33]) != convert_bin(temp_LO))
        fout1 << "$LO: " << convert_hex(reg[33]) << endl;
    safe_H = 1;
    safe_L = 1;
    reg[34] = reg[34] + 4;
    fout1 << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_mfhi(char *rd)
{
    int t1 = convert_dex(rd);
    long long temp = reg[t1];
    fout1 << "cycle " << cycle << endl;
    reg[t1] = reg[32];
    //reg[32] = 0;
    safe_H = 0;
    reg[34] = reg[34] + 4;
    if(t1 == 0){
//        fout2 << "In cycle " << cycle << ": " << "Write $0 Error" << endl;
        reg[t1] = 0;
    }
    if(convert_bin(temp) != convert_bin(reg[t1]))
    {
        if(t1 < 10)
            fout1 << "$0" << t1 << ": " << convert_hex(reg[t1]) << endl;
        else
            fout1 << "$"<<t1 << ": " << convert_hex(reg[t1]) << endl;
    }
    fout1 << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_mflo(char *rd)
{
    int t1 = convert_dex(rd);
    long long temp = reg[t1];
    fout1 << "cycle " << cycle << endl;
    reg[t1] = reg[33];
    //reg[33] = 0;
    safe_L = 0;
    reg[34] = reg[34] + 4;
    if(t1 == 0){
//        fout2 << "In cycle " << cycle << ": " << "Write $0 Error" << endl;
        reg[t1] = 0;
    }
    if(convert_bin(temp) != convert_bin(reg[t1]))
    {
        if(t1 < 10)
            fout1 << "$0" << t1 << ": " << convert_hex(reg[t1]) << endl;
        else
            fout1 << "$"<<t1 << ": " << convert_hex(reg[t1]) << endl;
    }
    fout1 << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
//*****************************************I Type
int ins_addi(char *rs , char *rt , int imm)
{
    int booling = 0;
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    long long temp_1 = 0;
    if(reg[t1] > 2147483647)
        temp_1 = int32_t(reg[t1]);
    else if(reg[t1] < int(-2147483648))
        temp_1 = (reg[t1]) & 2147483647;
    else
        temp_1 = reg[t1];
    fout1 << "cycle " << cycle << endl;
    //cout << "reg[t2] = " <<reg[t2] << endl;
    //cout << "reg[t1] = " << reg[t1] << endl;
    //cout << "imm = " << imm << endl;
    int t3 = imm;
    int temp_sign = 0;
    long long temp = reg[t2];
    reg[t2] = (temp_1) + t3;
    //cout << "reg[t2] = " <<reg[t2] << endl;
    if(t2 == 0){
//        fout2 << "In cycle " << cycle << ": " << "Write $0 Error" << endl;
        booling = 1;
    }
    int no_double = 0;
    if(reg[t2] > 2147483647 || reg[t2] <int(-2147483648))
    {
//        fout2 << "In cycle " << cycle << ": " << "Number Overflow" << endl;
        no_double = 1;
    }
    if((reg[t1] < 0 && imm < 0 && reg[t2] > 0) ||(reg[t1] > 0 && imm > 0 && reg[t2] < 0))
    {
 //       if(no_double == 0)
//        fout2 << "In cycle " << cycle << ": " << "Number Overflow" << endl;
    }
    if(booling == 1)
        reg[t2] = 0;
    if(convert_bin(reg[t2]) != convert_bin(temp)){
        if(t2 < 10)
            fout1 << "$0" << t2 << ": " << convert_hex(reg[t2]) << endl;
        else
            fout1 << "$"<<t2 << ": " << convert_hex(reg[t2]) << endl;
    }
    reg[34] = reg[34] + 4;
    fout1 << "PC: " << convert_hex(reg[34]) << endl;
    return 0;

}
int ins_addiu(char *rs , char *rt , int imm)
{

    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = imm;
    unsigned int temp_num_1 = 0;
    unsigned int temp_num_2 = 0;
    long long temp = reg[t2];
    fout1 << "cycle " << cycle << endl;
    //cout << "reg[t1] = " << reg[t1] << endl;
    //cout << " imm = " << t3 << endl;
    //cout << "reg[t2] = " << reg[t2] << endl;
    reg[t2] = int32_t(reg[t1]) + int32_t(t3) ;
    if(t2 == 0){
//        fout2 << "In cycle " << cycle << ": " << "Write $0 Error" << endl;
        reg[t2] = 0;
    }
    if(reg[t2] > 4294967295)
    {
        reg[t2] = reg[t2] & 4294967295;
    }
    string ttemp = "";
    ttemp = convert_bin(reg[t2]);
    if(ttemp[16] == '1')
    {
        reg[t2] = reg[t2] | 4294901760;
    }
    if(reg[t2] > 4294967295)
    {
        reg[t2] = reg[t2] & 4294967295;
    }
    if(reg[t2] != temp){
        if(t2 < 10)
            fout1 << "$0" << t2 << ": " << convert_hex(reg[t2]) << endl;
        else
            fout1 << "$"<<t2 << ": " << convert_hex(reg[t2]) << endl;
    }
    reg[34] = reg[34] + 4;
    fout1 << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_lw(char *rs , char *rt , int imm , int &d_va)
{
    int booling = 0;
    long long cover = 0;
    int close = 0;
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = imm;//if=4(remember imm is dexc)
    int temp_sign = 0;
    long long add_num = 0;
    long long temp_1 = 0;
    long long temp = reg[t2];
    //cout << reg[t2] << endl;
    //cout << reg[t1] << endl;
    if(reg[t1] > 2147483647)
        temp_1 = int32_t(reg[t1]);
    else if(reg[t1] < int(-2147483648))
        temp_1 = (reg[t1]) & 2147483647;
    else
        temp_1 = reg[t1];
    if(t2 == 0){
//        fout2 << "In cycle " << cycle << ": " << "Write $0 Error" << endl;
        booling = 1;
    }
    add_num = temp_1+(imm);
    cover = add_num;
    //cout << reg[t1] << endl;
    //cout << imm << endl;
    //cout << add_num << endl;
    int no_double = 0;
    if(add_num > 2147483647 || add_num < int(-2147483648))
    {
//        fout2 << "In cycle " << cycle << ": " << "Number Overflow" << endl;
        no_double = 1;
    }
    if((reg[t1] > 0 && imm > 0 && add_num < 0 )|| (reg[t1] < 0 && imm < 0 && add_num > 0))
    {
//        if(no_double == 0)
//        fout2 << "In cycle " << cycle << ": " << "Number Overflow" << endl;
    }
    if(add_num > 1020 || add_num < 0)
    {
 //       fout2 << "In cycle " << cycle << ": " << "Address Overflow" << endl;
        add_num = 0;
        close = 1;
    }
    d_va = add_num;
    //cout << "d_va = " << d_va << endl;
    int start_area = add_num/4;
    int start_word = add_num%4;
    string str_temp = d_mem[start_area+2];
    string str_real = "";
    for(int i = (start_word*8) ; i < ((start_word*8)+32) ; i++)
        str_real += str_temp[i];
    reg[t2] = convert_dex(str_real);
    //cout << imm << endl;
    if(cover % 4 != 0)
    {
 //       fout2 << "In cycle " << cycle << ": " << "Misalignment Error" << endl;
        close = 1;
    }
    if(close == 1)
        return -1;
    if(booling == 1)
        reg[t2] = 0;
    fout1 << "cycle " << cycle << endl;
    //cout << "t2 = " << t2 << endl;
    //cout << "reg[t2] = " << reg[t2] << endl;
    if(convert_bin(reg[t2]) != convert_bin(temp)){
        if(t2 < 10)
            fout1 << "$0" << t2 << ": " << convert_hex(reg[t2]) << endl;
        else
            fout1 << "$"<<t2 << ": " << convert_hex(reg[t2]) << endl;
    }
    reg[34] = reg[34] + 4;
    fout1 << "PC: " << convert_hex(reg[34]) << endl;
    //system("PAUSE");
    return 0;
}
int ins_lh(char *rs , char *rt , int imm, int &d_va)
{
    int booling =0;
    long long cover =0;
    int close = 0;
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = imm;
    int temp_sign = 0;
    long long add_num = 0;
    long long temp = reg[t2];
    long long temp_1 = 0;
    if(reg[t1] > 2147483647)
        temp_1 = int32_t(reg[t1]);
    else if(reg[t1] < int(-2147483648))
        temp_1 = (reg[t1]) & 2147483647;
    else
        temp_1 = reg[t1];
    if(t2 == 0){
//        fout2 << "In cycle " << cycle << ": " << "Write $0 Error" << endl;
        booling = 1;
    }
    add_num = temp_1+(imm);
    cover = add_num;
    int no_double = 0;
    if(add_num > 2147483647 || add_num < int(-2147483648))
    {
 //       fout2 << "In cycle " << cycle << ": " << "Number Overflow" << endl;
        no_double = 1;
    }
    if((reg[t1] > 0 && imm > 0 && add_num < 0 )|| (reg[t1] < 0 && imm < 0 && add_num > 0))
    {
 //       if(no_double == 0)
 //       fout2 << "In cycle " << cycle << ": " << "Number Overflow" << endl;
    }
    if(add_num > 1022 || add_num < 0)
    {
  //      fout2 << "In cycle " << cycle << ": " << "Address Overflow" << endl;
        add_num = 0;
        close = 1;
    }
    d_va = add_num;
    int start_area = add_num/4;
    int start_word = add_num%4;
    string str_temp = d_mem[start_area+2];
    string str_real = "";
    int count = 0;
    if(cover % 2 != 0)
    {
   //     fout2 << "In cycle " << cycle << ": " << "Misalignment Error" << endl;
        close = 1;
    }
    for(int i = (start_word*8) ; i < ((start_word*8)+16) ; i++)
    {
        if(str_temp[start_word*8] == '1')
        {
            if(count < 16)
            {
                str_real += "1";
                i = (start_word*8)-1;
                count ++ ;
            }
            else
            {
                str_real += str_temp[i];
            }
        }
        else if(str_temp[start_word*8] == '0')
        {
            if(count < 16)
            {
                str_real += "0";
                i = (start_word*8)-1;
                count ++ ;
            }
            else
            {
                str_real += str_temp[i];
            }
        }
    }
    reg[t2] = convert_dex(str_real);
    if(close == 1)
        return -1;
    if(booling == 1)
        reg[t2] = 0;
    fout1 << "cycle " << cycle << endl;
    if(convert_bin(reg[t2]) != convert_bin(temp)){
        if(t2 < 10)
            fout1 << "$0" << t2 << ": " << convert_hex(reg[t2]) << endl;
        else
            fout1 << "$"<<t2 << ": " << convert_hex(reg[t2]) << endl;
    }
    reg[34] = reg[34] + 4;
    fout1 << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_lb(char *rs , char *rt , int imm,int &d_va)
{
    int booling = 0;
    int close = 0;
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = imm;
    //fout1 << "t3"<< t3 << endl;
    long long add_num =0;
    int temp_sign=0;
    long long temp = reg[t2];
    long long temp_1 = 0;
    if(reg[t1] > 2147483647)
        temp_1 = int32_t(reg[t1]);
    else if(reg[t1] < int(-2147483648))
        temp_1 = (reg[t1]) & 2147483647;
    else
        temp_1 = reg[t1];
    if(t2 == 0){
  //      fout2 << "In cycle " << cycle << ": " << "Write $0 Error" << endl;
        booling = 1;
    }
    add_num = temp_1+(imm);
    int no_double = 0;
    if(add_num > 2147483647 || add_num < int(-2147483648))
    {
   //     fout2 << "In cycle " << cycle << ": " << "Number Overflow" << endl;
        no_double = 1;
    }
    if((reg[t1] > 0 && imm > 0 && add_num < 0 )|| (reg[t1] < 0 && imm < 0 && add_num > 0))
    {
   //     if(no_double == 0)
  //      fout2 << "In cycle " << cycle << ": " << "Number Overflow" << endl;
    }
    if(add_num > 1023 || add_num < 0)
    {
   //     fout2 << "In cycle " << cycle << ": " << "Address Overflow" << endl;
        add_num = 0;
        close = 1;
    }
    d_va = add_num;
    int start_area = add_num/4;
    int start_word = add_num%4;
    string str_temp = d_mem[start_area+2];
    string str_real = "";
    int count = 0;
    for(int i = (start_word*8) ; i < ((start_word*8)+8) ; i++)
    {
        if(str_temp[start_word*8] == '1')
        {
            if(count < 24)
            {
                str_real += "1";
                i = (start_word*8)-1;
                count ++ ;
            }
            else
            {
                str_real += str_temp[i];
            }
        }
        else if(str_temp[start_word*8] == '0')
        {
            if(count < 24)
            {
                str_real += "0";
                i = (start_word*8)-1;
                count ++ ;
            }
            else
            {
                str_real += str_temp[i];
            }
        }
    }
    reg[t2] = convert_dex(str_real);
    if(close == 1)
        return -1;
    if(booling == 1)
        reg[t2] = 0;
    fout1 << "cycle " << cycle << endl;
    if(convert_bin(reg[t2]) != convert_bin(temp)){
        if(t2 < 10)
            fout1 << "$0" << t2 << ": " << convert_hex(reg[t2]) << endl;
        else
            fout1 << "$"<<t2 << ": " << convert_hex(reg[t2]) << endl;
    }
    reg[34] = reg[34] + 4;
    fout1 << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_lhu(char *rs , char *rt , int imm,int &d_va)//+16-1(imm = 16 bits)
{
    int booling =0;
    long long cover = 0;
    int close = 0;
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = imm;
    //cout << reg[t1] << endl;
    //cout << imm << endl;
    long long temp = reg[t2];
    long long add_num = reg[t1] + imm;
    cover = add_num;
    if(t2 == 0){
   //     fout2 << "In cycle " << cycle << ": " << "Write $0 Error" << endl;
        booling = 1;
    }
  //  if(add_num > 2147483647)
 //   {
   //     fout2 << "In cycle " << cycle << ": " << "Number Overflow" << endl;
 //   }
    if(add_num > 1022 || add_num < 0)
    {
  //      fout2 << "In cycle " << cycle << ": " << "Address Overflow" << endl;
        add_num = 0;
        close = 1;
    }
    d_va = add_num;
    int start_area = add_num/4;
    int start_word = add_num%4;
    string str_temp = d_mem[start_area+2];
    string str_real = "";
    int count = 0;
    if(cover % 2 != 0)
    {
     //   fout2 << "In cycle " << cycle << ": " << "Misalignment Error" << endl;
        close = 1;
    }
    for(int i = (start_word*8) ; i < ((start_word*8)+16) ; i++)
    {
        if(count < 16)
        {
            str_real += "0";
            i = (start_word*8)-1;
            count ++ ;
        }
        else
        {
            str_real += str_temp[i];
        }
    }
    reg[t2] = convert_dex(str_real);
    if(close == 1)
        return -1;
    if(booling == 1)
        reg[t2] = 0;
    fout1 << "cycle " << cycle << endl;
    if(convert_bin(reg[t2]) != convert_bin(temp)){
        if(t2 < 10)
            fout1 << "$0" << t2 << ": " << convert_hex(reg[t2]) << endl;
        else
            fout1 << "$"<<t2 << ": " << convert_hex(reg[t2]) << endl;
    }
    reg[34] = reg[34] + 4;
    fout1 << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_lbu(char *rs , char *rt , int imm,int &d_va)//+16-1(imm = 16 bits)
{
    int booling = 0;
    int close = 0;
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = imm;
    long long temp = reg[t2];
    long long add_num = reg[t1] + imm;
    if(t2 == 0){
    //    fout2 << "In cycle " << cycle << ": " << "Write $0 Error" << endl;
        booling =1 ;
    }
   // if(add_num > 2147483647)
  //  {
  //      fout2 << "In cycle " << cycle << ": " << "Number Overflow" << endl;
  //  }
    if(add_num > 1023 || add_num < 0)
    {
  //      fout2 << "In cycle " << cycle << ": " << "Address Overflow" << endl;
        add_num = 0;
        close = 1;
    }
    d_va = add_num;
    int start_area = add_num/4;
    int start_word = add_num%4;
    string str_temp = d_mem[start_area+2];
    string str_real = "";
    int count = 0;
    for(int i = (start_word*8) ; i < ((start_word*8)+8) ; i++)
    {
        if(count < 24)
        {
            str_real += "0";
            i = (start_word*8)-1;
            count ++ ;
        }
        else
        {
            str_real += str_temp[i];
        }
    }
    d_va = convert_dex(str_real);
    reg[t2] = convert_dex(str_real);
    if(close == 1)
        return -1;
    if(booling == 1)
        reg[t2] = 0;
    fout1 << "cycle " << cycle << endl;
    if(convert_bin(reg[t2]) != convert_bin(temp)){
        if(t2 < 10)
            fout1 << "$0" << t2 << ": " << convert_hex(reg[t2]) << endl;
        else
            fout1 << "$"<<t2 << ": " << convert_hex(reg[t2]) << endl;
    }
    reg[34] = reg[34] + 4;
    fout1 << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_sw(char *rs , char *rt , int imm,int &d_va)
{
    int close = 0;
    long long cover = 0;
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = imm;
    long long add_num =0;
    int temp_sign = 0;
    long long temp = reg[t2];
    long long temp_1 = 0;
    if(reg[t1] > 2147483647)
        temp_1 = int32_t(reg[t1]);
    else if(reg[t1] < int(-2147483648))
        temp_1 = (reg[t1]) & 2147483647;
    else
        temp_1 = reg[t1];
    //cout << "reg[t1] = " << reg[t1] <<endl;
    /*
    if(reg[t1] > 2147483647)
    {
        temp_sign = int32_t(reg[t1]);
        add_num = temp_sign+(imm);
    }
    else
        add_num = reg[t1]+(imm)*/
    add_num = temp_1+(imm);
    cover = add_num;
    //cout << add_num << endl;
    int no_double = 0;
    if(add_num > 2147483647 || add_num < int(-2147483648))
    {
  //      fout2 << "In cycle " << cycle << ": " << "Number Overflow" << endl;
        no_double = 1;
    }
  /*  if((reg[t1] > 0 && imm > 0 && add_num < 0 )|| (reg[t1] < 0 && imm < 0 && add_num > 0))
    {
        if(no_double == 0)
        fout2 << "In cycle " << cycle << ": " << "Number Overflow" << endl;
    }*/
    if(add_num > 1020 || add_num < 0)
    {
    //    fout2 << "In cycle " << cycle << ": " << "Address Overflow" << endl;
        close = 1;
    }
    if(cover % 4 != 0)
    {
   //     fout2 << "In cycle " << cycle << ": " << "Misalignment Error" << endl;
        add_num = 0;
        close = 1;
    }
    d_va = add_num;
    int start_area = add_num/4;
    d_mem[start_area+2]=convert_bin(reg[t2]);
    if(close == 1)
        return -1;
    fout1 << "cycle " << cycle << endl;
    reg[34] = reg[34] + 4;
    fout1 << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_sh(char *rs , char *rt , int imm,int &d_va)
{
    int close = 0;
    long long cover = 0;
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = imm;
    long long add_num = 0;
    int temp_sign = 0;
    long long temp = reg[t2];
    long long temp_a = 0;
    if(reg[t1] > 2147483647)
        temp_a = int32_t(reg[t1]);
    else if(reg[t1] < int(-2147483648))
        temp_a = (reg[t1]) & 2147483647;
    else
        temp_a = reg[t1];
    add_num = temp_a+(imm);
    cover = add_num;
    int no_double = 0;
    if(add_num > 2147483647 || add_num < int(-2147483648))
    {
    //    fout2 << "In cycle " << cycle << ": " << "Number Overflow" << endl;
        no_double = 1;
    }
  /*  if((reg[t1] > 0 && imm > 0 && add_num < 0 )|| (reg[t1] < 0 && imm < 0 && add_num > 0))
    {
        if(no_double == 0)
   //     fout2 << "In cycle " << cycle << ": " << "Number Overflow" << endl;
    }*/
    if(add_num > 1022 || add_num < 0)
    {
   //     fout2 << "In cycle " << cycle << ": " << "Address Overflow" << endl;
        add_num = 0;
        close = 1;
    }
    if(cover % 2 != 0)
    {
   //     fout2 << "In cycle " << cycle << ": " << "Misalignment Error" << endl;
        close = 1;
    }
    if(close == 1)
        return -1;
    d_va = add_num;
    fout1 << "cycle " << cycle << endl;
    int start_area = add_num/4;
    int start_word = add_num%4;
    d_mem[start_area+2];
    unsigned int temp_1 = 0;
    unsigned int temp_2 = 0;
    if(start_word == 0)
    {
        temp_1 = reg[t2]&65535;
        temp_1 = temp_1 << 16;
        temp_2 = convert_dex(d_mem[start_area+2])&65535;
        d_mem[start_area+2] = convert_bin(temp_1+temp_2);
    }
    else
    {
        temp_1 = reg[t2]&65535;//low
        temp_2 = convert_dex(d_mem[start_area+2])&4294901760;//(2^32-1)-(2^16-1) high
        d_mem[start_area+2] = convert_bin(temp_1+temp_2);
    }
    reg[34] = reg[34] + 4;
    fout1 << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_sb(char *rs , char *rt , int imm,int &d_va)
{
    int close = 0;
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = imm;
    int temp_sign = 0;
    long long add_num = 0;
    long long temp = reg[t2];
    long long temp_a = 0;
    if(reg[t1] > 2147483647)
        temp_a = int32_t(reg[t1]);
    else if(reg[t1] < int(-2147483648))
        temp_a = (reg[t1]) & 2147483647;
    else
        temp_a = reg[t1];
    add_num = temp_a+imm;
    int no_double = 0;
    if(add_num > 2147483647 || add_num < int(-2147483648))
    {
    //    fout2 << "In cycle " << cycle << ": " << "Number Overflow" << endl;
        no_double = 1;
    }
 /*   if((reg[t1] > 0 && imm > 0 && add_num < 0 )|| (reg[t1] < 0 && imm < 0 && add_num > 0))
    {
        if(no_double == 0)
        fout2 << "In cycle " << cycle << ": " << "Number Overflow" << endl;
    }*/
    if(add_num > 1023 || add_num < 0)
    {
    //    fout2 << "In cycle " << cycle << ": " << "Address Overflow" << endl;
        add_num = 0;
        close = 1;
    }
    if(close == 1)
        return -1;
    d_va = add_num;
    fout1 << "cycle " << cycle << endl;
    int start_area = add_num/4;
    int start_word = add_num%4;
    d_mem[start_area+2];
    unsigned int temp_1 = 0;
    unsigned int temp_2 = 0;
    unsigned int temp_3 = 0;
    if(start_word == 0)
    {
        temp_1 = reg[t2]&255;//low
        temp_1 = temp_1 << 24;
        temp_2 = convert_dex(d_mem[start_area+2])&16777215;//(2^32-1)-(2^16-1) high
        d_mem[start_area+2] = convert_bin(temp_1+temp_2);
    }
    else if(start_word == 1)
    {
        temp_1 = reg[t2]&255;//low
        temp_1 = temp_1 << 16;
        temp_2 = convert_dex(d_mem[start_area+2])&4278190079;
        temp_3 = convert_dex(d_mem[start_area+2])&65535;
        d_mem[start_area+2] = convert_bin(temp_1+temp_2+temp_3);
    }
    else if(start_word == 2)
    {
        temp_1 = reg[t2]&255;//low
        temp_1 = temp_1 << 8;
        temp_2 = convert_dex(d_mem[start_area+2])&4294901760;//(2^32-1)-(2^16-1) high
        temp_3 = convert_dex(d_mem[start_area+2])&255;
        d_mem[start_area+2] = convert_bin(temp_1+temp_2+temp_3);
    }
    else
    {
        temp_1 = reg[t2]&255;//low
        temp_2 = convert_dex(d_mem[start_area+2])&4294967040;//(2^32-1)-(2^16-1) high
        d_mem[start_area+2] = convert_bin(temp_1+temp_2);
    }
    reg[34] = reg[34] + 4;
    fout1 << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_lui( char *rt , int imm)
{
    int t2 = convert_dex(rt);
    long long temp = reg[t2];
    fout1 << "cycle " << cycle << endl;
    reg[t2] = imm << 16;
    if(t2 == 0){
   //     fout2 << "In cycle " << cycle << ": " << "Write $0 Error" << endl;
        reg[t2] = 0;
    }
    if(convert_bin(reg[t2]) != convert_bin(temp)){
        if(t2 < 10)
            fout1 << "$0" << t2 << ": " << convert_hex(reg[t2]) << endl;
        else
            fout1 << "$"<<t2 << ": " << convert_hex(reg[t2]) << endl;
    }
    reg[34] = reg[34] + 4;
    fout1 << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_andi(char *rs , char *rt , int imm)
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = imm;
    long long temp = reg[t2];
    fout1 << "cycle " << cycle << endl;
    if(t2 == 0){
   //     fout2 << "In cycle " << cycle << ": " << "Write $0 Error" << endl;
        reg[t2] = 0;
    }
    if(imm < 0)
    {
        unsigned long long  j = (unsigned long long ) imm;
        j = j & 4294967295;
        imm = j;
    }
    reg[t2] = reg[t1]&imm;
    if(convert_bin(reg[t2]) != convert_bin(temp)){
        if(t2 < 10)
            fout1 << "$0" << t2 << ": " << convert_hex(reg[t2]) << endl;
        else
            fout1 << "$"<<t2 << ": " << convert_hex(reg[t2]) << endl;
    }
    reg[34] = reg[34] + 4;
    fout1 << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_ori(char *rs , char *rt , int imm)
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = imm;
    long long temp = reg[t2];
    fout1 << "cycle " << cycle << endl;
    if(imm < 0)
    {
        unsigned long long  j = (unsigned long long ) imm;
        j = j & 4294967295;
        imm = j;
    }
    reg[t2] = reg[t1]|imm;
    if(t2 == 0){
   //     fout2 << "In cycle " << cycle << ": " << "Write $0 Error" << endl;
        reg[t2] = 0;
    }
    if(convert_bin(reg[t2]) != convert_bin(temp)){
        if(t2 < 10)
            fout1 << "$0" << t2 << ": " << convert_hex(reg[t2]) << endl;
        else
            fout1 << "$"<<t2 << ": " << convert_hex(reg[t2]) << endl;
    }
    reg[34] = reg[34] + 4;
    fout1 << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_nori(char *rs , char *rt , int imm)
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = imm;
    long long temp = reg[t2];
    fout1 << "cycle " << cycle << endl;
    if(imm < 0)
    {
        unsigned long long  j = (unsigned long long ) imm;
        j = j & 4294967295;
        imm = j;
    }
    reg[t2] = ~(reg[t1]|imm);
    if(t2 == 0){
   //     fout2 << "In cycle " << cycle << ": " << "Write $0 Error" << endl;
        reg[t2] = 0;
    }
    if(convert_bin(reg[t2]) != convert_bin(temp)){
        if(t2 < 10)
            fout1 << "$0" << t2 << ": " << convert_hex(reg[t2]) << endl;
        else
            fout1 << "$"<<t2 << ": " << convert_hex(reg[t2]) << endl;
    }
    reg[34] = reg[34] + 4;
    fout1 << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_slti(char *rs , char *rt , int imm)
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = imm;
    long long temp = reg[t2];
    fout1 << "cycle " << cycle << endl;
    long long temp_1 = 0;
    /*
    if(imm < 0)
    {
        unsigned long long  j = (unsigned long long ) imm;
        j = j & 4294967295;
        imm = j;
    }*/
    if(reg[t1] > 2147483647) //from overflow error
        temp_1 = int32_t(reg[t1]);
    else if(reg[t1] < int(-2147483648))
        temp_1 = (reg[t1]) & 2147483647;
    else
        temp_1 = reg[t1];
    if(temp_1 < imm) // <X -> 1
        reg[t2] = 1;
    else
        reg[t2] = 0;
    if(t2 == 0){
  //      fout2 << "In cycle " << cycle << ": " << "Write $0 Error" << endl;
        reg[t2] = 0;
    }
    if(reg[t2] != temp){
        if(t2 < 10)
            fout1 << "$0" << t2 << ": " << convert_hex(reg[t2]) << endl;
        else
            fout1 << "$"<<t2 << ": " << convert_hex(reg[t2]) << endl;
    }
    reg[34] = reg[34] + 4;
    fout1 << "PC: " << convert_hex(reg[34]) << endl;
    return 0;
}
int ins_beq(char *rs , char *rt , int imm) // ==
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = imm;
    long long temp = reg[t2];
    fout1 << "cycle " << cycle << endl;
    long long temp_1 = 0;
    long long temp_2 = 0;
    //cout << "reg[t1] = " << reg[t1] <<endl;
    //cout << "reg[t2] = " << reg[t2] <<endl;
    if(reg[t1] > 2147483647)
        temp_1 = int32_t(reg[t1]);
    else if(reg[t1] < int(-2147483648))
        temp_1 = (reg[t1]) & 2147483647;
    else
        temp_1 = reg[t1];
    if(reg[t2] > 2147483647)
        temp_2 = int32_t(reg[t2]);
    else if(reg[t2] < int(-2147483648))
        temp_2 = (reg[t2]) & 2147483647;
    else
        temp_2 = reg[t2];
    //cout << "reg[t1] = " << reg[t1] <<endl;
    //cout << "reg[t2] = " << reg[t2] <<endl;
    //system("PAUSE");
    if(temp_1 == temp_2)
    {
        lock_num = 0;
        lock = 0;
    }
    else
    {
        lock = 1;
    }
    if(lock == 0)
    {
        reg[34] = reg[34] + 4 + (4*imm);
        fout1 << "PC: " << convert_hex(reg[34]) << endl;
        return (imm);
    }
    else
    {
        reg[34] = reg[34] + 4;
        fout1 << "PC: " << convert_hex(reg[34]) << endl;
    }
    if(lock == 1 && lock_num != 0)
        lock_num = 0;
    return 0;
}
int ins_bne(char *rs , char *rt , int imm) // !=
{
    int t1 = convert_dex(rs);
    int t2 = convert_dex(rt);
    int t3 = imm;
    long long temp = reg[t2];
    long long temp_1 =0;
    long long temp_2 = 0;
    if(reg[t1] > 2147483647)
        temp_1 = int32_t(reg[t1]);
    else if(reg[t1] < int(-2147483648))
        temp_1 = (reg[t1]) & 2147483647;
    else
        temp_1 = reg[t1];
    if(reg[t2] > 2147483647)
        temp_2 = int32_t(reg[t2]);
    else if(reg[t2] < int(-2147483648))
        temp_2 = (reg[t2]) & 2147483647;
    else
        temp_2 = reg[t2];
    fout1 << "cycle " << cycle << endl;
    //fout1 << reg[t1] << endl;
    //fout1 << reg[t2] << endl;
    if(temp_1 != temp_2)
    {
        lock_num = 0;
        lock = 0;
    }
    else
    {
        lock = 1;
    }
    if(lock == 0)
    {
        reg[34] = reg[34] + 4 + (4*imm);
        fout1 << "PC: " << convert_hex(reg[34]) << endl;
        return (imm);
    }
    else
    {
        reg[34] = reg[34] + 4;
        fout1 << "PC: " << convert_hex(reg[34]) << endl;
    }
    if(lock == 1 && lock_num != 0)
        lock_num = 0;
    return 0;
}
int ins_bgtz(char *rs, int imm) // !=
{
    int t1 = convert_dex(rs);
    int t3 = imm;
    long long temp_1 = 0;
    if(reg[t1] > 2147483647)
        temp_1 = int32_t(reg[t1]);
    else if(reg[t1] < int(-2147483648))
        temp_1 = (reg[t1]) & 2147483647;
    else
        temp_1 = reg[t1];
    fout1 << "cycle " << cycle << endl;
    //cout << "reg[t1] = "<< reg[t1] << endl;
    if(temp_1 > 0)
    {
        lock_num = 0;
        lock = 0;
    }
    else
    {
        lock = 1;
    }
    //cout << lock << endl;
    if(lock == 0)
    {
        reg[34] = reg[34] + 4 + (4*imm);
        fout1 << "PC: " << convert_hex(reg[34]) << endl;
        return imm;
    }
    else
    {
        reg[34] = reg[34] + 4;
        fout1 << "PC: " << convert_hex(reg[34]) << endl;
    }
    if(lock == 1 && lock_num != 0)
        lock_num = 0;
    return 0;
}
int ins_j(int address) //come back
{
    //cout << "YY" << endl;
    //fout1 << "j" << endl;
    int next_pos = 0;
    fout1 << "cycle " << cycle << endl;
    next_pos = (int(reg[34])-address)/4;
    reg[34] = address;
    fout1 << "PC: " << convert_hex(reg[34]) << endl;
    return (next_pos);

}
int ins_jal(int address) // come back
{
    //fout1 << "jal" << endl;
    fout1 << "cycle " << cycle << endl;
    int next_pos = 0;
    unsigned int temp = reg[31];
    reg[31] = reg[34]+4;
    reg[34] = address;
    next_pos = (reg[34]-reg[31])/4;
    if(convert_bin(temp) != convert_bin(reg[31]))
        fout1 << "$31: " << convert_hex(reg[31]) << endl;
    fout1 << "PC: " << convert_hex(reg[34]) << endl;
    return (next_pos);
}
void no_ins()
{
    fout1 << "cycle " << cycle << endl;
    reg[34] = reg[34] + 4;
    fout1 << "PC: " << convert_hex(reg[34]) << endl;
}
string conver_to_decode(int label , string opcode = "" , string func = "")
{
    string type_r[17] = {"add" , "addu" , "sub" , "and" , "or" ,
                       "xor" , "nor" , "nand" , "slt" , "sll" ,
                       "srl" , "sra" , "jr" , "mult" , "multu" ,
                       "mfhi" , "mflo"};
    string r_fun[17] = {"100000" , "100001" , "100010" , "100100" , "100101" ,
                     "100110" , "100111" , "101000" , "101010" , "000000" ,
                     "000010" , "000011" , "001000" , "011000" , "011001",
                     "010000" , "010010"};

    string type_i[18] = {"addi" , "addiu" , "lw" , "lh" , "lhu" ,
                       "lb" , "lbu" , "sw" , "sh" , "sb" ,
                       "lui" , "andi" , "ori" , "nori" , "slti" ,
                       "beq" , "bne" , "bgtz"};
    string i_opcode[18] = {"001000" , "001001" , "100011" , "100001" , "100101",
                         "100000" , "100100" , "101011" , "101001" , "101000",
                         "001111" , "001100" , "001101" , "001110" , "001010",
                         "000100" , "000101" , "000111"};
    string type_j[2] = {"j", "jal"};
    string j_opcode[2] = {"000010" , "000011"};
    string type_s[1] = {"halt"};
    string s_opcode[1] = {"111111"};
    if(label == 1) // divide and conquer
    {
        for(int i = 0; i < 17 ;i++)
        {
            string op = r_fun[i];
            if(op == func)
                return type_r[i];
            if(i == 16)
                return "no instrument";
        }
    }
    else if(label == 2)
    {
        for(int i = 0; i < 18 ;i++)
        {
            string op = i_opcode[i];
            if(op == opcode)
                return type_i[i];
            if(i == 17)
                return "no instrument";
        }

    }
    else if(label == 3)
    {
        if(j_opcode[0] == opcode)
            return type_j[0];
        else if(j_opcode[1] == opcode)
            return type_j[1];
        else
            return "no instrument";
    }
    else
    {
        if(s_opcode[0] == opcode)
            return type_s[0];
        else
            return "no instrument";

    }

}
int main(int argc, char ** argv)
{
    fout1.open("snapshot.rpt");
    fout3.open("report.rpt");
    FILE* fp;
    fp = fopen("iimage.bin" , "rb");
    if (!fp)
        return 1 ;
    unsigned char buff;
    vector<unsigned char>inst;
    //int cnt = 0, line = 0;
    while(fread(&buff,sizeof(char),1,fp) == 1)
    {
        inst.push_back(buff);

    }
    fclose(fp);
    vector<string >binary;
    string tempbin = "";
    for(int i = 0 ; i < inst.size() ; i++)
    {
        bitset<8> bin(inst[i]); //nest block bin is new declare
        string str = bin.to_string<char,std::string::traits_type,std::string::allocator_type>();
        tempbin = tempbin + str;
        if((i+1)%4 == 0)
        {
            binary.push_back(tempbin);
            tempbin = "";
        }
    }
    inst.clear();
    //dimage open ******************************************************************
    FILE* fp_2;
    fp_2 = fopen("dimage.bin" , "rb");
    if (!fp_2)
        return 1 ;
    unsigned char buff_2;
    vector<unsigned char>d_bin;
    while(fread(&buff_2,sizeof(char),1,fp_2) == 1)
    {
        d_bin.push_back(buff_2);

    }
    fclose(fp_2);
    string tempbin_2 = "";
    for(int i = 0 ; i < d_bin.size() ; i++)
    {
        bitset<8> bin(d_bin[i]); //nest block bin is new declare
        string str = bin.to_string<char,std::string::traits_type,std::string::allocator_type>();
        tempbin_2 = tempbin_2 + str;
        if((i+1)%4 == 0)
        {
            d_mem.push_back(tempbin_2);
            tempbin_2 = "";
        }
    }
    d_bin.clear();
    for(int i = 0 ; i < 512 ; i++)
    {
        if(i >= d_mem.size())
            d_mem.push_back(convert_bin(0));
    }
    //vector<string > ins;
    //int* label = (int*) malloc (sizeof(int));
    // initial register
    fout1 << "cycle " << cycle << endl;
    for(int i = 0 ; i < 35 ; i++)
    {
        if(i == 29)
            reg.push_back(convert_dex(d_mem[0]));
        else if (i == 34)
            reg.push_back(convert_dex(binary[0]));
        else
            reg.push_back(0x00);
    }
    for(int i = 0 ; i < 35 ; i++)
    {
        if(i < 10)
            fout1 << "$0" << i << ": " << convert_hex(reg[i]) << endl;
        else if (i == 32)
            fout1 << "$HI: " << convert_hex(reg[i]) << endl;
        else if (i == 33)
            fout1 << "$LO: " << convert_hex(reg[i]) << endl;
        else if (i == 34)
            fout1 << "PC: " << convert_hex(reg[i]) << endl;
        else
            fout1 << "$" << i << ": " << convert_hex(reg[i]) << endl;
    }
    fout1 << endl;
    fout1 << endl;
//************************************************************************************************
    int i_tlb_hit = 0;
    int i_tlb_miss = 0;
    int i_page_hit = 0;
    int i_page_miss = 0;
    int i_cache_hit = 0;
    int i_cache_miss = 0;
    int d_tlb_hit = 0;
    int d_tlb_miss = 0;
    int d_page_hit = 0;
    int d_page_miss = 0;
    int d_cache_hit = 0;
    int d_cache_miss = 0;
//  unit : byte
//-----------------------------------------
    vector<string>cmd;
    for(int i = 0 ; i < argc ; i++)
    {
        //cout << argv[i] << endl;
        cmd.push_back(argv[i]);
        //cout << temp[i] << endl;
    }
    int A = 64;
    int B = 32;
    int C = 8;
    int D = 16;
    int E = 16;
    int F = 4;
    int G = 4;
    int H = 16;
    int I = 4;
    int J = 1;
    for(int i = 0 ; i < cmd.size() ; i++)
    {
        if(i == 1)
            A = atoi(cmd[1].c_str());
        else if(i == 2)
            B = atoi(cmd[2].c_str());
        else if(i == 3)
            C = atoi(cmd[3].c_str());
        else if(i == 4)
            D = atoi(cmd[4].c_str());
        else if(i == 5)
            E = atoi(cmd[5].c_str());
        else if(i == 6)
            F = atoi(cmd[6].c_str());
        else if(i == 7)
            G = atoi(cmd[7].c_str());
        else if(i == 8)
            H = atoi(cmd[8].c_str());
        else if(i == 9)
            I = atoi(cmd[9].c_str());
        else if(i == 10)
            J = atoi(cmd[10].c_str());
    }
    cmd.clear();
    int i_mem_cmp = A;
    int d_mem_cmp = B;
    const int i_page = C;
    const int d_page = D;
    const int i_cache_size = E;
    const int i_block = F;
    const int i_way = G;
    const int d_cache_size = H;
    const int d_block = I;
    const int d_way = J;
    /*
    int i_mem_cmp = 64;
    int d_mem_cmp = 32;
    const int i_page = 8;
    const int d_page = 16;
    const int i_cache_size = 16;
    const int i_block = 4;
    const int i_way = 4;
    const int d_cache_size = 16;
    const int d_block = 4;
    const int d_way = 1;*/
//----------------------------------------
    const int i_page_entry = 1024/i_page;
    const int d_page_entry = 1024/d_page;
    int i_len = row_2(i_page_entry);
    int d_len = row_2(d_page_entry);
    int i_off_re = row_2(i_block);
    int d_off_re = row_2(d_block);
    int i_phy_num_max = i_mem_cmp / i_page;
    int d_phy_num_max = d_mem_cmp / d_page;
    string i_page_table[i_page_entry][4] = {{}};
    string i_tlb[i_page_entry/4][4] = {{}};
    string i_cache[i_cache_size/i_way/i_block][i_way] = {{}};
    string d_page_table[d_page_entry][4] = {{}};
    string d_tlb[d_page_entry/4][4] = {{}};
    string d_cache[d_cache_size/d_way/d_block][d_way] = {{}};
    int i_phy_num = 0;
    int i_t_lru[i_page_entry/4] = {0};
    for(int qq = 0 ; qq < (i_page_entry/4) ; qq++)
        i_t_lru[qq] = 0;
    int i_page_lru[i_page_entry/4] = {0};//max <= phy_max
    for(int qq = 0 ; qq < (i_page_entry/4) ; qq++)
        i_page_lru[qq] = 0;
    int i_page_count = 1;//if u_count == phy_max then clear i_page_lru oldest
    bool i_plru[i_cache_size/i_way/i_block][i_way] = {{0}};
    for(int qq = 0 ; qq < (i_cache_size/i_way/i_block) ; qq++)
        for(int ww = 0 ; ww < i_way ; ww++)
            i_plru[qq][ww] = 0;
    int d_phy_num = 0;
    int d_t_lru[d_page_entry/4] = {0};
    for(int qq = 0 ; qq < (d_page_entry/4) ; qq++)
        d_t_lru[qq] = 0;
    int d_page_lru[i_page_entry/4] = {0};//max <= phy_max
    for(int qq = 0 ; qq < (d_page_entry/4) ; qq++)
        d_page_lru[qq] = 0;
    int d_page_count = 1;
    bool d_plru[d_cache_size/d_way/d_block][d_way] = {{0}};
    for(int qq = 0 ; qq < (d_cache_size/d_way/d_block) ; qq++)
        for(int ww = 0 ; ww < d_way ; ww++)
            d_plru[qq][ww] = 0;
    for(int i = 2 ; i < int(binary.size()); i++)
    {
//********************************************************
        int d_addr = 0;
        string addr = convert_bin(reg[34]);
        //addr = str_cut(addr , 22 , 29);
        int i_end = 22 + i_len - 1;
        string i_vpn = str_cut(addr, 22 , i_end);//22-29:8
        string i_offset = str_cut(addr, i_end ,31-i_off_re);
        //cout << "i_vpn = " << i_vpn << endl;
        //cout << "i_offset = " << i_offset << endl;
        //system("PAUSE");
        int dec_i_vpn = convert_dex(i_vpn);
        int i_tlb_num = dec_i_vpn%(i_page_entry/4);
        int i_t_hit = 0;
        string i_ppn = "";
        for(int ti = 0 ; ti < (i_page_entry/4) ; ti++)
        {
            if(i_tlb[ti][2] == i_vpn)
            {
                if(i_t_lru[ti] != 0)
                {
                    i_tlb_hit++;
                    i_t_hit = 1;
                    i_ppn = i_tlb[ti][3];
                    int old_tlb_count = i_t_lru[ti];
                    i_t_lru[ti] = 1;
                    for(int tk = 0 ; tk < (i_page_entry/4) ; tk++)
                    {
                        if(tk != ti && i_t_lru[tk] < old_tlb_count && i_t_lru[tk] != 0)
                            i_t_lru[tk] = i_t_lru[tk] + 1;
                    }
                }
                else
                {
                    i_tlb_miss++;
                    i_t_hit = 2;
                    i_tlb[ti][2] = i_vpn;
                    if(i_page_table[dec_i_vpn][2] != "")
                    {
                        if(i_page_lru[dec_i_vpn] != 0) //i_page_hit
                        {
                            int i_page_count = i_page_lru[dec_i_vpn];
                            i_page_lru[dec_i_vpn] = 1;
                            i_page_hit++;
                            i_tlb[ti][3] = i_page_table[dec_i_vpn][3];
                            i_ppn = i_tlb[ti][3];
                            for(int tk = 0 ; tk < (i_page_entry/4) ; tk++)
                            {
                                if(tk != dec_i_vpn && i_page_lru[tk] != 0 && i_page_lru[tk] < i_page_lru[dec_i_vpn])
                                    i_page_lru[tk] = i_page_lru[tk] + 1;
                            }
                        }
                        else
                        {
                            i_page_lru[dec_i_vpn] = 1;
                            i_page_miss++;
                            if(i_phy_num == i_phy_num_max)
                                i_phy_num = 0;
                            i_page_table[dec_i_vpn][3] = to_str(i_phy_num);
                            i_tlb[ti][3] = to_str(i_phy_num);
                            i_ppn = i_tlb[ti][3];
                            i_phy_num++;
                            for(int tk = 0 ; tk < (i_page_entry/4) ; tk++)
                            {
                                if(i_page_lru[tk] == i_phy_num_max)
                                    i_page_lru[tk] = 0;
                                else if(tk != dec_i_vpn && i_page_lru[tk] != 0)
                                    i_page_lru[tk] = i_page_lru[tk] + 1;
                            }

                        }

                    }
                    else
                    {
                        i_page_lru[dec_i_vpn] = 1;
                        i_page_miss++;
                        if(i_phy_num == i_phy_num_max)
                            i_phy_num = 0;
                        i_page_table[dec_i_vpn][3] = to_str(i_phy_num);
                        i_tlb[ti][3] = to_str(i_phy_num);
                        i_ppn = i_tlb[ti][3];
                        i_phy_num++;
                        for(int tk = 0 ; tk < (i_page_entry/4) ; tk++)
                        {
                            if(i_page_lru[tk] == i_phy_num_max)
                                i_page_lru[tk] = 0;
                            else if(tk != dec_i_vpn && i_page_lru[tk] != 0)
                                i_page_lru[tk] = i_page_lru[tk] + 1;
                        }
                    }
                    i_t_lru[ti] = 1;
                    for(int tk = 0 ; tk < (i_page_entry/4) ; tk++)
                    {
                        if(tk != ti && i_t_lru[tk] != 0)
                            i_t_lru[tk] = i_t_lru[tk] + 1;
                        if(i_t_lru[tk] > i_phy_num_max)
                            i_t_lru[tk] = 0;
                    }

                }
                break;
            }
            else if(i_tlb[ti][2] == "")
            {
                i_tlb_miss++;
                i_t_hit = 2;
                i_tlb[ti][2] = i_vpn;
                if(i_page_table[dec_i_vpn][2] != "")
                {
                    if(i_page_lru[dec_i_vpn] != 0) //i_page_hit
                    {
                        int i_page_count = i_page_lru[dec_i_vpn];
                        i_page_lru[dec_i_vpn] = 1;
                        i_page_hit++;
                        i_tlb[ti][3] = i_page_table[dec_i_vpn][3];
                        i_ppn = i_tlb[ti][3];
                        for(int tk = 0 ; tk < (i_page_entry/4) ; tk++)
                        {
                            if(tk != dec_i_vpn && i_page_lru[tk] != 0 && i_page_lru[tk] < i_page_lru[dec_i_vpn])
                                i_page_lru[tk] = i_page_lru[tk] + 1;
                        }
                    }
                    else
                    {
                        i_page_lru[dec_i_vpn] = 1;
                        i_page_miss++;
                        if(i_phy_num == i_phy_num_max)
                            i_phy_num = 0;
                        i_page_table[dec_i_vpn][3] = to_str(i_phy_num);
                        i_tlb[ti][3] = to_str(i_phy_num);
                        i_ppn = i_tlb[ti][3];
                        i_phy_num++;
                        for(int tk = 0 ; tk < (i_page_entry/4) ; tk++)
                        {
                            if(i_page_lru[tk] == i_phy_num_max)
                                i_page_lru[tk] = 0;
                            else if(tk != dec_i_vpn && i_page_lru[tk] != 0)
                                i_page_lru[tk] = i_page_lru[tk] + 1;
                        }

                    }

                }
                else
                {
                    i_page_lru[dec_i_vpn] = 1;
                    i_page_miss++;
                    if(i_phy_num == i_phy_num_max)
                        i_phy_num = 0;
                    i_page_table[dec_i_vpn][3] = to_str(i_phy_num);
                    i_tlb[ti][3] = to_str(i_phy_num);
                    i_ppn = i_tlb[ti][3];
                    i_phy_num++;
                    for(int tk = 0 ; tk < (i_page_entry/4) ; tk++)
                    {
                        if(i_page_lru[tk] == i_phy_num_max)
                            i_page_lru[tk] = 0;
                        else if(tk != dec_i_vpn && i_page_lru[tk] != 0)
                            i_page_lru[tk] = i_page_lru[tk] + 1;
                    }
                }
                i_t_lru[ti] = 1;
                for(int tk = 0 ; tk < (i_page_entry/4) ; tk++)
                {
                    if(tk != ti && i_t_lru[tk] != 0)
                        i_t_lru[tk] = i_t_lru[tk] + 1;
                }
                break;
            }
        }
        if(i_t_hit == 0)
        {
            for(int ti = 0 ; ti < (i_page_entry/4) ; ti++)
            {
                if(i_t_lru[ti] == ((i_page_entry/4)-1))
                {
                    i_t_hit = 2;
                    i_tlb_miss++;
                    i_tlb[ti][2] = i_vpn;
                    if(i_page_table[dec_i_vpn][2] != "")
                    {
                        //
                        if(i_page_lru[dec_i_vpn] != 0) //i_page_hit
                        {
                            int i_page_count = i_page_lru[dec_i_vpn];
                            i_page_lru[dec_i_vpn] = 1;
                            i_page_hit++;
                            i_tlb[ti][3] = i_page_table[dec_i_vpn][3];
                            i_ppn = i_tlb[ti][3];
                            for(int tk = 0 ; tk < (i_page_entry/4) ; tk++)
                            {
                                if(tk != dec_i_vpn && i_page_lru[tk] != 0 && i_page_lru[tk] < i_page_count)
                                    i_page_lru[tk] = i_page_lru[tk] + 1;
                            }
                        }
                        else
                        {
                            i_page_lru[dec_i_vpn] = 1;
                            i_page_miss++;
                            if(i_phy_num == i_phy_num_max)
                                i_phy_num = 0;
                            i_page_table[dec_i_vpn][3] = to_str(i_phy_num);
                            i_tlb[ti][3] = to_str(i_phy_num);
                            i_ppn = i_tlb[ti][3];
                            i_phy_num++;
                            for(int tk = 0 ; tk < (i_page_entry/4) ; tk++)
                            {
                                if(i_page_lru[tk] == i_phy_num_max)
                                    i_page_lru[tk] = 0;
                                else if(tk != dec_i_vpn && i_page_lru[tk] != 0)
                                    i_page_lru[tk] = i_page_lru[tk] + 1;
                            }
                        }
                        //
                    }
                    else
                    {
                        i_page_lru[dec_i_vpn] = 1;
                        i_page_miss++;
                        if(i_phy_num == i_phy_num_max)
                            i_phy_num = 0;
                        i_page_table[dec_i_vpn][3] = to_str(i_phy_num);
                        i_tlb[ti][3] = to_str(i_phy_num);
                        i_ppn = i_tlb[ti][3];
                        i_phy_num++;
                        for(int tk = 0 ; tk < (i_page_entry/4) ; tk++)
                        {
                            if(i_page_lru[tk] == i_phy_num_max)
                                i_page_lru[tk] = 0;
                            else if(tk != dec_i_vpn && i_page_lru[tk] != 0)
                                i_page_lru[tk] = i_page_lru[tk] + 1;
                        }
                    }
                    i_t_lru[ti] = 1;
                    for(int tk = 0 ; tk < (i_page_entry/4) ; tk++)
                    {
                        if(tk != ti && i_t_lru[tk] != 0)
                            i_t_lru[tk] = i_t_lru[tk] + 1;
                    }
                    break;
                }
            }

        }
//********************************************************cache!!!!!!!
        string i_ppa = i_ppn+ i_offset;
        //cout << "i_ppa = " << i_ppa << endl;
        int i_c_h = 0;
        int i_cache_set = convert_dex(i_ppa)%(i_cache_size/i_way/i_block);
        //cout << "set = " << i_cache_set << endl;
        for(int cs = 0 ; cs < i_way ; cs++)
        {
            //cout << "i_cache[i_cache_set][cs] = " << i_cache[i_cache_set][cs] << endl;
            if(i_cache[i_cache_set][cs] == i_ppa)
            {
                i_c_h = 1;
                i_cache_hit++;
                int bit_count = 0;
                //cout << "block_h = " << cs << endl;
                for(int tn = 0 ; tn < i_way ; tn++)
                {
                    if(i_plru[i_cache_set][tn] == 1)
                        bit_count++;
                }
                if(bit_count == (i_way - 1))
                {
                    for(int tn = 0 ; tn < i_way ; tn++)
                    {
                        if(i_plru[i_cache_set][tn] == 1)
                            i_plru[i_cache_set][tn] = 0;
                        else
                            i_plru[i_cache_set][tn] = 1;
                    }
                }
                else
                {
                    i_plru[i_cache_set][cs] = 1;
                }
                break;
            }
        }
        if(i_c_h != 1)
        {

            i_cache_miss++;
            for(int cs = 0 ; cs < i_way ; cs++)
            {
                //cout << " cs" << cs << " = " << i_plru[i_cache_set][cs] << endl;
                if(i_plru[i_cache_set][cs] == 0)
                {
                    //cout << "block = " << cs << endl;

                    i_cache[i_cache_set][cs] = i_ppa;
                    //cout << "i_ppa = " << endl;
                    //cout << "i_cache[i_cache_set][cs] = " << i_cache[i_cache_set][cs] << endl;
                    //system("PAUSE");
                    int bit_count = 0;
                    for(int tn = 0 ; tn < i_way ; tn++)
                    {
                        if(i_plru[i_cache_set][tn] == 1)
                            bit_count++;
                    }
                    if(bit_count == (i_way - 1))
                    {
                        for(int tn = 0 ; tn < i_way ; tn++)
                        {
                            if(i_plru[i_cache_set][tn] == 1)
                                i_plru[i_cache_set][tn] = 0;
                            else
                                i_plru[i_cache_set][tn] = 1;
                        }
                    }
                    else
                    {
                        i_plru[i_cache_set][cs] = 1;
                    }
                    break;
                }
            }
        }
//********************************************************
        if(i < 2)
        {
            cycle++;
            no_ins();
            fout1 << endl;
            fout1 << endl;
        }
        else{
        int data_error = 0;
        //fout1 << "line = " <<(i-1) << endl;
        const string null = "";
        char* temp_bin = strdup(binary[i].c_str());
        char *opcode = new char[6]();
        opcode[6] = '\0';
        memcpy(opcode,temp_bin,6);
        string str_opcode = opcode;
        //delete[] opcode;
        if(str_opcode.compare("111111") == 0)
        {
            //free(opcode);
            break;
        }
        cycle++;
        //cout << "cycle " << cycle << endl;
        //fout1 << opcode << endl;
        //fout1 << "YES" << endl;
        if(str_opcode.compare("000000") == 0)
        {
            //label[i] = 1;
            char *func = new char[6]();
            func[6] = '\0';
            memcpy(func,temp_bin+26,6);
            char *rs = new char[5]();
            rs[5] = '\0';
            memcpy(rs,temp_bin+6,5);
            char *rt = new char[5]();
            rt[5] = '\0';
            memcpy(rt,temp_bin+11,5);
            char *rd = new char[5]();
            rd[5] = '\0';
            memcpy(rd,temp_bin+16,5);
            char *shamt = new char[5]();
            shamt[5] = '\0';
            memcpy(shamt,temp_bin+21,5);
            string ins = "";
            //fout1 << func << endl;
            ins = conver_to_decode(1 , null , func);
            //cout << ins << endl;
            if(ins == "add")
                ins_add(rs,rt,rd);
            if(ins == "addu")
                ins_addu(rs,rt,rd);
            if(ins == "sub")
                ins_sub(rs,rt,rd);
            if(ins == "and")
                ins_and(rs,rt,rd);
            if(ins == "or")
                ins_or(rs,rt,rd);
            if(ins == "xor")
                ins_xor(rs,rt,rd);
            if(ins == "nor")
                ins_nor(rs,rt,rd);
            if(ins == "nand")
                ins_nand(rs,rt,rd);
            if(ins == "slt")
                ins_slt(rs,rt,rd);
            if(ins == "sll")
                 ins_sll(rt,rd,shamt);
            if(ins == "srl")
                 ins_srl(rt,rd,shamt);
            if(ins == "sra")
                 ins_sra(rt,rd,shamt);
            if(ins == "jr")
            {
                int return_block = ins_jr(rs);
                i = i - return_block - 1;
                //cout << i << endl;
            }
            if(ins == "mult")
                 ins_mult(rs,rt);
            if(ins == "multu")
                 ins_multu(rs,rt);
            if(ins == "mfhi")
                 ins_mfhi(rd);
            if(ins == "mflo")
                 ins_mflo(rd);
            if(ins == "no instrument")
                 no_ins();
            delete[] func;
            delete[] rs;
            delete[] rt;
            delete[] rd;
            delete[] shamt;
            //fout1 << "r_type" << label[i] << endl;
        }
        else if(str_opcode.compare("000010")== 0) // jump
        {
            char *addrt = new char[26]();
            addrt[26] = '\0';
            memcpy(addrt,temp_bin+6,26);
            string temp_str = addrt;
            delete[] addrt;
            int addr = convert_dex(temp_str);
                int jal_mark = 0;
                char *temp_move_1 = new char[2]();
                temp_move_1[2] = '\0';
                memcpy(temp_move_1,temp_bin,2);
                char *temp_move_2 = new char[24]();
                temp_move_2[24] = '\0';
                memcpy(temp_move_2,temp_bin+8,24);
                char real_add[26] = {'0'};
                strcpy(real_add, temp_move_2);
                strcat(real_add, temp_move_1);
                int real_addr = convert_dex(real_add);
                jal_mark = ins_j(real_addr);
                i = i - jal_mark-1;
                delete[] temp_move_1;
                delete[] temp_move_2;
                delete[] addrt;
        }
        else if(str_opcode.compare("000011") == 0)
        {
            char *addrt = new char[26]();
            addrt[26] = '\0';
            memcpy(addrt,temp_bin+6,26);
            string temp_str = addrt;
            delete[] addrt;
            int addr = convert_dex(temp_str);
                int jal_mark = 0;
                char *temp_move_1 = new char[2]();
                temp_move_1[2] = '\0';
                memcpy(temp_move_1,temp_bin,2);
                char *temp_move_2 = new char[24]();
                temp_move_2[24] = '\0';
                memcpy(temp_move_2,temp_bin+8,24);
                char real_add[26] = {'0'};
                strcpy(real_add, temp_move_2);
                strcat(real_add, temp_move_1);
                int real_addr = convert_dex(real_add);
                jal_mark = ins_jal(real_addr);
                i = i + jal_mark;
                delete[] temp_move_1;
                delete[] temp_move_2;
                delete[] addrt;
        }
        else
        {

            int new_block = 0;
            char *rs = new char[5]();
            rs[5] = '\0';
            memcpy(rs,temp_bin+6,5);
            char *rt = new char[5]();
            rt[5] = '\0';
            memcpy(rt,temp_bin+11,5);
            char *a1 = new char[16]();
            a1[16] = '\0';
            memcpy(a1,temp_bin+16,16);
            int imm_unsigned = convert_dex(a1);
            int imm_signed = 0;
            if(imm_unsigned > 32767)
            {
                imm_signed = (int16_t) imm_unsigned;
            }
            else
                imm_signed = imm_unsigned;
            string ins = "";
            ins = conver_to_decode(2 , opcode , null);
            //cout << ins << endl;
            //system("PAUSE");
            if(ins == "addi")
                ins_addi(rs,rt,imm_signed);
            if(ins == "addiu")
                ins_addiu(rs,rt,imm_signed);
            if(ins == "lw")
            {
                if(ins_lw(rs,rt,imm_signed,d_addr) == -1)
                {
                    break;
                }
            }

            if(ins == "lh")
                if(ins_lh(rs,rt,imm_signed,d_addr) == -1)
                {
                    break;
                }
            if(ins == "lhu")
                if(ins_lhu(rs,rt,imm_unsigned,d_addr) == -1)
                {
                    break;
                }
            if(ins == "lb")
                if(ins_lb(rs,rt,imm_signed,d_addr) == -1)
                {
                    break;
                }
            if(ins == "lbu")
                if(ins_lbu(rs,rt,imm_unsigned,d_addr) == -1)
                {
                    break;
                }
            if(ins == "sw")
                if(ins_sw(rs,rt,imm_signed,d_addr) == -1)
                {
                    break;
                }
            if(ins == "sh")
                if(ins_sh(rs,rt,imm_signed,d_addr) == -1)
                {
                    break;
                }
            if(ins == "sb")
                if(ins_sb(rs,rt,imm_signed,d_addr) == -1)
                {
                    break;
                }
            if(ins == "lui")
                ins_lui(rt,imm_signed);
            if(ins == "andi")
                ins_andi(rs,rt,imm_unsigned);
            if(ins == "ori")
                ins_ori(rs,rt,imm_unsigned);
            if(ins == "nori")
                ins_nori(rs,rt,imm_unsigned);
            if(ins == "slti")
                ins_slti(rs,rt,imm_signed);
            if(ins == "beq")
                new_block = ins_beq(rs,rt,imm_signed);
            if(ins == "bne")
                new_block = ins_bne(rs,rt,imm_signed);
            if(ins == "bgtz")
                new_block = ins_bgtz(rs,imm_signed);
            if(ins == "no instrument")
                 no_ins();
            if(new_block != 0)
                i = i + new_block  ;
            if(ins == "lw" || ins == "lh" || ins == "lhu" || ins == "lb" || ins == "lbu" ||
            ins == "sw" || ins == "sh" || ins == "sb")
            {
//********************************************************
                    //cout << "cycle = " << cycle << endl;
                    string dd_addr = convert_bin(d_addr);
                    //cout << "d_addr = " << d_addr << endl;
                    //system("PAUSE");
                    int d_end = 22 + d_len - 1;
                    string d_vpn = str_cut(dd_addr, 22 , d_end);
                    string d_offset = str_cut(dd_addr, d_end ,31 - d_off_re);
                    //cout << "d_vpn = " << d_vpn << endl;
                    int dec_d_vpn = convert_dex(d_vpn);
                    int d_tlb_num = dec_d_vpn%(d_page_entry/4);
                    int d_t_hit = 0;
                    string d_ppn = "";
                    for(int ti = 0 ; ti < (d_page_entry/4) ; ti++)
                    {
                        if(d_tlb[ti][2] == d_vpn)
                        {
                            if(d_t_lru[ti] != 0)
                            {
                                d_tlb_hit++;
                                //cout << "tlb_hit" << endl;
                                d_t_hit = 1;
                                d_ppn = d_tlb[ti][3];
                                int old_tlb_count = d_t_lru[ti];
                                d_t_lru[ti] = 1;
                                for(int tk = 0 ; tk < (d_page_entry/4) ; tk++)
                                {
                                    if(tk != ti && d_t_lru[tk] != 0 && d_t_lru[tk] < old_tlb_count)
                                        d_t_lru[tk] = d_t_lru[tk] + 1;
                                }
                            }
                            else
                            {
                                d_tlb_miss++;
                                d_t_hit = 2;
                                d_tlb[ti][2] = d_vpn;
                                //
                                if(d_page_table[dec_d_vpn][2] != "")
                                {
                                    if(d_page_lru[dec_d_vpn] != 0) //i_page_hit
                                    {
                                        int d_page_count = d_page_lru[dec_d_vpn];
                                        d_page_lru[dec_d_vpn] = 1;
                                        d_page_hit++;
                                        d_tlb[ti][3] = d_page_table[dec_d_vpn][3];
                                        d_ppn = d_tlb[ti][3];
                                        for(int tk = 0 ; tk < (d_page_entry/4) ; tk++)
                                        {
                                            if(tk != dec_d_vpn && d_page_lru[tk] != 0 && d_page_lru[tk] < d_page_lru[dec_d_vpn])
                                                d_page_lru[tk] = d_page_lru[tk] + 1;
                                        }
                                    }
                                    else
                                    {
                                        d_page_lru[dec_d_vpn] = 1;
                                        d_page_miss++;
                                        if(d_phy_num == d_phy_num_max)
                                            d_phy_num = 0;
                                        d_page_table[dec_d_vpn][3] = to_str(d_phy_num);
                                        d_tlb[ti][3] = to_str(d_phy_num);
                                        d_ppn = d_tlb[ti][3];
                                        d_phy_num++;
                                        for(int tk = 0 ; tk < (d_page_entry/4) ; tk++)
                                        {
                                            if(d_page_lru[tk] == d_phy_num_max)
                                                d_page_lru[tk] = 0;
                                            else if(tk != dec_d_vpn && d_page_lru[tk] != 0)
                                                d_page_lru[tk] = d_page_lru[tk] + 1;
                                        }

                                    }

                                }
                                else
                                {
                                    d_page_lru[dec_d_vpn] = 1;
                                    d_page_miss++;
                                    if(d_phy_num == d_phy_num_max)
                                        d_phy_num = 0;
                                    d_page_table[dec_d_vpn][3] = to_str(d_phy_num);
                                    d_tlb[ti][3] = to_str(d_phy_num);
                                    d_ppn = d_tlb[ti][3];
                                    d_phy_num++;
                                    for(int tk = 0 ; tk < (d_page_entry/4) ; tk++)
                                    {
                                        if(d_page_lru[tk] == d_phy_num_max)
                                            d_page_lru[tk] = 0;
                                        else if(tk != dec_d_vpn && d_page_lru[tk] != 0)
                                            d_page_lru[tk] = d_page_lru[tk] + 1;
                                    }
                                }
                                d_t_lru[ti] = 1;
                                for(int tk = 0 ; tk < (d_page_entry/4) ; tk++)
                                {
                                    if(tk != ti && d_t_lru[tk] != 0)
                                        d_t_lru[tk] = d_t_lru[tk] + 1;
                                    if(d_t_lru[tk] > d_phy_num_max)
                                        d_t_lru[tk] = 0;
                                }
                            }

                            break;
                        }
                        else if(d_tlb[ti][2] == "")
                        {
                            d_tlb_miss++;
                            d_t_hit = 2;
                            d_tlb[ti][2] = d_vpn;
                            //
                            if(d_page_table[dec_d_vpn][2] != "")
                            {
                                if(d_page_lru[dec_d_vpn] != 0) //i_page_hit
                                {
                                    int d_page_count = d_page_lru[dec_d_vpn];
                                    d_page_lru[dec_d_vpn] = 1;
                                    d_page_hit++;
                                    d_tlb[ti][3] = d_page_table[dec_d_vpn][3];
                                    d_ppn = d_tlb[ti][3];
                                    for(int tk = 0 ; tk < (d_page_entry/4) ; tk++)
                                    {
                                        if(tk != dec_d_vpn && d_page_lru[tk] != 0 && d_page_lru[tk] < d_page_lru[dec_d_vpn])
                                            d_page_lru[tk] = d_page_lru[tk] + 1;
                                    }
                                }
                                else
                                {
                                    d_page_lru[dec_d_vpn] = 1;
                                    d_page_miss++;
                                    if(d_phy_num == d_phy_num_max)
                                        d_phy_num = 0;
                                    d_page_table[dec_d_vpn][3] = to_str(d_phy_num);
                                    d_tlb[ti][3] = to_str(d_phy_num);
                                    d_ppn = d_tlb[ti][3];
                                    d_phy_num++;
                                    for(int tk = 0 ; tk < (d_page_entry/4) ; tk++)
                                    {
                                        if(d_page_lru[tk] == d_phy_num_max)
                                            d_page_lru[tk] = 0;
                                        else if(tk != dec_d_vpn && d_page_lru[tk] != 0)
                                            d_page_lru[tk] = d_page_lru[tk] + 1;
                                    }

                                }

                            }
                            else
                            {
                                d_page_lru[dec_d_vpn] = 1;
                                d_page_miss++;
                                if(d_phy_num == d_phy_num_max)
                                    d_phy_num = 0;
                                d_page_table[dec_d_vpn][3] = to_str(d_phy_num);
                                d_tlb[ti][3] = to_str(d_phy_num);
                                d_ppn = d_tlb[ti][3];
                                d_phy_num++;
                                for(int tk = 0 ; tk < (d_page_entry/4) ; tk++)
                                {
                                    if(d_page_lru[tk] == d_phy_num_max)
                                        d_page_lru[tk] = 0;
                                    else if(tk != dec_d_vpn && d_page_lru[tk] != 0)
                                        d_page_lru[tk] = d_page_lru[tk] + 1;
                                }
                            }
                            //
                            d_t_lru[ti] = 1;
                            for(int tk = 0 ; tk < (d_page_entry/4) ; tk++)
                            {
                                if(tk != ti && d_t_lru[tk] != 0)
                                    d_t_lru[tk] = d_t_lru[tk] + 1;
                                if(d_t_lru[tk] > d_phy_num_max)
                                        d_t_lru[tk] = 0;
                            }
                            break;
                        }

                    }
                    if(d_t_hit == 0)
                    {
                        for(int ti = 0 ; ti < (d_page_entry/4) ; ti++)
                        {
                            if(d_t_lru[ti] == ((d_page_entry/4)-1))
                            {
                                d_t_hit = 2;
                                d_tlb_miss++;
                                d_tlb[ti][2] = d_vpn;
                                //****
                                if(d_page_table[dec_d_vpn][2] != "")
                                {
                                    if(d_page_lru[dec_d_vpn] != 0) //i_page_hit
                                    {
                                        int d_page_count = d_page_lru[dec_d_vpn];
                                        d_page_lru[dec_d_vpn] = 1;
                                        d_page_hit++;
                                        d_tlb[ti][3] = d_page_table[dec_d_vpn][3];
                                        d_ppn = d_tlb[ti][3];
                                        for(int tk = 0 ; tk < (d_page_entry/4) ; tk++)
                                        {
                                            if(tk != dec_d_vpn && d_page_lru[tk] != 0 && d_page_lru[tk] < d_page_count)
                                                d_page_lru[tk] = d_page_lru[tk] + 1;
                                        }
                                    }
                                    else
                                    {
                                        d_page_lru[dec_d_vpn] = 1;
                                        d_page_miss++;
                                        if(d_phy_num == d_phy_num_max)
                                            d_phy_num = 0;
                                        d_page_table[dec_d_vpn][3] = to_str(d_phy_num);
                                        d_tlb[ti][3] = to_str(d_phy_num);
                                        d_ppn = d_tlb[ti][3];
                                        d_phy_num++;
                                        for(int tk = 0 ; tk < (d_page_entry/4) ; tk++)
                                        {
                                            if(d_page_lru[tk] == d_phy_num_max)
                                                d_page_lru[tk] = 0;
                                            else if(tk != dec_d_vpn && d_page_lru[tk] != 0)
                                                d_page_lru[tk] = d_page_lru[tk] + 1;
                                        }
                                    }
                                }
                                else
                                {
                                    d_page_lru[dec_d_vpn] = 1;
                                    d_page_miss++;
                                    if(d_phy_num == d_phy_num_max)
                                        d_phy_num = 0;
                                    d_page_table[dec_d_vpn][3] = to_str(d_phy_num);
                                    d_tlb[ti][3] = to_str(d_phy_num);
                                    d_ppn = d_tlb[ti][3];
                                    d_phy_num++;
                                    for(int tk = 0 ; tk < (d_page_entry/4) ; tk++)
                                    {
                                        if(d_page_lru[tk] == d_phy_num_max)
                                            d_page_lru[tk] = 0;
                                        else if(tk != dec_d_vpn && d_page_lru[tk] != 0)
                                            d_page_lru[tk] = d_page_lru[tk] + 1;
                                    }
                                }
                                //****
                                d_t_lru[ti] = 1;
                                for(int tk = 0 ; tk < (d_page_entry/4) ; tk++)
                                {
                                    if(tk != ti && d_t_lru[tk] != 0)
                                        d_t_lru[tk] = d_t_lru[tk] + 1;
                                }
                                break;
                            }
                        }

                    }
//********************************************************
                    string d_ppa = d_ppn+ d_offset;
                    //cout << "d_ppa = " << d_ppa << endl;
                    int d_c_h = 0;
                    int d_cache_set = convert_dex(d_ppa)%(d_cache_size/d_way/d_block);
                    //cout << "d_cache_set = " << d_cache_set << endl;
                    //cout << "d_cache0 = " << d_cache[0][0] << endl;
                    //cout << "d_cache1 = " << d_cache[1][0] << endl;
                    //cout << "d_cache2 = " << d_cache[2][0] << endl;
                    //cout << "d_cache3 = " << d_cache[3][0] << endl;
                    for(int cs = 0 ; cs < d_way ; cs++)
                    {
                        if(d_cache[d_cache_set][cs] == d_ppa)
                        {
                            d_c_h = 1;
                            d_cache_hit++;
                            int bit_count = 0;
                            for(int tn = 0 ; tn < d_way ; tn++)
                            {
                                if(d_plru[d_cache_set][tn] == 1)
                                    bit_count++;
                            }
                            if(bit_count == (d_way - 1))
                            {
                                if(d_way != 1)
                                {
                                    for(int tn = 0 ; tn < d_way ; tn++)
                                    {
                                        if(d_plru[d_cache_set][tn] == 1)
                                            d_plru[d_cache_set][tn] = 0;
                                        else
                                            d_plru[d_cache_set][tn] = 1;
                                    }
                                }

                            }
                            else
                            {
                                d_plru[d_cache_set][cs] = 1;
                            }
                            break;
                        }
                    }
                    if(d_c_h != 1)
                    {
                        d_cache_miss++;
                        for(int cs = 0 ; cs < d_way ; cs++)
                        {
                            if(d_plru[d_cache_set][cs] == 0)
                            {
                                d_cache[d_cache_set][cs] = d_ppa;
                                int bit_count = 0;
                                for(int tn = 0 ; tn < d_way ; tn++)
                                {
                                    if(d_plru[d_cache_set][tn] == 1)
                                        bit_count++;
                                }
                                if(bit_count == (d_way - 1))
                                {
                                    if(d_way != 1)
                                    {
                                        for(int tn = 0 ; tn < d_way ; tn++)
                                        {
                                            if(d_plru[d_cache_set][tn] == 1)
                                                d_plru[d_cache_set][tn] = 0;
                                            else
                                                d_plru[d_cache_set][tn] = 1;
                                        }
                                    }
                                }
                                else
                                {
                                    d_plru[d_cache_set][cs] = 1;
                                }
                                break;
                            }
                        }
                    }
//********************************************************
            }
        }
        //delete[] opcode;
        fout1 << endl;
        fout1 << endl;
        }
    }

    fout3 << "ICache :" << endl;
    fout3 << "# hits: " << i_cache_hit << endl;
    fout3 << "# misses: " << i_cache_miss << endl;
    fout3 << endl;
    fout3 << "DCache :" << endl;
    fout3 << "# hits: " << d_cache_hit << endl;
    fout3 << "# misses: " << d_cache_miss << endl;
    fout3 << endl;
    fout3 << "ITLB :" << endl;
    fout3 << "# hits: " << i_tlb_hit << endl;
    fout3 << "# misses: " << i_tlb_miss << endl;
    fout3 << endl;
    fout3 << "DTLB :" << endl;
    fout3 << "# hits: " << d_tlb_hit << endl;
    fout3 << "# misses: " << d_tlb_miss << endl;
    fout3 << endl;
    fout3 << "IPageTable :" << endl;
    fout3 << "# hits: " << i_page_hit << endl;
    fout3 << "# misses: " << i_page_miss << endl;
    fout3 << endl;
    fout3 << "DPageTable :" << endl;
    fout3 << "# hits: " << d_page_hit << endl;
    fout3 << "# misses: " << d_page_miss << endl;
    fout3 << endl;

    d_mem.clear();
    d_bin.clear();
    #undef mult_sign
    #undef mult_unsign
    fout1.clear();
    fout1.close();
    fout3.clear();
    fout3.close();
    return 0;
}
