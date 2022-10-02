#include "opencb.h"

using namespace std;
//extern bool solution2;

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


inline GString BlankWith(GString &in,size_t i){
    GString ret = Str("");
    for(unsigned int j = 0;j < in.size()-i;++j){
        ret += Str(" ");
    }
    return ret;
}

void opencb::io::SwapPrint(vector<GString> data,fn line,fn perChar){
    bool _empty;
    unsigned int index = 0;
    opencb::base::SetConsolePosition();
    while(true){
        _empty = true;
        if(line)if(line(index,0,data))return;
        for(int idx = 0;idx < (int)data.size();++idx){
            GString & l = data[idx];
            if(l.size() > index){
                _empty = false;
                //Draw elements Here
                if(perChar)if(perChar(index,idx,data))return;
                opencb::base::SetConsolePosition(0,idx);
                sout << data[idx];
                opencb::base::SetConsolePosition(index+1,idx);
                //Build a blank
                sout << BlankWith(data[idx],index);
            }
            opencb::base::SetConsolePosition(index,idx+1);
        }
        if(_empty)break;
        ++index;
        opencb::base::SetConsolePosition(index);//Back to origin,default func(0,0)
    }
    opencb::base::SetConsolePosition(0,data.size());
}


void opencb::io::SwapPrintEx(vector<vector<GString>> d,fn xNew,fn yNew){
    for(vector<GString> & s : d)opencb::io::SwapPrint(s,xNew,yNew);
}

void opencb::base::SetColor(int fore,int backg){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),fore | (backg*80));
}

void opencb::io::EasyPrint(vector<GString> d,fn xNew,fn yNew){
    for(unsigned int i = 0;i < d.size();++i){
        if(yNew)if(yNew(i,0,d))return;
        for(unsigned int j = 0;j < d[i].size();++j){
            if(xNew)if(xNew(i,j,d))return;
            opencb::base::SetConsolePosition(0,i);
            sout << d[i];
            opencb::base::SetConsolePosition(j+1,i);
            //Build a blank
            sout << BlankWith(d[i],j);
        }
        sout << endl;
    }
}


void opencb::io::EasyDelay(GString s,int milli){
    for(gchar& c : s){
        sout << c;
        Sleep(milli);
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
