#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <fstream>
#include <conio.h>
#include <SFML/Audio.hpp>
#include <time.h>
#include "opencb.h"
#include "Generic.h"
#include "CClock.h"
#define CN "data/cn.txt"
#define EN "data/en.txt"
#define CON "data/config.cfg"
#define  IsKeyPressed(nVirtKey)     ((GetKeyState(nVirtKey) & (1<<(sizeof(SHORT)*8-1))) != 0)
#define  IsAKeyPressed(nVirtKey)     ((GetAsyncKeyState(nVirtKey) & (1<<(sizeof(SHORT)*8-1))) != 0)

using namespace std;
using namespace opencb::io;
using namespace opencb::base;
using namespace sf;

int sleept= 80;
HWND heart = NULL,gameWin = NULL;
sf::Music music;
#define GAME_WIN 2
#define GAME_OVER 1
#define GAME_CONT 0
int gameStatus = GAME_CONT;
struct Player{
    float x;
    float y;
    float w;
    float h;
    float hp;
    float maxHp;
    float shield;
    float maxShield;
    float speed;
};
struct Bullet{
    float x;
    float y;
    float w;
    float h;
    bool save {true};
    virtual void draw(){}
    virtual void flush(){}
    virtual ~Bullet(){}
};


unsigned int sysx,sysy;
string ts = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()~`_-+={}:\"<>?,./;\'\\|[]";
struct TextBullet : public Bullet{
    static HDC DC;
    string t;
    COLORREF co;
    void draw() override{
        COLORREF old = GetTextColor(DC);
        SetTextColor(DC,co);
        TextOut(DC,x,y,t.c_str(),t.size());
        SetTextColor(DC,old);
        y += sysy / 250;
        if(y > sysy+10)save = false;
    }
    void flush() override{
        t = "";
        t += ts[rand()%ts.size()];
        co = RGB(rand()%256,rand()%256,rand()%256);
    }
    TextBullet(){
        t = "";
        t += ts[rand()%ts.size()];
        x = rand()%(sysx-80)+80;
        y = 0;
        w = 8;
        h = 8;
    }
};
HDC TextBullet::DC = GetDC(NULL);

vector<Bullet*> bullets;

struct ResourceLock{
    ~ResourceLock(){
        for(Bullet * b : bullets)delete b;
    }
};
ResourceLock resourceLock;

Player pl = {0,0,20,20,100,100,100,100,1};
//extern bool solution2;

bool fnxx(int,int,vector<GString>&){
    Sleep(sleept);
    return false;
}

bool fndd(int,int,vector<GString>&){
    Sleep(sleept/2);
    return false;
}

bool fnss(int,int,vector<GString>&){
    Sleep(sleept);
    music.setPlayingOffset(music.getPlayingOffset() - sf::milliseconds(sleept + 5));
    return false;
}

GString operator +(vector<GString> d,int v){
    if(v < 0 || v >= (int)d.size())return Str("");
    return d[v];
}
vector<GString> subvec(vector<GString> d,int st,int ed){
    vector<GString> ret;
    for(int i = st;i <= ed;++i){
        ret.push_back(d + i);
    }
    return ret;
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_COMMAND:
            if(wParam == 1){
                PostQuitMessage(0);
            }
            break;
        case WM_DESTROY:
            break;
        case WM_CLOSE:
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

struct RectX{
    float x,y,w,h;
};
bool test_collision__2(RectX rect1, RectX rect2){
    int x1_1 = rect1.x;
    int y1_1 = rect1.y;
    int x1_2 = rect1.x + rect1.w;
    int y1_2 = rect1.y;
    int x1_3 = rect1.x;
    int y1_3 = rect1.y + rect1.h;
    int x1_4 = rect1.x + rect1.w;
     int y1_4 = rect1.y + rect1.h;



     int x2_1 = rect2.x;
     int y2_1 = rect2.y;
     int x2_2 = rect2.x + rect2.w;
     int y2_2 = rect2.y;
     int x2_3 = rect2.x;
     int y2_3 = rect2.y + rect2.h;
     int x2_4 = rect2.x + rect2.w;
     int y2_4 = rect2.y + rect2.h;

     // 判断矩形一的四个顶点之一是否在矩形二中
    if( (x1_1 > x2_1 && x1_1 < x2_4) && (y1_1 > y2_1 && y1_1 < y2_4) )
     {
         return true;
     }

     if( (x1_2 > x2_1 && x1_2 < x2_4) && (y1_2 > y2_1 && y1_2 < y2_4) )
     {
         return true;
     }

     if( (x1_3 > x2_1 && x1_3 < x2_4) && (y1_3 > y2_1 && y1_3 < y2_4) )
     {
         return true;
     }

     if( (x1_4 > x2_1 && x1_4 < x2_4) && (y1_4 > y2_1 && y1_4 < y2_4) )
     {
         return true;
     }

     // 判断矩形二的四个顶点之一是否在矩形一中
     if( (x2_1 > x1_1 && x2_1 < x1_4) && (y2_1 > y1_1 && y2_1 < y1_4) )
     {
         return true;
     }
    if( (x2_2 > x1_1 && x2_2 < x1_4) && (y2_2 > y1_1 && y2_2 < y1_4) )
    {
       return true;
    }

     if( (x2_3 > x1_1 && x2_3 < x1_4) && (y2_3 > y1_1 && y2_3 < y1_4) )
     {
         return true;
     }

     if( (x2_4 > x1_1 && x2_4 < x1_4) && (y2_4 > y1_1 && y2_4 < y1_4) )
     {
         return true;
     }

     return false;
}
void full_screen(HWND hwnd){
    int cx = GetSystemMetrics(SM_CXSCREEN);            /* 屏幕宽度 像素 */
    int cy = GetSystemMetrics(SM_CYSCREEN);            /* 屏幕高度 像素 */

    LONG l_WinStyle = GetWindowLong(hwnd,GWL_STYLE);   /* 获取窗口信息 */
    /* 设置窗口信息 最大化 取消标题栏及边框 */
    SetWindowLong(hwnd,GWL_STYLE,(l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);

    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, cx, cy, 0);
}
vector<GString> strings;

void Disable(){
    //设置控制台，禁用编辑
    auto hStdin = ::GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);
    mode &= ~ENABLE_QUICK_EDIT_MODE;
    SetConsoleMode(hStdin, mode);
    CONSOLE_CURSOR_INFO ci;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&ci);
    ci.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&ci);
}
void * game(void *){
    cck::Clock clk,tw;
    string show;
    while(true){
        if(IsAKeyPressed(VK_ESCAPE)){
            break;
        }else if(IsAKeyPressed('W')){
            if(pl.y - sysy/200 * pl.speed > 80){
                pl.y -= sysy/200 * pl.speed;
                SetWindowPos(heart,HWND_TOPMOST,(int)pl.x,(int)pl.y,(int)pl.w,(int)pl.h,0);
            }
        }else if(IsAKeyPressed('A')){
            if(pl.x - sysy/200 * pl.speed > 80){
                pl.x -= sysy/200 * pl.speed;
                SetWindowPos(heart,HWND_TOPMOST,(int)pl.x,(int)pl.y,(int)pl.w,(int)pl.h,0);
            }
        }else if(IsAKeyPressed('S')){
            if(pl.y + sysy/200 * pl.speed < sysy-pl.h){
                pl.y += sysy/200 * pl.speed;
                SetWindowPos(heart,HWND_TOPMOST,(int)pl.x,(int)pl.y,(int)pl.w,(int)pl.h,0);
            }
        }else if(IsAKeyPressed('D')){
            if(pl.x + sysy/200 * pl.speed < sysx-pl.w){
                pl.x += sysy/200 * pl.speed;
                SetWindowPos(heart,HWND_TOPMOST,(int)pl.x,(int)pl.y,(int)pl.w,(int)pl.h,0);
            }
        }
        if(clk.Now().offset >= 10){
            clk.Stop();
            clk.Start();
            {
                vector<Bullet*> tmp;
                for(Bullet* b : bullets){
                    b->draw();
                    if(test_collision__2({b->x,b->y,b->w,b->h},{pl.x,pl.y,pl.w,pl.h})){
                        pl.hp --;
                    }
                    if(b->save)tmp.push_back(b);
                    else delete b;
                }
                bullets = tmp;
            }
        }
        if(tw.Now().offset >= 1200){
            tw.Stop();
            tw.Start();
            bullets.push_back(new TextBullet());
            for(Bullet* b : bullets){
                b->flush();
            }
        }
        if(pl.hp <= 0){
            gameStatus = GAME_OVER;
            break;
        }
        show = "HP:";
        show += to_string((int)pl.hp) + "/" + to_string((int)pl.maxHp);
        TextOut(TextBullet::DC,0,0,show.c_str(),show.size());

    }
    if(gameStatus == GAME_OVER){
        music.stop();
        if(!music.openFromFile("data/gameover.ogg")){
            MessageBox(NULL,"Can not find music data/gameover.ogg!","Fatal Error",MB_TOPMOST | MB_OK | MB_ICONERROR);
            exit(-1);
        }
        music.play();
        ShowWindow(gameWin,SW_SHOW);
        ShowWindow(heart,SW_HIDE);
        full_screen(gameWin);
        SetWindowPos(gameWin, HWND_TOP, 0, 0, sysx, sysy, 0);
        Disable();
        EasyPrint(subvec(strings,25,26),fnxx);
        clrscr();
        SetColor(CL_YELLOW);
        sleept = 120;
        EasyPrint(subvec(strings,27,27),fnss,fnss);
        SetColor();
        Sleep(1000);
        ///Generate Error Code
        clrscr();
        vector<GString> tmp;
        GString code = Str("");
        for(int i = 0;i < 128;++i){
            code = Str("");
            for(int j = 0;j < 256;++j){
                code += (gchar)(ts[rand()%ts.size()]);
            }
            tmp.push_back(code);
        }
        system("color f0");
        sleept = 10;
        for(GString& str : tmp){
            sout << str << endl;
            fnss(0,0,tmp);
        }
    }
    PostMessage(heart,WM_COMMAND,1,0);
    return NULL;
}

TCHAR className[] = TEXT("Errtale_Wnd_Class");

int main()
{
    //不是伪随机！
    srand(time(0));
    system("cls & color 0f & mode con cols=128 lines=32");
    gameWin = GetConsoleWindow();
    SetWindowText(gameWin,"Errtale");
    {
        WNDCLASSEX wincl;        /* Data structure for the windowclass */

        /* The Window structure */
        wincl.hInstance = GetModuleHandle(NULL);
        wincl.lpszClassName = className;
        wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
        wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
        wincl.cbSize = sizeof (WNDCLASSEX);

        /* Use default icon and mouse-pointer */
        wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
        wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
        wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
        wincl.lpszMenuName = NULL;                 /* No menu */
        wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
        wincl.cbWndExtra = 0;                      /* structure or the window instance */
        /* Use Windows's default colour as the background of the window */
        wincl.hbrBackground = CreateSolidBrush(RGB(255,0,0));

        /* Register the window class, and if it fails quit the program */
        if (!RegisterClassEx (&wincl)){
            MessageBox(gameWin,"Can not register class!","Fatal Error",MB_OK | MB_ICONERROR);
            exit(-1);
        }
    }
    //Disable Console Controlls
    Disable();
    {
        sysx = GetSystemMetrics(SM_CXSCREEN);
        sysy = GetSystemMetrics(SM_CYSCREEN);
        pl.x = sysx/2;
        pl.y = sysy/2;
    }
    //Read config
    {
        int lang = 0;
        gifstream ifs(CON);
        if(ifs.good() && !ifs.eof()){
            ifs >> lang;
            ifs.close();
            if(lang == 1)ifs.open(CN);
            else ifs.open(EN);
        }else{
            ifs.close();
            gofstream ofs(CON);
            //Choose a language
            while(true){
                bool good = true;
                cout << "Please Select The Language 请选择语言：" << endl << "1.Simpled Chinese 简体中文" << endl << "2.English 英文" << endl;
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
                clrscr();
            }
            clrscr();
            ofs << lang;
            ofs.close();
        }
        //if(lang != 2)solution2 = true;
        GString l;
        while(!ifs.eof()){
            getline(ifs,l);
            strings.push_back(l);
        }
    }
    music.setLoop(true);
    if(!music.openFromFile("data/OnceUponATime.ogg")){
        MessageBox(gameWin,"Game music OnceUponATime.ogg has lost","Fatal Error",MB_OK | MB_ICONERROR);
        exit(-1);
    }
    SetWindowLong(gameWin,GWL_STYLE,GetWindowLong(gameWin,GWL_STYLE) & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
    Sleep(1000);
    if(IsKeyPressed(VK_SHIFT) != TRUE){
        sleept = 5;
        clrscr();
        SwapPrint(subvec(strings,0,10),fnxx);
        Sleep(1000);
        clrscr();
        music.play();
        sleept = 200;
        EasyPrint(subvec(strings,11,19),fndd,fnxx);
        Sleep(4500);
        clrscr();
        SetColor(CL_RED);
        sleept = 40;
        EasyPrint(subvec(strings,20,23),fnss,fnxx);
        Sleep(800);
        clrscr();
        SetColor();
        music.stop();
    }
    sleept = 50;
    EasyPrint(subvec(strings,24,24),fnxx);
    Sleep(100);
    system("cls");
    ShowWindow(gameWin,SW_HIDE);
    if(!music.openFromFile("data/Sans.ogg")){
        MessageBox(gameWin,"Game music Sans.ogg has lost","Fatal Error",MB_OK | MB_ICONERROR);
        exit(-1);
    }
    music.play();
    ///游戏正文
    heart = CreateWindowEx(0,className,"YourHeart",WS_POPUP,pl.x,pl.y,pl.w,pl.h,NULL,NULL,GetModuleHandle(NULL),NULL);
    //创建线程响应消息
    pthread_t gameT = 0;
    pthread_create(&gameT,NULL,game,NULL);
    pthread_detach(gameT);
    ShowWindow(heart,SW_SHOW);
    {
        MSG messages;            /* Here messages to the application are saved */
        /* Run the message loop. It will run until GetMessage() returns 0 */
        while (GetMessage(&messages, NULL, 0, 0))
        {
            if(gameStatus != GAME_CONT)break;
            /* Translate virtual-key messages into character messages */
            TranslateMessage(&messages);
            /* Send message to WindowProcedure */
            DispatchMessage(&messages);
        }
        SwitchToThisWindow(gameWin,TRUE);
        exit(0);
        //TerminateProcess(GetModuleHandle(NULL),0);
    }
}
