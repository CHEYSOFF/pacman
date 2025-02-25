#pragma once
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
#include <chrono>
#include <random>
#include <fstream>

#include "point.h"
#include "variables.h"

using namespace std;

int margin(string s){
    return (win_width/pix_char-s.size())/2;
}

int marggame(string s){
    return (wi*2-s.size())/2;
}

void cen_out(string s){

    int ot= margin(s);
    for(int i=0;i<ot;i++){
        cout<<" ";
    }

    cout<<s;


}

void cen_out_ga(string s){

    int ot= marggame(s);
    for(int i=0;i<ot;i++){
        cout<<" ";
    }

    cout<<s;


}

void updateScreen(){
    int i, j;
    
    for(i=0;i<he+4+3+2;i++) cout<<UP;

    cout<<GRA;
    cout<<" +=";
    for(int i=0; i<wi*2-1; i++) cout<<'=';
    cout<<"=+ ";
    cout<<'\n';
    // string tmp=to_string(wait_gamer)+" "+to_string(start_wait_ghost)+" "+to_string(ghost_speed_modifier)+" "+to_string(wait_ghost);
    string rn="ROUND NUMBER A";
    // cen_out(tmp);
    // cout<<'\n';
    int mar=marggame(rn);
    cout<<mar_left;
    for(int i=0;i<mar;i++) cout<<' ';
    cout<<GRA<<"ROUND NUMBER ";
    cout<<BLU<<round_num<<'\n';

    cout<<UP;
    for(int i=0;i<wi*2+mar_left.size()-1;i++) cout<<RIG;
    cout<<GRA<<" | ";
    cout<<'\n';

    cout<<" +=";
    for(int i=0; i<wi*2-1; i++) cout<<'=';
    cout<<"=+ ";
    cout<<'\n';

    for(i=0;i<he;i++){

        cout<<GRA<<mar_left;
        for(j=0;j<wi;j++){
            cout<<GRA;
            bool outed=0;
            point curpo;
            curpo.i=i;
            curpo.j=j;
            if(fi_mon!=u && fi_mon==curpo){
                cout<<fi_mon_col[moncol];
                if(gh_white) cout<<GRA;
                cout<<BOLD<<"@"<<" ";
                outed=1;
                continue;
            }
            else if(se_mon!=u && se_mon==curpo){
                cout<<se_mon_col[moncol];
                if(gh_white) cout<<GRA;
                cout<<BOLD<<"@"<<" ";
                outed=1;
                continue;
            }
            else if(th_mon!=u && th_mon==curpo){
                cout<<th_mon_col[moncol];
                if(gh_white) cout<<GRA;
                cout<<BOLD<<"@"<<" ";
                outed=1;
                continue;
            }
            else if(fo_mon!=u && fo_mon==curpo){
                cout<<fo_mon_col[moncol];
                if(gh_white) cout<<GRA;
                cout<<BOLD<<"@"<<" ";
                outed=1;
                continue;
            }
            else if(gam==curpo){
                cout<<YEL<<BOLD<<"C"<<" ";
                outed=1;
                continue;
            }
            if(!outed){


                if(arr[i][j]==0) cout<<GRA<<" "<<" ";
                else if(arr[i][j]==1) cout<<PUR<<"H"<<" "; 
                else if(arr[i][j]==2) cout<<GRE<<"*"<<" ";
                else if(arr[i][j]==5) cout<<RED<<BOLD<<"6"<<" ";
                else if(arr[i][j]==3) cout<<RED<<BOLD<<"#"<<" ";


            }
            
            
        }
        cout<<GRA<<"| ";
        cout<<'\n';
    }
    
    cout<<GRA;
    cout<<GRA<<" +=";
    for(int i=0; i<2*wi-1; i++) cout<<'=';
    cout<<"=+ ";

    cout<<'\n';
    cout<<GRA<<mar_left;
    cout<<'\n';
    cout<<GRA<<mar_left;
    cout<<YEL;
    string ys="YOUR SCORE: "+to_string(curscore);
    cen_out_ga(ys);
    cout<<"     ";//чтобы закрыть предыдущий текст :(
    cout<<'\n';
    cout<<GRA<<mar_left;
    string ll="LIVES LEFT: "+to_string(lives);
    
    cout<<RED;
    cen_out_ga(ll);
    cout<<"     ";//чтобы закрыть предыдущий текст :(
    cout<<'\n';
    
    for(int i=0;i<2*wi;i++){
        cout<<" ";
    }
    cout<<UP;
    cout<<'\n';

    cout<<GRA<<mar_left;
    
    

    if(energAct==1){
        
        string nrgtime=to_string(energTime/1000);
        string eia="ENERGIZER IS ACTIVE "+nrgtime;
        cout<<energColArr[energCol];
        cen_out_ga(eia);
        // for(int i=0;i<4;i++) cout<<' ';// закрашивание
        // cout<<'\n';
    }
    else{
        for(int i=0;i<2*wi;i++){
            cout<<" ";
        }
    }
    cout<<'\n';
    
    cout<<GRA;
    cout<<" +=";
    for(int i=0; i<wi*2-1; i++) cout<<'=';
    cout<<"=+ ";

    for(int i=0;i<4;i++) cout<<UP;
    for(int i=0;i<4;i++){
        
        for(int i=0;i<wi*2+mar_left.size()-1;i++) cout<<RIG;
        cout<<GRA<<" | ";
        cout<<'\n';
    }



    cout<<flush;
}

void scr_upd_tim(){
    while(gameContinue){
        updateScreen();
    }
}