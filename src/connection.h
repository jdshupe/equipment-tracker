// connection.h
#ifndef CONNECTION_H
#define CONNECTION_H

#include <iostream>
#include <fstream>
#include <pqxx/pqxx>
#include <string>

namespace database
{
	std::string select(std::string p_statement, int* data_rows);
	std::string select(std::string p_statement);

	void insert(std::string p_statement);
};

#endif
