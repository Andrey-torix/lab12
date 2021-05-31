#pragma once
#include "UsedMemory.hpp"
#include "StatSender.hpp"
#include <set>
#include <sstream>
#include "Histogram.hpp"

constexpr size_t kMinLines = 10;

//Histogram* his = new Histogram;
Histogram* his = new Histogram;

class PageContainer {
public:
    void Load(std::ifstream& io, const float& threshold) {
        std::vector<std::string> raw_data;
        while (!io.eof() && io.is_open()) {
            std::string line;
            std::getline(io, line, '\n');
            raw_data.push_back(std::move(line));
        }
        if (raw_data.size() < kMinLines) {
            throw std::runtime_error("too small input stream");
        }
        memory_counter_->OnRawDataLoad(raw_data_, raw_data);
        raw_data_ = std::move(raw_data);

        std::vector<Item> data;
        std::set<std::string> ids;
        for (const auto& line : raw_data_) {
            std::stringstream stream(line);

            Item item;
            stream >> item.id >> item.name >> item.score;

            if (auto&& [_, inserted] = ids.insert(item.id); !inserted) {
                throw std::runtime_error("already seen");
            }

            if (item.score > threshold) {
                data.push_back(std::move(item));
            }
            else {
                stat_sender_.Skip(item);
            }
        }

        if (data.size() < kMinLines) {
            throw std::runtime_error("oops");
        }
        his->thrc(raw_data_.size()-data.size());
        
        
        memory_counter_->OnDataLoad(data_, data);
        his->meanUsed(memory_counter_->Used() / data.size());
        stat_sender_.OnLoaded(data);
        data_ = std::move(data);
    }



    const Item& ByIndex(const size_t& i) const {
        return data_[i];
    }

    const Item& ById(const std::string& id) const {
        auto it = std::find_if(std::begin(data_), std::end(data_),
            [&id](const auto& i) { return id == i.id; });
        return *it;
    }

    void Reload(const float& threshold) {
        std::vector<Item> data;
        std::set<std::string> ids;
        for (const auto& line : raw_data_) {
            std::stringstream stream(line);

            Item item;
            stream >> item.id >> item.name >> item.score;

            if (auto&& [_, inserted] = ids.insert(item.id); !inserted) {
                throw std::runtime_error("already seen");
            }

            if (item.score > threshold) {
                data.push_back(std::move(item));
            }
            else {
                stat_sender_.Skip(item);
            }
        }

        if (data.size() < kMinLines) {
            throw std::runtime_error("oops");
        }
        his->thrc(raw_data_.size() - data.size());
        memory_counter_->OnDataLoad(data_, data);
        his->meanUsed(memory_counter_->Used() / data.size());
        stat_sender_.OnLoaded(data);
        data_ = std::move(data);
    }

    /*size_t GetDataSize() const {
        return data_.size();
    }*/

    /*void PrintTable() const {
        std::cout << "|\tid\t |\t\tname\t\t|\tscore\t|\n";
        std::cout << "_________________________________________\n";
        for (size_t i = 0; i < GetDataSize(); ++i) {
            const auto& item = ByIndex(i);
            std::cout << "|   " << item.id << "\t |\t\t" << item.name << "\t\t|\t" << item.score << "\t\t|" << std::endl;
            const auto& item2 = ById(std::to_string(i));
            std::cout << "|   " << item2.id << "\t |\t\t" << item2.name << "\t\t|\t" << item2.score << "\t\t|" << std::endl;
        }
    }*/

    PageContainer(UsedMemory* memory_counter)
        : memory_counter_(memory_counter) {}


private:
    UsedMemory* memory_counter_;
    StatSender stat_sender_;
    std::vector<Item> data_;
    std::vector<std::string> raw_data_;

};