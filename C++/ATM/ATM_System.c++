#include<iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct stAccount
{
    string Accountname;
    string PinCode;
    int Balance;
    bool MarkForDelete = false;
};

stAccount  CurrentAccount;
const string AccountFileName = "Accounts.txt";

void ShowMainMenue(int Balance);
void PerformMainMenueOption(int UserSelection, int Balance);
void QuickWithdraw(int Balance);
void login();

void Selections(){
    cout << "\t[1] Quick Withdraw.\n";
    cout << "\t[2] Normal Withdraw.\n";
    cout << "\t[3] Deposit\n";
    cout << "\t[4] Check Balance.\n";
    cout << "\t[5] Logout.";
}


void QuickWithdraw(int Balance){
    system("cls");
    int QuickWithdrawAmounts[] = {20, 50, 100, 200, 400, 600, 800, 1000};
    cout << "\n======================================\n";
    cout << "\t    Quick Withdraw";
    cout << "\n======================================\n";

    int withdraw;

    for (int i = 1;i <= 8; i++){
        cout << "\t["<< i <<"] " << QuickWithdrawAmounts[i - 1];

        if (i % 2 != 0){
          cout << "\t";
        }else {
            cout << "\n";
        }
    }

    cout << "\t[9] Exit\n";
    cout << "======================================\n";
    
    cout << "Your Balance is: [" << Balance << "]\n";
    cout << "choose what to withdraw from [1] to [8] ?";
    cin >> withdraw;

    string Sure;
    cout << "\n\nAre you Sure? ";
    cin >> Sure;
    
    if (Sure == "y" || Sure == "Y"){
        for (int i = 1;i <= 8; i++){
            if (Balance > QuickWithdrawAmounts[i - 1]){
                if (withdraw == i){
                    Balance -= QuickWithdrawAmounts[i - 1];
                }
            } else {
                cout << "The amount exceeds your balance, make another choice.";
                system("pause");
                QuickWithdraw(Balance);
            }
        }
        if (withdraw == 9){
            cout << "" ;
        }
    }
    cout << "\n\nDone Successfully. New balance is : " << Balance <<" \n";
    
    cout << "\nPress any key to go back to Main Menue... ";
    system("pause > nul");
    ShowMainMenue(Balance);

}

void NormalWithdraw(int Balance){
    system("cls");
    cout << "\n======================================\n";
    cout << "\t    Normal Withdraw";
    cout << "\n======================================\n";

    int NormalWthdrawAmount;

    cout << "\nEnter an amount multiple of 5's ?";
    cin >> NormalWthdrawAmount;

    while ((NormalWthdrawAmount % 5) == 0){
        if ((NormalWthdrawAmount % 5) == 0){
            if (Balance > NormalWthdrawAmount){
                string Sure;
                cout << "\n\nAre you Sure? ";
                cin >> Sure;

                if (Sure == "y" || Sure == "Y"){
                    Balance -= NormalWthdrawAmount;
                }
            } else {
                cout << "The amount exceeds your balance, make another choice.";
                system("pause");
                QuickWithdraw(Balance);
            }
        } else {
            cout << "\nEnter an amount multiple of 5's ?";
            cin >> NormalWthdrawAmount;
            
        }      
    }

           
    cout << "\n\nDone Successfully. New balance is : " << Balance <<" \n";
    
    cout << "\nPress any key to go back to Main Menue... ";
    system("pause > nul");
    ShowMainMenue(Balance);

}

void Deposit(int Balance){
    system("cls");
    cout << "\n======================================\n";
    cout << "\t    Deposit Screen";
    cout << "\n======================================\n";

    int Deposit_number;
    cout << "\nEnter a Positive Number: ";
    cin >> Deposit_number;

    if (Deposit_number < 0){
        cout << "Please Enter A poistive Number!";
        Deposit(Balance);
    }

    string Sure;
    cout << "\n\nAre you Sure? ";
    cin >> Sure;
    
    if (Sure == "y" || Sure == "Y"){
        Balance += Deposit_number;
    }
    cout << "\n\nDone Successfully. New balance is : " << Balance <<" \n";

    cout << "\nPress any key to go back to Main Menue... ";
    system("pause > nul");
    ShowMainMenue(Balance);
}

void CheckBalance(int Balance){
    cout << "\n==========================================\n";
    cout << "\t    Check Balance Screen";
    cout << "\n==========================================\n";

    cout << "Your balance is " << Balance <<" \n\n";

    cout << "\nPress any key to go back to Main Menue... ";
    system("pause > nul");
    ShowMainMenue(Balance);
}


void PerformMainMenueOption(int UserSelection, int Balance){
    if (UserSelection == 1){
        QuickWithdraw(Balance);
    } else if (UserSelection == 2){
        NormalWithdraw(Balance);
    } else if (UserSelection == 3){
        Deposit(Balance);
    } else if (UserSelection == 4){
        CheckBalance(Balance);
    } else if (UserSelection == 5){
        login();
    }  else {
        cout << "\nPlease Enter From [1] to [5]";
    }
}

void ShowMainMenue(int Balance){
    cout << "\n=============================================\n";
    cout << "\t   ATM Main Menue Screen";
    cout << "\n=============================================\n";

    Selections();
    cout << "\n=============================================\n";
    
    int UserSelection;
    cout << "Choose What do you want to do? [1 to 5] ? ";
    cin >> UserSelection;

    PerformMainMenueOption(UserSelection, Balance);
}


vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    short pos = 0;
    string sWord;

    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos);
        
        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length());
    }

    if (S1 != "")
    {
        vString.push_back(S1);
    }

    return vString;
}

stAccount ConvertAccountLineToRecord(string line, string seperator = "#//#"){
    stAccount Account;
    vector <string> VAccountData;

    VAccountData = SplitString(line,seperator);

    Account.Accountname = VAccountData[0];
    Account.PinCode = VAccountData[1];
    Account.Balance = stoi(VAccountData[2]);
    return Account;
}

vector <stAccount> LoadAccountsDataFromFile(string FileName){
    vector <stAccount> VAccounts;
    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open()){
        string line;
        stAccount Account;
        
        while (getline(MyFile, line)){
            Account = ConvertAccountLineToRecord(line);
            VAccounts.push_back(Account);
        }

        MyFile.close();
    }
    return VAccounts;
}

bool FindAccountByAccountNameAndPinCode(string AccountName, string PinCode, stAccount& Account){
    vector <stAccount> VAccounts = LoadAccountsDataFromFile(AccountFileName);

    for (stAccount A:VAccounts){

        if (A.Accountname == AccountName){
            Account = A;
            return true;
        }
    }

    return false;
}

bool LoadAccountInfo(string AccountName, string PinCode){
    if (FindAccountByAccountNameAndPinCode(AccountName, PinCode, CurrentAccount)){
        return true;
    } else {
        return false;
    }
}

void login(){
    bool loginFailed = false;

    string AccountName, PinCode;
    do{
        system("cls");

        cout << "\n-----------------------------\n" ;
        cout << "\tLogin Screen";
        cout << "\n-----------------------------\n" ;

        if(loginFailed){
            cout <<"Invalid AccountName/PinCode\n";
        }

        cout << "Enter Account Number:";
        cin >> AccountName;
        cout << "Enter PinCode:";
        cin >> PinCode;

        loginFailed = !LoadAccountInfo(AccountName, PinCode);
    } while(loginFailed);

    vector <stAccount> VAccounts = LoadAccountsDataFromFile(AccountFileName);
    ShowMainMenue(CurrentAccount.Balance);
}

int main(){
    login();
}