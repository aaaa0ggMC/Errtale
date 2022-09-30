#ifndef OPENCB_H_INCLUDED
#define OPENCB_H_INCLUDED
#include <windows.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace opencb{
    namespace base{
        void SetConsolePosition(int=0,int=0,HANDLE=GetStdHandle(STD_OUTPUT_HANDLE));
    }
    namespace io{
        typedef bool (*fn)(int,int,vector<string>&);
        #define cblambda [&](int x,int y,vector<string>& d)->bool
        template<typename Func> void SwapPrint_t(vector<string>&,Func xNew=cblambda{return false;},Func yNew=cblambda{return false;});
        void SwapPrint(vector<string>,fn xNew=NULL,fn yNew=NULL);
        void SwapPrintEx(vector<vector<string>>,fn xNew=NULL,fn yNew=NULL);
    }
}


#endif // OPENCB_H_INCLUDED
