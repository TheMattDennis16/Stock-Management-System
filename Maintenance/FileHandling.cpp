 #include "FileHandling.h"

LoadFromFile::LoadFromFile(std::vector<std::shared_ptr<Footwear>>* data)
{
	database = data;
}

bool LoadFromFile::save()
{
	save(defaultPath);
	return true;
}
void LoadFromFile::checkFile(std::string filepath)
{
    std::fstream openF;
    openF.open(filepath.c_str(), std::ios::in);
    if(openF.is_open() == false)
    {
        std::ofstream makeF(filepath.c_str());
        makeF.close();
    }
    openF.close();
}
bool LoadFromFile::save(std::string filePath)
{
    checkFile(filePath);
    std::fstream file;
    file.open(filePath, std::fstream::out);
    if (file.is_open())
    {
        int new1 = NULL;
		for (std::vector<std::shared_ptr<Footwear>>::iterator itt = database->begin(); itt != database->end(); itt++)
        {
			if (std::shared_ptr<Boot> boot = std::dynamic_pointer_cast<Boot>(*itt))
            {
                file << "Boot," << boot->getName() << "," << boot->getColour() << ","
                    << boot->getMaterial() << "," << boot->getLaceStyle() << "," << boot->getSoleStyle() << ","
                    << boot->getSize() << "," << boot->getPrice() << "," << boot->getStock() << ","
                    << boot->getBootType() << "," << boot->getTargetEnvironment() << std::endl;
            }
            else if (std::shared_ptr<Shoe> shoe = std::dynamic_pointer_cast<Shoe>(*itt))
            {
                file << "Shoe," << shoe->getName() << "," << shoe->getColour() << ","
                    << shoe->getMaterial() << "," << shoe->getLaceStyle() << "," << shoe->getSoleStyle() << ","
                    << shoe->getSize() << "," << shoe->getPrice() << "," << shoe->getStock() << ","
                    << shoe->getShoeStyle() << std::endl;
            }
            new1++;
        }
        file.close();
        return true;
    }
    return false;
}
std::vector<std::shared_ptr<Footwear>>* LoadFromFile::load()
{
	return load(defaultPath);
}
std::vector<std::shared_ptr<Footwear>>* LoadFromFile::load(std::string filePath)
{
    checkFile(filePath);
	std::vector<std::shared_ptr<Footwear>>* returnVals = new std::vector<std::shared_ptr<Footwear>>;
	std::ifstream file;
	file.open(filePath, std::fstream::in);
	if (file.is_open())
	{
        /*
            Reads each CSV line into the vector.
        */
        std::vector<std::string> lines;
		std::string line = "";
		while (std::getline(file, line))
		{
			if (line.size() != 0)
			{
				lines.push_back(line);
			}
		}
        LoadFromFile::writeToLog("\nLoading stock", LoadFromFile::INCOMING);

        /*
            Parses on each comma, inserts each item into values vector.
        */
        for (int i = 0; i < lines.size(); i++)
		{
			std::istringstream strStream(lines.at(i));
			std::vector<std::string> values;
			std::string item = "";
			while (std::getline(strStream, item, ','))
			{
				values.push_back(item);
			}

			std::shared_ptr<Footwear> footItem;
			if (values.at(0) == "Boot")
			{
				std::shared_ptr<Boot> boot(new Boot);
				boot->setBootType(values.at(9));
				boot->setTargetEnvironment(values.at(10));
				footItem = boot;
			}
			else if (values.at(0) == "Shoe")
			{
				std::shared_ptr<Shoe> shoe(new Shoe);
				shoe->setShoeStyle(values.at(9));
				footItem = shoe;
			}
			footItem->setName(values.at(1));
			footItem->setColour(values.at(2));
			footItem->setMaterial(values.at(3));
			footItem->setLaceStyle(values.at(4));
			footItem->setSoleStyle(values.at(5));
			footItem->setSize(atof(values.at(6).c_str()));
			footItem->setPrice(atof(values.at(7).c_str()));
			footItem->addStock(atoi(values.at(8).c_str()));
			returnVals->push_back(footItem);
		}
        LoadFromFile::writeToLog("Done loading stock", LoadFromFile::INCOMING);
		return returnVals;
	}
    return returnVals;
}

void LoadFromFile::writeToLog(std::string item,  LogTypes type)
{
    std::string fileType;
    if(type == INCOMING)
        fileType = "incoming.log";
    else fileType = "outgoing.log";
    checkFile(fileType);
    std::fstream file;
    file.open(fileType, std::fstream::out | std::fstream::app);
    if (file.is_open())
    {
        file << item << std::endl;
    }
    file.close();
}
