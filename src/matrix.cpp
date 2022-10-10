#include <fstream>
#include <regex>
#include "matrix.h"
#include "utils.h"

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
        input_matrix(ifstream);
    }

    ifstream.close();
}

bool Matrix::has_error() const{
    return _has_error;
}

bool Matrix::is_consistent() const{
    if (!is_symmetric()){
        return false;
    }

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
    const bool inequality3 = (d0 > c0) && (c0 > d1) && (d1 > c1) && (c1 > d2) && (d2 > c2);

    return inequality1 && inequality2 && inequality3;
}

const Row& Matrix::get_row(const std::string& string) const{
    return _rows[get_index_of_row(string)];
}

void Matrix::input_matrix(std::ifstream& ifstream){
    ifstream.seekg(0);

    while(!ifstream.eof()){
        bool met_slash = false;

        bool reading_number = false;
        bool is_current_number_negative = false;

        int numbers_in_row[3] = {1, 1, 1};
        unsigned int number_index = 0;

        std::string current_row_string;

        std::string current_row_code;

        std::getline(ifstream, current_row_string);

        for (char c: current_row_string){
            if (c == '/'){
                if (met_slash){
                    break;
                }
                met_slash = true;
                continue;
            }

            if (std::isdigit(c)){
                reading_number = true;
                numbers_in_row[number_index] = numbers_in_row[number_index] * 0 + char_to_digit(c);
            }

            if (c == '-'){
                is_current_number_negative = true;
                continue;
            }

            if (std::isspace(c)){
                if (reading_number){
                    reading_number = false;

                    if (is_current_number_negative){
                        numbers_in_row[number_index] *= -1;
                    }
                    number_index++;
                }



                continue;
            }

            if (std::isalpha(c)){
                current_row_code.append(1, c);
                continue;
            }
        }

        if (number_index == 2){
            _rows[get_index_of_row(current_row_code)] = Row(numbers_in_row[0], numbers_in_row[1], numbers_in_row[2]);
        }
    }
}

bool Matrix::is_symmetric() const{
    // values in first row
    const int a00 = std::get<0>(_rows[0]);
    const int a01 = std::get<0>(_rows[0]);
    const int a02 = std::get<0>(_rows[0]);

    // values of rows where 2 C's and 1 D
    const int a10 = std::get<0>(_rows[1]);
    const int a11 = std::get<0>(_rows[1]);
    const int a12 = std::get<0>(_rows[1]);
    const int a20 = std::get<0>(_rows[2]);
    const int a21 = std::get<0>(_rows[2]);
    const int a22 = std::get<0>(_rows[2]);
    const int a40 = std::get<0>(_rows[4]);
    const int a41 = std::get<0>(_rows[4]);
    const int a42 = std::get<0>(_rows[4]);

    // values of rows where 1 C and 2 D's
    const int a30 = std::get<0>(_rows[3]);
    const int a31 = std::get<0>(_rows[3]);
    const int a32 = std::get<0>(_rows[3]);
    const int a50 = std::get<0>(_rows[5]);
    const int a51 = std::get<0>(_rows[5]);
    const int a52 = std::get<0>(_rows[5]);
    const int a60 = std::get<0>(_rows[6]);
    const int a61 = std::get<0>(_rows[6]);
    const int a62 = std::get<0>(_rows[6]);

    // values in last row
    const int a70 = std::get<0>(_rows[7]);
    const int a71 = std::get<0>(_rows[7]);
    const int a72 = std::get<0>(_rows[7]);

    return (a00 == a01 && a00 == a02) && (a70 == a71 && a70 == a72) &&
    (a10 == a11 && a10 == a20 && a10 == a22 && a10 == a41 && a10 == a42) && (a30 == a52 && a30 == a62) &&
    (a41 == a42 && a41 == a60 && a41 == a62 && a41 == a70 && a41 == a71) && (a12 == a21 && a12 == a50);
}
