#include <fstream>
#include <regex>
#include "matrix.h"

inline const char BETRAYAL_SYMBOL = 'D';

unsigned int get_index_of_row(const std::string& row){
    // Set "C" = 0, "D" = 1, so we code any string of "C"`s and "D"`s by binary string.
    // For example, in our notation "CCC" = 000, "DCD" = 101, "DDD" = 111
    // We sort all codes of 3 digits and define index of row as index of code of this string
    // For example, in out notation index of "CCC" = 0, index of "DCD" = 6, index of "DDD" = 7

    return (row[0] == BETRAYAL_SYMBOL) * 4 + (row[1] == BETRAYAL_SYMBOL) * 2 + (row[2] == BETRAYAL_SYMBOL);
}

bool is_matrix_file_valid(std::ifstream& ifstream){
    static const std::regex useless_reg(R"((//.*)|(\s*))");
    static const std::regex row_reg(R"(\s*[CD]\s+[CD]\s+[CD]\s+-?\d+\s+-?\d+\s+-?\d+(\s*|\s+//.*))");

    unsigned int rows_count = 0;
    while(!ifstream.eof()){
        std::string current_row;

        std::getline(ifstream, current_row);

        if (std::regex_match(current_row.data(), useless_reg)){
            continue;
        }

        if (std::regex_match(current_row.data(), row_reg)){
            rows_count++;
            continue;
        }

        return false;
    }

    return rows_count == ROWS_COUNT;
}

Matrix::Matrix(const std::string& path){
    std::ifstream ifstream(path);

    if (!ifstream.is_open()){
        _has_error = true;
        return;
    }

    _has_error = !is_matrix_file_valid(ifstream);

    if (!_has_error){

    }

    ifstream.close();
}

bool Matrix::has_error() const{
    return _has_error;
}

bool Matrix::is_consistent() const{
    const int c0 = std::get<0>(_rows[0]);
    const int c1 = std::get<0>(_rows[1]);
    const int c2 = std::get<0>(_rows[3]);

    const int d0 = std::get<2>(_rows[1]);
    const int d1 = std::get<1>(_rows[3]);
    const int d2 = std::get<0>(_rows[7]);

    // These tell that cooperation is more beneficial in a long game
    const bool inequality1 = (3 * c0 > 2 * c1 + d0);
    const bool inequality2 = (3 * c0 > 2 * d1 + c2);

    // This sets relations between betrayal and cooperation
    const bool inequality3 = (d0 > c0) && (c1 > d1) && (d1 > c1) && (c1 > d2) && (d2 > c2);

    return inequality1 && inequality2 && inequality3;
}

const Row& Matrix::get_row(const std::string& string) const{
    return _rows[get_index_of_row(string)];
}
