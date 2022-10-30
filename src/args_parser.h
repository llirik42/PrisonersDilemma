#pragma once

#include <vector>
#include <string>
#include <map>
#include "utils.h"

enum ParsingStatus{
    SUCCESS,
    TOO_FEW_ARGS,
    REPEATED_ARGS,
    HELP_IS_NOT_ONLY_ARG,
    INCORRECT_ARGS,
    TOO_MANY_STRATEGIES_FOR_NON_TOURNAMENT,
    UNKNOWN_STRATEGIES,
    NO_STRATEGIES,
};

class ArgsParser{
    using MetArgsMap = std::map<std::string, bool>;
public:
    ArgsParser(int arc, const char** argv, const StrategiesDescription& strategies_description);

    [[nodiscard]] ParsingStatus get_parsing_status() const;

    [[nodiscard]] bool is_help_mode() const;

    [[nodiscard]] const std::vector<std::string>& get_strategies_names() const;

    [[nodiscard]] unsigned int get_steps_count() const;

    [[nodiscard]] const std::string& get_matrix_file_path() const;

    [[nodiscard]] GameMode get_game_mode() const;
private:
    std::vector<std::string> _strategies_names;
    unsigned int _steps_count;
    std::string _matrix_file_path;
    GameMode _game_mode;
    ParsingStatus _parsing_status;
    bool _help;

    void parse(int arc, const char** argv, const StrategiesDescription& strategies_description);

    friend void extract_args(int arc, const char** argv, MetArgsMap& met_args, ArgsParser& parser);

    friend void extract_steps_count(const char* arg, ArgsParser& parser);

    friend void extract_matrix_file_path(const char* arg, ArgsParser& parser);

    friend void extract_game_mode(const char* arg, ArgsParser& parser);

    friend void extract_strategies_names(const char* arg, ArgsParser& parser);

    friend ParsingStatus validate_count_of_met_args(const MetArgsMap& met_args);

    friend ParsingStatus validate_strategies(const ArgsParser& parser, const StrategiesDescription& description);

    friend bool is_help_only_arg(MetArgsMap& met_args);
};
