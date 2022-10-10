#pragma once

#include <array>
#include <string>

using Row = std::array<int, 3>; // 3 values in each row
inline const unsigned int ROWS_COUNT = 8;

class Matrix{
private:
    Row _rows[ROWS_COUNT];
    bool _has_error;

    void input(std::ifstream& ifstream);

    [[nodiscard]] bool is_symmetric() const;
public:
    explicit Matrix(const std::string& path);

    [[nodiscard]] bool has_error() const; // Have errors occurred during initialization

    [[nodiscard]] bool is_consistent() const; // Checks inequalities

    [[nodiscard]] const Row& get_row(const std::string& row_code) const; // receives "CCC", "CCD" ...

    [[nodiscard]] int get_element(const std::string& row_code, int index_in_row) const;
};
