#include "storage.h"

bool AbstractStorage::is_empty() const{
    return false;
}

Choices AbstractStorage::get_last_enemies_choices([[maybe_unused]] const Strategy& strategy) const{
    return {};
}

unsigned int AbstractStorage::get_free_id(){
    return 0;
}

void AbstractStorage::append_choices([[maybe_unused]] const Choices& choice){}

Storage::Storage(const std::string& configs_path){
    _ids_count = 0;
    _configs_path = configs_path;
}

bool Storage::is_empty() const{
    return _history.empty();
}

Choices Storage::get_last_enemies_choices(const Strategy& strategy) const{
    Choices result;

    unsigned int id = _ids[strategy];

    const Choices last_choices = _history.back();
    for (unsigned int i = 0; i < last_choices.size(); i++){
        if (i != id){
            result.push_back(last_choices[i]);
        }
    }

    return result;
}

void Storage::register_strategy(const Strategy& strategy){
    _ids[strategy] = _ids_count++;
}

void Storage::append_choices(const Choices& choices){
    _history.push_back(choices);
}
