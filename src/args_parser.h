#pragma once

#include <vector>
#include <string>
#include "strategies_factory.h"
#include "utils.h"

enum ParsingStatus{
    SUCCESS,
    TOO_FEW_ARGS,
    TOO_MANY_ARGS,
    HELP_IS_NOT_ONLY_ARG,
    INCORRECT_STRATEGIES,
    INCORRECT_MODE,
    INCORRECT_STEPS_COUNT,
    INCORRECT_MATRIX_PATH
};

class ArgsParser{
private:
    std::vector<std::string> _strategies_titles;
    unsigned int _steps_count;
    std::string _matrix_file_path;
    GameMode _game_mode;
    ParsingStatus _parsing_status;
    bool _help;
public:
    ArgsParser(int arc, char** argv, const StrategiesDescription& strategies_description);

    [[nodiscard]] ParsingStatus get_parsing_status() const;
    [[nodiscard]] bool is_help_mode() const;

    [[nodiscard]] const std::vector<std::string>& get_strategies_titles() const;
    [[nodiscard]] unsigned int get_steps_count() const;
    [[nodiscard]] const std::string& get_matrix_file_path() const;
    [[nodiscard]] GameMode get_game_mode() const;
};
