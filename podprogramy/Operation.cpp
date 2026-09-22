// Mikolaj Suchan
#include <string>
#include <cstdarg>

using namespace std;

void extract_operation( va_list &arguments, int size, string* nums ){
    if (size == 0)
        return;
    *(nums + size - 1) = (string)va_arg(arguments, char*);
    extract_operation(arguments, size - 1, nums);
}

string Operation(string (*func)(int, const string*), int size, const string* nums) {
    return func(size, nums);
}

string Operation(string (*func)(int, const string*), int size, ...) {
    string* nums = new string[size];
    va_list arguments;
    va_start(arguments, size);
    extract_operation(arguments, size, nums);
    string ans = Operation(func, size, nums);
    va_end(arguments);
    delete [] nums;
    return ans;
}


void Operation(string* ans, string (*func)(int, const string*), int size, ...) {
    string* nums = new string[size];
    va_list arguments;
    va_start(arguments, size);
    extract_operation(arguments, size, nums);
    *ans = Operation(func, size, nums);
    va_end(arguments);
    delete [] nums;
}


void Operation(string* ans, string (*func)(int, const string*), int size, const string* nums) {
    *ans = Operation(func, size, nums);
}


void Operation(string& ans, void (*func)(string*, int, const string*), int size, const string* nums) {
    func(&ans, size, nums);
}

void Operation(string& ans, void (*func)(string*, int, const string*), int size, ...) {
    string* nums = new string[size];
    va_list arguments;
    va_start(arguments, size);
    extract_operation(arguments, size, nums);
    func(&ans, size, nums);
    va_end(arguments);
    delete [] nums;
}
