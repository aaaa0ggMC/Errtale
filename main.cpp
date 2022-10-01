#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <conio.h>
#include "opencb.h"
#define CN "data/cn.txt"
#define EN "data/en.txt"
#define CON "data/config.cfg"
#define  IsKeyPressed(nVirtKey)     ((GetKeyState(nVirtKey) & (1<<(sizeof(SHORT)*8-1))) != 0)

using namespace std;
using namespace opencb::io;
using namespace opencb::base;

int sleept= 80;

bool fnxx(int,int,vector<string>&){
    Sleep(sleept);
    return false;
}

bool fndd(int,int,vector<string>&){
    Sleep(sleept/2);
    return false;
}

string operator +(vector<string> d,int v){
    if(v < 0 || v >= (int)d.size())return "";
    return d[v];
}
vector<string> subvec(vector<string> d,int st,int ed){
    vector<string> ret;
    for(int i = st;i <= ed;++i){
        ret.push_back(d + i);
    }
    return ret;
}

int main()
{
    system("cls & color 0f & mode con cols=128 lines=32");
    vector<string> strings;
    HWND gameWin = GetConsoleWindow();
    SetWindowText(gameWin,"Errtale");
    //Disable Console Controlls
    {
        //设置控制台，禁用编辑
        auto hStdin = ::GetStdHandle(STD_INPUT_HANDLE);
        DWORD mode;
        GetConsoleMode(hStdin, &mode);
        mode &= ~ENABLE_QUICK_EDIT_MODE;
        SetConsoleMode(hStdin, mode);

    }
    //Read config
    {
        int lang = 0;
        ifstream ifs(CON);
        if(ifs.good() && !ifs.eof()){
            ifs >> lang;
            ifs.close();
            if(lang == 1)ifs.open(CN);
            else ifs.open(EN);
        }else{
            ifs.close();
            ofstream ofs(CON);
            //Choose a language
            cout << "Please Select The Language 请选择语言：" << endl << "1.Simpled Chinese 简体中文" << endl << "2.English 英文" << endl;
            while(true){
                bool good = true;
                char c = _getch();
                if(c == '1'){
                    ifs.open(CN);
                    if(!ifs.good()){
                        cout << "Can't load file " CN << "  无法加载文件 " << CN <<endl;
                        good = false;
                    }
                    lang = 1;
                }else if(c == '2'){
                    ifs.open(EN);
                    if(!ifs.good()){
                        cout << "Can't load file " EN << "  无法加载文件 " << EN <<endl;
                        good = false;
                    }
                    lang = 2;
                }else good = false;
                if(good){
                    break;
                }
            }
            ofs << lang;
            ofs.close();
        }
        string l;
        while(!ifs.eof()){
            getline(ifs,l);
            strings.push_back(l);
        }
    }
    SetWindowLong(gameWin,GWL_STYLE,GetWindowLong(gameWin,GWL_STYLE) & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
    Sleep(1000);
    if(IsKeyPressed(VK_SHIFT) != TRUE){
        sleept = 5;
        SwapPrint(subvec(strings,0,10),fnxx);
        Sleep(1000);
        clrscr();
        sleept = 20;
        SwapPrint(subvec(strings,11,19),fnxx,fndd);
        Sleep(4500);
        clrscr();
        SetColor(CL_RED);
        sleept = 80;
        EasyPrint(subvec(strings,20,23),fnxx,fndd);
        Sleep(800);
        clrscr();
        SetColor();
    }
    sleept = 50;
    EasyPrint(subvec(strings,24,24),fnxx);
    Sleep(100);
    system("cls");
    ShowWindow(gameWin,SW_HIDE);

    ShowWindow(gameWin,SW_SHOW);
    return 0;
}
