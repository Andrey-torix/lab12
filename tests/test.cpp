// Copyright 2021 Andreytorix
#include <gtest/gtest.h>
#include "../include/UsedMemory.hpp"
#include "../include/PageContainer.hpp"
#include <fstream>
TEST(TestCaseUsed_memory, Test1) {
	LogSingleton::getInstance()->Log_level(true);
	UsedMemory m;
	std::vector<std::string> old_items{"test1"};
	std::vector<std::string> new_items{"test1","test2","test3"};
	m.OnRawDataLoad(old_items, new_items);
  EXPECT_EQ(m.Used(), 30);
}
/*TEST(TestItems, Test2) {
	UsedMemory m;
	std::vector<Item> old_items1{};
	std::vector<Item> new_items1{};
	Item tmp;
	tmp.id = 1;
	tmp.name = "test1";
	tmp.score = 10;
	new_items1.push_back(tmp);
	tmp.id = 2;
	tmp.name = "test2";
	tmp.score = 20;
	new_items1.push_back(tmp);
	tmp.id = 3;
	tmp.name = "test3";
	tmp.score = 30;
	new_items1.push_back(tmp);
	m.OnDataLoad(old_items1, new_items1);
	std::cout << m.Used() << std::endl;
	EXPECT_EQ(m.Used(), 102);
  EXPECT_TRUE(true);
}

TEST(incorrect, EmptyFile) {
	std::ifstream emptyfile{ "empty.txt" };
	UsedMemory* usedMemory = new UsedMemory();
	PageContainer* pageContainer = new PageContainer(usedMemory);
	EXPECT_THROW(pageContainer->Load(emptyfile,10), std::runtime_error);
	delete(usedMemory);
	delete(pageContainer);
}*/

