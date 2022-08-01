
#pragma once
#include <vector>
#include "data_src/Game.h"
#include <string>
#include <iostream>
#include <cmath>
using namespace std;


class MaxHeap {
    private:
    int size = 0;
    //MaxHeap as vector representation
    
    vector <Game> heapMax;

    public:
int getSize() {
  return size;
}
    void insertGame(Game next) {
        
        //Creates new game object to be inserted into the maxheap
        
        heapMax.push_back(next);
      size++;

        int pos = (heapMax.size()-1);
        int parent = floor(((pos - 1)/2));

        //While the parent of the inserted node is less than the inserted node swap them

        while (pos != 0 && (heapMax.at(parent).getRating() < heapMax.at(pos).getRating())) {
                Game temp = heapMax.at(pos);
                heapMax.at(pos) = heapMax.at(parent);
                heapMax.at(parent) = temp;
                pos = parent;
                parent = floor(((pos - 1)/2));
        }

    }
    Game removeTop() {
      size--;
        Game top = heapMax.at(0);
        heapMax.at(0) = heapMax.at(heapMax.size()-1);
        heapMax.pop_back();

        //Intializes variable to keep track of the right child, left child, and the postion of the node that is being put into the correct place

        int pos = 0;
        int lc = (pos*2) + 1;
        int rc = (pos*2) + 2;

        //Keeps track of the max child if it is greater than that of the node being put into the correct place

        int maxi = pos;

        while (true) {
            if ((lc < heapMax.size()) && (heapMax.at(lc).getRating() > heapMax.at(maxi).getRating())) {
                maxi = lc;
            }
            if ((rc < heapMax.size()) && (heapMax.at(rc).getRating() > heapMax.at(maxi).getRating())) {
                maxi = rc;
            }
            if (maxi != pos) {
                // Game temp = heapMax.at(pos);
                // heapMax.at(pos) = heapMax.at(maxi);
                // heapMax.at(maxi) = heapMax.at(pos);
                swap(heapMax[maxi], heapMax[pos]);
                //cout << "pos :" << pos << " " << "maxi1: " << maxi << endl;
                pos = maxi;

                lc = (pos*2) + 1;
                rc = (pos*2) + 2;
                //cout << "pos :" << pos << " " << "maxi2: " << maxi << endl;
            }
            else {
                break;
            }
        }
        return top;

    }

};