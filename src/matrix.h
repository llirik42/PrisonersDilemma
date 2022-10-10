#pragma once

#include <tuple>
#include <string>

using Row = std::tuple<int, int, int>;
inline const unsigned int ROWS_COUNT = 8;

class Matrix{
private:
    Row _rows[ROWS_COUNT];
    bool _has_error;

    void input_matrix(std::ifstream& ifstream);

    [[nodiscard]] bool is_symmetric() const;
public:
    explicit Matrix(const std::string& path);

    [[nodiscard]] bool has_error() const; // Have errors occurred during initialization

    [[nodiscard]] bool is_consistent() const; // Checks inequalities

    [[nodiscard]] const Row& get_row(const std::string& string) const; // receives "CCC", "CCD" ...
};
