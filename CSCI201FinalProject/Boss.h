#ifndef Boss
#define Boss
#include <iostream>
#include <random>
#include <stdlib.h>
#include <string>
#include <time.h>

using namespace std;

class boss {
private:
  int HP = 50;//initial boss HP
  int phys_damage = 5;
  string Spell_name[5] = {"Fire ball", "Lightning strike", "Frozen ground",
                          "Sun beam", "Earth splitter"};
  int Spell_damage[5] = {10, 8, 5, 7, 9};
  int Spell_cooldown[5] = {0, 0, 0, 0, 0};
  string Boss_name;
  string name_list[5] = {"Lord of the flies", "Eternal Darkness", "Your Mom",
                         "Balthazar", "Shadow Fiend"};

public:
  boss(int HP_item_count, int dmg_item_count) {//constructor to create boss based on amount of equipment player has
    srand(time(NULL));
    HP = HP + HP_item_count * 5;
    phys_damage = phys_damage + dmg_item_count * 10;
    Boss_name = name_list[rand() % 5];
  }
  string get_boss_name() { return Boss_name; }
  int get_HP() { return HP; }
  string UseSpell(int i) {//use spell function
    if (Spell_cooldown[i] == 0) {
      return Spell_name[i];
    } else {
      return "On cooldown";
    }
  }
  int SpellDamage(int i) { return Spell_damage[i]; }
  void BeginofTurn() {//cooldown count
    for (int i; i < 5; i++) {
      if (Spell_cooldown[i] != 0) {
        Spell_cooldown[i] = -1;
      }
    }
  }
  int UsePhysical() { return phys_damage; }
  void takeDamage(int a) { HP = HP - a; }
};

#endif