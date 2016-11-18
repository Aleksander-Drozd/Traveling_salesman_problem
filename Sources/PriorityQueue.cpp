//
// Created by John on 18-Nov-16.
//

#include "../Headers/PriorityQueue.h"

#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

PriorityQueue::PriorityQueue() {
    size = 0;
    root = NULL;
    id = 1;
}

PriorityQueue::~PriorityQueue() {
    for(int i=0; i<size; i++)
        delete root[i];
    delete [] root;
}

void PriorityQueue::add(int** matrix, int* rowIndexes, int* columnIndexes, int matrixSize, int lowerBound) {
    treeNode** tree;

    tree = new treeNode* [size + 1];

    for(int i=0; i<size; i++) {
        tree[i] = new treeNode;
        tree[i] -> matrix = root[i] -> matrix;
        tree[i] -> rowIndexes = root[i] -> rowIndexes;
        tree[i] -> columnIndexes = root[i] -> columnIndexes;
        tree[i] -> size = root[i] -> size;
        tree[i] -> lowerBound = root[i] -> lowerBound;

        delete root[i];
    }

    tree[size] = new treeNode;
    tree[size] -> matrix =  matrix;
    tree[size] -> rowIndexes = rowIndexes;
    tree[size] -> columnIndexes = columnIndexes;
    tree[size] -> size = matrixSize;
    tree[size] -> lowerBound = lowerBound;

    delete [] root;
    root = tree;
    size++;
    orderAfterAdding();
}

void PriorityQueue::orderAfterAdding()
{
    int node = size - 1;
    int parent = (size-1)/2;
    treeNode* pom;

    while(root[node] -> lowerBound < root[parent] -> lowerBound) {
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
    treeNode* pom;

    if(root[index] -> lowerBound < root[parent] -> lowerBound) {
        while(root[index] -> lowerBound < root[parent] -> lowerBound) {
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
        if(root[leftChild] -> lowerBound < root[index] -> lowerBound) {
            pom = root[index];
            root[index] = root[leftChild];
            root[leftChild] = pom;
        }
        return;
    }

    while(root[index] -> lowerBound > root[leftChild] -> lowerBound || root[index] -> lowerBound > root[rightChild] -> lowerBound) {
        if(root[rightChild] -> lowerBound < root[leftChild] -> lowerBound) {
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
            if(root[index] -> lowerBound > root[leftChild] -> lowerBound) {
                pom = root[index];
                root[index] = root[leftChild];
                root[leftChild] = pom;
            }
            return;
        }
    }
}

PriorityQueue::treeNode* PriorityQueue::getFirst() {
    return root[0];
}

void PriorityQueue::display() {
    if (root == NULL)
        return;
    cout<<("", "", 0);
    system("pause");
}
