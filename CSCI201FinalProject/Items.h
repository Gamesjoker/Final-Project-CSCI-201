#ifndef Items
#define Items
#include <iostream>
#include <random>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>
using namespace std;
//use of polymorphism and inheritance to create equipments
class items {
private:
  int benefit;
  string name;

public:
  string getname() { return name; }
  void setname(string N) { name = N; }

  int getbenefit() { return benefit; }
  void setbenefit(int b) { benefit = b; }
};

class weapon : public items {
private:
  string weapNames[5] = {"Shortsword", "Handaxe", "Javelin", "Scimitar",
                         "Rapier"};

public:
  weapon() {
    srand(time(NULL));
    int i = rand() % 5;
    setname(weapNames[i]);
    int j = rand() % 6 + 5;
    setbenefit(j);
  }
};

class accessory : public items {
private:
  string details[3] = {"Gloves", "Ring of Health", "Ring of Protection"};

public:
  string getlist(int i) { return details[i]; }
  accessory(int i) {
    setname(getlist(i));
    setbenefit(5);
  }
};

class armor : public items {
private:
  string details[5] = {"Helmet", "Bracer", "Chainmail", "Trouser", "Boots"};

public:
  string getlist(int i) { return details[i]; }
  armor(int i) {
    setname(getlist(i));
    setbenefit(5);
  }
};

#endif