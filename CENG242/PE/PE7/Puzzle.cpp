#include "Puzzle.h"


/****************************************************/
/****              *** PUZZLE ***                ****/

/* Contsructor : It takes three integers in the following order:
    The first argument is size of the puzzle which is 2^N for some N >= 0.
    The second argument is the initial row id of the puzzle.
    The third argument is the initial column id of the puzzle.
    
    After initialization with the above arguments, the necessary 
    pointers should be initialized to NULL.
    Note that the final row id in this puzzle is equal to: 
       initial_row_id + size - 1.
    Note that the final column id in this puzzle is equal to: 
       initial_column_id + size - 1.
       
    ATTENTION: If a sub-puzzle member does not include any Piece, namely, 
    if its piece is NULL, then do NOT construct it. In other words, do 
    NOT construct subpuzzles unless they are required. 
*/
Puzzle::Puzzle(int x, int y, int z) {
    // TODO    
    this->size  = x;       
    this->first_row = y;
    this->first_column = z;
    this->top_left = NULL;
    this->top_right = NULL;
    this->bottom_left = NULL;
    this->bottom_right = NULL;
    this->piece = NULL;    
}

/* Destructor  : It should destruct its sub-puzzles, yet it is NOT responsible
   of the destruction of its Piece member.
*/
Puzzle::~Puzzle() {
    // TODO
    delete top_left; 
    delete top_right;
    delete bottom_left;
    delete bottom_right;
}

/* Copy constructor : It totally applies deep copy except the Piece
   member part. Do not deep copy Piece objects of the puzzle, instead
   do shallow copy for Pieces.
*/
Puzzle::Puzzle(const Puzzle& puzzle) {
    // TODO
    this->size = puzzle.size;
    this->first_row = puzzle.first_row;
    this->first_column = puzzle.first_column;

    if (puzzle.top_left != NULL) {
        this->top_left = new Puzzle(*puzzle.top_left);
    } else {
        this->top_left = NULL;
    }
    if (puzzle.top_right!= NULL) {
        this->top_right = new Puzzle(*puzzle.top_right);
    } else {
        this->top_right = NULL;
    }
    if (puzzle.bottom_left!= NULL) {
        this->bottom_left = new Puzzle(*puzzle.bottom_left);
    } else {
        this->bottom_left = NULL;
    }
    if (puzzle.bottom_right!= NULL) {
        this->bottom_right = new Puzzle(*puzzle.bottom_right);
    } else {
        this->bottom_right = NULL;
    }
    this->piece = puzzle.piece;   
}

/* Assignment operator : It totally applies shallow copy.
*/
Puzzle& Puzzle::operator=(const Puzzle& puzzle) {
    // TODO
    this->size  = puzzle.size;       
    this->first_row = puzzle.first_row;
    this->first_column = puzzle.first_column;
    this->top_left = puzzle.top_left;    
    this->top_right = puzzle.top_right;   
    this->bottom_left = puzzle.bottom_left; 
    this->bottom_right = puzzle.bottom_right;  
    this->piece = puzzle.piece;
    return *this;
}

/* This method directly assigns (without copying) the given Piece object to
   the corresponding sub-puzzle (cell) whose indices given in the second 
   argument in array form as follows <row_id, column_id>.
   
    ATTENTION: If a sub-puzzle member does not include any Piece, namely, 
    if its piece is NULL, then do NOT construct it. In other words, do 
    NOT construct subpuzzles unless they are required.
*/
void Puzzle::placePiece(const Piece& piece, int indices[2] ) {
    // TODO
    if(this->size == 1) {
        this->piece = &piece;
    }
    else if(indices[0] < first_row + size/2 && indices[1]< first_column +size/2){
        if(this->top_left==NULL){this->top_left= new Puzzle(size/2, first_row,first_column); }
        this->top_left->placePiece(piece,indices);
    }
    else if(indices[0] >= first_row + size/2 && indices[1]< first_column +size/2){
        if(this->bottom_left==NULL){this->bottom_left = new Puzzle(size/2, first_row + size/2 ,first_column);}
        this->bottom_left->placePiece(piece,indices);
    }
    else if(indices[0] < first_row + size/2 && indices[1] >= first_column + size/2){
        if(this->top_right==NULL){this->top_right = new Puzzle(size/2, first_row ,first_column + size/2); }
        this->top_right->placePiece(piece,indices);
    }
    else if(indices[0] >= first_row + size/2 && indices[1]>= first_column +size/2){
        if(this->bottom_right==NULL){this->bottom_right = new Puzzle(size/2, first_row + size/2,first_column + size/2); }
        this->bottom_right->placePiece(piece,indices);
    }
}

/* It returns directly the piece object located in the sub-puzzle (cell)
   whose row id and column id are given in the first and second elements of 
   2D array as argument, respectively. If there is no piece in the requested 
   indices, then this method throws an EmptyCellRequest exception defined in 
   Exception.h file.
*/
const Piece& Puzzle::getPiece(int indices[2]) const {
    // TODO
    if(this->size == 1) {
            return *(this->piece);
    }
    else if(indices[0] < first_row + size/2 && indices[1]< first_column +size/2){
        if(top_left!=NULL){this->top_left->getPiece(indices);} 
        else{throw EmptyCellRequest();}       
    }
    else if(indices[0] >= first_row + size/2 && indices[1]< first_column +size/2){
        if(bottom_left!= NULL){this->bottom_left->getPiece(indices);}
        else{throw EmptyCellRequest();} 
    }
    else if(indices[0] < first_row + size/2 && indices[1] >= first_column + size/2){
        if(top_right != NULL){this->top_right->getPiece(indices);}
        else{throw EmptyCellRequest();} 
    }
    else if(indices[0] >= first_row + size/2 && indices[1]>= first_column +size/2){
        if(bottom_right != NULL){this->bottom_right->getPiece(indices);}
        else{throw EmptyCellRequest();} 
    }
    
}

/* This method returns the sub-puzzle whose initial and final row-column ids 
   are given in the first and second arguments, respectively. The indices
   given in the arguments will be given as an exact correspondence to one of
   the sub-puzzles of the current puzzle object.
   
   ATTENTION: The sub-puzzle to be cropped may correspond to a NULL part of the
   Puzzle object. In that case, it is enough to you to create a new Puzzle 
   object that satisfies the asked properties and return it. OF course, do NOT 
   forget to do this operation by escaping from memory leaks!!!
*/
Puzzle Puzzle::crop(int from[2], int to[2]) const {
    // TODO
    int from_x = from[0];
    int from_y = from[1];
    int to_x = to[0];
    int to_y = to[1];
    int new_size = to[0] - from[0] +1;    
    if(this->size == new_size){
        return *this ;
    }

    if(from[0] < first_row + size/2 && from[1]< first_column +size/2){
        if(top_left!= NULL){return this->top_left->crop(from,to);}
        else{return Puzzle(size,from[0],from[1]);}
    }
    else if(from[0] >= first_row + size/2 && from[1]< first_column +size/2){
        if(bottom_left!= NULL){return this->bottom_left->crop(from,to);}
        else{return Puzzle(size,from[0],from[1]);}
    }
    else if(from[0] < first_row + size/2 && from[1] >= first_column + size/2){
        if(top_right!= NULL){return this->top_right->crop(from,to);}
        else{return Puzzle(size,from[0],from[1]);}
    }
    else if(from[0] >= first_row + size/2 && from[1]>= first_column +size/2){
        if(bottom_right!= NULL){return this->bottom_right->crop(from,to);}
        else{return Puzzle(size,0,0);}
    }
}

/****************************************************/
/*        THE BELOW PART WILL NOT BE GRADED.        */
/*      YOU CAN IMPLEMENT IF YOU WOULD LIKE TO.     */
/****************************************************/
/*
    This method puts (patches) the given puzzle onto the corresponding part
    of the current puzzle object. To which part it will be patched on could
    be determined by just checking the initial row-column indices and the size
    of the puzzle given in the argument. 
    Unlike crop() method, the puzzle given in the argument may not be an exact 
    correspondence of some sub-puzzle. It is ensured that the given argument will
    be located on some sub-space of the current puzzle, yet it may *partially* 
    overlap with some or more sub-puzzles (See the figure in the pdf).
    The patch operation requires deep-copy of the corresponding sub-puzzles
    whereas it requires shallow copy of the corresponding Piece objects.
    
    HINT: You may get benefit from placePiece() method and you may start your
    operation by clearing the corresponding parts of the current puzzle.
*/
void Puzzle::patch(const Puzzle&) {
    // TODO
}

