#include "../Headers/PriorityQueue.h"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

PriorityQueue::PriorityQueue() {
    size = 0;
    root = NULL;
    id = 1;
    cr = cl = cp = "  ";
    cr[0] = 218; cr[1] = 196;
    cl[0] = 192; cl[1] = 196;
    cp[0] = 179;
}

PriorityQueue::~PriorityQueue() {
    for(int i=0; i<size; i++)
        delete root[i];
    delete [] root;
}

void PriorityQueue::add(Solution* solution) {
    Solution** tree;

    tree = new Solution* [size + 1];

    for(int i=0; i<size; i++) {
        tree[i] = new Solution();
        memcpy(tree[i], root[i], sizeof(Solution));

        delete root[i];
    }

    tree[size] = solution;

    delete [] root;
    root = tree;
    size++;
    orderAfterAdding();
}

void PriorityQueue::orderAfterAdding()
{
    int node = size - 1;
    int parent = (size-1)/2;
    Solution* pom;

    while(root[node] -> getLowerBound() < root[parent] -> getLowerBound()) {
        pom = root[parent];
        root[parent] = root[node];
        root[node] = pom;
        node = parent;
        parent = (node - 1)/2;
    }
}

void PriorityQueue::remove()
{
    if(root == NULL)
        return;

    if(size == 1) {
        delete root[0];
        root = NULL;
        size--;
        return;
    }

    delete root[0];
    root[0] = root[size-1];

    size--;
    orderAfterRemoving();
}

void PriorityQueue::orderAfterRemoving() {
    int index = 0;
    int rightChild = 2*index + 2;
    int leftChild = 2*index + 1;
    int parent = (index-1)/2;
    Solution* pom;

    if(root[index] -> getLowerBound() < root[parent] -> getLowerBound()) {
        while(root[index] -> getLowerBound() < root[parent] -> getLowerBound()) {
            pom = root[parent];
            root[parent] = root[index];
            root[index] = pom;
            index = parent;
            parent = (index-1)/2;
        }
        return;
    }

    if(leftChild >= size)
        return;

    if(rightChild >= size) {
        if(root[leftChild] -> getLowerBound() < root[index] -> getLowerBound()) {
            pom = root[index];
            root[index] = root[leftChild];
            root[leftChild] = pom;
        }
        return;
    }

    while(root[index] -> getLowerBound() > root[leftChild] -> getLowerBound() || root[index] -> getLowerBound() > root[rightChild] -> getLowerBound()) {
        if(root[rightChild] -> getLowerBound() < root[leftChild] -> getLowerBound()) {
            pom = root[rightChild];
            root[rightChild] = root[index];
            root[index] = pom;
            index = rightChild;
        }
        else {
            pom = root[leftChild];
            root[leftChild] = root[index];
            root[index] = pom;
            index = leftChild;
        }

        leftChild = 2*index + 1;
        rightChild = 2*index + 2;

        if(leftChild >= size)
            return;

        if(rightChild >= size) {
            if(root[index] -> getLowerBound() > root[leftChild] -> getLowerBound()) {
                pom = root[index];
                root[index] = root[leftChild];
                root[leftChild] = pom;
            }
            return;
        }
    }
}

Solution* PriorityQueue::getFirst() {
    return root[0];
}

void PriorityQueue::display() {
    if (root == NULL)
        return;

    printBT("", "", 0);
    system("pause");
}

void PriorityQueue::printBT(string sp, string sn, int v) {
    string s;

    if(v < size) {
        s = sp;
        if(sn == cr) s[s.length() - 2] = ' ';
        printBT(s + cp, cr, 2 * v + 2);

        s = s.substr(0,sp.length()-2);

        cout << s << sn << root[v] -> getLowerBound() << endl;

        s = sp;
        if(sn == cl) s[s.length() - 2] = ' ';
        printBT(s + cp, cl, 2 * v + 1);
    }
}