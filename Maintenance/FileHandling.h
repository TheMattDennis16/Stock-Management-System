#ifndef FILEHANDLING_H
#define FILEHANDLING_H

#include <fstream>
#include <sstream>
#include "Footwear.h"
#include <memory>

class LoadFromFile
{
private:
	std::string defaultPath = "backup.csv";
	std::vector<std::shared_ptr<Footwear>>* database;
    static void checkFile(std::string filepath);

public:
    enum LogTypes
    {
        INCOMING,
        OUTGOING
    };
	LoadFromFile(std::vector<std::shared_ptr<Footwear>>* data);
    static void writeToLog(std::string item, LogTypes type);
	bool save();
	bool save(std::string filePath);
	std::vector<std::shared_ptr<Footwear>>* load();
	std::vector<std::shared_ptr<Footwear>>* load(std::string filePath);
};

#endif
