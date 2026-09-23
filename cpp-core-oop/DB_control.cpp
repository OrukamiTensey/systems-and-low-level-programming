#include "DB_control.h"

int DB_control::createDB(const char* file_name)
{
	sqlite3* DB;

	int control = 0;
	control = sqlite3_open(file_name, &DB);

	sqlite3_close(DB);

	return 0;
}

int DB_control::createTable(const char* file_name, string sql_columns)
{
	sqlite3* DB;
	char* messageError;

	string sql = sql_columns;

	try
	{
		int control = 0;
		control = sqlite3_open(file_name, &DB);
		
		control = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
		if (control != SQLITE_OK)
		{
			cerr << "Error in createTable function: " << messageError << endl;
			sqlite3_free(messageError);
		}
		else
		{
			cout << "Table created Successfully" << endl;
		}
		
		sqlite3_close(DB);
	}
	catch (const exception& e)
	{
		cerr << e.what();
	}

	return 0;
}

int DB_control::deleteData(const char* file_name, string table_name)
{
	sqlite3* DB;
	char* messageError;

	string sql = "DELETE FROM " + table_name + ";";
	string sql_reset = "DELETE FROM sqlite_sequence WHERE name = '" + table_name + "';";	// reset autoincrement

	int control = sqlite3_open(file_name, &DB);
	
	control = sqlite3_exec(DB, sql.c_str(), callback, NULL, &messageError);
	if (control != SQLITE_OK)
	{
		cerr << "Error in deleteData function." << endl;
		sqlite3_free(messageError);
	}
	else
	{
		cout << "Records deleted Successfully!" << endl;
	}

	control = sqlite3_exec(DB, sql_reset.c_str(), NULL, 0, &messageError);		// reseting autoincrement
	if (control != SQLITE_OK)
	{
		cerr << "Error resetting auto-increment in deleteData function: " << messageError << endl;
		sqlite3_free(messageError);
	}
	else
	{
		cout << "Auto-increment reset Successfully!" << endl;
	}

	sqlite3_close(DB);
	
	return 0;
}

int DB_control::insertData(const char* file_name, string sql_value)
{
	sqlite3* DB;
	char* messageError;

	string sql = sql_value;

	int control = sqlite3_open(file_name, &DB);
	
	control = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (control != SQLITE_OK)
	{
		cerr << "Error in insertData function: " << messageError << endl;
		sqlite3_free(messageError);
	}
	else
	{
		cout << "Records inserted Successfully!" << endl;
	}

	return 0;
}

int DB_control::printData(const char* file_name, string columns_name, string table_name, string object_condition)
{
	sqlite3* DB;
	char* messageError;

	string sql = "SELECT " + columns_name + " FROM " + table_name;
	if (object_condition != "")
	{
		sql += " WHERE " + object_condition;
	}

	int control = sqlite3_open(file_name, &DB);
	
	control = sqlite3_exec(DB, sql.c_str(), callback, NULL, &messageError);

	if (control != SQLITE_OK)
	{
		cerr << "Error in printData function: " << messageError << endl;
		sqlite3_free(messageError);
	}
	else
	{
		cout << "Records printed Successfully!" << endl;
	}
	sqlite3_close(DB);

	return 0;
}

int DB_control::callback(void* NotUsed, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++)
	{
		cout << azColName[i] << ": " << argv[i] << endl;	// column name and value for delete method
	}

	cout << endl;

	return 0;
}

string DB_control::readFromFile(string file_name)
{
	ifstream myfile;
	string fileText = "";

	myfile.open(file_name);
	if (myfile.is_open())
	{
		string line = "";
		while (getline(myfile, line))
		{
			fileText += line + "\n";
		}
		fileText.pop_back();
	}
	else
	{
		cout << "Couldn't open file\n";
	}

	myfile.close();

	return fileText;
}

bool DB_control::dataExists(const char* file_name, string columns_name, string table_name, string object_condition)
{
	sqlite3* DB;
	char* messageError;
	sqlite3_stmt* stmt;
	string sql = "SELECT " + columns_name + " FROM " + table_name + " WHERE " + object_condition + " LIMIT 1;";
	bool exists = false;

	sqlite3_open(file_name, &DB);

	if (sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
	{
		cerr << "Failed to prepare statement: " << sqlite3_errmsg(DB) << endl;
		sqlite3_close(DB);
		return false;
	}

	if (sqlite3_step(stmt) == SQLITE_ROW) exists = true;
	

	sqlite3_finalize(stmt);
	sqlite3_close(DB);

	return exists;
}