#include <fstream>
#include <regex>
#include <map>
#include "matrix.h"
#include "utils.h"

inline const char BETRAYAL_SYMBOL = 'D';

std::map<std::string, int> STRING_TO_ROW_INDEX{
    {"CCC", 0},
    {"CCD", 1},
    {"CDC", 2},
    {"CDD", 3},
    {"DCC", 4},
    {"DCD", 5},
    {"DDC", 6},
    {"DDD", 7},
    };

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

void Matrix::input(std::ifstream& ifstream){
    ifstream.clear();
    ifstream.seekg(0);

    while(!ifstream.eof()){
        std::string current_row_string;

        std::string current_row_code;

        std::getline(ifstream, current_row_string);

        static const std::regex useless_reg(R"((//.*)|(\s*))");
        static const std::regex row_reg(R"(\s*[CD]\s+[CD]\s+[CD]\s+-?\d+\s+-?\d+\s+-?\d+(\s*|\s+//.*))");

        std::regex numbers_regex(R"((-*[1-9]\d*)|0)");
        std::regex letters_regex(R"([CD])");

        if (std::regex_match(current_row_string.data(), useless_reg)){
            continue;
        }

        std::smatch match1;
        std::string::const_iterator searchStart1(current_row_string.cbegin());

        for (unsigned int i = 0; i < 3; i++){
            regex_search(searchStart1, current_row_string.cend(), match1, letters_regex);
            current_row_code.append(match1[0]);
            searchStart1 = match1.suffix().first;
        }

        const unsigned int index_of_row = STRING_TO_ROW_INDEX[current_row_code];

        std::smatch match2;
        std::string::const_iterator searchStart2(current_row_string.cbegin());

        for (unsigned int i = 0; i < 3; i++){
            regex_search(searchStart2, current_row_string.cend(), match2, numbers_regex);
            _rows[index_of_row][i] = std::stoi(match2[0]);
            searchStart2 = match2.suffix().first;
        }
    }
}

bool Matrix::is_symmetric() const{
    // Checks matrix for symmetry
    // For example, in row "CCC" all 3 values must be equal
    // In rows "CCD", "DCC", "CDC" values of single "D" must be equal and ...

    // values of "CCC" row
    const int c01 = get_element("CCC", 0);
    const int c02 = get_element("CCC", 1);
    const int c03 = get_element("CCC", 2);
    const bool equality_1 = c01 == c02 && c01 == c03;

    // values of C`s where 2 C's and 1 D
    const int c11 = get_element("CCD", 0);
    const int c12 = get_element("CCD", 1);
    const int c13 = get_element("CDC", 0);
    const int c14 = get_element("CDC", 2);
    const int c15 = get_element("DCC", 1);
    const int c16 = get_element("DCC", 2);
    const bool equality_2 = c11 == c12 && c11 == c13 && c11 == c14 && c11 == c15 && c11 == c16;

    // values of C`s where 1 C and 2 D`s
    const int c21 = get_element("CDD", 0);
    const int c22 = get_element("DCD", 1);
    const int c23 = get_element("DDC", 2);
    const bool equality_3 = c21 == c22 && c21 == c23;

    // values of D`s where 1 D and 2 C`s
    const int d01 = get_element("CCD", 2);
    const int d02 = get_element("CDC", 1);
    const int d03 = get_element("DCC", 0);
    const bool equality_4 = d01 == d02 && d01 == d03;

    // values of D`s where 2 D's and 1 C
    const int d11 = get_element("CDD", 1);
    const int d12 = get_element("CDD", 2);
    const int d13 = get_element("DCD", 0);
    const int d14 = get_element("DCD", 2);
    const int d15 = get_element("DDC", 0);
    const int d16 = get_element("DDC", 1);
    const bool equality_5 = d11 == d12 && d11 == d13 && d11 == d14 && d11 == d15 && d11 == d16;

    // values of "DDD" row
    const int d21 = get_element("DDD", 0);
    const int d22 = get_element("DDD", 1);
    const int d23 = get_element("DDD", 2);
    const bool equality_6 = d21 == d22 && d21 == d23;

    return equality_1 && equality_2 && equality_3 && equality_4 && equality_5 && equality_6;
}

Matrix::Matrix(const std::string& path){
    std::ifstream ifstream(path);

    if (!ifstream.is_open()){
        _has_error = true;
        return;
    }

    _has_error = !is_matrix_file_valid(ifstream);

    if (!_has_error){
        input(ifstream);
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

    const int c0 = get_element("CCC", 0);
    const int c1 = get_element("CCD", 0);
    const int c2 = get_element("CDD", 0);

    const int d0 = get_element("CCD", 2);
    const int d1 = get_element("DCD", 0);
    const int d2 = get_element("DDD", 0);

    // These tell that cooperation is more beneficial in a long game
    const bool inequality_1 = (3 * c0 > 2 * c1 + d0);
    const bool inequality_2 = (3 * c0 > 2 * d1 + c2);

    // This sets relations between betrayal and cooperation
    const bool inequality_3 = (d0 > c0) && (c0 > d1) && (d1 > c1) && (c1 > d2) && (d2 > c2);

    return inequality_1 && inequality_2 && inequality_3;
}

const Row& Matrix::get_row(const std::string& row_code) const{
    return _rows[STRING_TO_ROW_INDEX[row_code]];
}

int Matrix::get_element(const std::string& row_code, int index_in_row) const{
    return get_row(row_code)[index_in_row];
}
