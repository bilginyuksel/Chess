#include "chess.h"

CBoard :: CBoard(){
    // config board. Set pieces start formation.
    for (int x = 0; x < 8; ++x) {
			for (int y = 0; y < 8; ++y) {
				board[x][y] = nullptr;
			}
	}
	// Allocate and place black pieces
	for (int y = 0; y < 8; ++y) {
		board[6][y] = new CPawn(false);
	}
	board[7][0] = new CRook(false);
	board[7][1] = new CKnight(false);
	board[7][2] = new CBishop(false);
	board[7][3] = new CKing(false);
	board[7][4] = new CQueen(false);
	board[7][5] = new CBishop(false);
	board[7][6] = new CKnight(false);
	board[7][7] = new CRook(false);
	// Allocate and place white pieces
	for (int y = 0; y < 8; ++y) {
		board[1][y] = new CPawn(true);
	}
	board[0][0] = new CRook(true);
	board[0][1] = new CKnight(true);
	board[0][2] = new CBishop(true);
	board[0][3] = new CKing(true);
    board[0][4] = new CQueen(true);
	board[0][5] = new CBishop(true);
	board[0][6] = new CKnight(true);
	board[0][7] = new CRook(true);
}

void CBoard :: display(){
    std::cout<<"a b c d e f g h"<<std::endl;
    for (int i=0;i<8;i++) {
        for(int j=0;j<8;j++) {
            if(board[i][j]==nullptr){
            std::cout<<"  ";
        } else std::cout<<(char)board[i][j]->getRep()<<" ";
        
        }
        std::cout<<" "<<i+1<<std::endl;
    }
}

bool CPawn :: canMove(int currX,int currY,int destX,int destY,CPiece *board[8][8]){

    // find distance
    int dist = destX-currX;

    // early check for minimum wasting time.
    if(dist>1 || dist<-1) return false;

    // If distance is negative than it should be black pawn or it is invalid move
    if(dist<0 && getColor()==false) {
        // black moving
        if(board[destX][destY]==nullptr){
            // empty square move forward
            return true;
        }else if(board[destX][destY]!=nullptr && destY==currY)return false;
        // not empty square it means trying to eat something
        // check if it has not the same color go on it.
        return (board[destX][destY]!=nullptr && board[destX][destY]->getColor()!=getColor())?true:false;

    } else if(dist>0 && getColor()==true){    // If distance is positive than it should be black pawn or it is invalid move
        // white pawn moving forward
        if(board[destX][destY]==nullptr){
            // empty square move forward
            return true;
        }else if(board[destX][destY]!=nullptr && destY==currY)return false;
        // not empty square it means trying to eat something
        // check if it has not the same color go on it.
        return (board[destX][destY]!=nullptr && board[destX][destY]->getColor()!=getColor())?true:false;

        
    }    

    return false;

}


bool CRook :: canMove(int currX,int currY,int destX,int destY,CPiece *board[8][8]){
    // Rook can only move one axis for that move
    // Doesn't matter if its Y or X.

    // early check 
    if(currX != destX && currY!=destY) return false;
    // Checks if same color not null piece at same destination it returns false.
    if(board[destX][destY]!=nullptr && board[destX][destY]->getColor()==getColor()) return false;
    
    
    // now check if some piece here or not but first take the distance
    // and find which direction rook moves.
    int distance; // decleare distance

    if(currX == destX && currY != destY ){
        //  moving on axis Y
        distance = destY- currY; // initialize distance
        std::cout<<"X Equal Distance : "<<distance<<std::endl;
        if(distance<0){
            for(int i = destY+1; i<currY;i++){
                // move on board columns
                // check if someone here or not
                if(board[currX][i]!=nullptr) return false;
            }
        }else{
            for(int i = currY+1; i<destY;i++){
                // move on board columns
                // check if someone here or not
                if(board[currX][i]!=nullptr) return false;
            }
        }
        return true;  
    }
    else if(currY == destY && currX != destX){
        // moving on axis X
        distance = destX- currX; // initialize distance
        std::cout<<"Y Equal Distance : "<<distance<<std::endl;

        if(distance<0){
            for(int i = destX+1; i<currX;i++){
                // move on board rows
                // check if someone here or not
                if(board[i][currY]!=nullptr) return false;
            }
        }else{
            for(int i = currX+1; i<destX;i++){
                // move on board rows
                // check if someone here or not
                if(board[i][currY]!=nullptr) return false;
            }
        }
        return true;  
    }

    return true;
}


bool CBishop :: canMove(int currX,int currY,int destX,int destY,CPiece *board[8][8]){
    // Bishop can move 4 situation
    // first check if someone same color with you on the destination point
    if(board[destX][destY]!=nullptr && board[destX][destY]->getColor()==getColor()) return false;
    if(abs(destX-currX) != abs(destY-currY)) return false;

    // then if destination point is nullptr. Or not has the same color
    // x++ y++ situation
    if(destX>currX && destY>currY){
        for(int i=currX+1,j=currY+1;i<destX;i++,j++){
            if(board[i][j]!=nullptr) return false;
        }
    }
    // x++ y-- situation
    else if(destX>currX && destY<currY){
        for(int i=currX+1,j=currY-1;i<destX,j>destY;i++,j--){
            if(board[i][j]!=nullptr) return false;
        }
    }
    // x-- y-- situation
    else if(destX<currX && destY<currY){
        for(int i=currX-1,j=currY-1;i>destX,j>destY;i--,j--){
            if(board[i][j]!=nullptr) return false;
        }
    }
    // x-- y++ situation
    else if(destX<currX && destY>currY){
        for(int i=currX-1,j=currY+1;i>destX,j<destY;i--,j++){
            if(board[i][j]!=nullptr) return false;
        }
    }

    return true;
}

bool CQueen :: canMove(int currX, int currY, int destX, int destY, CPiece *board[8][8]){
    // Check if the destination object has the same color
    if(board[destX][destY]!= nullptr && board[destX][destY]->getColor() == getColor()) return false;

    // Queen can move like bishop or queen can move like a rook.
    // So we have to check both situations for queen.
    // If we think rook moving logic we have to focus columns or row one of them
    // have to equal and the other one increasing or decreasing.
    // And also bishop has 4 situations on moving logic (x++,y--),(x++,y++),(x--,y--),(x--,y++)
    
    // moving at X axis ### LIKE A ROOK
    if(destY == currY && destX!=currX){
        if(destX>currX){
            // going positive direction at x axis
            for(int i=currX+1;i<destX;i++)
                if(board[i][destY]!=nullptr) return false;
        }else{
            //going negative direction at x axis
            for(int i=currX-1;i>destX;i--)
                if(board[i][destY]!=nullptr) return false;
        }
    }
    // moving at Y axis. ### LIKE A ROOK
    else if(destX==currX && currY!=destY){
        if(destY>currY){
            // going positive direction at y axis
            for(int i=currY+1;i<destY;i++)
                if(board[destX][i]!=nullptr)return false;
        }else{
            // going negative direction at y axis
            for(int i=currY-1;i>destY;i--)
                if(board[destX][i]!=nullptr)return false;
        }
    }
    else if(abs(destX-currX)!=abs(destY-currY)) return false;
    // x++ y++ situation ### LIKE A BISHOP
    else if(destX>currX && destY>currY ){
        for(int i=currX+1,j=currY+1;i<destX;i++,j++){
            if(board[i][j]!=nullptr) return false;
        }
    }
    // x++ y-- situation ### LIKE A BISHOP
    else if(destX>currX && destY<currY ){
        for(int i=currX+1,j=currY-1;i<destX,j>destY;i++,j--){
            if(board[i][j]!=nullptr) return false;
        }
    }
    // x-- y-- situation ### LIKE A BISHOP
    else if(destX<currX && destY<currY ){
        for(int i=currX-1,j=currY-1;i>destX,j>destY;i--,j--){
            if(board[i][j]!=nullptr) return false;
        }
    }
    // x-- y++ situation ### LIKE A BISHOP
    else if(destX<currX && destY>currY ){
        for(int i=currX-1,j=currY+1;i>destX,j<destY;i--,j++){
            if(board[i][j]!=nullptr) return false;
        }
    }

    return true;
}

bool CKnight :: canMove(int currX, int currY, int destX, int destY, CPiece *board[8][8]){
    // Knight moves L shape to everywhere.

    //Chech if some piece with the same color present on the target square
    if(board[destX][destY]!=nullptr && board[destX][destY]->getColor()==getColor()) return false;

    // In Knight position you can move at most 8 possible places.
    // Suppose you are at row x and column y. You can never land the same row or the same column.
    // distance always should be sqrt(5)
    double distance = sqrt(pow(currX-destX,2)+pow(currY-destY,2));
    // std::cout<<"CKnight Distance : "<<distance<<std::endl;
    // it has to 2,1 all the time so distance has to root(5) equal to 2.36...
    if(distance!=sqrt(5) || currX==destX || currY==destY) return false;


    return true;
}

bool CKing :: canMove(int currX, int currY, int destX, int destY, CPiece *board[8][8]){
    // Check if same color piece at the destination
    if(board[destX][destY]!=nullptr && board[destX][destY]->getColor()==getColor()) return false;

    // King can play everywhere 1 square
    // so calculate the distance
    int dist = sqrt(pow(currX-destX,2)+pow(currY-destY,2));
    // std::cout<<"King Distance : "<<dist<<std::endl;
    if(dist!=1) return false;

   
    return true;
}

void CChess :: start(){
    do{
        std::string move_info;
        std::cin>>move_info;
        move(move_info,gBoard.board); // change turn in move.
        if(isCheck(gBoard.board)) s=CHECK;
        gBoard.display();
    }while((s != GAMEOVER) ||  (s !=STALEMATE));
}


void CChess :: move(std::string m,CPiece* board[8][8]){
    // substring string
    // a b c d e f g h// 0 1 2 3 4 5 6 7
    std::string currCol=m.substr(0,1);
    int currX=std::stoi(m.substr(1,1));
    std::string destCol=m.substr(2,1);
    int destX=std::stoi(m.substr(3,1));
    std::string columns[] = {"a","b","c","d","e","f","g","h"};
    int currY=0;
    int destY = 0;
    int counter=0;
    for(std::string col : columns){
        if(destCol == col) destY = counter;
        if(currCol == col) currY = counter;
        ++counter;
    }
    // substring string
    --currX; --destX;
    // Test purposes....
    // std::cout<<"CurrX : "<<currX<<std::endl;
    // std::cout<<"CurrY : "<<currY<<std::endl;
    // std::cout<<"DestX : "<<destX<<std::endl;
    // std::cout<<"DestY : "<<destY<<std::endl;
    
    // check if move is valid or not
    bool isValid = board[currX][currY]->canMove(currX,currY,destX,destY,board);

    
    if(isValid){
        std::cout<<"Valid."<<std::endl;
        // whose turn is it, just add move to player's move.
        turn?player1.addMove(m):player2.addMove(m);
        // for eat situation (kill the piece) we have to check move valid until the last destination**

        // auto swap = [board]()-> void{
            
        // };
        // auto undoSwap = [board]()->void{

        // };


        // swap elements to that position
        board[destX][destY] = board[currX][currY];
        board[currX][currY] = nullptr;
        // check if isCheck after you moved the pieces
        // invalid move

        if(isCheck(board)); 
        else nextTurn();

    }else{
        std::cout<<"Invalid."<<std::endl;
        // repeat move. this move is invalid.
    }

}

bool CChess :: isCheck(CPiece* board[8][8]){
    // find the kings position for player which who plays!!
    //if turn==true, then its white player player1
    // if turn==false, then its black player player2
    CPlayer currentPlayer = turn?player1:player2;
    int kingX=0,kingY=0;
    for(int i=0;i<8;i++) {
        for(int j=0;j<8;j++){ 
            if(board[i][j]!=nullptr && board[i][j]->getRep()=='K' && board[i][j]->getColor()==currentPlayer.getColor()){
                kingX = i; kingY =j; break;
            }
        }
    }
    // std::cout<<"king x : "<<kingX<<", king y: "<<kingY<<std::endl;
    // after finding king position attack all opponents which hasn't the same color with the king
    // if attacker returns true its isCheck position.
    for(int x=0;x<8;x++){
        for(int y=0;y<8;y++){
            if(board[x][y]!=nullptr && board[x][y]->canMove(x,y,kingX,kingY,board)){
                // std::cout<<"piece : "<<board[x][y]->getRep()<<std::endl;
                // std::cout<<"color : "<<board[x][y]->getColor()<<std::endl;
                // std::cout<<"x: "<<x<<", y: "<<y<<std::endl;
                return true;
            }
        }
    }
    return false;
}

int main(){
    CChess game;
    game.start();
    

    return 0;
}