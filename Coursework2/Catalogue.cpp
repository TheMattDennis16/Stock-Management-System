#include "Catalogue.h"

Catalogue::Catalogue()
{
    catalogue = new std::vector<std::shared_ptr<Footwear>>;
	queue = new std::vector<std::shared_ptr<Footwear>>;
	LoadFromFile loadF(catalogue);
	catalogue = loadF.load();
	position = NULL;
}

Catalogue::Catalogue(const Catalogue &cat)
{
	catalogue = new std::vector<std::shared_ptr<Footwear>>;
	*catalogue = *cat.catalogue;
}

Catalogue::~Catalogue()
{
	delete catalogue;
	delete queue;
}

int Catalogue::getShoeStock() const
{
	int total = NULL;
	for (std::vector<std::shared_ptr<Footwear>>::iterator itt = catalogue->begin(); itt != catalogue->end(); itt++)
	{
		if (std::shared_ptr<Shoe> shoe = std::dynamic_pointer_cast<Shoe>(*itt))
		{
            total += shoe->getStock();
		}
	}
	return total;
}

int Catalogue::getBootStock() const
{
	int total = NULL;
	for (std::vector<std::shared_ptr<Footwear>>::iterator itt = catalogue->begin(); itt != catalogue->end(); itt++)
	{
		if (std::shared_ptr<Boot> boot = std::dynamic_pointer_cast<Boot>(*itt))
		{
            total += boot->getStock();
		}
	}
	return total;
}

int Catalogue::getTotalStock() const
{
	int total = NULL;
	for (std::vector<std::shared_ptr<Footwear>>::iterator itt = catalogue->begin(); itt != catalogue->end(); itt++)
	{
		std::shared_ptr<Footwear> current = *itt;
        total += current->getStock();
	}
	return total;
}

void Catalogue::insert(std::shared_ptr<Footwear> item)
{
	catalogue->push_back(item);
    LoadFromFile::writeToLog("Inserted item " +item->getName(), LoadFromFile::INCOMING);
}

void Catalogue::insert(std::vector<std::string> details)
{
    std::shared_ptr<Footwear> currItem(new Footwear);
    if(details.size() == 8)
    {
        std::shared_ptr<Shoe> currNew(new Shoe);
        currNew->setShoeStyle(details.at(7));
        currItem = currNew;
    }
    else if (details.size() == 9)
    {
        std::shared_ptr<Boot> currNew(new Boot);
        currNew->setBootType(details.at(7));
        currNew->setTargetEnvironment(details.at(8));
        currItem = currNew;
    }
    currItem->setName(details.at(0));
    currItem->setColour(details.at(1));
    currItem->setMaterial(details.at(2));
    currItem->setLaceStyle(details.at(3));
    currItem->setSoleStyle(details.at(4));
    currItem->setSize(atof(details.at(5).c_str()));
    currItem->setPrice(atof(details.at(6).c_str()));
    currItem->setStock(0);
    catalogue->push_back(currItem);
    LoadFromFile::writeToLog("Inserted item " +details.at(0), LoadFromFile::INCOMING);
}

size_t Catalogue::size() const
{
	return catalogue->size();
}

void Catalogue::next()
{
    if((position + 1) < catalogue->size())
    {
        position++;
    }
}

void Catalogue::next(int amount)
{
    if ((position + amount) < catalogue->size())
	{
		position += amount;
	}
}

void Catalogue::previous()
{
    if((position - 1) >= 0)
    {
        position--;
    }
}

void Catalogue::previous(int amount)
{
    if ((position - amount) >= 0)
	{
		position -= amount;
	}
}

void Catalogue::setCurrent(std::shared_ptr<Footwear> find)
{
    int i = NULL;
	for (std::vector<std::shared_ptr<Footwear>>::iterator itt = catalogue->begin(); itt != catalogue->end(); itt++)
    {
        if(*itt == find)
        {
            position = i;
        }
        i++;
    }
}

std::shared_ptr<Footwear> Catalogue::getCurrent() const
{
    if (position < catalogue->size() && position >= 0)
	{
        if(catalogue->at(position) != nullptr)
        {
            return catalogue->at(position);
        }
	} 
	std::shared_ptr<Footwear> blank;
    return blank;
}

std::vector<std::shared_ptr<Footwear>>* Catalogue::search(std::string colour, std::string size)
{
    if(colour == "")
    {
        colour = "null";
    }
    if(size == "")
    {
        size = "null";
    }
    std::vector<std::shared_ptr<Footwear>>* returnData = new std::vector<std::shared_ptr<Footwear>>;
    for (std::vector<std::shared_ptr<Footwear>>::iterator itt = catalogue->begin(); itt != catalogue->end(); itt++)
    {
        std::shared_ptr<Footwear> current = *itt;
        if (std::to_string(current->getSize()) == size && current->getColour() == colour)
        {
            returnData->push_back(current);
        }
        else if (current->getColour() == colour)
        {
            returnData->push_back(current);
        }
    }
    return returnData;
}

void Catalogue::save()
{
	LoadFromFile saving(catalogue);
	saving.save();
}

bool Catalogue::addToQueue(std::shared_ptr<Footwear> item)
{
    if (item->getStock() > 0)
	{
		queue->push_back(item);
		return true;
	}
	return false;
}

size_t Catalogue::queueSize()
{
    return queue->size();
}

void Catalogue::removeFromQueue(std::shared_ptr<Footwear> item)
{
	std::vector<std::shared_ptr<Footwear>>* temp = new std::vector<std::shared_ptr<Footwear>>;
	for (std::vector<std::shared_ptr<Footwear>>::iterator itt = queue->begin(); itt != queue->end(); itt++)
	{
		if (*itt != item)
		{
			temp->push_back(*itt);
		}
	}
	queue->swap(*temp);
}
void Catalogue::remove(std::shared_ptr<Footwear> curr)
{
	std::vector<std::shared_ptr<Footwear>>* temp = new std::vector<std::shared_ptr<Footwear>>;
	for (std::vector<std::shared_ptr<Footwear>>::iterator itt = catalogue->begin(); itt != catalogue->end(); itt++)
    {
        if (*itt != curr)
        {
            temp->push_back(*itt);
        }
    }
    catalogue->swap(*temp);
}

std::vector<std::pair<std::string, int>> Catalogue::generateReportStockCount()
{
    std::vector<std::pair<std::string, int>> results;
    for(int i = 0; i < catalogue->size(); i++)
    {
		std::shared_ptr<Footwear> current = catalogue->at(i);
        std::string name = current->getName() + ", " + std::to_string(current->getSize());
        std::pair<std::string, int> result = { name, current->getStock()};
        results.push_back(result);
    }
    return results;
}

void Catalogue::end()
{
    position = (catalogue->size()-1);
}
void Catalogue::start()
{
    position = NULL;
}
