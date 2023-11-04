#include <sqlite3.h>
#include<iostream>

int main()
{
    sqlite3* db;
    int rc = sqlite3_open("my_database.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return rc;
    }


    const char* createTableSQL = "CREATE TABLE IF NOT EXISTS Purchases_table (id INTEGER PRIMARY KEY, name TEXT);";
    rc = sqlite3_exec(db, createTableSQL, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    sqlite3_close(db);
}

#include <sqlite3.h>
#include <iostream>

int main() {
    sqlite3* db;
    int rc = sqlite3_open("mydatabase.db", &db);
    if (rc) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 1;
    }

    const char* sql = "INSERT INTO mytable (column1, column2) VALUES (?, ?);";

    // Prepare the SQL statement
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 1;
    }

    // Bind values to the prepared statement
    const char* value1 = "dynamic_value1";
    const char* value2 = "dynamic_value2";
    sqlite3_bind_text(stmt, 1, value1, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, value2, -1, SQLITE_STATIC);

    // Execute the prepared statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}
