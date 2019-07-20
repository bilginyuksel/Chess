#include <iostream>
#include <vector>
#include <math.h>

// enum columns{a,b,c,d,e,f,g,h};
enum GameStatus{ACTIVE=100,GAMEOVER,STALEMATE};
enum PlayerStatus{NORMAL=50,CHECK,CHECKMATE};

// abstract piece class
class CPiece{
private:
    char representation;
    bool isWhite;
    int rank;

public:
    CPiece(){}
    CPiece(char r,int rank,bool isw){
        representation = r; isWhite =isw; this->rank = rank;
    }
    bool getColor(){ return isWhite;}
    char getRep(){return representation;}
    virtual bool canMove(int ,int ,int ,int ,CPiece *board[8][8]) = 0; // Check if piece's move is legal or not
};


class CPawn : public CPiece{
public:
    CPawn(){}
    CPawn(bool isw):CPiece('p',1,isw){}
    bool canMove(int ,int,int,int,CPiece* board[8][8]);
};

class CBishop : public CPiece{
public:
    CBishop(){}
    CBishop(bool isw) : CPiece('b',3,isw){}
    bool canMove(int,int,int,int,CPiece *board[8][8]);
};

class CKnight : public CPiece{
public:
    CKnight(){}
    CKnight(bool isw) : CPiece('k',3,isw){}
    bool canMove(int,int,int,int,CPiece *board[8][8]);


};

class CRook : public CPiece{
public:
    CRook(){}
    CRook(bool isw) : CPiece('r',5,isw){}
    bool canMove(int,int,int,int,CPiece *board[8][8]);

};
class CQueen : public CPiece{
public:
    CQueen(){}
    CQueen(bool isw) : CPiece('Q',9,isw){}
    bool canMove(int,int,int,int,CPiece *board[8][8]);

};

class CKing : public CPiece {
public:
    CKing(){}
    CKing(bool isw) : CPiece('K',0,isw){}
    bool canMove(int,int,int,int,CPiece *board[8][8]);

};


class CBoard{
public:
    CPiece *board[8][8];

    CBoard(); //Config pieces
    void display();
    bool isCheck(); // Check for every move... # And every turnover

};

class CPlayer{
private:
    std::string nick;
    bool color;
    int score;
    PlayerStatus pS;
    std::vector< std::string > moves;

public:
    CPlayer(){
        score = 0;
        pS = NORMAL;
    }
    void setStatus(PlayerStatus s){
        pS = s;
    }
    std::string showStatus(){
        if(pS==NORMAL)
            return " NORMAL";
        else if(pS == CHECK)
            return " CHECK";
        else if(pS == CHECKMATE)
            return " CHECK MATE";
    }
    void addMove(std::string move){
        moves.push_back(move);
    }
    void setColor(bool c){color=c;}
    bool getColor(){return color;}
};

class CChess{
private:
    CBoard gBoard;
    bool turn;
    GameStatus gS;
    CPlayer player1; // plays white pieces
    CPlayer player2; // plays black pieces

    void nextTurn(){this->turn = !turn;}

public:
    CChess(){
        // Starting conditions
        player1.setColor(true); player2.setColor(false);
        gS=ACTIVE;
        turn = true;
    }
    void start();
    void move(std::string,CPiece* board[8][8]);
    bool isCheck(CPiece* board[8][8]);

};

