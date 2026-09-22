// Mikolaj Suchan

#define nullptr 0

class FRUIT_CLASS;
class TREE_CLASS;
class GARDEN_CLASS;

class BRANCH_CLASS {
    private:
        unsigned int height;
        unsigned int length;
        unsigned int fruitsTotal;
        unsigned int weightsTotal;
        TREE_CLASS* tree;
        
        FRUIT_CLASS* fruitTail;
        FRUIT_CLASS* fruitHead;
        BRANCH_CLASS* prev;
        BRANCH_CLASS* next;
        
    public:
        BRANCH_CLASS( unsigned int = 0, BRANCH_CLASS* = nullptr, TREE_CLASS* = nullptr);
        BRANCH_CLASS( const BRANCH_CLASS& );
        ~BRANCH_CLASS( void );
        
        void updateFruitsTotal( int diff );
        void updateWeightsTotal( int diff );
        BRANCH_CLASS* getPrev( void );
        BRANCH_CLASS* getNext( void );
        void setPrev( BRANCH_CLASS* prev );
        void setNext( BRANCH_CLASS* next );
        void setfruitTail( FRUIT_CLASS* fruitTail );
        void setfruitHead( FRUIT_CLASS* fruitHead );
        FRUIT_CLASS* getFruitHead( void );
        FRUIT_CLASS* getFruitTail( void );
        void setTreePointer( TREE_CLASS* tree );
        void setHeight( unsigned int height );

        unsigned int getFruitsTotal( void );
        unsigned int getWeightsTotal( void );
        unsigned int getHeight( void );
        unsigned int getLength( void );
        void growthBranch( void );
        void fadeBranch( void );
        void harvestBranch( unsigned int );
        void cutBranch( unsigned int );
        FRUIT_CLASS* getFruitPointer( unsigned int );
        TREE_CLASS* getTreePointer( void );
};