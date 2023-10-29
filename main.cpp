// Last Changed on PC
#include <iostream>
#include <map>
#include <vector>
#include "entity.hpp"
using namespace std;


int main(int argv, char** args){ 
    Entity NPC = Entity("Civilian", 1, 0);
    printEntity(NPC);

    return 0;
}