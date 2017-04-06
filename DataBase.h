#define NOMINMAX
#include <vector>
#include <map>
#include "Render.h"
#include <pqxx/pqxx>
class DataBase;  // опережающее объ€вление

class SingletonDestroyer
{
private:
	DataBase* p_instance;
public:
	~SingletonDestroyer();
	void initialize(DataBase* p);
};

class DataBase
{
private:
	std::vector<Property> properties;
	static DataBase* p_instance;
	static SingletonDestroyer destroyer;
	~DataBase();
protected:
	DataBase();
	DataBase(const DataBase&);
	DataBase& operator=(DataBase&);
	
	friend class SingletonDestroyer;
public:
	void Save();
	std::vector<Property>& getProperties();
	static DataBase* getInstance();
	std::map<std::wstring, int> diction;
};
