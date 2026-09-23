#ifndef DB_CONTROL_H_INCLUDED
#define DB_CONTROL_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include "sqlite3.h"

using namespace std;

class DB_control
{
	private:
		template <typename T>
		T getColumnValue(sqlite3_stmt* stmt, int columnIndex)
		{
			if constexpr (is_same_v<T, int>)
			{
				return sqlite3_column_int(stmt, columnIndex);
			}
			else if constexpr (is_same_v<T, double>)
			{
				return sqlite3_column_double(stmt, columnIndex);
			}
			else if constexpr (is_same_v<T, const char*>)
			{
				return reinterpret_cast<const char*>(sqlite3_column_text(stmt, columnIndex));
			}
			else
			{
				throw runtime_error("Unsupported type");
			}
		}


	public:
		static int createDB(const char* file_name);
		static int createTable(const char* file_name, string sql_columns);
		static int deleteData(const char* file_name, string table_name);
		static int insertData(const char* file_name, string sql_value);
		static int printData(const char* file_name, string columns_name, string table_name, string object_condition);
		static int callback(void* NotUsed, int argc, char** argv, char** azColName);
		bool dataExists(const char* file_name, string columns_name, string table_name, string object_condition);

		string readFromFile(string file_name);

		template <typename T>
		T getValue(const char* file_name, string columns_name, string table_name, string search_argument, string search_value)
		{
			sqlite3* DB;
			sqlite3_stmt* stmt;
			T value = 0.0f;

			string sql = "SELECT " + columns_name + " FROM " + table_name + " WHERE " + search_argument + " = ?;";

			int control = sqlite3_open(file_name, &DB);
			if (control != SQLITE_OK)
			{
				cerr << "Error opening DB: " << sqlite3_errmsg(DB) << endl;
				return value;
			}

			control = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);
			if (control != SQLITE_OK)
			{
				cerr << "Error preparing statement: " << sqlite3_errmsg(DB) << endl;
				sqlite3_close(DB);
				return value;
			}

			sqlite3_bind_text(stmt, 1, search_value.c_str(), -1, SQLITE_STATIC);

			control = sqlite3_step(stmt);
			if (control == SQLITE_ROW)
			{
				value = static_cast<T>(DB_control::getColumnValue<T>(stmt, 0));
			}
			else if (control == SQLITE_DONE)
			{
				cout << "No product found with name: " << search_value << endl;
			}
			else
			{
				cerr << "Error executing statement: " << sqlite3_errmsg(DB) << endl;
			}

			sqlite3_finalize(stmt);
			sqlite3_close(DB);

			return value;
		}
};


#endif // DB_CONTROL_H