#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <map>
#include <ctime>
#include <fstream>
#ifdef _WIN32
#include <conio.h>
#endif
#include <Windows.h>

using namespace std;

class Transaction {
public:
    string type;
    string category;
    double amount;
    time_t date;

    Transaction(string t, string c, double a, time_t d) : type(t), category(c), amount(a), date(d) {}

    time_t getDate() const {
        return date;
    }
};

class User {
public:
    string username;
    string password;
    bool isAdmin;

    User(string u, string p, bool admin) : username(u), password(p), isAdmin(admin) {}
};

class FinancialManagementSystem {
private:
    vector<Transaction> transactions;
    double totalIncome = 0.0;
    double totalExpenses = 0.0;
    map<string, double> categoryExpenses;

public:
    void addIncome(double amount, string category) {
        time_t now = time(0);
        transactions.push_back(Transaction("Income", category, amount, now));
        totalIncome += amount;
    }

    void addExpense(double amount, string category, tm& expenseDate) {
        time_t date = mktime(&expenseDate);
        transactions.push_back(Transaction("Expense", category, amount, date));
        totalExpenses += amount;
        categoryExpenses[category] += amount;
    }

    void generateReport() {
        ofstream reportFile("financial_report.txt");
        if (!reportFile) {
            cerr << "Error creating report file\n";
            return;
        }

        reportFile << fixed << setprecision(2);
        reportFile << "Financial Report:\n";
        reportFile << "=========================\n";
        reportFile << "Total Income: $" << totalIncome << "\n";
        reportFile << "Total Expenses: $" << totalExpenses << "\n";
        reportFile << "Net Savings: $" << (totalIncome - totalExpenses) << "\n";
        reportFile << "=========================\n";
        
        reportFile << "\nExpenses by Category:\n";
        for (const auto& category : categoryExpenses) {
            reportFile << category.first << ": $" << category.second << "\n";
        }
        reportFile << "=========================\n";
        
        reportFile.close();
        cout << "Report saved to financial_report.txt\n";
    }

    void showTransactions() {
        cout << "\nAll Transactions:\n";
        cout << "=========================\n";
        for (const auto& transaction : transactions) {
            cout << transaction.type << " | " << transaction.category << " | $" << transaction.amount << " | " << ctime(&transaction.date);
        }
        cout << "=========================\n";
    }
};

void clearScreen() {
    system("cls");
}

void setConsoleColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void showMainMenu() {
    clearScreen();
    setConsoleColor(11);
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "|          Financial Management System           |\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    setConsoleColor(13);
    cout << "| 1. Admin Login                                 |\n";
    cout << "| 2. User Login                                  |\n";
    cout << "| 3. Exit                                        |\n";
    setConsoleColor(11);
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    setConsoleColor(14);
    cout << "Select an option: ";
    
}

bool authenticateUser(const vector<User>& users, bool& isAdmin) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
#ifdef _WIN32
    char ch;
    password = "";
    while ((ch = _getch()) != '\r') {
        cout << "*";
        password += ch;
    }
    cout << endl;
#else
    cin >> password;
#endif

    for (const auto& user : users) {
        if (user.username == username && user.password == password) {
            isAdmin = user.isAdmin;
            return true;
        }
    }
    cout << "Authentication failed. Please try again.\n";
    return false;
}

void adminMenu(FinancialManagementSystem& fms) {
    int choice;
    do {
        clearScreen();
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "|             Admin Menu                      |\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "| 1. Add Income                               |\n";
        cout << "| 2. Add Expense                              |\n";
        cout << "| 3. Show Transactions                        |\n";
        cout << "| 4. Generate Report                          |\n";
        cout << "| 5. Logout                                   |\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "Select an option: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                double amount;
                string category;
                cout << "Enter income amount: ";
                cin >> amount;
                cout << "Enter income category: ";
                cin >> category;
                fms.addIncome(amount, category);
                break;
            }
            case 2: {
                double amount;
                string category;
                int year, month, day;
                tm expenseDate = {};
                cout << "Enter expense amount: ";
                cin >> amount;
                cout << "Enter expense category: ";
                cin >> category;
                cout << "Enter expense date (YYYY-MM-DD): ";
                cin >> year >> month >> day;
                expenseDate.tm_year = year - 1900; 
                expenseDate.tm_mon = month - 1;    
                expenseDate.tm_mday = day;         
                fms.addExpense(amount, category, expenseDate);
                break;
            }
            case 3:
                fms.showTransactions();
                break;
            case 4:
                fms.generateReport();
                break;
            case 5:
                cout << "Logging out...\n";
                return;
            default:
                cout << "Invalid option! Try again.\n";
        }
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
    } while (true);
}

void userMenu(FinancialManagementSystem& fms) {
    clearScreen();
    ifstream reportFile("financial_report.txt");
    if (reportFile) {
        cout << "Financial Report:\n";
        cout << reportFile.rdbuf();
        reportFile.close();
    } else {
        cout << "No report available.\n";
    }
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

int main() {
    vector<User> users = {
        User("admin", "adminpass", true),
        User("user", "userpass", false)
    };

    bool isAdmin = false;
    int choice;

    do {
        showMainMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                if (authenticateUser(users, isAdmin) && isAdmin) {
                    clearScreen();
                    FinancialManagementSystem fms;
                    adminMenu(fms);
                } else
{
                    cout << "Invalid credentials or insufficient privileges!\n";
                }
                break;
            case 2:
                if (authenticateUser(users, isAdmin) && !isAdmin) {
                    clearScreen();
                    FinancialManagementSystem fms;
                    userMenu(fms);
                } else {
                    cout << "Invalid credentials or insufficient privileges!\n";
                }
                break;
            case 3:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid option! Try again.\n";
        }
    } while (choice != 3);

    return 0;
}
