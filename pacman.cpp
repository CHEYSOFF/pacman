#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <Winuser.h>
#include <time.h>
#include <thread>
#include <string>
#include <queue>
#include <algorithm>
#include <atomic>

using namespace std;


#define PUR "\033[95m"
#define BLU "\033[94m"
#define CYA "\033[96m"
#define GRE "\033[92m"
#define YEL "\033[93m"
#define RED "\033[91m"
#define GRA "\033[0m"

// int gcd(int a, int b){

// }

struct point{

    int i, j;

};

point operator+(point a, point b){
    point tmp;
    tmp.i=a.i+b.i;
    tmp.j=a.j+b.j;
    return tmp;
}
point operator-(point a, point b){
    point tmp;
    tmp.i=a.i-b.i;
    tmp.j=a.j-b.j;
    return tmp;
}
bool operator==(point a, point b){
    return (a.i==b.i && a.j==b.j);
}
bool operator!=(point a, point b){
    return (a.i!=b.i || a.j!=b.j);
}

point u;


// bool door=1;//0 открыта 1 закрыта
int dir;
int curscore=0;
const int he = 31;//26
const int wi = 28;//26
int arr[he][wi]={   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                    {1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                    {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
                    {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
                    {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                    {1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
                    {1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
                    {1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
                    {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
           /* 14 */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                    {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
                    {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
                    {1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1},
                    {1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1},
                    {1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1},
                    {1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
                    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
                    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };

point gam;


bool cango(point p){
    if( (arr[p.i][p.j]!=1 && !(p.i==12 && p.j>=11 && p.j<=16) ) || (p.i==14 && ( p.j==-1 || p.j==wi )  ) ) return true;
    return false;
}



// class Monster{
//     public:
//         int x_pos;
//         int y_pos;
// };

point fi_mon;
point se_mon;

// vector< point > monster_pos;

void updateScreen(){
    int i, j;
    // cout<<endl;
    for(i=0;i<he+1;i++){
        
        cout<<"\033[F";
        // cout<<"                                                                                                                                              ";
        // cout<<"\033[F";
    }
    // string s(he);
    // cout<<'\n';
    for(i=0;i<he;i++){
        cout<<"   ";
        for(j=0;j<wi;j++){
            bool ghost=0;
            point curpo;
            curpo.i=i;
            curpo.j=j;
            if(fi_mon!=u && fi_mon==curpo){
                cout<<CYA<<"@"<<" ";
                ghost=1;
                continue;
            }
            else if(se_mon!=u && se_mon==curpo){
                cout<<BLU<<"@"<<" ";
                ghost=1;
                continue;
            }
            // for(int mon_num=0; mon_num<monster_pos.size(); mon_num++){
            //     if(monster_pos[mon_num]==curpo){
            //         cout<<CYA<<"@"<<" ";
            //         ghost=1;
            //         break;
            //     }
            // }
            if(!ghost){


                if(arr[i][j]==5) cout<<YEL<<"C"<<" ";
                else if(arr[i][j]==0) cout<<GRA<<"."<<" ";
                else if(arr[i][j]==1) cout<<PUR<<"H"<<" "; 


            }
            
            
        }
        // cout<<"                       ";
        cout<<'\n';
    }
    cout<<"YOUR SCORE="<<curscore<<'\n';
    cout<<flush;
}

atomic< int > death;//1 съеден монстром || -1 лив || 0 жив
static atomic< bool > gameContinue = true;
void goup(){
    
    point p=gam;
    p.i--;
    if( cango(p) ){
        arr[gam.i][gam.j]= 0;
        arr[gam.i-1][gam.j]= 5;
        gam.i--;
        return;
    }


    
}

void godown(){
    point p=gam;
    p.i++;
    if(cango(p) ){
        arr[gam.i][gam.j]= 0;
        arr[gam.i+1][gam.j]= 5;
        gam.i++;
        return;
    }

}

void goleft(){
    point p=gam;
    p.j--;
    if(cango( p ) ){

        if(gam.i==14 && gam.j==0){
            arr[gam.i][gam.j]= 0;
            arr[gam.i][wi-1]= 5;
            gam.j=wi-1;
            return;
        }
        
        arr[gam.i][gam.j]= 0;
        arr[gam.i][gam.j-1]= 5;
        gam.j--;
        return;
    }
    


    
}

void goright(){

    point p=gam;
    p.j++;

    if(cango( p ) ){
        if(gam.i==14 && gam.j==wi-1){
            arr[gam.i][gam.j]= 0;
            arr[gam.i][0]= 5;
            gam.j=0;
            return;
        }

        arr[gam.i][gam.j]= 0;
        arr[gam.i][gam.j+1]= 5;
        gam.j++;
        return;


    }

    


    
}

bool valid(point a){
    if(a.i<he && a.i>=0 && a.j<wi && a.j>=0 && arr[a.i][a.j]!=1) return 1;
    else return 0; 
}

// point fix(point a){
//     if(a.j==-(wi-1)) a.j=1;
//     else if(a.j==(wi-1) ) a.j=-1;
//     return a;
// }


point fastest_way(point s, point e){
    queue< point > q;
    q.push (s);
    point tmp_p;
    tmp_p.i=0;
    tmp_p.j=0;
    if(s==e) return tmp_p;
    
    vector< vector<point> > used(he, vector< point >(wi, u) );
    
    // used[s.i][s.j]=0;

    point hod[4];

    point tmp;

    tmp.i=0;
    tmp.j=1;
    hod[0]=tmp;

    tmp.j=-1;
    hod[1]=tmp;

    tmp.i=1;
    tmp.j=0;
    hod[2]=tmp;

    tmp.i=-1;
    hod[3]=tmp;


    for(;!q.empty();){

        point from=q.front();
        q.pop();

        for(int kt=0; kt<4;kt++){

            point to=from+hod[kt];
            if( to.i==14 && to.j==-1 ){
                to.j=27;
            }
            else if( to.i==14 && to.j==28 ){
                to.j=0;
            }
            

            if( valid(to) && used[to.i][to.j]==u){
                used[to.i][to.j]=from;
                q.push(to);


                if(to==e){

                    point nev=to;
                    for(;;){
                        
                        if(nev==u) return u;
                        
                        if(used[nev.i][nev.j]==s){
                            point ans=nev-s;
                            return(ans);
                        }

                        nev=used[nev.i][nev.j];
                    }

                }



            }


        }



    }

        
    return u;
}


void mon_bfs(){

    point mon_dir=fastest_way(fi_mon, gam );
    if(mon_dir==u){
        return;
    }
    point newpos=fi_mon+mon_dir;
    fi_mon=newpos;
    if( newpos==gam ){
        gameContinue=0;
        death=1;

        
        return;
    }
    

}


void mon_left(int &dir){
    
    
    // point next=next_point(dir)


}

const int dop=2000;
const int dcl=20000;
atomic< int > curtime=0;
const int cycle=dop+dcl;
const int wait_ghost=400;
const int wait_gamer=300;

void mon_thr(){
    vector< bool > monplaced(3, 0);
    // bool mon2placed=0;
    int m_l_dir=0;//0 вверх | 1 вправо | 2 вниз | 3 влево
    while(gameContinue){
        
        if(curtime >= (cycle)*0 ){
            if( !monplaced[1] ){
                fi_mon.i=14;
                fi_mon.j=12;

            }
            monplaced[1]=1;
            mon_bfs();
        }
        
        if(curtime >= (cycle)*1 ){

            if( !monplaced[2] ){
                se_mon.i=14;
                se_mon.j=11;

            }
            monplaced[2]=1;
            mon_left(m_l_dir); 
        } 
        Sleep(wait_ghost);
        

    }

}

void dopen(){
    for(int j=11;j<=16;j++) arr[12][j]=0;
}

void dclose(){
    for(int j=11;j<=16;j++) arr[12][j]=1;
}

void character(){
    // cout<<-1;
    dir=1; //0 вверх | 1 вправо | 2 вниз | 3 влево

    while (gameContinue){
        

        // BYTE helpar[256];
        // for(int i=0;i<256;i++)helpar[i]=0; 
        // GetKeyboardState(helpar);
        // int p;
        // for (int _i = 0; _i < 5; _i++)
        // for(int i=0;i<256;i++){
        //     // cout<<helpar[i]<<" ";
        //     if((int)helpar[i] & 0x8000) p=i;
        // }
        
        // // cout << ((short)GetKeyState('D') & 0x8000) << endl;
        // if ((short)GetKeyState('W') & 0x8000)
        //         goup();
        // else if ((short)GetKeyState('S') & 0x8000)
        //         godown();
        // else if ((short)GetKeyState('A') & 0x8000)
        //         goleft();
        // else if ((short)GetKeyState('D') & 0x8000)
        //         goright();
        // else if ((short)GetKeyState(VK_ESCAPE) & 0x8000)
        // {
        //         gameContinue=0;
        //         return;
        // }
        


        switch(dir){
            case 0:
                goup();
                break;
            case 2:
                godown();
                break;
            case 3:
                goleft();
                break;
            case 1:
                goright();
                break;
        }





        // updateScreen();
        // SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE) ,ENABLE_ECHO_INPUT);
        // BlockInput(true);
        Sleep(wait_gamer);
        // BlockInput(false);
        // SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE) ,ENABLE_ECHO_INPUT);
        // if (!gameContinue.is_lock_free()) return;
    }
    return;
}



void door_time(){
    while(gameContinue){

        dopen();
        // door=0;
        // updateScreen();
        Sleep(dop);
        if(curtime<cycle*3) curtime+=dop;
        
        // door=1;
        dclose();
        // updateScreen();
        Sleep(dcl);
        if(curtime<cycle*3) curtime+=dcl;

        // if (!gameContinue.is_lock_free()) return;


    }
}

void scr_upd_tim(){
    while(gameContinue){
        updateScreen();
        // Sleep(10);
        // if (!gameContinue.is_lock_free()) return;
    }
}

void input_key(){
    while(gameContinue){
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE) );
    
        switch(getch()){
                case 119:
                    if(arr[gam.i-1][gam.j]!=1){
                        dir=0;
                    }
                    
                    break;
                case 115:
                    if(arr[gam.i+1][gam.j]!=1){
                        dir=2;
                    }
                    
                    break;
                case 97:
                    if( (gam.j>=0 && arr[gam.i][gam.j-1]!=1) || (gam.i==14 && gam.j==0 )  ){
                        dir=3;
                    }
                    
                    break;
                case 100:
                    if( (gam.j+1<wi && arr[gam.i][gam.j+1]!=1) || (gam.i==14 && gam.j==wi-1) ){
                        dir=1;
                    }
                    
                    break;
                case 27:
                    gameContinue=0;
                    death=-1;
                    break;
                    // return;
            }

            // if (!gameContinue.is_lock_free()) return;

    }
}


void leave(){
    
    system("cls");
    cout<<"GAME OVER\n";;
    cout<<"YOUR SCORE="<<curscore<<'\n';
    cout<<flush;

}


void threads_begin(){

    thread cha(character);
    thread inp(input_key);
    thread door(door_time);
    thread screen(scr_upd_tim);
    thread mon(mon_thr);

    screen.join();
    door.detach();
    cha.detach();
    inp.detach();
    mon.detach();

}


int main(){
    

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    srand(time(NULL));
    
    u.i=-1;
    u.j=-1;

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
    GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);
    short winHeight = scrBufferInfo.srWindow.Bottom - scrBufferInfo.srWindow.Top + 1;
    short scrBufferWidth = scrBufferInfo.dwSize.X;        
    short scrBufferHeight = scrBufferInfo.dwSize.Y;        
    COORD newSize;
    newSize.X = scrBufferWidth;
    newSize.Y = winHeight;
    SetConsoleScreenBufferSize(hOut, newSize);

    HWND hwnd = GetConsoleWindow();
    ShowScrollBar(hwnd, SB_BOTH, 0);
    RECT ConsoleRect;
    GetWindowRect(hwnd, &ConsoleRect);
    MoveWindow(hwnd, ConsoleRect.left, ConsoleRect.top, 470, 570, TRUE);
    // cin.sync();
    
    // cout<<'\n';

    int lives=3;
    // if (!gameContinue.is_lock_free()) return 10;

    
    while(lives!=0){
        gam.i=1;
        gam.j=1;
        curtime=0;
        gameContinue=1;
        fi_mon=u;
        se_mon=u;
        system("cls");
        cout<<flush;
        updateScreen();
        death=0;
        gam.i=1;
        gam.j=1; 
        
        
        threads_begin();
        arr[gam.i][gam.j]=0;
        
        cout<<"LIVEs="<<lives<<endl;


        // inp.detach();
        // screen.detach();
        // door.detach();
        // cha.detach();


        cout<<death<<endl;

        Sleep(10000);

        if(death==-1){
            break;
        }

        lives--;

        cout<<"YOU DIED\n";
        cout<<"Lives left: "<<lives<<'\n';


    }

    leave();
    return 0;

    



    
    /*5-персонаж
      7-монстр
      0-пустота
      1-стенка
      9-выход
      224-клавиша вверх
      119-W
      97-A
      115-S
      100-D
      27-ESC*/

    


    
    return 0;


    // mon.detach();
    // t.detach();
}