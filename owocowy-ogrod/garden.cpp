// Mikolaj Suchan

#include "garden.hpp"
#include "tree.hpp"
#include "branch.hpp"
#include "fruit.hpp"

unsigned int GARDEN_CLASS::getTreesTotal( void ) {
    return treesTotal;
}

unsigned int GARDEN_CLASS::getBranchesTotal( void ) {
    return branchesTotal;
}

unsigned int GARDEN_CLASS::getFruitsTotal( void ) {
    return fruitsTotal;
}

unsigned int GARDEN_CLASS::getWeightsTotal( void ) {
    return weightsTotal;
}

void GARDEN_CLASS::plantTree( void ) {
    this->treesTotal++;
    if (treeHead == nullptr) {
        TREE_CLASS* new_tree = new TREE_CLASS(0, nullptr, this);
        this->treeHead = new_tree;
        this->treeTail = new_tree;
        addafter = new_tree;
    } else if (addafter == nullptr) {
        TREE_CLASS* new_tree = new TREE_CLASS(0, nullptr, this);
        new_tree->setNext(treeHead);
        addafter = new_tree;
        treeHead->setPrev(new_tree);
        treeHead = new_tree;

        while (addafter->getNext() != nullptr && addafter->getNumber() + 1 == addafter->getNext()->getNumber()) {
            addafter = addafter->getNext();
        }
    } else {
        TREE_CLASS* new_tree = new TREE_CLASS(addafter->getNumber() + 1, addafter, this);
        new_tree->setNext(addafter->getNext());
        if (addafter->getNext() != nullptr) {
            addafter->getNext()->setPrev(new_tree);
        } else 
            treeTail = new_tree;
        addafter->setNext(new_tree);
        
        while (addafter->getNext() != nullptr && addafter->getNumber() + 1 == addafter->getNext()->getNumber()) {
            addafter = addafter->getNext();
        }
    }
}

GARDEN_CLASS::GARDEN_CLASS( const GARDEN_CLASS& garden ) {
    this->treesTotal = garden.treesTotal;
    this->branchesTotal = garden.branchesTotal;
    this->fruitsTotal = garden.fruitsTotal;
    this->weightsTotal = garden.weightsTotal;
    
    this->treeTail = nullptr;
    this->treeHead = nullptr;
    this->addafter = nullptr;

    TREE_CLASS* curr = garden.treeHead;
    while (curr != nullptr) {
        TREE_CLASS* new_tree = new TREE_CLASS(*curr);
        new_tree->setGardenPointer(this);
        if (treeTail != nullptr) {
            treeTail->setNext(new_tree);
            new_tree->setPrev(treeTail);
            treeTail = new_tree;
        } else {
            treeHead = new_tree;
            treeTail = new_tree;
        }
        if (addafter == nullptr) {
            TREE_CLASS* prev_tree = new_tree->getPrev();
            if (prev_tree != nullptr && curr->getNumber() > prev_tree->getNumber() + 1) {
                addafter = new_tree->getPrev();
            }
        }
        curr = curr->getNext();
    }
}

void GARDEN_CLASS::extractTree( unsigned int number ) {
    if (treeHead == nullptr)
        return;
    TREE_CLASS* curr = nullptr;
    if (treeTail->getNumber() - number < number - treeHead->getNumber()) {
        curr = treeTail;
        while (curr != nullptr && curr->getNumber() != number) {
            curr = curr->getPrev();
        }
    } else {
        curr = treeHead;
        while (curr != nullptr && curr->getNumber() != number) {
            curr = curr->getNext();
        }
    }
    
    if (curr != nullptr) {
        if (addafter != nullptr) {
            if (number <= addafter->getNumber()) {
                addafter = curr->getPrev();
            }
        }

        TREE_CLASS* prev = curr->getPrev();
        TREE_CLASS* next = curr->getNext();

        if (prev != nullptr) {
            prev->setNext(next);
        } else {
            treeHead = next;
        }

        if (next != nullptr) {
            next->setPrev(prev);
        } else {
            treeTail = prev;
        }
                
        treesTotal--;
        branchesTotal -= curr->getBranchesTotal();
        fruitsTotal -= curr->getFruitsTotal();
        weightsTotal -= curr->getWeightsTotal();
        delete curr;
    }
}

void GARDEN_CLASS::growthGarden( void ) {
    TREE_CLASS* curr = treeHead;
    while (curr != nullptr) {
        curr->growthTree();
        curr = curr->getNext();
    }
}

void GARDEN_CLASS::fadeGarden( void ) {
    TREE_CLASS* curr = treeHead;
    while (curr != nullptr) {
        curr->fadeTree();
        curr = curr->getNext();
    }
}

void GARDEN_CLASS::harvestGarden( unsigned int number ) {
    TREE_CLASS* curr = treeHead;
    while (curr != nullptr) {
        curr->harvestTree(number);
        curr = curr->getNext();
    }
}

TREE_CLASS* GARDEN_CLASS::getTreePointer( unsigned int number ) {
    TREE_CLASS* curr = treeHead;
    while (curr != nullptr) {
        if (curr->getNumber() == number)
            return curr;
        curr = curr->getNext();
    }
    return nullptr;
}

void GARDEN_CLASS::cloneTree( unsigned int number ) {
    TREE_CLASS* tree = getTreePointer(number);
    if (tree != nullptr) {
        TREE_CLASS* new_tree = new TREE_CLASS(*tree);
        new_tree->setGardenPointer(this);
        treesTotal++;
        branchesTotal += new_tree->getBranchesTotal();
        fruitsTotal += new_tree->getFruitsTotal();
        weightsTotal += new_tree->getWeightsTotal();

        if (addafter == nullptr) {
            addafter = new_tree;
            new_tree->setNumber(0);
            new_tree->setNext(treeHead);
            if (treeHead != nullptr)
                treeHead->setPrev(new_tree);
            treeHead = new_tree;
        } else {
            new_tree->setPrev(addafter);
            new_tree->setNumber(addafter->getNumber() + 1);
            new_tree->setNext(addafter->getNext());
            if (addafter->getNext() != nullptr) {
                addafter->getNext()->setPrev(new_tree);
            } else 
                treeTail = new_tree;
            addafter->setNext(new_tree);
            
            while (addafter->getNext() != nullptr && addafter->getNumber() == addafter->getNext()->getNumber() + 1) {
                addafter = addafter->getNext();
            }
        }
    }
}

void GARDEN_CLASS::settreeTail( TREE_CLASS* treeTail ) {
    this->treeTail = treeTail;
}

void GARDEN_CLASS::settreeHead( TREE_CLASS* treeHead ) {
    this->treeHead = treeHead;
}

TREE_CLASS* GARDEN_CLASS::gettreeTail( void ) {
    return treeTail;
}

TREE_CLASS* GARDEN_CLASS::gettreeHead( void ) {
    return treeHead;
}

GARDEN_CLASS::GARDEN_CLASS( void ) {
    treesTotal = 0;
    branchesTotal = 0;
    fruitsTotal = 0;
    weightsTotal = 0;
    treeTail = nullptr;
    treeHead = nullptr;
    addafter = nullptr;
}

GARDEN_CLASS::~GARDEN_CLASS( void ) {
    TREE_CLASS* curr = treeHead;
    while (curr != nullptr) {
        TREE_CLASS* temp = curr;
        curr = curr->getNext();
        delete temp;
    }
    addafter = nullptr;
    treeHead = nullptr;
    treeTail = nullptr;
}

void GARDEN_CLASS::updateBranchesTotal( int diff ) {
    branchesTotal += diff;
}

void GARDEN_CLASS::updateFruitsTotal( int diff ) {
    fruitsTotal += diff;
}

void GARDEN_CLASS::updateWeightsTotal( int diff ) {
    weightsTotal += diff;
}

void GARDEN_CLASS::updateTreesTotal( int diff ) {
    treesTotal += diff;
}

TREE_CLASS* GARDEN_CLASS::getaddafter( void ) {
    return addafter;
}