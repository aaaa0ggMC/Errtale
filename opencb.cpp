#include "opencb.h"

using namespace std;

void opencb::base::SetConsolePosition(int x,int y,HANDLE h){
    SetConsoleCursorPosition(h,{(short)x,(short)y});
}

template<typename Func> void opencb::io::SwapPrint_t(vector<string>& data,Func line,Func perChar){
    bool _empty;
    unsigned int index = 0;
    while(true){
        _empty = true;
        if(line)if(line(index,0,data))return;
        for(unsigned int idx = 0;idx < data.size();++idx){
            constexpr string & l= data[idx];
            if(l.size() > index){
                _empty = false;
                //Draw elements Here
                if(perChar)if(perChar(index,idx,data))return;
                cout << l[index];
                opencb::base::SetConsolePosition(0,index+1);
            }
        }
        if(_empty)break;
        ++index;
        opencb::base::SetConsolePosition();//Back to origin,default func(0,0)
    }
}

void opencb::io::SwapPrint(vector<string> data,fn line,fn perChar){
    bool _empty;
    unsigned int index = 0;
    opencb::base::SetConsolePosition();
    while(true){
        _empty = true;
        if(line)if(line(index,0,data))return;
        for(int idx = 0;idx < (int)data.size();++idx){
            string & l = data[idx];
            if(l.size() > index){
                _empty = false;
                //Draw elements Here
                if(perChar)if(perChar(index,idx,data))return;
                cout << l[index];
            }
            opencb::base::SetConsolePosition(index,idx+1);
        }
        if(_empty)break;
        ++index;
        opencb::base::SetConsolePosition(index);//Back to origin,default func(0,0)
    }
    opencb::base::SetConsolePosition(0,data.size());
}


void opencb::io::SwapPrintEx(vector<vector<string>> d,fn xNew,fn yNew){
    for(vector<string> & s : d)opencb::io::SwapPrint(s,xNew,yNew);
}

void opencb::base::SetColor(int fore,int backg){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),fore | (backg*80));
}


void opencb::io::EasyPrint(vector<string> d,fn xNew,fn yNew){
    for(unsigned int i = 0;i < d.size();++i){
        if(yNew)if(yNew(i,0,d))return;
        for(unsigned int j = 0;j < d[i].size();++j){
            if(xNew)if(xNew(i,j,d))return;
            cout << d[i][j];
        }
        cout << endl;
    }
}


void opencb::io::clrscr(){
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );

	GetConsoleScreenBufferInfo( hConsole, &csbi );
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter( hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten );
	GetConsoleScreenBufferInfo( hConsole, &csbi );
	FillConsoleOutputAttribute( hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten );
	SetConsoleCursorPosition( hConsole, coordScreen );
}
