#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>
#include <limits>
#include <Windows.h>
using namespace std;

string dataPath = "data/data.csv";
string settingsPath = "data/settings.csv";
double initBal = 0.00;

string currentTime()
{
    time_t currentTime = time(0);
    struct tm *localTime = localtime(&currentTime);
    char formattedTime[20];
    strftime(formattedTime, sizeof(formattedTime), "%d-%m-%Y %H:%M", localTime);
    return string(formattedTime);
}

void welcome();
void addEntry();
void report();
void mainMenu();

int main()
{
    system("cls");
    welcome();
}

void welcome()
{
    cout << "\033[1;36m========================================" << endl;
    cout << "========Personal Finance Tracker========" << endl;
    cout << "========================================\033[0m" << endl;
    cout << "\033[1;33mWhat do you want to do?\033[0m" << endl;
    cout << endl;
    cout << "\033[32m1. Add Entry" << endl;
    cout << "2. Report\033[0m" << endl;
    cout << "\033[1;31m0. Exit\033[0m" << endl;
    cout << "--> ";
    int x;
    while (!(cin >> x) || x < 0 || x > 2)
    {
        cin.clear();
        cin.ignore();
        cout << "\033[1;31mInvalid option. Try again with valid options.\033[0m" << endl;
        cout << "-->";
    }

    if (x == 1)
    {
        addEntry();
    }
    if (x == 2)
    {
        report();
    }
    if (x == 0)
    {
        system("cls");
        cout << "\033[1;35mSpend your money mindfully." << endl;
        cout << "Good Luck! See you soon.\033[0m" << endl;
        exit(0);
    }
    mainMenu();
}

void addEntry()
{
    ofstream fout(dataPath, ios::app);
    string date = currentTime(), description, category;
    double amount;
    system("cls");
    cout << "\033[1;36m========================================" << endl;
    cout << "=============Adding an Entry============" << endl;
    cout << "========================================\033[0m" << endl;
    cout << "Current time: " << date << endl;
    cout << "Give a description: ";
    cin.ignore();
    getline(cin, description);
    do
    {
        cout << "Enter the cost: ";
        if (cin >> amount)
        {
            if (amount >= 0)
            {
                cin.ignore(1000, '\n');
                break;
            }
            else
            {
                cout << "\033[1;31mThe cost cannot be negative. Please try again.\033[0m" << endl;
            }
        }
        else
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\033[1;31mInvalid input. Please enter a valid number for the cost.\033[0m" << endl;
        }
    } while (true);

    cout << "Select a category:" << endl;
    cout << "1. Food" << endl;
    cout << "2. Rent" << endl;
    cout << "3. Utility" << endl;
    cout << "4. Entertainment" << endl;
    cout << "5. Transportation" << endl;
    cout << "6. Custom" << endl;
    cout << "-->";
    int x;
    while (!(cin >> x) || x < 1 || x > 6)
    {
        cin.ignore();
        cout << "\033[1;31mInvalid input. Please select a valid category (1-6)\033[0m" << endl;
        cout << "-->";
    }
    cin.ignore();
    switch (x)
    {
    case 1:
        category = "Food";
        break;
    case 2:
        category = "Rent";
        break;
    case 3:
        category = "Utility";
        break;
    case 4:
        category = "Entertainment";
        break;
    case 5:
        category = "Transportation";
        break;
    case 6:
        cout << "Enter custom category: ";
        getline(cin, category);
        break;
    default:
        break;
    }
    fout << date << "," << description << "," << amount << "," << category << endl;
    fout.close();
    system("cls");
    cout << "\033[1;32mEntry added successfully!\033[0m" << endl;
};

void report()
{
    system("cls");
    cout << "\033[1;36m========================================" << endl;
    cout << "=================Report=================" << endl;
    cout << "========================================\033[0m" << endl;
    ifstream fin(dataPath, ios::in);
    string line, date, description, amount, category;
    double totalSpending = 0, f = 0, r = 0, u = 0, e = 0, t = 0, o = 0;
    while (getline(fin, line))
    {
        string d, des, p, c;
        stringstream inString(line);
        getline(inString, d, ',');
        getline(inString, des, ',');
        getline(inString, p, ',');
        getline(inString, c, '\n');
        if (c == "Food")
        {
            f += stod(p);
        }
        else if (c == "Rent")
        {
            r += stod(p);
        }
        else if (c == "Utility")
        {
            u += stod(p);
        }
        else if (c == "Entertainment")
        {
            e += stod(p);
        }
        else if (c == "Transportation")
        {
            t += stod(p);
        }
        else
        {
            o += stod(p);
        }
        totalSpending += stod(p);
    }
    cout << "Spending on Food           : " << f << " BDT" << endl;
    cout << "Spending on Rent           : " << r << " BDT" << endl;
    cout << "Spending on Utility        : " << u << " BDT" << endl;
    cout << "Spending on Entertainment  : " << e << " BDT" << endl;
    cout << "Spending on Transportation : " << t << " BDT" << endl;
    cout << "Spending on Others         : " << o << " BDT" << endl;
    cout << "Total spending             : " << totalSpending << endl;
    cin.get();
    mainMenu();
}

void mainMenu()
{
    cout << "Press any key to go to main Menu" << endl;
    cout << "-->";
    cin.get();
    system("cls");
    welcome();
};