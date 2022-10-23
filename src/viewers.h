#pragma once

#include "strategies_factory.h"
#include "utils.h"
#include "args.h"

using StrategiesIndexes = std::array<unsigned int, 3>;

class Viewer{
private:
    const unsigned int _players_count;
    unsigned int _rounds_counter;
public:
    explicit Viewer(unsigned int players_count);
    static void view_incorrect_command() ;
    static void view_final_score(const Score& final_score);
    void view_help_command(const StrategiesDescription& strategies_description) const;
    static void view_round(const Score& current_score, const Triplet<Step>& choices, const Score& delta_score);
    void view_round(const Score& current_score, const Score& delta_score, StrategiesIndexes indexes);
    void view_parsing_error(ParsingStatus status);
};
