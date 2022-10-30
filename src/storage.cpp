#include "storage.h"

Choices AbstractStorage::get_last_enemies_choices([[maybe_unused]] unsigned int id) const{
    return {};
}

void AbstractStorage::append_choices([[maybe_unused]] Choices choice){}

bool Storage::is_empty() const{
    return !_history.empty();
}

Choices Storage::get_last_enemies_choices(unsigned int id) const{
    Choices result;

    const Choices last_choices = _history.back();
    for (unsigned int i = 0; i < last_choices.size(); i++){
        if (i != id){
            result.push_back(last_choices[i]);
        }
    }

    return result;
}

Storage::Storage(const std::string& configs_path){
    _ids_count = 0;
    _configs_path = configs_path;
}

unsigned int Storage::get_free_id(){
    return _ids_count++;
}

void Storage::append_choices(Choices choices){
    _history.push_back(choices);
}
