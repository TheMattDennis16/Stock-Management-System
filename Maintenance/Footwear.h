#ifndef Footwear_H
#define Footwear_H

#include <vector>
#include <string>

enum SoleStyle
{
	FLAT,
	WEDGE,
	PLATFORM
};
struct BaseData 
{
	std::string name_;
	std::string colour_;
	std::string material_;
	std::string laceStyle_;
	SoleStyle soleStyle_;
	double size_;
	double price_;
	int stockCount_;
};
class Footwear
{
private:
	BaseData data;

public:
    Footwear();
    Footwear(BaseData newData);
    virtual ~Footwear();
    void setSize(double size);
    double getSize();
    void setPrice(double price);
    double getPrice();
    void setColour(std::string colour);
    std::string getColour();
    void setMaterial(std::string material);
    std::string getMaterial();
	int getStock();
    void setStock(int stock);
	void addStock(int amount);
	void removeStock(int amount);
    std::string getName();
    void setName(std::string name);

    virtual std::vector<std::string> getDetails();
    void setLaceStyle(std::string lace);
    std::string getLaceStyle();
    void setSoleStyle(std::string sole);
    std::string getSoleStyle();

};

class Shoe : public Footwear
{
private:
	enum ShoeStyle 
	{
		FLIPFLOP,
		COURT,
		SANDAL,
		TRAINER,
		SLIPPER
	};
	ShoeStyle shoeStyle_;
public:
    Shoe(); //
    Shoe(BaseData data);
	~Shoe(); //
	void setShoeStyle(std::string style);//
	std::string getShoeStyle();//

	virtual std::vector<std::string> getDetails();//
};

class Boot : public Footwear
{
private:
	enum BootStyle
	{
		CHELSEA,
		KNEE,
		ANKLE,
		THIGH,
		JODHPUR,
		RIGGER
	};
	BootStyle bootType_;
	std::string targetEnvironment_;

public:
    Boot();
    Boot(BaseData base);
	~Boot();
	virtual std::vector<std::string> getDetails();//

	void setBootType(std::string style);//
	std::string getBootType();//
	void setTargetEnvironment(std::string type);//
	std::string getTargetEnvironment();//
};
#endif
