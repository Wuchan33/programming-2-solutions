// Mikolaj Suchan
#include <string>
#include <cstdarg>

using namespace std;

void inner( string first, string second, int size_first, int size_second, int* arr ){
    if (size_second < 0)
        return;
    *(arr + size_first + size_second + 1) += (first[size_first] - '0') * (second[size_second] - '0');
    inner(first, second, size_first, size_second - 1, arr);
}

void outer( string first, string second, int size_first, int size_second, int* arr ){
    if (size_first < 0)
        return;
    inner(first, second, size_first, size_second, arr);
    outer(first, second, size_first - 1, size_second, arr);
}

void carry_fix( int* arr, int size, int carry ){
    if (size < 0)
        return;
    *(arr + size) = *(arr + size) + carry;
    carry = (*(arr + size)) / 10;
    *(arr + size) = (*(arr + size)) % 10;
    carry_fix(arr, size - 1, carry);
}

void fix_mult( string& str ){
    if (str.size() == 0 || str[0] != '0')
        return;
    str.erase(0, 1);
    fix_mult(str);
}

void clear_arr(int* arr, int size) {
    if (size < 0)
        return;
    *(arr + size) = 0;
    clear_arr(arr, size - 1);
}

string get_str( int* arr, int size ){
    if (size < 0)
        return "";
    char digit = (*(arr + size)) + '0';
    return get_str(arr, size - 1) + digit;
}

string Mult( int i, const string* nums ) {
    if (i == 1)
        return *nums;

    string prev = Mult(i - 1, nums);
    string curr = *(nums + i - 1);
    
    int sign = 1;
    if (prev[0] == '-')
        sign *= -1;
    if (prev[0] == '-' || prev[0] == '+')
        prev.erase(0, 1);
    if (curr[0] == '-')
        sign *= -1;
    if (curr[0] == '-' || curr[0] == '+')
        curr.erase(0, 1);

    int size = prev.size() + curr.size();
    int* arr = new int[size];
    clear_arr(arr, size - 1);
    outer(prev, curr, prev.size() - 1, curr.size() - 1, arr);
    carry_fix(arr, size - 1, 0);
    string ans = get_str(arr, size - 1);
    delete [] arr;
    fix_mult(ans);
    if (ans == "")
        return "0";
    if (sign == -1)
        ans = '-' + ans;
    return ans;
}

void extract_mult( va_list &arguments, int size, string* nums ){
    if (size == 0)
        return;
    *(nums + size - 1) = (string)va_arg(arguments, char*);
    extract_mult(arguments, size - 1, nums);
}

string Mult( int size, ... ){
    string* nums = new string[size];
    va_list arguments;
    va_start(arguments, size);
    extract_mult(arguments, size, nums);
    string ans = Mult(size, nums);
    va_end(arguments);
    delete [] nums;
    return ans;
}

void Mult( string* ans, int size, const string* nums ){
    *ans = Mult(size, nums);
}

void Mult( string* ans, int size, ... ){
    string* nums = new string[size];
    va_list arguments;
    va_start(arguments, size);
    extract_mult(arguments, size, nums);
    *ans = Mult(size, nums);
    va_end(arguments);
    delete [] nums;
}

void Mult( string& ans, int size, const string* nums ){
    ans = Mult(size, nums);
}

void Mult( string& ans, int size, ... ){
    string* nums = new string[size];
    va_list arguments;
    va_start(arguments, size);
    extract_mult(arguments, size, nums);
    ans = Mult(size, nums);
    va_end(arguments);
    delete [] nums;
}