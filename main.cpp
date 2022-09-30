#include <iostream>
#include <stdlib.h>
#include "opencb.h"

using namespace std;
using namespace opencb::io;

int sleept= 80;

bool fnxx(int,int,vector<string>&){
    Sleep(sleept);
    return false;
}

int main()
{
    vector<vector<string>> s= {
        {
            "Long long ago,there are two races---HUMANS and MONSTERS",
            "One day,war broke out between the two races,and at last the human won",
            "They sealed the monsters UNDERGROUND with a magic spell that could not be broken easily",
            "The monsters lived in the underground and slowly built their civilization...",
            "In 201X,one day,a child fell into the hole in Mt.Ebbot and saw the world",
            "And the child impossibly led the civilization to death..."
        },
        {
            "Eventually,They all died!"
        }
    };
    SwapPrint(s[0],fnxx);
    Sleep(2500);
    system("cls");
    SwapPrint(s[1],fnxx);
    return 0;
}
