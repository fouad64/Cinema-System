#include "./member.hpp"


bool member::login(sqlite3* db, string& role)
{
    sqlite3_stmt* stmt = nullptr;
    string query;
    string email, password;
    bool success = false;
    cout << "Enter your email: ";
    cin >> email;
    cout << "\nEnter your password: ";
    cin >> password;

    query = "SELECT email, password FROM users WHERE password='" + password +"' AND email='" + email + "';";
    //SELECT email, password FROM users WHERE password='v_password' AND email='v_email';
    if(executeSQL(db, "BEGIN TRANSACTION;"))
    if(executeSQL(db, query))
    if(executeSQL(db, "COMMIT;"))
    {
        query = "SELECT role FROM users WHERE password='" + password +"' AND email='" + email + "';";
        if(sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
        {
            if(sqlite3_step(stmt) == SQLITE_ROW)
            {
                const unsigned char* text = sqlite3_column_text(stmt, 0);
                if(text) role = reinterpret_cast<const char*>(text);
                success = true;
            }
        }
        if(stmt) sqlite3_finalize(stmt);
    }

    return success;
}

bool member::signup(sqlite3* db)
{
    string query;
    string name,email,password,role;
    cout << "Enter your email: ";
    cin >> email;
    cout << "\nEnter your password: ";
    cin >> password;
    cout<< "\nName: ";
    cin >> name;
    role = "customer";
    query = "INSERT INTO users(name,email,password,role) VALUES('" + name +"', '" + email + "', '" + password + "', 'customer')";
    if(executeSQL(db, "BEGIN TRANSACTION;"))
    if(executeSQL(db, query))
    if(executeSQL(db, "COMMIT;")) return true;

    return false;

}