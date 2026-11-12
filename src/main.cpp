#include "project/map.h"

#include <iostream>

int main() {
    Map scores;
    scores.insert("alice", 92);
    scores.insert("manpreet", 88);
    scores.insert("zoe", 95);
    scores.update("manpreet", 90);

    for (const std::string& key : scores.keys()) {
        std::cout << key << ": " << scores.at(key) << '\n';
    }

    return 0;
}