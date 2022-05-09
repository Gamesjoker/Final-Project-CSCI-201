#include <iostream>
#include <random>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Monster
{
private:
  //Initialize private variables to 0
  int monster_max_HP=0;
  int monsterDamage=0;
  int monsterHP=0;
public:
  //Constructor to create a monster
  Monster(int monHP, int monDamage) {
    monster_max_HP = monHP + 1;
    monsterDamage = monDamage + 1;
    setMonsterHP(monster_max_HP);
  }
  //class function definitions
  void setMonsterHP(int hp){monsterHP=hp;}
  int getMonster_max_HP(){return monster_max_HP;}
  int getMonsterHP() {
    return monsterHP;
  }
  int getMonsterDamage() {
    return monsterDamage;
  }
  void takeDamage(int d){
    monsterHP = monsterHP - d;
  }
};