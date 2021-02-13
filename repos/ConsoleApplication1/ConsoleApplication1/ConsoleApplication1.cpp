// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<vector>
#include<stack>

using namespace std;
bool match(string str, string re)
{
    int sl = str.length(), rl = re.length();
    int i = sl-1, j = rl-1;
    while (j >= 0)
    {
        if (i==-1 && (re[j]== '?' || re[j] == '*')) return true;
        if (re[j] == '?')
        {
            if (re[j-1] == str[i]) i--;            
            j -= 2;
        }
        else if (re[j] == '*')
        {
            while (i>=0 && re[j-1] == str[i]) i--;
            j-=2;
        }
        else if (str[i] == re[j]) {
            i--; j--;
        }
        else return false;   
    }
    if (i != -1 || j != -1) return false;
    return true;
}
/*int is_match(char* pattern, char* string)
{
    if (!pattern[0]) {
        return !string[0];
    }
    else if (pattern[1] == '?') {
        return (pattern[0] == string[0] && is_match(pattern + 2, string + 1))
            || is_match(pattern + 2, string);
    }
    else if (pattern[1] == '*') {
        size_t i;
        for (i = 0; string[i] == pattern[0]; i++)
            if (is_match(pattern + 2, string + i)) return 1;
        return 0;
    }
    else {
        return pattern[0] == string[0] && is_match(pattern + 1, string + 1);
    }
}*/
int main()
{
    std::cout << "Hello World!\n";
    if (match("sumy", "dum?y")) cout << "yra" << endl;
    if (match("dummy", "dumm?y")) cout << "yra" << endl;
            
            // dumy dun?y
    if (match("c", "d*c")) cout << "yra3" << endl;
    match("dum?y", "dummy");
    match("dumm?y", "dummy");
    if (match("dummmy", "dum*y")) cout << "yra2" << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
