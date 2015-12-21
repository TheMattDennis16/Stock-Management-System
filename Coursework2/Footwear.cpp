#include "Footwear.h"
#include "FileHandling.h"

Footwear::Footwear()
{
    data.name_ = "Null";
	data.material_ = "Unknown";
	data.colour_ = "Unknown";
	data.laceStyle_ = "Unknown";
	data.soleStyle_ = FLAT;
	data.size_ = 0.0;
	data.price_ = 0.0;
	data.stockCount_ = 0;
}

Footwear::Footwear(BaseData newData)
{
    data = newData;
}

Footwear::~Footwear()
{
}

void Footwear::setSize(double size)
{
	data.size_ = size;
}

double Footwear::getSize()
{
	return data.size_;
}

void Footwear::setPrice(double price)
{
	data.price_ = price;
}

double Footwear::getPrice()
{
	return data.price_;
}

void Footwear::setColour(std::string colour)
{
	data.colour_ = colour;
}

std::string Footwear::getColour()
{
	return data.colour_;
}

void Footwear::setMaterial(std::string material)
{
	data.material_ = material;
}

std::string Footwear::getMaterial()
{
	return data.material_;
}

Shoe::Shoe() : Footwear()
{
	shoeStyle_ = TRAINER;
}

Shoe::Shoe(BaseData data) : Footwear(data)
{
    shoeStyle_ = TRAINER;
}

Shoe::~Shoe()
{
}
Boot::Boot() : Footwear()
{
	bootType_ = ANKLE;
	targetEnvironment_ = "Unknown";
}
Boot::Boot(BaseData base) : Footwear(base)
{
    bootType_ = ANKLE;
    targetEnvironment_ = "Unknown";
}

Boot::~Boot()
{
}
std::vector<std::string> Footwear::getDetails()
{
	std::vector<std::string> returnVals;
	returnVals.push_back(data.name_);
	returnVals.push_back(data.colour_);
	returnVals.push_back(data.material_);
	returnVals.push_back(getLaceStyle());
	returnVals.push_back(getSoleStyle());
	returnVals.push_back(std::to_string(data.size_));
	returnVals.push_back(std::to_string(data.price_));
	returnVals.push_back(std::to_string(data.stockCount_));
	return returnVals;
}
std::vector<std::string> Shoe::getDetails()
{
	std::vector<std::string> returnVals = Footwear::getDetails();
	returnVals.push_back(getShoeStyle());
	return returnVals;
}
std::vector<std::string> Boot::getDetails()
{
	std::vector<std::string> returnVals = Footwear::getDetails();
	returnVals.push_back(targetEnvironment_);
	returnVals.push_back(getBootType());
	return returnVals;
}

void Footwear::setLaceStyle(std::string lace)
{
	data.laceStyle_ = lace;
}
std::string Footwear::getLaceStyle()
{
	return data.laceStyle_;
}
void Footwear::setSoleStyle(std::string sole)
{
	if (sole == "Flat")
		data.soleStyle_ = FLAT;
	else if (sole == "Wedge")
		data.soleStyle_ = WEDGE;
	else if (sole == "Platform")
		data.soleStyle_ = PLATFORM;
	
}
std::string Footwear::getSoleStyle()
{
	if (data.soleStyle_ == FLAT)
		return "Flat";
	else if (data.soleStyle_ == WEDGE)
		return "Wedge";
	return "Platform";
}
void Shoe::setShoeStyle(std::string style)
{
	if (style == "Flipflop")
		shoeStyle_ = FLIPFLOP;
	else if (style == "Court")
		shoeStyle_ = COURT;
	else if (style == "Sandal")
		shoeStyle_ = SANDAL;
	else if (style == "Trainer")
		shoeStyle_ = TRAINER;
	else if (style == "Slipper")
		shoeStyle_ = SLIPPER;
}
std::string Shoe::getShoeStyle()
{
	if (shoeStyle_ == FLIPFLOP)
		return "Flipflop";
	else if (shoeStyle_ == COURT)
		return "Court";
	else if (shoeStyle_ == SANDAL)
		return "Sandal";
	else if (shoeStyle_ == TRAINER)
		return "Trainer";
	return "Slipper";
}
void Boot::setBootType(std::string style)
{
	if (style == "Chelsea")
		bootType_ = CHELSEA;
	else if (style == "Knee")
		bootType_ = KNEE;
	else if (style == "Ankle")
		bootType_ = ANKLE;
	else if (style == "Thigh")
		bootType_ = THIGH;
	else if (style == "Jodhpur")
		bootType_ = JODHPUR;
	else if (style == "Rigger")
		bootType_ = RIGGER;
}
std::string Boot::getBootType()
{
	if (bootType_ == CHELSEA)
		return "Chelsea";
	else if (bootType_ == KNEE)
		return "Knee";
	else if (bootType_ == ANKLE)
		return "Ankle";
	else if (bootType_ == THIGH)
		return "Thigh";
	else if (bootType_ == JODHPUR)
		return "Jodhpur";
	return "Rigger";
}
void Boot::setTargetEnvironment(std::string type)
{
	targetEnvironment_ = type;
}
std::string Boot::getTargetEnvironment()
{
	return targetEnvironment_;
}
int Footwear::getStock()
{
	return data.stockCount_;
}
void Footwear::addStock(int amount)
{
    LoadFromFile::writeToLog(("Adding " + std::to_string(amount) + " of " + data.name_), LoadFromFile::INCOMING);
    data.stockCount_ += amount;
}
std::string Footwear::getName()
{
    return data.name_;
}
void Footwear::setName(std::string name)
{
    data.name_ = name;
}
void Footwear::removeStock(int amount)
{
	data.stockCount_ -= amount;
    LoadFromFile::writeToLog(("Removing "+std::to_string(amount)+" of " + data.name_), LoadFromFile::OUTGOING);
}
void Footwear::setStock(int stock)
{
    data.stockCount_ = stock;
}
