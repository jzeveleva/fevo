// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string.h>
#include <vector>
using namespace std;
vector<string> keypad { "", "", "abc", "def", "ghi", "jkl", "mno",
"pqrs", "tuv", "wxyz" };
void printWords(vector<int> number, int curr_digit, string output, int n) {
    int i;
    if (curr_digit == n) {
        cout << output << " ";
        return;
    }
    for (i = 0; i < keypad[number[curr_digit]].size(); i++) {
        output[curr_digit] = keypad[number[curr_digit]][i];
        printWords(number, curr_digit + 1, output, n);
        if (number[curr_digit] == 0 || number[curr_digit] == 1)
            return;
    }
}
int main(void) {
    vector<int>number = { 6,8,7 };
    cout << "The output character formed is : \n";
    int n = number.size();
    string result(n, ' ');
    
    printWords(number, 0, result, n);
    return 0;
}