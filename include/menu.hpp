#pragma once
#include <boost/program_options.hpp>
#include <string>
class EApplication {
public:

	void menu(int argc, const char** argv);
	int exec();
	int ar;
private:
	boost::program_options::options_description m_desk{ "Доступные опции" };
	boost::program_options::variables_map m_vm;
	
	std::string input_path;
	int threshold;
};