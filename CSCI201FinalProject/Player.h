#ifndef Player
#define Player
#include <iostream>
#include <random>
#include <stdlib.h>
#include <string>
#include <time.h>
using namespace std;
class player {
private:
  int max_HP = 50;
  int HP = 50;
  int phys_damage = 5;
  string Spell_name[5] = {"Heal", "Fire ball", "Sun ray", "Ice pick",
                          "Electric strike"};
  int Spell_damage[5] = {0, 10, 5, 7, 8};
  int Spell_cooldown[5] = {0, 0, 0, 0, 0};
  string player_name;

public:
  player(string name) { player_name = name; }
  int physatk() { return phys_damage; } // player use physical attack

  string UseSpell(int i) { // player use spell attack thus add to cooldown
    if (Spell_cooldown[i - 1] == 0) {
      cout << endl;
      return player_name + " uses " + Spell_name[i - 1] + "!";
    } else {   
      cout << endl;
      return "Spell is on cooldown.";
    }
  }

  int MagicDamage(int i) { 
    Spell_cooldown[i - 1] = 5;
    return Spell_damage[i - 1];
    } // return spell damage

  void HealSpell() { // one heal spell to restore HP
    Spell_cooldown[0] = 5;
    if (HP < max_HP && HP > (max_HP - 5)) {
      HP = (HP + 5) - ((HP + 5) % 50);
      cout << " " << player_name << " heal self for 5 HP. Total HP is: " << HP << endl;
      cout << endl;
    } else if (HP > 0 && HP <= (max_HP - 5)) {
      HP = HP + 5;
      cout << " " << player_name << " heal self for 5 HP. Total HP is: " << HP << endl;
      cout << endl;
    } else {
      cout << " You are at full HP and cannot be healed!" << endl;
      cout << endl;
    }
  }

  void takedamage(int d) { HP = HP - d; }

  void BeginofTurn() { // to count spell cooldown per turn
    for (int i = 0; i < 5; i++) {
      if (Spell_cooldown[i] != 0) {
        Spell_cooldown[i]--;
      }
    }
  }

  void increase_max_HP(int h) { max_HP = max_HP + h; }
  void increase_phys_damage(int d) { phys_damage = phys_damage + d; }
  void increase_spell_damage(int sd) {
    for (int i = 1; i < 5; i++) {
      Spell_damage[i] = Spell_damage[i] + 5;
    }
  }
  int getHP() { return HP; }
  void roundHPrecover() { //to recover player HP
    if (HP <= (max_HP - 10)) {
      HP = (HP + 10);
    } else if (HP == max_HP) {
      HP = HP + 0;
    } else {
      HP = (HP + 10) - (HP + 10) % max_HP;
    }
  }
  int getMax_HP() { return max_HP; }
};
#endif