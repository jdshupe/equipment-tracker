// connection.cpp
#include "connection.h"

using namespace std;
using namespace pqxx;


string database::select(string p_statement, int* data_rows)
{
	string sql = p_statement;
	try 
	{
		connection C("user=postgres " \
					"password=Thisisastrongpassword " \
					"host=db.zhjuuyxtilgjluzixcwh.supabase.co " \
					"port=5432 " \
					"dbname=postgres");
		if (C.is_open())
		{
		} else {
			cout << "Can't open database" << endl;
		}

		nontransaction N(C);
		string resultData;
		result R( N.exec( sql ));
		*data_rows = R.size();

		for (result::const_iterator c = R.begin(); c != R.end();c++) {
			for (int i = 0; i < R.columns(); i++) {
				resultData += c[i].as<string>() + ",";
			}
		}
		C.disconnect();
		return resultData;
	} catch (const std::exception &e) {
		cerr << e.what() << std::endl;
		return "NULL";
	}
}


void database::insert(string p_statement)
{
	string sql = p_statement;
	try 
	{
		connection C("user=postgres " \
					"password=Thisisastrongpassword " \
					"host=db.zhjuuyxtilgjluzixcwh.supabase.co " \
					"port=5432 " \
					"dbname=postgres");
		if (C.is_open())
		{
		} else {
			cout << "Can't open database" << endl;
		}

		work W(C);

		W.exec( sql );
		W.commit();
		C.disconnect();
	} catch (const std::exception &e) {
		cerr << e.what() << std::endl;
	}
}
