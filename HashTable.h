#pragma once
#include "data_src/Game.h"
#include <list>
#include <vector>
#include <cctype>
#include <cmath>
using std::list;
using std::string;
using std::vector;
#define MAX_INT = 2147483647;
using namespace bridges;

struct HashTable{
    //Variables
    vector<list<Game>> table;
    int itemsContained;

    //Constructors/Destructor//
    HashTable();
    HashTable(const HashTable& rhs);
    HashTable(vector<Game>& rhs);

    //Operator Overloads//
    Game operator[](const string name);

    //General Functions//
    void Clear();
    void Resize();
    int Hash(string name);
    void Insert(Game& game);
    Game Find(string name);
};

    //Constructors/Destructor//
    HashTable::HashTable(){
        table.resize(100);
        itemsContained = 0;
    }
    HashTable::HashTable(const HashTable& rhs){
        table = rhs.table;
    }

    HashTable::HashTable(vector<Game>& rhs){
        itemsContained = 0;
        table.resize(100);
        for(auto it = rhs.begin(); it != rhs.end(); it++){
            Insert(*it);
        }
    }

    //Operator Overloads//
    Game HashTable::operator[](const string name){
        Game result = Find(name);
        return result;
    }


    //Basic Functions//
    void HashTable::Clear(){
        table.clear();
        table.resize(100);
        itemsContained = 0;
    }

    void HashTable::Resize(){
        vector<list<Game>> tempTable = table;
        Clear();
        table.resize(tempTable.size() * 2);
        for(int i = 0; i < tempTable.size(); i++){
            for(auto it = tempTable[i].begin(); it != tempTable[i].end(); it++){
                Insert(*it);
            }
        }
    }

    int HashTable::Hash(string name){
        int prime = 7;
        long long sum = 0;
        for(int i = 0; i < name.size(); i++){
            int k = i % 8;
            sum += name[i] * pow(prime, k);
        }
        int hash = sum % table.size();
        return hash;
    }

    void HashTable::Insert(Game& game){
        if(((float)itemsContained/(float)table.size()) >= 0.8){
            Resize();
        }
        int hashValue = Hash(game.getTitle());
        table[hashValue].push_front(game);
        itemsContained++;
    }

    Game HashTable::Find(string name){
        vector<string> noGenre;
        Game found("Game Not Found", "0", 0.0, noGenre);
        int hashValue = Hash(name);
        if(!table[hashValue].empty()){
            for(auto it = table[hashValue].begin(); it != table[hashValue].end(); it++){
                if(it->getTitle() == name){
                    found = *it;
                    break;
                }
            }   
        }
        return found;
    }