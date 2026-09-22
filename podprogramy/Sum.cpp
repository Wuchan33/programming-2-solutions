// Mikolaj Suchan
#include <string>
#include <cstdarg>
#include <iostream>

using namespace std;

string add( string first, string second, int i, int carry ){
    if (i < 0)
        return "";
    int first_digit = first[i] - '0', second_digit = second[i] - '0';
    char digit = (first_digit + second_digit + carry) % 10 + '0';
    carry = (first_digit + second_digit + carry) > 9;
    return add(first, second, i - 1, carry) + digit;
}

void inverse( string& str, int i ){
    if (i < 0)
        return;
    str[i] = ('9' - str[i]) + '0';
    inverse(str, i - 1);
}

string fix_len( string str, int add, int size ){
    if (size == 0)
        return "";
    if (add > size)
        return '0' + fix_len(str, add - 1, size);
    else
        return fix_len(str, add - 1, size - 1) + str[size - 1];
}

string add_one( string str, int i, int carry ){
    if (i < 0)
        return "";
    char digit = (str[i] - '0' + carry) % 10 + '0';
    carry = (str[i] - '0' + carry) > 9;
    return add_one(str, i - 1, carry) + digit;
}

string fix( string str, int i, int size, bool check ) {
    if (i == size && check == false)
        return "0";
    else if (i == size)
        return "";

    if (str[i] != '0' && str[i] != '-')
        check = true;
    if (str[i] == '-' || check == true)
        return str[i] + fix(str, i + 1, size, check);
    return fix(str, i + 1, size, check);
}

string Sum( int i, const string* nums ){
    if (i == 1)
        return *nums;

    string prev = Sum(i - 1, nums);
    string curr = *(nums + i - 1);
    
    char sign_prev = '0', sign_curr = '0';
    if (prev[0] == '-')
        sign_prev = '9';
    if (prev[0] == '-' || prev[0] == '+')
        prev.erase(0, 1);
    if (curr[0] == '-')
        sign_curr = '9';
    if (curr[0] == '-' || curr[0] == '+')
        curr.erase(0, 1);
    
    int size_prev = prev.size(), size_curr = curr.size();
    if (size_prev > size_curr)
        curr = fix_len(curr, size_prev, size_curr);
    else if (size_curr > size_prev)
        prev = fix_len(prev, size_curr, size_prev);

    prev = "00" + prev;
    curr = "00" + curr;

    if (sign_prev == '9') {
        inverse(prev, prev.size() - 1);
        prev = add_one(prev, prev.size() - 1, 1);
    }

    if (sign_curr == '9') {
        inverse(curr, curr.size() - 1);
        curr = add_one(curr, curr.size() - 1, 1);
    }

    string temp_sum = add(prev, curr, prev.size() - 1, 0);
    if (temp_sum[0] != '0') {
        inverse(temp_sum, temp_sum.size() - 1);
        temp_sum = add_one(temp_sum, temp_sum.size() - 1, 1);
        temp_sum = '-' + temp_sum;
    }

    temp_sum = fix(temp_sum, 0, temp_sum.size(), 0);
    if (temp_sum[0] == '-' && temp_sum[1] == '0')
        temp_sum = "0";
    return temp_sum;
}



void extract_sum( va_list &arguments, int size, string* nums ){
    if (size == 0)
        return;
    *(nums + size - 1) = (string)va_arg(arguments, char*);
    extract_sum(arguments, size - 1, nums);
}

string Sum( int size, ... ){
    string* nums = new string[size];
    va_list arguments;
    va_start(arguments, size);
    extract_sum(arguments, size, nums);
    string ans = Sum(size, nums);
    va_end(arguments);
    delete [] nums;
    return ans;
}


void Sum( string* ans, int size, const string* nums ){
    *ans = Sum(size, nums);
}

void Sum( string* ans, int size, ...){
    string* nums = new string[size];
    va_list arguments;
    va_start(arguments, size);
    extract_sum(arguments, size, nums);
    *ans = Sum(size, nums);
    va_end(arguments);
    delete [] nums;
}

void Sum( string& ans, int size, const string* nums ){
    ans = Sum(size, nums);
}

void Sum( string& ans, int size, ...) {
    string* nums = new string[size];
    va_list arguments;
    va_start(arguments, size);
    extract_sum(arguments, size, nums);
    ans = Sum(size, nums);
    va_end(arguments);
    delete [] nums;
}