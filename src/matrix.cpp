#include "matrix.h"
#include <fstream>

inline const char BETRAYAL_SYMBOL = 'D';
inline const unsigned int ROWS_COUNT = 8;
inline const unsigned int PLAYERS_COUNT = 3;

unsigned int get_index_of_row(const std::string& row){
    // Set "C" = 0, "D" = 1, so we code any string of "C"`s and "D"`s by binary string.
    // For example, in our notation "CCC" = 000, "DCD" = 101, "DDD" = 111
    // We sort all codes of 3 digits and define index of row as index of code of this string
    // For example, in out notation index of "CCC" = 0, index of "DCD" = 6, index of "DDD" = 7

    return (row[0] == BETRAYAL_SYMBOL) * 4 + (row[1] == BETRAYAL_SYMBOL) * 2 + (row[2] == BETRAYAL_SYMBOL);
}

Matrix::Matrix(const std::string& path){



    /*
    for (unsigned int i = 0; i < 8; i++){
        std::string current_row;

        for (unsigned int j = 0; j < PLAYERS_COUNT; j++){
            ifstream >> current_row[j];
        }

        const unsigned int index_of_current_row = get_index_of_row(current_row);



        ifstream >> current_row[]
    }









    _rows[0] = Row(1, 2, 3);
    _rows[1] = Row(1, 2, 3);
    _rows[2] = Row(1, 2, 3);
    _rows[3] = Row(1, 2, 3);
    _rows[4] = Row(1, 2, 3);
    _rows[5] = Row(1, 2, 3);
    _rows[6] = Row(1, 2, 3);
    _rows[7] = Row(1, 2, 3);
    */
    _has_error = path[0] == 'c';
}

bool Matrix::has_error() const{
    return true;

    return _has_error;
}

bool Matrix::is_consistent() const{
    return false;
}

const Row& Matrix::get_row(const std::string& string) const{
    return _rows[get_index_of_row(string)];
}
