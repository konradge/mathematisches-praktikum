#include <vector>

enum Player { YELLOW = 1, RED = 2 };

enum State { EMPTY_STATE, YELLOW_STATE, RED_STATE };
enum WinningState { UNFINISHED, YELLOW_WON, RED_WON, DRAW };

class Board {
 public:
  Board(int n, int m);

  bool hasWon(Player player) const;
  WinningState getWinningState() const;

  bool insert(int column, Player player);

  bool boardFilled() const;

  void clear();

  State operator()(int row, int col) const;
  State& operator()(int row, int col);

 private:
  int col_count, row_depth;

  // Each entry of the outter vector is one column of the board.
  // Each entry in the inner vector is one position in this column, where row=0
  // is the bottommost position.
  std::vector<std::vector<State>> board;
};