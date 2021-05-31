#pragma once
#include <vector>
#include "Log.hpp"

class UsedMemory {

public:
    void OnDataLoad(const std::vector<Item>& old_items, const std::vector<Item>& new_items) {
        LogSingleton::getInstance()->WriteDebug("UsedMemory::OnDataLoad");
        for (const auto& item : old_items) {
            used_ -= item.id.capacity();
            used_ -= item.name.capacity();
            used_ -= sizeof(item.score);
        }

        for (const auto& item : new_items) {
            used_ += item.id.capacity();
            used_ += item.name.capacity();
            used_ += sizeof(item.score);
        }
        LogSingleton::getInstance()->Write("UsedMemory::OnDataLoad: new size = " + std::to_string(used_));
    }
    void OnRawDataLoad(const std::vector<std::string>& old_items,
        const std::vector<std::string>& new_items) {
       LogSingleton::getInstance()->WriteDebug("UsedMemory::OnRawDataLoads");
        for (const auto& item : old_items) {
            used_ -= item.capacity();
        }
        for (const auto& item : new_items) {
            used_ += item.capacity();
        }
        LogSingleton::getInstance()->Write("UsedMemory::OnDataLoad: new size = " + std::to_string(used_));
    }
    size_t Used() {
        return used_;
    }
private:
    size_t used_ = 0;
};