#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <Windows.h>
#include <vector>
#include <conio.h>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

#define time 3
#define fastertime 1
#define LINE "----------------------"

struct account {
    string username;
    string password;
    int balance = 0;
};

vector<account> accounts;
int noAccounts = -1;

string readpass()
{
    string s;
    while (1)
    {
        char c = _getch();
        if (c == 13)
        {
            cout << "\n";
            return s;
        }
        else if (c == 8)
        {
            if (s.size() > 0)
            {
                s.pop_back();
                cout << "\b \b";
            }
        }
        else
        {
            s += c;
            cout << "*";
        }
    }
}


void readLog() {
    string user, pass;
    int bal;
    ifstream fin("accounts.log");
    fin >> noAccounts;
    for (int i = 0; i <= noAccounts; i++) {
        fin >> user >> pass >> bal;
        account a;
        a.username = user;
        a.password = pass;
        a.balance = bal;

        accounts.push_back(a);
    }
}

void writeLog() {
    ofstream fout("accounts.log");
    fout << noAccounts << "\n";
    for (int i = 0; i <= noAccounts; i++) {
        if(accounts[i].username != "closed")
          fout << accounts[i].username << " " << accounts[i].password << " " << accounts[i].balance << "\n";
    }
}

struct Bank {
public:
    void createAccount(string username, string password) {
        noAccounts++;
        accounts.resize(noAccounts + 1);
        accounts[noAccounts].username = username;
        accounts[noAccounts].password = password;
        accounts[noAccounts].balance = 0;
    }
    int findAccount(string username) {
        for (int i = 0; i <= noAccounts; i++) {
            if (accounts[i].username == username)
                return i;
        }
        return -1;
    }
    bool login(string username, string password) {
        int index;
        index = findAccount(username);
        if (index == -1 || accounts[index].password != password)
            return false;
        return true;
    }
    void deposit(string username, int ammount) {
        accounts[findAccount(username)].balance += ammount;
    }
    void withdraw(string username, int ammount) {
        accounts[findAccount(username)].balance -= ammount;
    }
    int balanceCheck(string username) {
        return  accounts[findAccount(username)].balance;
    }
    void transfer(string sender, string recepient, int ammount) {
        accounts[findAccount(sender)].balance -= ammount;
        accounts[findAccount(recepient)].balance += ammount;
    }
    void closeAccount(string username){
        accounts[findAccount(username)].username = "closed";
    }
};

void loggedinMenu(string usernames);

void mainMenu() {
    string username, password1, password2, choice;
    {
        cout << "  /$$$$$$                  /$$          \n";
        cout << " /$$__  $$                | $$          \n";
        cout << "| $$  \\ $$ /$$$$$$$   /$$$$$$$ /$$   /$$\n";
        cout << "| $$$$$$$$| $$__  $$ /$$__  $$| $$  | $$\n";
        cout << "| $$__  $$| $$  \\ $$| $$  | $$| $$  | $$\n";
        cout << "| $$  | $$| $$  | $$| $$  | $$| $$  | $$\n";
        cout << "| $$  | $$| $$  | $$|  $$$$$$$|  $$$$$$/\n";
        cout << "|__/  |__/|__/  |__/ \\_______/ \\______/ \n";
        cout << "                                        \n";
        cout << "                                        \n";
        cout << "                                        \n";
        cout << " /$$$$$$$                      /$$      \n";
        cout << "| $$__  $$                    | $$      \n";
        cout << "| $$  \\ $$  /$$$$$$  /$$$$$$$ | $$   /$$\n";
        cout << "| $$$$$$$  |____  $$| $$__  $$| $$  /$$/\n";
        cout << "| $$__  $$  /$$$$$$$| $$  \\ $$| $$$$$$/ \n";
        cout << "| $$  \\ $$ /$$__  $$| $$  | $$| $$_  $$ \n";
        cout << "| $$$$$$$/|  $$$$$$$| $$  | $$| $$ \\  $$\n";
        cout << "|_______/  \\_______/|__/  |__/|__/  \\__/\n";
        cout << "                                        \n";
        cout << "                                        \n";
        cout << "                                        \n";
    }
    cout << "Welcome to Andu Bank!\n\nWe are not as the others, you can trustfully deposit your salary or get a loan from us\nand we promise to take even more money from you as tax than our competitors<3\n\nIf you consider that having to create or log in an account after you have already inserted\nyour card please understand it's just another way we can steal even more money from you.";
    cout << "\n\nChoose one of the following options:\n\n1 -> Create a new account\n\n2 -> Log in an already existing account\n\n3 -> Exit(You will not get your card back)\n\nYour choice: ";
    cin >> choice;
    if (choice < "1" || choice>"3") {
        system("CLS");
        cout << "That is not a valid option! Please try again!";
        sleep_for(seconds(time));
        system("CLS");
        mainMenu();
        return;
    }
    if (choice == "3") {
        writeLog();
        return;
    }
    if (choice == "1") {
        Bank bank;
        system("CLS");
        cout << "Please enter the desired username: ";
        cin >> username;
        if (bank.findAccount(username) != -1) {
            cout << "\nThere is already another account with that username. Please try again!";
            sleep_for(seconds(time));
            system("CLS");
            mainMenu();
            return;
        }
        if (username=="closed") {
            cout << "\nThat username is unavailable!Please try again...";
            sleep_for(seconds(time));
            system("CLS");
            mainMenu();
            return;
        }
        cout << "\nPerfect! The username is available!";
        sleep_for(seconds(fastertime));
        cout << "\n\nPlease enter your password(preferably the one from gmail, netflix, paypal, etc...):  ";
        password1 = readpass();
        cout << "\n\nPlease enter your unsafe password again: ";
        password2 = readpass();
        if (password1 != password2) {
            system("CLS");
            cout << "You have managed to write two different passwords...Please try again and do better!";
            sleep_for(seconds(time));
            system("CLS");
            mainMenu();
            return;
        }
        bank.createAccount(username, password1);
        system("CLS");
        cout << "Your account has been succesfully created! It's credentials have been shared with the 437 hackers. Returning to the main menu...";
        sleep_for(seconds(time));
        system("CLS");
        loggedinMenu(username);
        return;
    }
    if (choice == "2") {
        Bank bank;
        system("CLS");
        cout << "Please enter your username: ";
        cin >> username;
        cout << "\n\nPlease enter your password:  ";
        password1 = readpass();
        if (!bank.login(username, password1)) {
            system("CLS");
            cout << "The username and password do not match any account in our unsecure database...Please try again!";
            sleep_for(seconds(time));
            system("CLS");
            mainMenu();
            return;
        }
        else {
            system("CLS");
            loggedinMenu(username);
            return;
        }
    }
}

void loggedinMenu(string username) {
    int ammount;
    string recepient, yesno, choice;
    Bank bank;
    cout << "  /$$$$$$                  /$$          \n";
    cout << " /$$__  $$                | $$          \n";
    cout << "| $$  \\ $$ /$$$$$$$   /$$$$$$$ /$$   /$$\n";
    cout << "| $$$$$$$$| $$__  $$ /$$__  $$| $$  | $$\n";
    cout << "| $$__  $$| $$  \\ $$| $$  | $$| $$  | $$\n";
    cout << "| $$  | $$| $$  | $$| $$  | $$| $$  | $$\n";
    cout << "| $$  | $$| $$  | $$|  $$$$$$$|  $$$$$$/\n";
    cout << "|__/  |__/|__/  |__/ \\_______/ \\______/ \n";
    cout << "                                        \n";
    cout << "                                        \n";
    cout << "                                        \n";
    cout << " /$$$$$$$                      /$$      \n";
    cout << "| $$__  $$                    | $$      \n";
    cout << "| $$  \\ $$  /$$$$$$  /$$$$$$$ | $$   /$$\n";
    cout << "| $$$$$$$  |____  $$| $$__  $$| $$  /$$/\n";
    cout << "| $$__  $$  /$$$$$$$| $$  \\ $$| $$$$$$/ \n";
    cout << "| $$  \\ $$ /$$__  $$| $$  | $$| $$_  $$ \n";
    cout << "| $$$$$$$/|  $$$$$$$| $$  | $$| $$ \\  $$\n";
    cout << "|_______/  \\_______/|__/  |__/|__/  \\__/\n";
    cout << "                                        \n";
    cout << "                                        \n";
    cout << "                                        \n\n";
    cout << "Logged in as " << username << ".\n\n";
    cout << "Please choose one of the following options: \n\n";
    cout << "1 -> Withdraw\n\n";
    cout << "2 -> Deposit\n\n";
    cout << "3 -> Check the balance of you account\n\n";
    cout << "4 -> Transfer to another account\n\n";
    cout << "5 -> Close account\n\n";
    cout << "6 -> Log out of " << username << "\n\n";
    cin >> choice;
    if (choice < "1" || choice>"6") {
        system("CLS");
        cout << "That is not a valid option! Please try again!";
        sleep_for(seconds(time));
        system("CLS");
        loggedinMenu(username);
        return;
    }
    if (choice == "6") {
        system("CLS");
        cout << "Logging out of " << username << "...";
        sleep_for(seconds(time));
        system("CLS");
        mainMenu();
        return;
    }
    if(choice == "5"){
        system("CLS");
        cout << "Are you sure you want to close the folowing account " << username << "???\n";
        cout<<"Type YES or NO: ";
        cin>>yesno;
        if(yesno!="YES"){
          system("CLS");
          loggedinMenu(username);
        }
        system("CLS");
        cout<<"Closing account "<<username<<" ...";
        sleep_for(seconds(time));
        system("CLS");
        bank.closeAccount(username);
        mainMenu();
        return;
    }
    if (choice == "3") {
        system("CLS");
        cout << "The available balance in your account is: $" << bank.balanceCheck(username);
        sleep_for(seconds(time));
        system("CLS");
        loggedinMenu(username);
        return;
    }
    if (choice == "2") {
        system("CLS");
        cout << "Please enter the ammount you wish to deposit: ";
        cin >> ammount;
        system("CLS");
        cout << "Depositing " << ammount << "$...";
        sleep_for(seconds(time));
        system("CLS");
        bank.deposit(username, ammount);
        cout << "Succesfully deposited " << ammount << "$ in account " << username << "\nAvailable balance $" << bank.balanceCheck(username);
        sleep_for(seconds(time));
        system("CLS");
        loggedinMenu(username);
        return;
    }
    if (choice == "1") {
        system("CLS");
        cout << "Please enter the ammount you wish to withdraws: ";
        cin >> ammount;
        system("CLS");
        if (accounts[bank.findAccount(username)].balance < ammount) {
            system("CLS");
            cout << "There is not enough money in the account to withdraw $" << ammount << " Please try again..." << "\nAvailable ammount $" << accounts[bank.findAccount(username)].balance;
            sleep_for(seconds(time));
            system("CLS");
            loggedinMenu(username);
            return;
        }
        cout << "Withdrawing " << ammount << "$...";
        sleep_for(seconds(time));
        system("CLS");
        bank.withdraw(username, ammount);
        cout << "Succesfully withdrawn " << ammount << "$ from account " << username << "\nRemaining balance $" << accounts[bank.findAccount(username)].balance;
        sleep_for(seconds(time));
        system("CLS");
        loggedinMenu(username);
        return;
    }
    if (choice == "4") {
        system("CLS");
        cout << "Please enter the recepient of your transfer: ";
        cin >> recepient;
        cout << "\n\nPlease enter the ammount you wish to transfer: ";
        cin >> ammount;
        system("CLS");
        if (accounts[bank.findAccount(username)].balance < ammount) {
            system("CLS");
            cout << "There is not enough money in the account to complete the transfer $" << ammount << " Please try again..." << "\nAvailable ammount $" << accounts[bank.findAccount(username)].balance;
            sleep_for(seconds(time));
            system("CLS");
            loggedinMenu(username);
            return;
        }
        if (bank.findAccount(recepient) == -1) {
            system("CLS");
            cout << "The account you wish to transfer to doesn't exist. Please try again...";
            sleep_for(seconds(time));
            system("CLS");
            loggedinMenu(username);
            return;
        }
        cout << "Transfering " << ammount << "$...";
        sleep_for(seconds(time));
        system("CLS");
        bank.transfer(username, recepient, ammount);
        cout << "Succesfully transfered " << ammount << "$ from account " << username << " to account " << recepient << "\nRemaining balance $" << bank.balanceCheck(username);
        sleep_for(seconds(time));
        system("CLS");
        loggedinMenu(username);
        return;
    }
}

void  intro() {
    string pin;
    cout << "Enter card.";
    while (true) {
        cout << ".";
        if (GetKeyState(VK_SPACE) & 0x8000)
            break;
        sleep_for(milliseconds(500));
        cout << ".";
        if (GetKeyState(VK_SPACE) & 0x8000)
            break;
        sleep_for(milliseconds(500));
        cout << "\b \b";
        if (GetKeyState(VK_SPACE) & 0x8000)
            break;
        sleep_for(milliseconds(500));
        cout << "\b \b";
        if (GetKeyState(VK_SPACE) & 0x8000)
            break;
        sleep_for(milliseconds(500));
    }
    system("CLS");
    cout << "Note: Be sure that no one is around as we will not take any safety precautions\nto keep your account safe. We can not ensure you that there is any money left in your\naccount at any given point in time as we have probably sold all your personal\ninformation and stole all the money in your account!";
    cout << "\n\nEnter your pin: ";
    cin >> pin;
    system("CLS");
    cout << "Sending your pin and card information to 437 hackers, please wait...";
    sleep_for(seconds(time));
    system("CLS");
    cout << "Succes! You will now proceed to our totally legit and not scam banking options...";
    sleep_for(seconds(time));
    system("CLS");
    mainMenu();
}

void maximizeWindow()
{
    system("mode con COLS=700");
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
    SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
}

int main()
{
    maximizeWindow();
    readLog();
    intro();
    return 0;
}
