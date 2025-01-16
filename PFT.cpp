#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>
#include <limits>
#include <Windows.h>
using namespace std;

string dataPath = "data.csv";
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
void clear();
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
    ifstream fin(dataPath, ios::in);
    ofstream fout(dataPath, ios::app);
    bool isEmpty = fin.peek() == ifstream::traits_type::eof();
    string date = currentTime(), description, category;
    double amount;
    string month = date.substr(3, 2);
    system("cls");
    string line, matchMonth;
    getline(fin, line);
    stringstream inputString(line);
    getline(inputString, matchMonth);
    cout << "\033[1;36m========================================" << endl;
    cout << "=============Adding an Entry============" << endl;
    cout << "========================================\033[0m" << endl;
    if (isEmpty)
    {
        string date = currentTime();
        fout << date << ",Initial Entry,0.00,Initialization" << endl;
        addEntry();
    }
    cout << "Current time: " << date << endl;
    if (month == matchMonth.substr(3, 2))
    {
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
        mainMenu();
    }
    else
    {
        cout << "A new month has started." << endl;
        cout << "What would you like to do?" << endl;
        cout << "1. View the report for the previous month" << endl;
        cout << "2. Clear the data for the previous month and start fresh" << endl;
        cout << "--> ";
        int choice;
        while (!(cin >> choice) || (choice != 1 && choice != 2))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\033[1;31mInvalid choice. Please select 1 or 2.\033[0m" << endl;
            cout << "--> ";
        }
        cin.ignore();

        if (choice == 1)
        {
            report();
        }
        else if (choice == 2)
        {
            fin.close();
            fout.close();
            clear();
            cout << "\033[1;32mData cleared successfully. You can now start adding entries for the new month.\033[0m" << endl;
        }
    }
    fin.close();
    fout.close();
};
void report()
{
    system("cls");
    cout << "\033[1;36m========================================" << endl;
    cout << "=================Report=================" << endl;
    cout << "========================================\033[0m" << endl;
    ifstream fin(dataPath, ios::in);
    string linee, matchMonth;
    getline(fin, linee);
    stringstream inputString(linee);
    getline(inputString, matchMonth);
    string month = "Month-" + matchMonth.substr(3, 2);
    cout << "----------------" + month + "----------------" << endl;
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
void clear()
{
    string path = "data/month-" + currentTime().substr(3, 2) + ".csv";
    if (rename(dataPath.c_str(), path.c_str()) != 0)
    {
        perror("Error renaming file");
    }
    else
    {
        cout << "\033[1;32mPrevious month's data archived as: " << path << "\033[0m" << endl;
    }
    ofstream newFile(dataPath, ios::out);
    if (!newFile)
    {
        cout << "\033[1;31mError creating new CSV file for the current month.\033[0m" << endl;
        return;
    }
    newFile.close();
    cout << "\033[1;32mNew CSV file created for the current month.\033[0m" << endl;
}