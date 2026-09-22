// Mikolaj Suchan

#include "fruit.hpp"
#include "branch.hpp"
#include "tree.hpp"
#include "garden.hpp"

FRUIT_CLASS::FRUIT_CLASS( unsigned int length, FRUIT_CLASS* prev, BRANCH_CLASS* branch ) {
    this->length = length;
    this->weight = 0;
    this->prev = prev;
    this->next = nullptr;
    this->branch = branch;
}

FRUIT_CLASS::FRUIT_CLASS( const FRUIT_CLASS& fruit ) {
    this->length = fruit.length;
    this->weight = fruit.weight;
    this->prev = nullptr;
    this->next = nullptr;
    this->branch = nullptr;
}

void FRUIT_CLASS::setBranchPointer( BRANCH_CLASS* branch ) {
    this->branch = branch;
}

unsigned int FRUIT_CLASS::getLength( void ) {
    return length;
}

unsigned int FRUIT_CLASS::getWeight( void ) {
    return weight;
}

void FRUIT_CLASS::growthFruit( void ) {
    updateWeight(1);
}

void FRUIT_CLASS::fadeFruit( void ) {
    if (weight > 0) {
        updateWeight(-1);
    }
}

void FRUIT_CLASS::pluckFruit( void ) {
    updateWeight(-weight);
}

BRANCH_CLASS* FRUIT_CLASS::getBranchPointer( void ) {
    return branch;
}

FRUIT_CLASS::~FRUIT_CLASS( void ) {
}

void FRUIT_CLASS::updateWeight( int diff ) {
    weight += diff;
    if (branch != nullptr) {
        branch->updateWeightsTotal(diff);
    }
}

FRUIT_CLASS* FRUIT_CLASS::getNext( void ) {
    return next;
}

FRUIT_CLASS* FRUIT_CLASS::getPrev( void ) {
    return prev;
}

void FRUIT_CLASS::setPrev( FRUIT_CLASS* prev ) {
    this->prev = prev;
}

void FRUIT_CLASS::setNext( FRUIT_CLASS* next ) {
    this->next = next;
}