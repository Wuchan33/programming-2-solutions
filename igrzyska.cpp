// Mikołaj Suchan

#include <iostream>
#include <string>

using namespace std;

class PLAYER_CLASS {
    private:
        virtual void die() {
            curr_health = 0;
        }
    protected:
        PLAYER_CLASS* prev;
        PLAYER_CLASS* next;
        unsigned int max_health;
        unsigned int curr_health;
        unsigned int agility;
        unsigned int strength;
    public:
        virtual string get_name() {
            return "";
        }

        virtual unsigned int getDefense() {
            return 0;
        }

        virtual bool alive() {
            return getRemainingHealth() > 0;
        }

        virtual unsigned int getRemainingHealth() {
            return ((curr_health * 100) / max_health);
        }

        virtual unsigned int getDamage() {
            return strength;
        }

        virtual unsigned int getAgility() {
            return agility; 
        }

        virtual void takeDamage( unsigned int val ){
            if (curr_health > val) {
                curr_health -= val;
            } else {
                curr_health = 0;
                die();
            }
        }
        
        virtual void applyWinnerReward() {
            agility += 2;
            strength += 2;
        }

        virtual void cure() {
            curr_health = max_health;
        }

        virtual void printParams() = 0;

        friend class CAESAR_CLASS;
        friend class SQUAD_CLASS;
};

class CAESAR_CLASS {
    public:
        unsigned int judgment_cnt;
        unsigned int attack_cnt;

        void judgeDeathOrLife( PLAYER_CLASS* player ) {
            judgment_cnt++;
            if (attack_cnt % 2 == 0) {
                if (judgment_cnt % 3 == 0) {
                    player->die();
                }
        }
    }
};

class ARENA_CLASS {
    private:
        CAESAR_CLASS* ceasar;
    public:
        ARENA_CLASS (CAESAR_CLASS* ptr) {
            ceasar = ptr;
            ceasar->judgment_cnt = 0;
            ceasar->attack_cnt = 0;
        }

        void fight(PLAYER_CLASS* first, PLAYER_CLASS* second) {
            if (first->alive() == false || second->alive() == false)
                return;
            PLAYER_CLASS* temp;
            if (first->getAgility() < second->getAgility()) {
                temp = first;
                first = second;
                second = temp;
            }

            first->printParams();
            second->printParams();

            unsigned int attack_cnt = 0;
            while(attack_cnt < 40 && first->getRemainingHealth() >= 10 && second->getRemainingHealth() >= 10) {
                second->takeDamage(first->getDamage());
                attack_cnt++;
                second->printParams();
                if (second->getRemainingHealth() < 10 || attack_cnt == 40)
                    break;
                first->takeDamage(second->getDamage());
                attack_cnt++;
                first->printParams();
            }

            ceasar->attack_cnt = attack_cnt;

            if (first->alive()) {
                ceasar->judgeDeathOrLife(first);
                first->printParams();
            }
            
            if (second->alive()) {
                ceasar->judgeDeathOrLife(second);
                second->printParams();
            }

            if (first->alive()) {
                first->applyWinnerReward();
                first->cure();
            }

            if (second->alive()) {
                second->applyWinnerReward();
                second->cure();
            }

            first->printParams();
            second->printParams();
        }
};

class HUMAN_CLASS : virtual public PLAYER_CLASS {
    private:
        void die() {
            curr_health = 0;
        }
    protected:
        unsigned int defense;
        string human_id;
    public:
        HUMAN_CLASS( string id ) {
            prev = NULL;
            next = NULL;
            curr_health = 200;
            max_health = 200;
            strength = 30;
            agility = 10;
            defense = 10;
            human_id = id;
        }

        unsigned int getDamage() {
            return strength;
        }

        unsigned int getDefense() {
            return defense;
        }

        void takeDamage( unsigned int val) {
            if (val < defense + agility)
                val = 0;
            else
                val -= defense + agility;
            if (curr_health > val) {
                curr_health -= val;
            } else {
                curr_health = 0;
                die();
            }

        }
        
        string get_name() {
            return human_id;
        }

        void printParams() {
            if (alive()) {
                cout << human_id << ":" << max_health << ":" << curr_health << ":" << this->getRemainingHealth() << "%:" << this->getDamage() << ":" <<
                 this->getAgility() << ":" << defense << endl;
            } else {
                cout << human_id << ":R.I.P." << endl;
            }
        }
};

class BEAST_CLASS : virtual public PLAYER_CLASS {
    private:
        void die() {
            curr_health = 0;
        }
    protected:
        string beast_id;
    public:
        BEAST_CLASS( string id ) {
            prev = NULL;
            next = NULL;
            max_health = 150;
            curr_health = 150;
            strength = 40;
            agility = 20;
            beast_id = id;
        }
        
        unsigned int getDamage() {
            if (getRemainingHealth() < 25) {
                return strength * 2;
            } else {
                return strength;
            }
        }

        void takeDamage( unsigned int val ) {
            if (val < agility / 2)
                val = 0;
            else
                val -= agility / 2;
            if (curr_health > val) {
                curr_health -= val;
            } else {
                curr_health = 0;
                die();
            }        
        }
        
        string get_name() {
            return beast_id;
        }

        void printParams() {
            if (alive()) {
                cout << beast_id << ":" << max_health << ":" << curr_health << ":" << this->getRemainingHealth() << "%:" << this->getDamage() << ":" <<
                 this->getAgility() << endl;
            } else {
                cout << beast_id << ":R.I.P." << endl;
            }
        }
};

class BERSERKER_CLASS : public BEAST_CLASS, public HUMAN_CLASS {
    private:
        bool isBeast;
        void die() {
            isBeast = false;
            curr_health = 0;
        }
    public:
        BERSERKER_CLASS( string humanId, string beastId ) : HUMAN_CLASS(humanId), BEAST_CLASS(beastId) {
            prev = NULL;
            next = NULL;
            max_health = 200;
            curr_health = 200;
            strength = 35;
            agility = 5;
            defense = 15;
            isBeast = false;
        }

        unsigned int getDamage() {
            if (isBeast) {
                return BEAST_CLASS::getDamage();
            } else {
                return HUMAN_CLASS::getDamage();
            }
        }

        unsigned int getDefenes() {
            if (isBeast) {
                return BEAST_CLASS::getDefense();
            } else {
                return HUMAN_CLASS::getDefense();
            }
        }

        void takeDamage( unsigned int val ) {
            if (isBeast) {
                BEAST_CLASS::takeDamage(val);
            } else {
                HUMAN_CLASS::takeDamage(val);
                if (getRemainingHealth() < 25) {
                    isBeast = true;
                }
            }
            if (curr_health == 0) {
                die();
            }
        }

        unsigned int getAgility() {
            if (isBeast) {
                return BEAST_CLASS::getAgility();
            } else {
                return HUMAN_CLASS::getAgility();
            }
        }
        
        void cure() {
            curr_health = max_health;
            isBeast = false;
        }

        void printParams() {
            if (isBeast) {
                BEAST_CLASS::printParams();
            } else {
                HUMAN_CLASS::printParams();
            }
        }

        string get_name() {
            if (isBeast) {
                return BEAST_CLASS::get_name();
            } else {
                return HUMAN_CLASS::get_name();
            }
        }
};

class SQUAD_CLASS : virtual public PLAYER_CLASS {
    private:
        string squad_id;
        unsigned int members_cnt;
        PLAYER_CLASS* head;
        void die() {
            PLAYER_CLASS* temp;
            while (head) {
                temp = head;
                head = head->next;
                temp->die();
            }
            members_cnt = 0;
            strength = 0;
            curr_health = 0;
            max_health = 1;
            agility = -1;
        }
    public:
        SQUAD_CLASS( string id ){
            squad_id = id;
            members_cnt = 0;
            head = NULL;
            prev = NULL;
            next = NULL;
            agility = -1;
            strength = 0;
            max_health = 1;
            curr_health = 0;
        }
        
        unsigned int getDamage() {
            deleteDead();
            updateValues();
            return strength;
        }

        void takeDamage( unsigned int val ) {
            deleteDead();
            updateValues();

            if (!members_cnt)
                return;
            val /= members_cnt;
            PLAYER_CLASS* temp = head;
            while (temp) {
                temp->takeDamage(val);
                temp = temp->next;
            }

            deleteDead();
            updateValues();
        }
        
        void addPlayer( PLAYER_CLASS* new_player) {
            new_player->prev = NULL;
            new_player->next = NULL;
            PLAYER_CLASS* temp = head;
            new_player->next = temp;
            if (temp)
                temp->prev = new_player;
            head = new_player;
            deleteDead();
            updateValues();
        }

        unsigned int getAgility() {
            deleteDead();
            updateValues();
            return agility;
        }

        void printParams() {
            deleteDead();
            updateValues();
            if (members_cnt) {
                cout << squad_id << ":" << members_cnt << ":" << getRemainingHealth() << "%:" << getDamage() << ":" << getAgility() << endl;
                sortList();
                PLAYER_CLASS* temp = head;
                while (temp) {
                    temp->printParams();
                    temp = temp->next;
                }
            } else {
                cout << squad_id << ":nemo" << endl;
            }
        }

        bool compare(PLAYER_CLASS* A, PLAYER_CLASS* B) {
            if (A->get_name() != B->get_name())
                return A->get_name() > B->get_name();
            if (A->max_health != B->max_health)
                return A->max_health > B->max_health;
            if (A->curr_health != B->curr_health)
                return A->curr_health > B->curr_health;
            if (A->getDamage() != B->getDamage())
                return A->getDamage() > B->getDamage();
            if (A->getAgility() != B->getAgility())
                return A->getAgility() > B->getAgility();
            return false;
        }

        void sortList() {
            if (members_cnt <= 1)
                return;

            bool check;
            PLAYER_CLASS* curr;
            PLAYER_CLASS* last = NULL;

            do {
                check = false;
                curr = head;

                while (curr->next != last) {
                    if (compare(curr, curr->next)) {
                    PLAYER_CLASS* nxt = curr->next;
                    
                    if (curr->prev)
                        curr->prev->next = nxt;
                    else
                        head = nxt;

                    if (nxt->next)
                        nxt->next->prev = curr;

                    curr->next = nxt->next;
                    nxt->prev = curr->prev;
                    curr->prev = nxt;
                    nxt->next = curr;

                    check = true;
                    } else {
                        curr = curr->next;
                    }
                }
                last = curr;
            } while (check);
        }
        
        PLAYER_CLASS* getHead() {
            return head;
        }

        void deleteDead() {
            PLAYER_CLASS* temp = head;
            while (temp) {
                if (temp->alive() == false) {
                    PLAYER_CLASS* toDelete = temp;
                    temp = temp->next;
            
                    if (toDelete->prev) {
                        toDelete->prev->next = toDelete->next;
                    } else {
                        head = toDelete->next;
                    }
            
                    if (toDelete->next) {
                        toDelete->next->prev = toDelete->prev;
                    }
                    
                } else {
                    temp = temp->next;
                }
            }
        }

        void updateValues() {
            PLAYER_CLASS* temp = head;
            members_cnt = 0;
            agility = -1;
            curr_health = 0;
            max_health = 1;
            strength = 0;
            while (temp) {
                strength += temp->getDamage();
                members_cnt++;
                if (temp->getAgility() < agility)
                    agility = temp->getAgility();
                if ((temp->curr_health * 100) / temp->max_health > ((curr_health * 100) / max_health)) {
                    curr_health = temp->curr_health;
                    max_health = temp->max_health;
                }
                temp = temp->next;
            }
        }

        void cure() {
            deleteDead();
            PLAYER_CLASS* curr = head;
            while(curr) {
                curr->cure();
                curr = curr->next;
            }
            updateValues();
        }

        void applyWinnerReward(){
            deleteDead();
            PLAYER_CLASS* curr = head;
            while(curr) {
                curr->applyWinnerReward();
                curr = curr->next;
            }
            updateValues();
        }

        string get_name() {
            return squad_id;
        }
};
