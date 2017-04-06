#define NOMINMAX
#include "DataBase.h"
#include <exception>
#include <fstream>

#pragma comment (lib, "libpqxx.lib")

DataBase * DataBase::p_instance = nullptr;
SingletonDestroyer DataBase::destroyer;

SingletonDestroyer::~SingletonDestroyer() {
	delete p_instance;
}
void SingletonDestroyer::initialize(DataBase* p) {
	p_instance = p;
}

DataBase::DataBase()
{
	//check if the database isn't created
	
	std::ostringstream conn_string("");
	conn_string << "host=" << "localhost"
		<< " user=" << "postgres"
		<< " password=" << "123456"
		<< " dbname=" << "postgres";
	try
	{
		pqxx::connection conn(conn_string.str());
		pqxx::work xact(conn, "SampleSelect");

		std::string query(std::string("CREATE TABLE IF NOT EXISTS distributors (") +
			std::string("id     serial PRIMARY KEY,\n") +
			std::string("shape    integer,\n") +
			std::string("color    bigint,\n") +
			std::string("posx    integer,\n") +
			std::string("posy    integer,\n") +
			std::string("posz    integer,\n") +
			std::string("scale    float,\n") +
			std::string("anglex    float,\n") +
			std::string("angley    float,\n") +
			std::string("anglez    float,\n") +
			std::string("name   char(40)\n")+
			std::string(");"));
		xact.exec(query);
		xact.commit();

		pqxx::work read_data(conn, "SampleRead");
		pqxx::result res = read_data.exec("SELECT * FROM distributors ORDER BY id");
		int index = 0;
		for (auto row : res)
		{
			Property tmp;
			tmp.added = false;
			tmp.id = row[0].as<int>();
			tmp.shape = (shapes)row[1].as<int>();
			tmp.color = row[2].as<unsigned int>();
			tmp.position[0] = row[3].as<int>();
			tmp.position[1] = row[4].as<int>();
			tmp.position[2] = row[5].as<int>();
			tmp.scale = row[6].as<float>();
			tmp.angleX = row[7].as<float>();
			tmp.angleY = row[8].as<float>();
			tmp.angleZ = row[9].as<float>();

			std::string str = row[10].as<std::string>();
			std::wstring widestr = std::wstring(str.begin(), str.end());
			diction.insert(std::pair<std::wstring, int>(widestr , index));

			index++;
			properties.push_back(tmp);

		}
		
		conn.disconnect();

	}
	catch (pqxx::broken_connection)
	{
		throw std::exception("Broken connection");
	}
	
}

void DataBase::Save()
{
	//we need to save the scene
	

	DataBase* db = DataBase::getInstance();
	
	std::ofstream fwrite1("log1.txt");
	fwrite1 << db->getProperties()[1].angleX ;
	fwrite1.flush();
	fwrite1.close();

	std::ostringstream conn_string("");
	conn_string << "host=" << "localhost"
		<< " user=" << "postgres"
		<< " password=" << "123456"
		<< " dbname=" << "postgres";
	try
	{
		pqxx::connection conn(conn_string.str());
		//
		pqxx::work xact(conn, "SampleSelect");
		
		
		for (auto &el : properties)
		{
			if (!el.added && !el.deleted)
			{
				
				xact.exec(
					"UPDATE distributors SET (shape, color, posx, posy, posz, scale, anglex, angley, anglez) = "
					"(" +
					std::to_string(el.shape) + ", " +
					std::to_string(el.color) + ", " +
					std::to_string(el.position[0]) + ", " +
					std::to_string(el.position[1]) + ", " +
					std::to_string(el.position[2]) + ", " +
					std::to_string(el.scale) + ", " +
					std::to_string(el.angleX) + ", " +
					std::to_string(el.angleY) + ", " +
					std::to_string(el.angleZ) +
					") WHERE id = " + std::to_string(el.id));
				

			}
		}
		
		

		
		for (auto &el : properties)
		{
			if (el.added && !el.deleted)
			{
				xact.exec(
					"INSERT INTO distributors(shape, color, posx, posy, posz, scale, anglex, angley, anglez, name) "
					"VALUES (" +
					std::to_string(el.shape) + ", " +
					std::to_string(el.color) + ", " +
					std::to_string(el.position[0]) + ", " +
					std::to_string(el.position[1]) + ", " +
					std::to_string(el.position[2]) + ", " +
					std::to_string(el.scale) + ", " +
					std::to_string(el.angleX) + ", " +
					std::to_string(el.angleY) + ", " +
					std::to_string(el.angleZ) + ", " +
					"'" + el.name + "'" +
					")");
			}
		}
		xact.commit();
		/*
		for (auto &el : properties)
		{
			if (!el.added && el.deleted)
			{
				xact.exec(std::string("DELETE FROM distributors WHERE id = ") + std::to_string(el.id));
			}
		}

		xact.commit();
		*/
		conn.disconnect();
		
	}
	
	catch (pqxx::broken_connection &e)
	{
		std::ofstream fwrite("log.txt");
		fwrite << e.what();
		fwrite.flush();
		fwrite.close();
		
		throw std::exception("Broken connection");
	}
}

DataBase* DataBase::getInstance() {
	if (!p_instance) 
	{
		try
		{
			p_instance = new DataBase();
			destroyer.initialize(p_instance);
		}
		catch (std::exception& e)
		{
			throw e;
		}

		
	}
	return p_instance;
}

std::vector<Property> & DataBase::getProperties()
{
	return properties;
}

DataBase::~DataBase()
{

}