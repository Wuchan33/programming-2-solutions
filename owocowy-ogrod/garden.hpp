// Mikolaj Suchan

#define nullptr 0

class FRUIT_CLASS;
class BRANCH_CLASS;
class TREE_CLASS;

class GARDEN_CLASS {
    private:
        unsigned int treesTotal;
        unsigned int branchesTotal;
        unsigned int fruitsTotal;
        unsigned int weightsTotal;

        TREE_CLASS* treeTail;
        TREE_CLASS* treeHead;
        TREE_CLASS* addafter;
    public:
        GARDEN_CLASS( void );
        ~GARDEN_CLASS( void );
        GARDEN_CLASS( const GARDEN_CLASS& );

        TREE_CLASS* getaddafter( void );
        void settreeTail( TREE_CLASS* treeTail );
        void settreeHead( TREE_CLASS* treeHead );
        void setPrev( GARDEN_CLASS* prev );
        void setNext( GARDEN_CLASS* next );
        GARDEN_CLASS* getPrev( void );
        GARDEN_CLASS* getNext( void );
        TREE_CLASS* gettreeTail( void );
        TREE_CLASS* gettreeHead( void );
        void updateTreesTotal( int diff );
        void updateBranchesTotal( int diff );
        void updateFruitsTotal( int diff );
        void updateWeightsTotal( int diff );

        unsigned int getTreesTotal( void );
        unsigned int getBranchesTotal( void );
        unsigned int getFruitsTotal( void );
        unsigned int getWeightsTotal( void );
        void plantTree( void );
        void extractTree( unsigned int );
        void growthGarden( void );
        void fadeGarden( void );
        void harvestGarden( unsigned int );
        TREE_CLASS* getTreePointer( unsigned int );
        void cloneTree( unsigned int );
};