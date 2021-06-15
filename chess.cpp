#include <eosio/eosio.hpp>

using namespace eosio;


class[[eosio::contract("chess")]] chess : public contract
{

public:

    using contract::contract;

    chess(name reciever, name code, datastram<const char *> ds) : contract(reciever, code, ds) {}

   static constexpr name none = "none"_n;
   static constexpr name draw = "draw"_n;

   bool checkOnWhite = false;
   bool checkOnBlack = false;

    struct [[eosio::table]] game
    {
        static constexpr uint16_t boardWidth = 8;
        static constexpr uint16_t boardHeight = boardWidth;

        game() : board(boardWidth * boardHeight, 0){}

        name whitePlayer;
        name blackPlayer;
        name turn;
        name winner = none;

        std::vector<uint8_t> board;

        void initBoard()
        {
            board.assign(boardWidth * boardHeight, 0);

            // assign pieces at start


        }

        void resetGame()
        {
            //this game in infinite on time so if one player calls reset he/she would be the looser
            //who ever calls this is the looser its different from draw
        }
    };

    typedef eosio::multi_index<"games"_n, game> games;

    [[eosio::action]]
    void createNewGame(const name &whitePlayer, const name &blackPlayer);

    [[eosio::action]]
    void resetGame(const name aPlayer);

    // The position reaches a stalemate where it is one player's turn to move, but his king is NOT in check and yet he does not have another legal move:
    //The players may simply agree to a draw and stop playing
    // There are not enough pieces on the board to force a checkmate (example: a king and a bishop vs.a king)
    // A player declares a draw if the same exact position is repeated three times (though not necessarily three times in a row)
    // Fifty consecutive moves have been played where neither player has moved a pawn or captured a piece
    
    [[epsio::action]]
    void draw(const name aPlayer);

    [[eosio::action]]
    void move(const name aPlayer,
             const name pieceOneRowFrom,
             const name pieceOneColumFrom,
             const name peceOneRowTo,
             const name peceOneColumTo,
             //king jump move ONLY
             const name pieceTwoRowFrom,
             const name pieceTwoColumFrom,
             const name peceTwoRowTo,
             const name peceTwoColumTo, );

    // system actually doesnt check for "check" position it should called from player who "check" the other party
    [[eosio::action]]
    void check(const name aPlayer, const name piece)             


    private:
    /* data */

    assignPiecesAtStart();

    whichPieceAt();

// it must be that king's very first move
// it must be that rook's very first move
// there cannot be any pieces between the king and rook to move
// the king may not be in check or pass through check
    isItCastleMoveKingSide();
    isItCastleMoveQueenSide();

    //one user check flag is true their move has to be a get of the check move or it's a checkmate
    outOfCheckMove();

    isItCheckmate();

    isItenPassant();




    

};


