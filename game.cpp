// Last Changed on Mac
#include <SDL2/SDL.h>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class Technique{
    private:
        string name;
        int type = -1;
        int base_stat = 0;
        string description;
        vector<string> types = {"Martial", "Spiritual", "Unique"};

    public:
        Technique(string n, int t, int b, string d){
            type = t;
            base_stat = b;
            description = d;
            name = n;
        }

        string getName(){
            return name;
        }

        int getType(){
            return type;
        }

        vector<string> getTypes(){
            return types;
            
        }
};

class Entity{
    public:
        string name;
        int level = 1;

        int healthPoints = 0;
        int maxHealthPoints = 0;

        int baseDamage = 0;

        string affinity;
        vector<string> affinities = {"None", "Air", "Fire", "Ice", "Electricity", "Combustion", "Pyschokinesis", "Poison", "Gravity", "Plant"};

        Entity(string n, int l, int a){
            name = n;
            level = l;
            affinity = affinities[a];

            baseDamage = level*2;
            maxHealthPoints = level*30;
            healthPoints = maxHealthPoints;
        }

        void maxResources(){
            healthPoints = maxHealthPoints;
        }

        string getName(){
            return name;
        }

        int getLevel(){
            return level;
        }

        int getHp(){
            return healthPoints;
        }

        int getMaxHp(){
            return maxHealthPoints;
        }

        int getDamage(){
            return baseDamage;
        }

        string getAffinity(){
            return affinity;
        }

        void takeDamage(int dmg){
            healthPoints = healthPoints - dmg;
        }
};

class Player: public Entity{
    private:
        map<string,int> stats = {
            {"Combat", 1},
            {"Endurance", 1},
            {"Spirit", 1},
            {"Potential", 1}
        };
        
        double experience = 0;
        int stat_point = 0;
        
        map<string, int> concepts = {
            {"Aura Manipulation"    ,   0},
            {"Sense"                ,   0},
            {"Step"                 ,   0},
            {"Release"              ,   0},
            {"Emission"             ,   0},
            {"Medicine"             ,   0},
            {"Counter"              ,   0}
        };

        vector<vector<Technique>> techniques;

        // Resource Variables
        
        int staminaPoints = 0;
        int maxStaminaPoints = 0;
        int spiritPoints = 0;
        int maxSpiritPoints = 0;

        // Attack Damage (Base)
        int attackDamage = stats.at("Combat")*4;
        // Ability Power (Base)
        int abilityPower = stats.at("Spirit")*5;

    public:
        Player(string n, int l)
        : Entity(n, l, 0)
        {
            maxHealthPoints = level*15;
            healthPoints = maxHealthPoints;

            maxStaminaPoints = getLevel()*4;
            staminaPoints = maxStaminaPoints;

            maxSpiritPoints = getLevel()*3;
            spiritPoints = maxSpiritPoints;

            techniques.resize(100);
        }

        void levelUp(){
            int potential = stats.at("Potential");
            while(experience >= (level*level+10)){
                experience = experience - (level*level+10);
                level += 1;
                switch(potential){
                    case 1:
                        stat_point += 3;
                        break;
                    case 2:
                        stat_point += 4;
                        break;
                    case 3:
                        stat_point += 5;
                        break;  
                }

                maxHealthPoints += 15;
                maxStaminaPoints += 4;
                maxSpiritPoints += 3;
            
            }
            healthPoints = maxHealthPoints;
            staminaPoints = maxStaminaPoints;
            spiritPoints = maxSpiritPoints;
        }

        void addExperience(double increment){
            experience += increment;
            if(experience >= level*level + 10){
                levelUp();
            }
        }

        void increaseStats(int c, int e, int s){
            int total = c+e+s;
            if(total <= stat_point){
                stats.at("Combat") += c;
                stats.at("Endurance") += e;
                stats.at("Spirit") += s;

                maxHealthPoints += e*15;
                maxStaminaPoints += e*4;
                maxSpiritPoints += s*3;    

                attackDamage += c*4;
                abilityPower += s*5;
            }
            stat_point -= total;
        }

        double getExperience(){
            return experience;
        }

        int getConcept(string index){
            return concepts.at(index);
        }

        double getExperienceNeeded(){
            return level*level+10;
        }

        void learnTechnique(Technique t){
            switch(t.getType()){
                case 0:
                    techniques[0].push_back(t);
                    break;
                case 1:
                    techniques[1].push_back(t);
                    break;
                case 2:
                    techniques[2].push_back(t);
                    break;
            }
        }

        void maxResources(){
            healthPoints = maxHealthPoints;
            staminaPoints = maxStaminaPoints;
            spiritPoints = maxSpiritPoints;
        }

        vector<Technique> getTechniques(int type){
            return techniques[type];
        }

        Technique getTechnique(int type, int index){
            return techniques[type][index];
        }

        int getStat(string index){
            return stats.at(index);
        }

        int getAttackDamage(){
            return attackDamage;
        }

        int getAbilityPower(){
            return abilityPower;
        }

        int getStamina(){
            return staminaPoints;
        }

        int getMaxStamina(){
            return maxStaminaPoints;
        }

        int getSpirit(){
            return spiritPoints;
        }

        int getMaxSpirit(){
            return maxSpiritPoints;
        }

        int getStatPoints(){
            return stat_point;
        }

        void raisePotential(){
            if(stats.at("Potential") == 1 || stats.at("Potential") == 2){
                stats.at("Potential") += 1;
            }
        }

        void raiseConcept(string concept){
            concepts.at(concept) += 1;
        }
};


// Functions Purely for test / console !!
void printCharacterSheet(Player e){
    cout << "Name: " << e.getName() << ", Lv. " << e.getLevel() << endl;
    cout << "HP: " << e.getHp() << " / " << e.getMaxHp() << ", Stamina: " << e.getStamina() << " / " << e.getMaxStamina() << endl;
    cout << "Spirit: " << e.getSpirit() << " / " << e.getMaxSpirit() << ", Stat Point(s): " << e.getStatPoints() << endl;
    cout << "Affinity: " << e.getAffinity() << endl;
    cout << "Experience: " << e.getExperience() << " / " << e.getExperienceNeeded() << endl;
    cout << "Stats:" << endl;
    cout << "\tCombat: " << e.getStat("Combat") << endl;
    cout << "\t\tBase Attack Damage: " << e.getAttackDamage() << endl;
    cout << "\tEndurance: " << e.getStat("Endurance") << endl;
    cout << "\tSpirit: " << e.getStat("Spirit") << endl;
    cout << "\t\tBase Ability Power: " << e.getAbilityPower() << endl;
    cout << "\tPotential: " << e.getStat("Potential") << endl;
    switch(e.getStat("Potential")){
        case 1:
            cout << "\t\t" << "3 Stat Points per level" << endl;
            break;
        case 2:
            cout << "\t\t" << "4 Stat Points per level" << endl;
            break;
        case 3:
            cout << "\t\t" << "5 Stat Points per level" << endl;
            break;  
    }
    cout << "Concepts:" << endl;
    string concepts[] = {"Aura Manipulation", "Sense", "Step", "Release", "Emission", "Medicine", "Counter"};
    for(string s : concepts){
        cout << "\t" << s << ": " << e.getConcept(s) << endl;
    }

    cout << "Techniques:" << endl;
    
    string types[] = {"Martial", "Spirit", "Unique"};
    for(int i = 0; i < 3; i++){
        cout << "\t" << types[i] << ":" << endl;
        for(int j = 0; j < e.getTechniques(i).size(); j++){
            cout << "\t\t" << j+1 << ") " << e.getTechnique(i,j).getName() << endl;
        }
    }
}

void printEntity(Entity e){
    cout << "Name: " << e.getName() << ", Lv. " << e.getLevel() << endl;
    cout << "HP: " << e.getHp() << " / " << e.getMaxHp() << endl;
    cout << "Damage: " << e.getDamage() << endl;
    cout << "Affinity: " << e.getAffinity() << endl;
}

void runSDL(){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Cursed - Version 0.0.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
    
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);

    SDL_Delay(10000);
}

int main(int argv, char** args){ 
    runSDL();

    return 0;
}