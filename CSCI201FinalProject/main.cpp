/*
* Authors: Khoi Nguyen, Alexander Horine
* CSCI 201
* Date last modified: 5/4/2022
* Purpose: Create an RPG game using polymorphism, vectors, class objects, exception handling, loops, and arrays, with other programming practice.
*/
#include "Boss.h"
#include "Items.h"
#include "Monster.h"
#include "Player.h"
#include <iostream>
#include <limits>
#include <random>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>
using namespace std;
//exception handling for player's choice
void checkint(int &i, int lower_end, int upper_end, int excpt) {
  while (true) {
    try {
      cout << "Your choice is:";
      cin >> i;
      if (cin.fail()) {
        throw "Invalid";
      } else if (i >= lower_end && i <= upper_end || i == excpt) {
        break;
      } else {
        throw(i);
      }
    } catch (const char *msg) {
      cin.clear();

      cout << "Error: Not a valid input." << endl;
    } catch (int i) {
      cin.clear();

      cout << "Error: input out of range. Try again!" << endl;
    }
  }
}

int main() {
//declaring all variables that will be used in the game
  string playerName;
  int i, a, d, h, turn;
  int bossHP, playerHP, playerDamage;
  int monsterHP, monsterDamage;
  int HPItemCount, dmgItemCount;
  int weapon_count = 0, item_count = 0;
  int armor_count = 0;
  int accessory_count = 0;
//creating a vector to store items
  vector<items *> Item;

  
  //Introduction to the game and its story
  cout << "Every century, the forces of good and evil collide." << endl;
  cout << endl;
  cout << "Now, the time has come once again to fight for the fate of all humankind." << endl;
  cout << endl;
  cout << "Evil forces have taken over the world and only one brave warrior will be able to stop it." << endl;
  cout << endl;
  cout << "It is up to you to persevere through the darkness and put an end to this evil reign of terror." << endl;
  cout << endl;
  cout << "Your journey begins now!" << endl;
  cout << endl;
  cout << "------------------------------" << endl;

  // setting player name to be used in game
  cout << endl;
  cout << "Enter your name" << endl;
  getline(cin >> ws, playerName);
  player Player1(playerName);

  // normal rounds
  vector<Monster> mons; // vectors for storing monster objects
  mons.reserve(10);
  srand(time(NULL));
  for (int i = 0; i < 10; i++) { // create and randomize monsters' stats
    int monHP = rand() % 20;
    int monDamage = rand() % 10;
    mons.push_back(Monster(monHP, monDamage));
  }
  // loop for first 10 rounds
  for (int i = 0; i < 10; i++) {
    if (Player1.getHP() <= 0) {//end the game if player's HP falls to 0
      cout << "You lost." << endl;
      break;
    }
    //begin of round and randomize speed to determine who goes first
    cout << endl;
    cout << "A monster has appeared. Prepare to fight!" << endl;
    cout << endl;
    cout << "HP: " << mons[i].getMonster_max_HP() << endl;
    cout << "Damage: " << mons[i].getMonsterDamage() << endl;
    cout << endl;
    int monsterSpeed = rand() % 20 + 1;
    int playerSpeed = rand() % 20 + 1;

    if (monsterSpeed > playerSpeed) {
      turn = 1;
    } else {
      turn = 0;
    }
    while (true) {
      //loop for the fighting in round
      if (turn == 1) {//monster turn
        cout << "Monster's turn: " << endl;
        cout << "The monster attacks you with " << mons[i].getMonsterDamage()
             << " damage!" << endl;
        Player1.takedamage(mons[i].getMonsterDamage());
        cout << "Your HP is " << Player1.getHP() << "." << endl;
        cout << endl;
        turn = 0;
      } else if (turn == 0) {//player turn
        int choice = 0;
        Player1.BeginofTurn();
        cout << "---" << endl;
        cout << "Your turn:" << endl;
        cout << "What would you like to do?"
             << "\n1. Use sword."
             << "\n2. Use Spell." << endl;
        checkint(choice, 1, 2, 1);
        cout << endl;
        if (choice == 1) {//physical attack
          cout << "You attack the monster with your sword. Deal "
               << Player1.physatk() << " physical damage to monster." << endl;
          mons[i].takeDamage(Player1.physatk());
          cout << "Monster HP is " << mons[i].getMonsterHP() << "." << endl;
          cout << endl;
        } else {//magical attack
          cout << "Choose a spell to cast:"
               << "\n1. Heal."
               << "\n2. Fire ball."
               << "\n3. Sun Ray."
               << "\n4. Ice Pick"
               << "\n5. Electric Strike." << endl;
          int choice;
          checkint(choice, 1, 5, 1);
          while (true) {//check to see if spell is usable
            if (Player1.UseSpell(choice) != "Spell is on cooldown.") {
              if (choice == 1) {
                cout << Player1.UseSpell(choice);
                Player1.HealSpell();
                break;
              } else {
                cout << Player1.UseSpell(choice) << endl;
                cout << "Monster takes " << Player1.MagicDamage(choice)
                     << " magic damage!" << endl;
                mons[i].takeDamage(Player1.MagicDamage(choice));
                cout << "Monster HP is " << mons[i].getMonsterHP() << "."
                     << endl;
                cout << endl;
                break;
              }
            } else {
              cout << Player1.UseSpell(choice) << endl;
              cout << "Please choose another spell or 0 for physical attack!" << endl;
              checkint(choice, 1, 5, 0);
              if (choice == 0) {
                cout << "You attack the monster with your sword. Deal "
                     << Player1.physatk() << " physical damage to monster."
                     << endl;
                mons[i].takeDamage(Player1.physatk());
                cout << "Monster HP is " << mons[i].getMonsterHP() << "."
                     << endl;
                break;
              } else {
                continue;
              }
            }
          }
        }
        turn = 1;
      }
      if (mons[i].getMonsterHP() <= 0) {//monster defeated and tally new equipments if conditions are met
        cout << endl;
        cout << "Congratulations! You defeated the monster!"
             << "\nRewards (if any) has been added."
             << "\nHP has been recovered by 10." << endl;
        if (mons[i].getMonster_max_HP() == 20 && armor_count < 5) {
          Item.push_back(new armor(armor_count));
          cout << endl;
          cout << "You received a " << Item[item_count]->getname() << "."
               << endl;
          cout << "Modify your HP by " << Item[item_count]->getbenefit()
               << " HP." << endl;
          Player1.increase_max_HP(Item[item_count]->getbenefit());
          armor_count += 1;
          item_count +=1;
        }
        if (mons[i].getMonsterDamage() == 10 && weapon_count < 1) {
          Item.push_back(new weapon());
          cout << endl;
          cout << "You received a " << Item[item_count]->getname() << "."
               << endl;
          cout << "Modify your physical damage by "
               << Item[item_count]->getbenefit() << "." << endl;
          Player1.increase_phys_damage(Item[item_count]->getbenefit());
          weapon_count += 1;
          item_count += 1;
        }
        if (mons[i].getMonsterDamage() >= 5 &&
            mons[i].getMonsterDamage() < 10 && accessory_count < 3) {
          Item.push_back(new accessory(accessory_count));
          cout << endl;
          cout << "You received a " << Item[item_count]->getname() << "."
               << endl;
          cout << "Modify your spell damage by "
               << Item[item_count]->getbenefit() << "." << endl;
          Player1.increase_spell_damage(Item[item_count]->getbenefit());
          accessory_count += 1;
          item_count += 1;
        }

        Player1.roundHPrecover();//recover fixed HP for player
        cout << "---------------------------------" << endl;
        break;
      }
    }
  }

  //Continuation of the game's story
  cout << endl;
  cout << "The evil army of monsters have been defeated, but one final challenge remains." << endl;
  cout << endl;
  cout << "An evil master of many names is determined to end your quest and continue this reign of terror." << endl;
  cout << endl;
  cout << "Get ready. The final battle begins now!" << endl;
  cout << endl;
  cout << "-------------------------------" << endl;
  
  
  // boss round
  boss Boss1(item_count, weapon_count);//Creating Boss object based on amount of equipments
  cout << endl;
  cout << "The Boss " << Boss1.get_boss_name()
       << " has appeared. Prepare to fight!" << endl;
  cout << endl;
  cout << "HP: " << Boss1.get_HP() << endl;
  cout << endl;
  int BossSpeed = rand() % 20 + 1;//randomize turn for player and Boss to see who goes first
  int PlayerSpeed = rand() % 20 + 1;

  if (BossSpeed > PlayerSpeed) {
    turn = 1;
  } else {
    turn = 0;
  }
  do {//loop of the battle
    if (turn == 1) {//Boss turn
      cout << "It is the boss turn!" << endl;
      cout << endl;
      cout << "The boss is attacking..." << endl;
      cout << endl;
      Boss1.BeginofTurn();
      srand(time(NULL));
      int atktype = rand() % 2;//randomize boss's behavior
      if (atktype == 0) {//physical attack
        cout << "Boss attacks you with his battle axe!" << endl;
        playerDamage = Boss1.UsePhysical();
        Player1.takedamage(playerDamage);
        turn = 0;
        cout << "Player takes " << playerDamage << " physical damage!" << endl;
        cout << "Player HP: " << Player1.getHP() << endl;
        cout << endl;
      } else {//magical attack
        bool Casted = false;
        while (Casted == false) {
          int i = rand() % 5;
          if (Boss1.UseSpell(i) != "On cooldown") {
            Casted = true;
            cout << "The boss uses " << Boss1.UseSpell(i) << "!" << endl;
            ;
            playerDamage = Boss1.SpellDamage(i);
            Player1.takedamage(playerDamage);
            cout << "Player takes " << playerDamage << " magical damage!"
                 << endl;
            cout << "Player HP: " << Player1.getHP() << endl;
            cout << endl;
          }
        }
        turn = 0;
      }
    } else {//Player turn
      int choice = 0;
      Player1.BeginofTurn();
      cout << "---" << endl;
      cout << "Your turn:" << endl;
      cout << "What would you like to do?"
           << "\n1. Use sword."
           << "\n2. Use Spell." << endl;
      checkint(choice, 1, 2, 1);
      if (choice == 1) {//physical attack
        cout << endl;
        cout << "You attack the Boss with your sword. Deal "
             << Player1.physatk() << " physical damage to Boss." << endl;
        Boss1.takeDamage(Player1.physatk());
        cout << "Boss HP is " << Boss1.get_HP() << "." << endl;
        cout << endl;
      } else {//magical attack
        cout << endl;
        cout << "Choose a spell to cast:"
             << "\n1. Heal."
             << "\n2. Fire ball."
             << "\n3. Sun Ray."
             << "\n4. Ice Pick"
             << "\n5. Electric Strike." << endl;
        int choice;
        checkint(choice, 1, 5, 1);
        while (true) {//spell casting loop
          if (Player1.UseSpell(choice) != "Spell is on cooldown.") {
            if (choice == 1) {//Success on healing spell
              cout << Player1.UseSpell(choice);
              Player1.HealSpell();
              break;
            } else {//success on attack spell
              cout << Player1.UseSpell(choice) << endl;
              cout << "Boss takes " << Player1.MagicDamage(choice)
                   << " magic damage!" << endl;
              Boss1.takeDamage(Player1.MagicDamage(choice));
              cout << "Boss HP is " << Boss1.get_HP() << "." << endl;
              cout << endl;
              break;
            }
          } else {//spell on cooldown
            cout << Player1.UseSpell(choice);
            cout << "\nPlease choose another spell or 0 for physical attack!"<<endl;
            checkint(choice, 1, 5, 0);
            if (choice == 0) {
              cout << "You attack the Boss with your sword. Deal "
                   << Player1.physatk() << " physical damage to Boss."
                   << endl;
              Boss1.takeDamage(Player1.physatk());
              cout << "Boss HP is " << Boss1.get_HP() << "." << endl;
              cout << endl;
              break;
            } else {
              continue;
            }
          }
        }
      }
      turn = 1;
    }
  }
    while (Player1.getHP()>0 && Boss1.get_HP()>0);//loop until player or boss die
  if (Player1.getHP() <= 0){//player lost
    cout << endl;
    cout << "You lost!"<<endl;
    cout << "The reign of terror continues." << endl;
    cout << "Game Over" << endl;
  }
  else if (Boss1.get_HP()<=0){//Boss lost
    cout << endl;
    cout << "Congratulations!" << endl;
    cout << endl;
    cout << "The evil forces of " << Boss1.get_boss_name()<<" have been defeated!" << endl;
    cout << endl;
    cout << "The reign of terror is over." << endl;
    cout << endl;
    cout << "And you, " << playerName << ", will always be remembered for your perseverance and bravery." << endl;
  }
  return 0;
}