#pragma once

#include "strategies_factory.h"
#include "utils.h"
#include "args_parser.h"


class GameViewer{
private:
    const unsigned int _players_count;
    unsigned int _rounds_counter;
public:
    GameViewer();
    explicit GameViewer(unsigned int players_count);

    void view_round(const Score& current_score, const Score& delta_score, StrategiesIndexes indexes);

    static void view_incorrect_matrix();
    static void view_incorrect_command() ;
    static void view_parsing_error(ParsingStatus status);
    static void view_final_score(const Score& final_score);
    static void view_help_command(StrategiesDescription& strategies_description);
    static void view_round(const Score& current_score, const Triplet<Step>& choices, const Score& delta_score);
};
