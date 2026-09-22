// Mikolaj Suchan

#define nullptr 0

class BRANCH_CLASS;
class TREE_CLASS;
class GARDEN_CLASS;

class FRUIT_CLASS {
    private:
        FRUIT_CLASS* prev;
        FRUIT_CLASS* next;
        unsigned int length;
        unsigned int weight;
        BRANCH_CLASS* branch;
    public:
        FRUIT_CLASS( unsigned int = 0, FRUIT_CLASS* = nullptr, BRANCH_CLASS* = nullptr);
        FRUIT_CLASS( const FRUIT_CLASS& );
        ~FRUIT_CLASS( void );

        void updateWeight( int diff );
        FRUIT_CLASS* getPrev( void );
        FRUIT_CLASS* getNext( void );
        void setPrev( FRUIT_CLASS* prev );
        void setNext( FRUIT_CLASS* next );
        void setBranchPointer( BRANCH_CLASS* branch );

        unsigned int getLength( void );
        unsigned int getWeight( void );
        void growthFruit( void );
        void fadeFruit( void );
        void pluckFruit( void );
        BRANCH_CLASS* getBranchPointer ( void ); 
};