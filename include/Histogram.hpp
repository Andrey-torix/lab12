#pragma once
#include <string>
#include <iostream>
#include "Log.hpp"
//#include "PageContainer.hpp"
class Histogram
{
public:
	void meanUsed(float sc) {
		score = sc;
	}
	void thrc(int th) {
		threshold_count = th;
	}
	void Message() {
		LogSingleton::getInstance()->Write("Среднее значение: " + std::to_string(score) + " Отброшено: " + std::to_string(threshold_count));
	}
	Histogram(){}

private:
	float score;
	int threshold_count;
};


