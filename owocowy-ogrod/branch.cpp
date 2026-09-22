// Mikolaj Suchan

#include "fruit.hpp"
#include "branch.hpp"
#include "tree.hpp"
#include "garden.hpp"


unsigned int BRANCH_CLASS::getFruitsTotal( void ) {
    return fruitsTotal;
}

unsigned int BRANCH_CLASS::getWeightsTotal( void ) {
    return weightsTotal;
}

unsigned int BRANCH_CLASS::getHeight( void ) {
    return height;
}

unsigned int BRANCH_CLASS::getLength( void ) {
    return length;
}

void BRANCH_CLASS::growthBranch( void ) {
    FRUIT_CLASS* curr = fruitHead;
    while (curr != nullptr) {
        curr->growthFruit();
        curr = curr->getNext();
    }

    length++;
    if (length % 2 == 0) {
        FRUIT_CLASS* newFruit = new FRUIT_CLASS(length, fruitTail, this);
        if (fruitTail != nullptr) {
            fruitTail->setNext(newFruit);
            setfruitTail(newFruit);
        } else {
            setfruitHead(newFruit);
            setfruitTail(newFruit);
        }
        updateFruitsTotal(1);
    }
}

void BRANCH_CLASS::fadeBranch( void ) {
    FRUIT_CLASS* fruit = fruitHead;
    while (fruit != nullptr) {
        fruit->fadeFruit();
        fruit = fruit->getNext();
    }

    if (length == 0)
        return;
    
    if (length % 2 == 0) {
        updateWeightsTotal(-fruitTail->getWeight());
        updateFruitsTotal(-1);
        FRUIT_CLASS* temp = fruitTail;
        FRUIT_CLASS* prev_fruit = fruitTail->getPrev();
        if (prev_fruit != nullptr) {
            prev_fruit->setNext(nullptr);
            setfruitTail(prev_fruit);
        } else {
            setfruitTail(nullptr);
            setfruitHead(nullptr);
        }
        delete temp;
    }
    length--;
}

void BRANCH_CLASS::harvestBranch( unsigned int amount ) {
    FRUIT_CLASS* fruit = fruitHead;
    while (fruit != nullptr) {
        if (fruit->getWeight() >= amount) {
            fruit->pluckFruit();
        }
        fruit = fruit->getNext();
    }
}

void BRANCH_CLASS::cutBranch( unsigned int amount ) {
    if (amount >= length)
        return;
    FRUIT_CLASS* curr = fruitTail;
    while (curr != nullptr) {
        if (curr->getLength() <= amount)
            break;
        updateWeightsTotal(-curr->getWeight());
        updateFruitsTotal(-1);
        FRUIT_CLASS* temp = curr;
        curr = curr->getPrev();
        delete temp;
    }

    if (curr != nullptr) {
        curr->setNext(nullptr);
        setfruitTail(curr);
    } else {
        setfruitTail(nullptr);
        setfruitHead(nullptr);
    }

    length = amount;
}

FRUIT_CLASS* BRANCH_CLASS::getFruitPointer( unsigned int index ) {
    if (index > length || index % 2)
        return nullptr;
    FRUIT_CLASS* curr = fruitHead;
    while (curr != nullptr) {
        if (curr->getLength() == index) {
            return curr;
        } else if (curr->getLength() > index) {
            return nullptr;
        }
        curr = curr->getNext();
    }
    return nullptr;
}

TREE_CLASS* BRANCH_CLASS::getTreePointer( void ) {
    return tree;
}

BRANCH_CLASS::BRANCH_CLASS( const BRANCH_CLASS& branch ) {
    this->height = branch.height;
    this->length = branch.length;
    this->fruitsTotal = branch.fruitsTotal;
    this->weightsTotal = branch.weightsTotal;
    this->tree = nullptr;

    this->fruitTail = nullptr;
    this->fruitHead = nullptr;
    FRUIT_CLASS* curr = branch.fruitHead;
    FRUIT_CLASS* prev_fruit = nullptr;
    while (curr != nullptr) {
        FRUIT_CLASS* newFruit = new FRUIT_CLASS(*curr);
        newFruit->setBranchPointer(this);
        if (fruitTail != nullptr) {
            fruitTail->setNext(newFruit);
            fruitTail = newFruit;
        } else {
            fruitHead = newFruit;
            fruitTail = newFruit;
        }

        newFruit->setPrev(prev_fruit);
        prev_fruit = newFruit;
        curr = curr->getNext();
    }

    this->prev = nullptr;
    this->next = nullptr;
}

BRANCH_CLASS::BRANCH_CLASS( unsigned int height, BRANCH_CLASS* prev, TREE_CLASS* tree) {
    this->height = height;
    this->length = 0;
    this->fruitsTotal = 0;
    this->weightsTotal = 0;
    this->tree = tree;
    this->fruitTail = nullptr;
    this->fruitHead = nullptr;
    this->prev = prev;
    this->next = nullptr;
}

BRANCH_CLASS::~BRANCH_CLASS( void ) {
    FRUIT_CLASS* curr = fruitTail;
    while (curr != nullptr) {
        FRUIT_CLASS* prev_fruit = curr->getPrev();
        delete curr;
        curr = prev_fruit;
    }
}

void BRANCH_CLASS::setfruitHead( FRUIT_CLASS* fruitHead ) {
    this->fruitHead = fruitHead;
}

void BRANCH_CLASS::setfruitTail( FRUIT_CLASS* fruitTail ) {
    this->fruitTail = fruitTail;
}

FRUIT_CLASS* BRANCH_CLASS::getFruitHead( void ) {
    return fruitHead;
}

FRUIT_CLASS* BRANCH_CLASS::getFruitTail( void ) {
    return fruitTail;
}

void BRANCH_CLASS::setNext( BRANCH_CLASS* next ) {
    this->next = next;
}

void BRANCH_CLASS::setPrev( BRANCH_CLASS* prev ) {
    this->prev = prev;
}

BRANCH_CLASS* BRANCH_CLASS::getNext( void ) {
    return next;
}

BRANCH_CLASS* BRANCH_CLASS::getPrev( void ) {
    return prev;
}

void BRANCH_CLASS::updateFruitsTotal( int diff ) {
    fruitsTotal += diff;
    if (tree != nullptr) {
        tree->updateFruitsTotal(diff);
    }
}

void BRANCH_CLASS::updateWeightsTotal( int diff ) {
    weightsTotal += diff;
    if (tree != nullptr) {
        tree->updateWeightsTotal(diff);
    }
}

void BRANCH_CLASS::setTreePointer( TREE_CLASS* tree ) {
    this->tree = tree;
}

void BRANCH_CLASS::setHeight( unsigned int height ) {
    this->height = height;
}