#include <bits/stdc++.h>
#include <windows.h>

// ----------------------------------------HELPER FUNCTIONS --------------------------------------
int get_random_number(int maxLimit) {
    return rand() % maxLimit;
}
bool find_unassigned_location(std::vector<std::vector<int>> &grid, int & row, int & col) {
    for (row = 0; row < 9; row++) {
        for (col = 0; col < 9; col++) {
            if (grid[row][col] == 0)
                return true;
        }
    }

    return false;
}
bool used_in_row(std::vector<std::vector<int>> &grid, int row, int num) {
    for (int col = 0; col < 9; col++) {
        if (grid[row][col] == num)
            return true;
    }

    return false;
}
bool used_in_col(std::vector<std::vector<int>> &grid, int col, int num) {
    for (int row = 0; row < 9; row++) {
        if (grid[row][col] == num)
            return true;
    }

    return false;
}
bool used_in_box(std::vector<std::vector<int>> &grid, int box_row, int box_col, int num) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (grid[row + box_row][col + box_col] == num)
                return true;
        }
    }

    return false;
}
bool is_safe(std::vector<std::vector<int>> &grid, int row, int col, int num) {
    return !used_in_row(grid, row, num) && !used_in_col(grid, col, num) && 
            !used_in_box(grid, row - row % 3, col - col % 3, num);
}
// -----------------------------------------------------------------------------------------------

class Sudoku {
 private:
    std::vector<std::vector<int>> grid;
    std::vector<std::vector<int>> soln_grid;
    std::vector<int> guess_num;
    std::vector<int> grid_pos;
    bool grid_status;

 public:
    // Sudoku();
    // void create_seed();
    // void print_grid();
    // bool solve_grid();
    // std::string get_grid();
    // void count_soln(int & number);
    // void gen_puzzle();
    // bool verify_grid_status(); 

    Sudoku() {
        this -> grid.assign(9, std::vector<int> (9, 0));
        this -> soln_grid.assign(9, std::vector<int> (9, 0));
        this -> guess_num.assign(9, 0);
        this -> grid_pos.assign(81, 0);
        this -> grid_status = false;

        iota((this -> grid_pos).begin(), (this -> grid_pos).end(), 0);
        std::random_shuffle((this -> grid_pos).begin(), (this -> grid_pos).end(), get_random_number);

        iota((this -> guess_num).begin(), (this -> guess_num).end(), 1);
        std::random_shuffle((this -> guess_num).begin(), (this -> guess_num).end(), get_random_number);

        this -> grid_status = true;
    }

    void create_seed() {
        this -> solve_grid();

        for (int row = 0; row < 9; row++) {
            for (int column = 0; column < 9; column++) {
                this -> soln_grid[row][column] = this -> grid[row][column];
            }
        }
    }

    std::string get_grid() {
        std::string s;
        for (int row = 0; row < 9; row++) {
            for (int column = 0; column < 9; column++) {
                s += std::to_string(grid[row][column]);
            }
        }

        return s;
    }

    bool verify_grid_status() {
        return grid_status;
    }

    void print_grid() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (grid[i][j] == 0)
                    std::cout << ".";
                else
                    std::cout << grid[i][j];
                std::cout << "|";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        std::cout << "Solution for the sudoku is : \n";
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                std::cout << soln_grid[i][j] << "|";
            }
            std::cout << std::endl;
        }

        std::cout << std::endl;
    }


    bool solve_grid() {
        int row, col;

        if (!find_unassigned_location(this -> grid, row, col))
            return true;

        for (int num = 0; num < 9; num++) {
            if (is_safe(this -> grid, row, col, this -> guess_num[num])) {
                this -> grid[row][col] = this -> guess_num[num];
                if (solve_grid())
                    return true;
                this -> grid[row][col] = 0;
            }
        }

        return false;
    }

    void count_soln(int & number) {
        int row, col;

        if (!find_unassigned_location(this -> grid, row, col)) {
            number++;
            return;
        }

        for (int i = 0; i < 9 && number < 2; i++) {
            if (is_safe(this -> grid, row, col, this -> guess_num[i])) {
                this -> grid[row][col] = this -> guess_num[i];
                count_soln(number);
            }

            this -> grid[row][col] = 0;
        }
    }

    void gen_puzzle() {
        for (int i = 0; i < 81; i++) {
            int x = (this -> grid_pos[i]) / 9;
            int y = (this -> grid_pos[i]) % 9;
            int temp = this -> grid[x][y];
            this -> grid[x][y] = 0;

            int check = 0;
            count_soln(check);
            if (check != 1) {
                this -> grid[x][y] = temp;
            }
        }
    }
};


// std::vector<std::string> original;
// std::vector<std::string> Board = {
//     "_ | _ | _ | _ | _ | _ | _ | _ | _ |",
//     "_ | _ | _ | _ | _ | _ | _ | _ | _ |",
//     "_ | _ | _ | _ | _ | _ | _ | _ | _ |",
//     "_ | _ | _ | _ | _ | _ | _ | _ | _ |",
//     "_ | _ | _ | _ | _ | _ | _ | _ | _ |",
//     "_ | _ | _ | _ | _ | _ | _ | _ | _ |",
//     "_ | _ | _ | _ | _ | _ | _ | _ | _ |",
//     "_ | _ | _ | _ | _ | _ | _ | _ | _ |",
//     "_ | _ | _ | _ | _ | _ | _ | _ | _ |",
//     "_ | _ | _ | _ | _ | _ | _ | _ | _ |",
// };


signed main() {
    srand(time(NULL));

    Sudoku *puzzle = new Sudoku();
    puzzle -> create_seed();
    puzzle -> gen_puzzle();
    puzzle -> print_grid();

    return 0;
}
