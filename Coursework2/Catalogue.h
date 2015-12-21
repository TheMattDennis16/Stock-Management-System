#ifndef CATALOGUE_H
#define CATALOGUE_H

#include "Footwear.h"
#include "FileHandling.h"
#include <utility>
#include <memory>

class Catalogue
{
private:
    std::vector<std::shared_ptr<Footwear>>* catalogue;
	std::vector<std::shared_ptr<Footwear>>* queue;
    int position;

public:
	Catalogue();
	Catalogue(const Catalogue &cat);
	~Catalogue();
    int getShoeStock() const;
    int getBootStock() const;
    int getTotalStock() const;
	void insert(std::shared_ptr<Footwear> item);
    void insert(std::vector<std::string> details);
    size_t size() const;
    void next();
	void next(int amount);
    void end();
    void previous();
	void previous(int amount);
    void start();
    void setCurrent(std::shared_ptr<Footwear> find);
    std::shared_ptr<Footwear> getCurrent() const;
	void remove(std::shared_ptr<Footwear> curr);
	std::vector<std::shared_ptr<Footwear>>* search(std::string colour, std::string size);
	void save();

	bool addToQueue(std::shared_ptr<Footwear> item);
    size_t queueSize();
	void removeFromQueue(std::shared_ptr<Footwear> item);
    std::vector<std::pair<std::string, int>> generateReportStockCount();
};
#endif
