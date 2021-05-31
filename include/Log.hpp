#pragma once
#include <string>
#include <iostream>
class LogSingleton {
public:
	static LogSingleton* getInstance() {
		static LogSingleton instance;
		return &instance;
	}
	void Write(std::string_view message) const { *out_ <<"Info: "<< message << std::endl; }
	void WriteDebug(std::string_view message) const {
		if (level_) *out_ <<"Debug: "<< message << std::endl;
	}
	void Log_level(bool lvl) {
		level_ = lvl;
		out_ = &std::cout;
		 
	}

private:
	LogSingleton() {}
	bool level_;
	mutable std::ostream* out_;
};

struct Item {
	std::string id;
	std::string name;
	float score = 0;
};

//для использования класса 
/*
LogSingleton::getInstance()->метод();
*/