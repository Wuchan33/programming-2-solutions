// Mikolaj Suchan

#include "fruit.hpp"
#include "branch.hpp"
#include "tree.hpp"
#include "garden.hpp"

unsigned int TREE_CLASS::getBranchesTotal( void ) {
    return branchesTotal;
}

unsigned int TREE_CLASS::getFruitsTotal( void ) {
    return fruitsTotal;
}

unsigned int TREE_CLASS::getWeightsTotal( void ) {
    return weightsTotal;
}

unsigned int TREE_CLASS::getNumber( void ) {
    return number;
}

unsigned int TREE_CLASS::getHeight( void ) {
    return height;
}

void TREE_CLASS::updateBranchesTotal( int diff ) {
    branchesTotal += diff;
    if (garden != nullptr) {
        garden->updateBranchesTotal(diff);
    }
}

void TREE_CLASS::updateFruitsTotal( int diff ) {
    fruitsTotal += diff;
    if (garden != nullptr) {
        garden->updateFruitsTotal(diff);
    }
}

void TREE_CLASS::updateWeightsTotal( int diff ) {
    weightsTotal += diff;
    if (garden != nullptr) {
        garden->updateWeightsTotal(diff);
    }
}

void TREE_CLASS::setPrev( TREE_CLASS* prev ) {
    this->prev = prev;
}

void TREE_CLASS::setNext( TREE_CLASS* next ) {
    this->next = next;
}

TREE_CLASS* TREE_CLASS::getPrev( void ) {
    return prev;
}

TREE_CLASS* TREE_CLASS::getNext( void ) {
    return next;
}

void TREE_CLASS::setBranchTail( BRANCH_CLASS* branchTail ) {
    this->branchTail = branchTail;
}

void TREE_CLASS::setBranchHead( BRANCH_CLASS* branchHead ) {
    this->branchHead = branchHead;
}

BRANCH_CLASS* TREE_CLASS::getBranchHead( void ) {
    return branchHead;
}

BRANCH_CLASS* TREE_CLASS::getBranchTail( void ) {
    return branchTail;
}

void TREE_CLASS::growthTree( void ) {
    BRANCH_CLASS* branch = branchHead;
    while (branch != nullptr) {
        branch->growthBranch();
        branch = branch->getNext();
    }

    height++;
    if (height % 3 == 0) {
        BRANCH_CLASS* newBranch = new BRANCH_CLASS(height, branchTail, this);
        if (branchTail != nullptr) {
            branchTail->setNext(newBranch);
            setBranchTail(newBranch);
        } else {
            setBranchHead(newBranch);
            setBranchTail(newBranch);
        }
        updateBranchesTotal(1);
    }
}

void TREE_CLASS::fadeTree( void ) {
    BRANCH_CLASS* branch = branchHead;
    while (branch != nullptr) {
        branch->fadeBranch();
        branch = branch->getNext();
    }

    if (height == 0)
        return;
    
    if (height % 3 == 0) {
        BRANCH_CLASS* temp = branchTail;
        updateWeightsTotal(-temp->getWeightsTotal());
        updateBranchesTotal(-1);
        updateFruitsTotal(-temp->getFruitsTotal());

        BRANCH_CLASS* prev_branch = temp->getPrev();
        if (prev_branch != nullptr) {
            prev_branch->setNext(nullptr);
            setBranchTail(prev_branch);
        } else {
            setBranchTail(nullptr);
            setBranchHead(nullptr);
        }
        delete temp;
    }
    height--;
}

void TREE_CLASS::harvestTree( unsigned int number ) {
    BRANCH_CLASS* branch = branchHead;
    while (branch != nullptr) {
        branch->harvestBranch(number);
        branch = branch->getNext();
    }
}

void TREE_CLASS::cutTree( unsigned int amount ) {
    if (amount >= height)
        return;
    BRANCH_CLASS* curr = branchTail;
    while (curr != nullptr) {
        if (curr->getHeight() <= amount)
            break;
        updateWeightsTotal(-curr->getWeightsTotal());
        updateBranchesTotal(-1);
        updateFruitsTotal(-curr->getFruitsTotal());
        BRANCH_CLASS* temp = curr;
        curr = curr->getPrev();
        delete temp;
    }

    if (curr != nullptr) {
        curr->setNext(nullptr);
        setBranchTail(curr);
    } else {
        setBranchTail(nullptr);
        setBranchHead(nullptr);
    }

    height = amount;
}

void TREE_CLASS::cloneBranch( BRANCH_CLASS* branch ) {
    BRANCH_CLASS* curr = branchHead;
    while (curr != nullptr) {
        if (curr->getLength() == 0)
            break;
        curr = curr->getNext();
    }

    if (curr == nullptr)
        return;
    
    BRANCH_CLASS* new_branch = new BRANCH_CLASS(*branch);
    new_branch->setTreePointer(this);
    new_branch->setHeight(curr->getHeight());
    updateFruitsTotal(new_branch->getFruitsTotal());
    updateWeightsTotal(new_branch->getWeightsTotal());
    BRANCH_CLASS* prev_branch = curr->getPrev();
    BRANCH_CLASS* next_branch = curr->getNext(); 
    if (prev_branch != nullptr)
        prev_branch->setNext(new_branch);
    else
        branchHead = new_branch;
    if (next_branch != nullptr)
        next_branch->setPrev(new_branch);
    else
        branchTail = new_branch;
    new_branch->setPrev(prev_branch);
    new_branch->setNext(next_branch);
    delete curr;
}

void TREE_CLASS::setGardenPointer( GARDEN_CLASS* garden ) {
    this->garden = garden;
}

TREE_CLASS::TREE_CLASS( const TREE_CLASS& tree ) {
    branchesTotal = tree.branchesTotal;
    fruitsTotal = tree.fruitsTotal;
    weightsTotal = tree.weightsTotal;
    number = tree.number;
    height = tree.height;
    
    garden = nullptr;
    branchTail = nullptr;
    branchHead = nullptr;
   
    BRANCH_CLASS* curr = tree.branchHead;
    BRANCH_CLASS* prev_branch = nullptr;
    
    while (curr != nullptr) {
        BRANCH_CLASS* newBranch = new BRANCH_CLASS(*curr);
        newBranch->setTreePointer(this);
        if (branchTail != nullptr) {
            branchTail->setNext(newBranch);
            branchTail = newBranch;
        } else {
            branchHead = newBranch;
            branchTail = newBranch;
        }

        newBranch->setPrev(prev_branch);
        prev_branch = newBranch;
        curr = curr->getNext();
    }

    this->prev = nullptr;
    this->next = nullptr;
}

TREE_CLASS::TREE_CLASS( unsigned int number, TREE_CLASS* prev, GARDEN_CLASS* garden) {
    this->branchesTotal = 0;
    this->fruitsTotal = 0;
    this->weightsTotal = 0;
    this->number = number;
    this->height = 0;
    this->garden = garden;

    this->branchTail = nullptr;
    this->branchHead = nullptr;

    this->prev = prev;
    this->next = nullptr;
}

TREE_CLASS::~TREE_CLASS( void ) {
    BRANCH_CLASS* curr = branchTail;
    while (curr != nullptr) {
        BRANCH_CLASS* prev_branch = curr->getPrev();
        delete curr;
        curr = prev_branch;
    }
}

void TREE_CLASS::setNumber( unsigned int number ) {
    this->number = number;
}

GARDEN_CLASS* TREE_CLASS::getGardenPointer( void ) {
    if (garden != nullptr)
        return garden;
    return nullptr;
}

BRANCH_CLASS* TREE_CLASS::getBranchPointer( unsigned int index ) {
    if (index > height || index % 3)
        return nullptr;
    BRANCH_CLASS* curr = branchHead;
    while (curr != nullptr) {
        if (curr->getHeight() == index) {
            return curr;
        } else if (curr->getHeight() > index) {
            return nullptr;
        }
        curr = curr->getNext();
    }
    return nullptr;
}