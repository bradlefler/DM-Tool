#include <iostream>
#include <stdlib.h> //for rand and srand
#include <vector>
#include <ctime>

using namespace std;

struct Unit
{
       string Uname;
       int init;
};

int roll();
void collectPlayers(vector<Unit> &pcs);
void rollInitiative(vector<Unit> mons, vector<Unit> pcs, vector<Unit> &initiatives);
void collectMonsters(vector<Unit> &mons);
void print(vector<Unit> &initiatives);

int main()
{
       srand (time(0));
       bool PCSet = false; //checks to see if characters have been added to the intiative order
       char response;
       vector<Unit> pcs;
       vector<Unit> mons;
       vector<Unit> initiatives;
       while(response != 'Q' && response != 'q')
       {
              cout<<"What would you like to do?"<<endl;
              cout<<"A. Roll Dice"<<endl;
              cout<<"B. Roll Initiatives"<<endl;
              cout<<"Q. Quit"<<endl;
              cin>>response;
              if(response == 'A' || response == 'a')
              {
                     int result = roll();
                     cout<<"You Rolled: "<<result<<endl;
              }
              else if(response == 'B' || response == 'b')
              {
                     if(!PCSet)
                     {
                            collectPlayers(pcs);
                            PCSet = true;
                     }
                     mons.clear();
                     collectMonsters(mons);
                     rollInitiative(mons, pcs, initiatives);
                     print(initiatives);

              }
              else if(response == 'T' || response == 't')
              {
                     int mSize = mons.size();
                     int pSize = pcs.size();
                     for(int i = 0; i < mSize; i++)
                     {
                            cout<<mons[i].Uname<<" "<<mons[i].init<<endl;
                     }
                     for(int i = 0; i < pSize; i++)
                     {
                            cout<<pcs[i].Uname<<" "<<pcs[i].init<<endl;
                     }
              }
              else if(response == 'Q' || response == 'q')
              {
                     cout<<"Quitting!"<<endl;
              }
              else
              {
                     cout<<"Invalid Response."<<endl;
              }
       }
       return 0;
}

int roll()
{
       int mod;
       int type;
       int amount;
       cout<<"What kind of dice? (i.e. 20, 8, etc.)"<<endl;
       cin>>type;
       cout<<"What modifiers do the dice have? (If no modifiers, put 0.)"<<endl;
       cin>>mod;
       cout<<"How many dice are you rolling?"<<endl;
       cin>>amount;
       int result = 0;
       for(int i = 0; i < amount; i++)
       {
              int dice = rand() % type + 1;
              result = result + dice;
       }

       return result + mod;
}


void collectPlayers(vector<Unit> &pcs)
{
       int num = 0;
       cout<<"How many players do you have?"<<endl;
       cin>>num;
       pcs.resize(num);
       for(int i = 0; i < num; i++)
       {
              string name;
              int initMod;
              cout<<"What is the name of player "<<i + 1<<"?"<<endl;
              cin>>name;
              cout<<"What is that player's initiative modifier?"<<endl;
              cin>>initMod;
              pcs[i].Uname = name;
              pcs[i].init = initMod;
       }
}

void collectMonsters(vector<Unit> &mons)
{
       int num = 0;
       cout<<"How many types of monsters are you adding?"<<endl;
       cin>>num;
       for(int i = 0; i < num; i++)
       {
              string name;
              int modifier;
              int amount;
              cout<<"What is the name of your monster?"<<endl;
              cin>>name;
              cout<<"How many of them are there?"<<endl;
              cin>>amount;
              cout<<"What is their initiative modifier?"<<endl;
              cin>>modifier;

              Unit temp;
              temp.Uname = name;
              temp.init = modifier;
              for(int i = 0; i < amount; i++)
              {
                     mons.push_back(temp);
              }
       }

}

void rollInitiative(vector<Unit> mons, vector<Unit> pcs, vector<Unit> &initiatives)
{
       int mons_size = mons.size();
       int pcs_size = pcs.size();
       int size = mons_size + pcs_size;
       initiatives.resize(size);
       int place = 0;
       for(int j = 0; j < mons_size; j++)
       {
              string name = mons[j].Uname;
              int mod = mons[j].init;
              string monName = name + to_string(j);
              int dice = rand() % 20 + 1;
              initiatives[place].Uname = monName;
              initiatives[place].init = dice + mod;
              place++;
       }
       for(int i = 0; i < pcs_size; i++)
       {
              string pname = pcs[i].Uname;
              int mod = pcs[i].init;
              int dice = rand() % 20 + 1;
              initiatives[place].Uname = pname;
              initiatives[place].init = dice + mod;
              place++;
       }
}

void print(vector<Unit> &initiatives)
{
       int size = initiatives.size();
       for(int i = 30; i >=0; i--)
       {
              for(int j = 0; j < size; j++)
              {
                     if(initiatives[j].init == i)
                     {
                            cout<<initiatives[j].Uname<<" "<<initiatives[j].init<<endl;
                     }
              }
       }
}
