#include "menu.hpp"
#include <iostream>
#include "Histogram.hpp"
#include "PageContainer.hpp"
#include "StatSender.hpp"
#include "UsedMemory.hpp"
#include "Log.hpp"
void EApplication::menu(int argc, const char** argv) { 
        ar = argc;
        m_desk.add_options()("help", "вызов справки")
            ("log_debug", "off/on = Info/Debug")
            ("input", boost::program_options::value<std::string>(&input_path)->composing()->default_value("data.txt"), "Путь к файлу")
            ("threshold", boost::program_options::value<int>(&threshold)->composing()->default_value(1), "порог");
        try {
        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, m_desk), m_vm);
        }
        catch (std::string ex) {
            std::cout << "Пожалуйста, используйте --help опцию для вывода справки"
                << std::endl;
        }
        boost::program_options::notify(m_vm);
}

int EApplication::exec() {
    if (m_vm.count("help")) {
        std::cout << m_desk << std::endl;
        return 1;
    }
   else {
        if (ar > 1)
        {
            std::cout <<"Аргументов "<< ar << std::endl;
            if (m_vm.count("log_debug")) {
                LogSingleton::getInstance()->Log_level(true);
            }
           UsedMemory* usedMemory = new UsedMemory();
            PageContainer* pageContainer = new PageContainer(usedMemory);
            Histogram* histogram = new Histogram();
            std::ifstream file(input_path);
            pageContainer->Load(file, threshold);
            LogSingleton::getInstance()->Write(std::to_string(usedMemory->Used()));
            for (size_t i = 0; i < 5; ++i) {
                std::cout << pageContainer->ByIndex(i).name << ": " << pageContainer->ByIndex(i).score;
                std::cout << pageContainer->ById(std::to_string(i)).name << ": " << pageContainer->ById(std::to_string(i)).score;
            }
            pageContainer->Reload(threshold);
            LogSingleton::getInstance()->Write(std::to_string(usedMemory->Used()));
        }
        else {
            std::cout << "Пожалуйста, используйте --help опцию для вывода справки"
                << std::endl;
            return 1;
        }
    }

   /* if (m_vm.count("log-level") && m_vm.count("thread-count") && m_vm.count("output") && m_vm.count("input-file")) {*/
    return 0;
}