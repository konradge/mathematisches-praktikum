#include <cstddef>
#include <vector>

enum Player { YELLOW = 1, RED = 2 };

enum State { EMPTY_STATE, YELLOW_STATE, RED_STATE };
enum WinningState { UNFINISHED, YELLOW_WON, RED_WON, DRAW };

class Board {
 public:
  Board(size_t n, size_t m);
  Board(Board& b);

  bool hasWon(Player player) const;
  WinningState getWinningState() const;

  bool insert(size_t column, Player player);

  bool canInsert(size_t column) const;

  bool boardFilled() const;

  void clear();

  State operator()(size_t row, size_t col) const;
  State& operator()(size_t row, size_t col);

  size_t get_col_count() const { return col_count; }

  size_t get_row_depth() const { return row_depth; }

 private:
  size_t col_count, row_depth;

  // Each entry of the outter vector is one column of the board.
  // Each entry in the inner vector is one position in this column, where row=0
  // is the bottommost position.
  std::vector<std::vector<State>> board;
};