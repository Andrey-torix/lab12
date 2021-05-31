#pragma once
#include <vector>
#include "Log.hpp"
#include <fstream>
class StatSender {
public:
    void OnLoaded(const std::vector<Item>& new_items) {
        LogSingleton::getInstance()->WriteDebug("StatSender::OnDataLoad");

        AsyncSend(new_items, "/items/loaded");
    }
    void Skip(const Item& item) {
        AsyncSend({ item }, "/items/skiped");
    }
private:
    void AsyncSend(const std::vector<Item>& items, std::string_view path) {
        LogSingleton::getInstance()->Write(path);
        LogSingleton::getInstance()->Write("send stat " + std::to_string(items.size()));

        for (const auto& item : items) {
            LogSingleton::getInstance()->WriteDebug("send: " + item.id);
            // ... some code
            fstr << item.id << item.name << item.score;
            fstr.flush();
        }
    }
    std::ofstream fstr{ "network", std::ios::binary };
};