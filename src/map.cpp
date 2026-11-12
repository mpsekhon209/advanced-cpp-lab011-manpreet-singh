#include "project/map.h"

#include <algorithm>
#include <stdexcept>

Map::Map() = default;

bool Map::empty() const noexcept {
    return entries_.empty();
}

std::size_t Map::size() const noexcept {
    return entries_.size();
}

std::size_t Map::findIndex(const std::string& key) const {
    const auto entry = std::lower_bound(
        entries_.begin(), entries_.end(), key,
        [](const KeyValuePair& pair, const std::string& candidate) {
            return pair.key < candidate;
        });
    if (entry == entries_.end() || entry->key != key) {
        return entries_.size();
    }
    return static_cast<std::size_t>(entry - entries_.begin());
}

void Map::sortEntries() {
    std::sort(entries_.begin(), entries_.end(),
              [](const KeyValuePair& a, const KeyValuePair& b) {
                  return a.key < b.key;
              });
}

bool Map::contains(const std::string& key) const {
    return findIndex(key) != entries_.size();
}

bool Map::insert(const std::string& key, int value) {
    const auto position = std::lower_bound(
        entries_.begin(), entries_.end(), key,
        [](const KeyValuePair& pair, const std::string& candidate) {
            return pair.key < candidate;
        });
    if (position != entries_.end() && position->key == key) {
        return false;
    }
    entries_.insert(position, KeyValuePair{key, value});
    return true;
}

bool Map::update(const std::string& key, int newValue) {
    const std::size_t index = findIndex(key);
    if (index == entries_.size()) {
        return false;
    }
    entries_[index].value = newValue;
    return true;
}

bool Map::erase(const std::string& key) {
    const std::size_t index = findIndex(key);
    if (index == entries_.size()) {
        return false;
    }
    entries_.erase(entries_.begin() + static_cast<std::ptrdiff_t>(index));
    return true;
}

int Map::at(const std::string& key) const {
    const std::size_t index = findIndex(key);
    if (index == entries_.size()) {
        throw std::out_of_range("Map key not found: " + key);
    }
    return entries_[index].value;
}

int& Map::at(const std::string& key) {
    const std::size_t index = findIndex(key);
    if (index == entries_.size()) {
        throw std::out_of_range("Map key not found: " + key);
    }
    return entries_[index].value;
}

std::vector<std::string> Map::keys() const {
    std::vector<std::string> result;
    for (const auto& entry : entries_) {
        result.push_back(entry.key);
    }
    return result;
}

std::vector<int> Map::values() const {
    std::vector<int> result;
    for (const auto& entry : entries_) {
        result.push_back(entry.value);
    }
    return result;
}

bool Map::isSorted() const noexcept {
    for (std::size_t i = 1; i < entries_.size(); ++i) {
        if (entries_[i - 1].key > entries_[i].key) {
            return false;
        }
    }
    return true;
}
