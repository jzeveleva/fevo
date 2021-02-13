// prep1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stack>
#include <unordered_map>
using namespace std;

bool balanced(string s)
{
    stack<char> st;
    if (s.length() == 0) return true;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '{' || s[i] == '(' || s[i] == '[')
            st.push(s[i]);
        else if (s[i] == '}' || s[i] == ')' || s[i] == ']')
        {
            if (!st.empty()) {
                char t = st.top();
                if (t != it->second) return false;
                if (t == '[' && s[i] != ']') return false;
                if (t == '{' && s[i] != '}') return false;
                if (t == '(' && s[i] != ')') return false;

                st.pop();
            }
            else return false;
        }            
    }
    if (st.empty()) return true;
}
int main()
{
    std::cout << "Hello World!\n";
    unordered_map<char, char> mchar;
    mcar['{'] = '}';
    string s = "  ] [ ";
    bool b = balanced(s);

        cout << "b=" << b << endl;
}
//{([])} is balanced, and { [}] () is not

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
