// Last Changed on PC

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
    private:

        map<string,int> stats = {
            {"Combat", 1},
            {"Endurance", 1},
            {"Spirit", 1},
            {"Potential", 1}
        };

        string name;
        int level = 1;
        double experience = 0;
        int stat_point = 0;
        
        map<string,bool> concepts = {
            {"Aura Manipulation"    ,   false},
            {"Sense"                ,   false},
            {"Step"                 ,   false},
            {"Release"              ,   false},
            {"Medicine"             ,   false},
            {"Counter"              ,   false}
        };

        vector<vector<Technique>> techniques;

        // Resource Variables
        int healthPoints = 0;
        int maxHealthPoints = 0;
        int staminaPoints = 0;
        int maxStaminaPoints = 0;
        int spiritPoints = 0;
        int maxSpiritPoints = 0;

        // Attack Damage (Base)
        int attackDamage = stats.at("Combat")*4;
        // Ability Power (Base)
        int abilityPower = stats.at("Spirit")*5;

    public:
        Entity(string n, int l){
            name = n;
            level = l;

            maxHealthPoints = level*15;
            healthPoints = maxHealthPoints;

            maxStaminaPoints = level*4;
            staminaPoints = maxStaminaPoints;

            maxSpiritPoints = level*3;
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

        void maxResources(){
            healthPoints = maxHealthPoints;
            staminaPoints = maxStaminaPoints;
            spiritPoints = maxSpiritPoints;
        }

        string getName(){
            return name;
        }

        int getLevel(){
            return level;
        }

        double getExperience(){
            return experience;
        }

        bool getConcept(string index){
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

        vector<Technique> getTechniques(int type){
            return techniques[type];
        }

        Technique getTechnique(int type, int index){
            return techniques[type][index];
        }

        int getStat(string index){
            return stats.at(index);
        }

        int getHp(){
            return healthPoints;
        }

        int getAttackDamage(){
            return attackDamage;
        }

        int getAbilityPower(){
            return abilityPower;
        }

        int getMaxHp(){
            return maxHealthPoints;
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

};

// Functions Purely for test / console !!
void printCharacterSheet(Entity e){
    cout << "Name: " << e.getName() << ", Lv. " << e.getLevel() << endl;
    cout << "HP: " << e.getHp() << " / " << e.getMaxHp() << ", Stamina: " << e.getStamina() << " / " << e.getMaxStamina() << endl;
    cout << "Spirit: " << e.getSpirit() << " / " << e.getMaxSpirit() << ", Stat Point(s): " << e.getStatPoints() << endl;
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
    string concepts[] = {"Aura Manipulation", "Sense", "Step", "Release", "Medicine", "Counter"};
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

int main(){
    system("cls");

    // Martial Techniques
    Technique jab = Technique("Jab", 0, 7, "A quick strike.");
    Technique manjiKick = Technique("Manji Kick", 0, 14, "A kick from the ground.");

    // Spirit Techniques
    Technique spiritGun = Technique("Spirit Gun", 1, 15, "A small blast of spirit energy.");
    Technique waltz = Technique("Waltz", 1, 0, "Successive 'Steps', high speed movement.");
    Technique piercingSoul = Technique("Piercing Soul", 1, 25, "A piercing shot of spirit energy.");
    
    // Unique Techniques
    Technique rejection = Technique("Rejection", 2, 7, "Reject any and all phenomena.");
    Technique femboy = Technique("Femboy Mode", 2, 9999, "Activate Femboy Mode");

    Entity riley = Entity("Riley", 1);

    riley.addExperience(109000); // Added XP instead of initializing at lvl 69
    riley.increaseStats(50, 10, 144); // Added stats to make u a glass cannon

    riley.learnTechnique(waltz);
    riley.learnTechnique(manjiKick);
    riley.learnTechnique(rejection);
    riley.learnTechnique(piercingSoul);
    riley.learnTechnique(spiritGun);
    riley.learnTechnique(jab);
    riley.learnTechnique(femboy);
    printCharacterSheet(riley);

    return 0;
}