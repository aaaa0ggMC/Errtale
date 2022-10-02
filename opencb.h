#ifndef OPENCB_H_INCLUDED
#define OPENCB_H_INCLUDED

#define USE_UNICODE

#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include "Generic.h"

using namespace std;
//static bool solution2 = false;

namespace opencb{
    namespace base{
        void SetConsolePosition(int=0,int=0,HANDLE=GetStdHandle(STD_OUTPUT_HANDLE));
        #define CL_BLACK 0
        #define CL_BLUE 1
        #define CL_GRREN 2
        #define CL_LGREEN 3
        #define CL_RED 4
        #define CL_PURPLE 5
        #define CL_YELLOW 6
        #define CL_DWHITE 7
        #define CL_GRAY 8
        #define CL_SBLUE 9
        #define CL_SGREEN 10
        #define CL_SLGREEN 11
        #define CL_SRED 12
        #define CL_SPURPLE 13
        #define CL_SYELLOW 14
        #define CL_WHITE 15
        void SetColor(int fore=CL_WHITE,int backg=CL_BLACK);
    }
    namespace io{
        typedef bool (*fn)(int,int,vector<GString>&);
        #define cblambda [&](int x,int y,vector<GString>& d)->bool
        template<typename Func> void SwapPrint_t(vector<GString>&,Func xNew=cblambda{return false;},Func yNew=cblambda{return false;});
        void SwapPrint(vector<GString>,fn xNew=NULL,fn yNew=NULL);
        void SwapPrintEx(vector<vector<GString>>,fn xNew=NULL,fn yNew=NULL);
        void EasyPrint(vector<GString>,fn xNew = NULL,fn yNew = NULL);
        void clrscr();
    }
}


#endif // OPENCB_H_INCLUDED
