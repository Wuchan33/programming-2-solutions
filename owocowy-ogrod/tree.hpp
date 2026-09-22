// Mikolaj Suchan

#define nullptr 0

class FRUIT_CLASS;
class BRANCH_CLASS;
class GARDEN_CLASS;

class TREE_CLASS {
    private:
        unsigned int branchesTotal;
        unsigned int fruitsTotal;
        unsigned int weightsTotal;
        unsigned int number;
        unsigned int height;
        GARDEN_CLASS* garden;

        BRANCH_CLASS* branchTail;
        BRANCH_CLASS* branchHead;
        
        TREE_CLASS* prev;
        TREE_CLASS* next;
    public:
        TREE_CLASS( unsigned int = 0, TREE_CLASS* = nullptr, GARDEN_CLASS* = nullptr);
        ~TREE_CLASS( void );
        TREE_CLASS( const TREE_CLASS& );
        
        void updateBranchesTotal( int diff );
        void updateFruitsTotal( int diff );
        void updateWeightsTotal( int diff );
        void setGardenPointer( GARDEN_CLASS* garden );
        TREE_CLASS* getPrev( void );
        TREE_CLASS* getNext( void );
        void setPrev( TREE_CLASS* prev );
        void setNext( TREE_CLASS* next );
        void setBranchTail( BRANCH_CLASS* branchTail );
        void setBranchHead( BRANCH_CLASS* branchHead );
        BRANCH_CLASS* getBranchHead( void );
        BRANCH_CLASS* getBranchTail( void );
        void setNumber( unsigned int number );

        unsigned int getBranchesTotal( void );
        unsigned int getFruitsTotal( void );
        unsigned int getWeightsTotal( void );
        unsigned int getNumber( void );
        unsigned int getHeight( void );
        void growthTree( void );
        void fadeTree( void );
        void harvestTree( unsigned int );
        void cutTree( unsigned int );
        void cloneBranch( BRANCH_CLASS* );
        GARDEN_CLASS* getGardenPointer( void );
        BRANCH_CLASS* getBranchPointer( unsigned int );

};