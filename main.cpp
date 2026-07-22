#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <ctime>

using namespace std;

class Transaction
{
public:
    int id;
    string type;
    double amount;
    string category;
    string description;
    string date;
};

vector<Transaction> transactions;

void showMenu();
void addIncome();
void addExpense();
void listTransactions();
void showBalance();
void saveToFile();
void loadFromFile();
void createReport();
void deleteTransaction();
void updateTransaction();
void showStatistics();
void filterTransactions();
void printTableHeader();
void printTransaction(const Transaction &t);
string chooseIncomeCategory();
string chooseExpenseCategory();
string getCurrentDate();


int main()
{
    loadFromFile();

    int choice;

    do
    {
        showMenu();
        cin >> choice;

        switch(choice)
        {
            case 1:
                addIncome();
                break;

            case 2:
                addExpense();
                break;

            case 3:
                listTransactions();
                break;

            case 4:
                filterTransactions();
                break;
                        
            case 5:
                showBalance();
                break;

            case 6:
                createReport();
                break;

            case 7:
                updateTransaction();
                break;

            case 8:
                deleteTransaction();
                break;

            case 9:
                showStatistics();
                break;

            case 10:
                cout << "Programdan cikiliyor...\n";
                break;

            default:
                cout << "Gecersiz secim!" << endl;
        }

    } while(choice != 10);

    return 0;
}

void showMenu()
{
    cout << "\n========== PERSONAL BUDGET TRACKER ==========\n";
    cout << "1. Gelir Ekle\n";
    cout << "2. Gider Ekle\n";
    cout << "3. Islemleri Listele\n";
    cout << "4. Islemleri Filtrele\n";
    cout << "5. Bakiyeyi Goster\n";
    cout << "6. Rapor Olustur\n";
    cout << "7. Islem Guncelle\n";
    cout << "8. Islem Sil\n";
    cout << "9. Istatistikler\n";
    cout << "10. Cikis\n";
    cout << "Seciminiz: ";
}

void addIncome()
{
    Transaction t;

    t.id = transactions.size() + 1;
    t.type = "Income";

    do
    {
        cout << "\nGelir Tutari: ";
        cin >> t.amount;

        if(t.amount <= 0)
        {
            cout << "Lutfen 0'dan buyuk bir tutar giriniz.\n";
        }

    } while(t.amount <= 0);

    t.category = chooseIncomeCategory();

    cin.ignore();

    cout << "Aciklama: ";
    getline(cin, t.description);

    t.date = getCurrentDate();

    transactions.push_back(t);

    saveToFile();

    cout << "\nGelir basariyla eklendi!\n";
}
void addExpense()
{
    Transaction t;

    t.id = transactions.size() + 1;
    t.type = "Expense";

    do
    {
        cout << "\nGider Tutari: ";
        cin >> t.amount;

        if(t.amount <= 0)
        {
            cout << "Lutfen 0'dan buyuk bir tutar giriniz.\n";
        }

    } while(t.amount <= 0);

    t.category = chooseExpenseCategory();

    cin.ignore();

    cout << "Aciklama: ";
    getline(cin, t.description);

    t.date = getCurrentDate();

    transactions.push_back(t);

    saveToFile();

    cout << "\nGider basariyla eklendi!\n";
}

void listTransactions()
{
    if(transactions.empty())
    {
        cout << "\nHenuz hic islem yok!\n";
        return;
    }

    cout << fixed << setprecision(2);

    printTableHeader();

    for(const auto &t : transactions)
    {
        printTransaction(t);
    }

    cout << string(110, '=') << endl;
}

void showBalance()
{
    double balance = 0;

    for(const auto &t : transactions)
    {
        if(t.type == "Income")
        {
            balance += t.amount;
        }
        else
        {
            balance -= t.amount;
        }
    }

    cout << fixed << setprecision(2);
    cout << "\nMevcut Bakiye: " << balance << " TL\n";
}

void saveToFile()
{
    ofstream file("transactions.txt");

    if(!file)
    {
        cout << "Dosya acilamadi!" << endl;
        return;
    }

    for(const auto &t : transactions)
    {
        file << t.id << endl;
        file << t.type << endl;
        file << t.amount << endl;
        file << t.category << endl;
        file << t.description << endl;
        file << t.date << endl;
    }

    file.close();
}

void createReport()
{
    ofstream report("report.txt");

    if(!report)
    {
        cout << "Rapor dosyasi olusturulamadi!" << endl;
        return;
    }

    report << "========== PERSONAL BUDGET REPORT ==========\n\n";

    double balance = 0;

    for(const auto &t : transactions)
    {
        report << "ID          : " << t.id << endl;
        report << "Type        : " << t.type << endl;
        report << "Amount      : " << t.amount << " TL" << endl;
        report << "Category    : " << t.category << endl;
        report << "Description : " << t.description << endl;
        report << "Date        : " << t.date << endl;
        report << "--------------------------------------------" << endl;

        if(t.type == "Income")
            balance += t.amount;
        else
            balance -= t.amount;
    }

    report << "\nCurrent Balance : " << balance << " TL" << endl;

    report.close();

    cout << "\nRapor basariyla olusturuldu!" << endl;
}

 

void deleteTransaction()
{
    if(transactions.empty())
    {
        cout << "\nSilinecek islem bulunamadi.\n";
        return;
    }

    int id;

    cout << "\nSilmek istediginiz ID: ";
    cin >> id;

    for(int i = 0; i < transactions.size(); i++)
    {
        if(transactions[i].id == id)
        {
            transactions.erase(transactions.begin() + i);

            for(int j = 0; j < transactions.size(); j++)
            {
                transactions[j].id = j + 1;
            }

            saveToFile();

            cout << "\nIslem basariyla silindi.\n";
            return;
        }
    }

    cout << "\nBu ID'ye ait islem bulunamadi.\n";
}

void loadFromFile()
{
    ifstream file("transactions.txt");

    if(!file)
    {
        return;
    }

    Transaction t;

    while(file >> t.id)
    {
        file >> t.type;
        file >> t.amount;

        file.ignore();

        getline(file, t.category);
        getline(file, t.description);
        getline(file, t.date);

        transactions.push_back(t);
    }

    file.close();
}

void updateTransaction()
{
    if(transactions.empty())
    {
        cout << "\nGuncellenecek islem bulunamadi.\n";
        return;
    }

    int id;

    cout << "\nGuncellemek istediginiz ID: ";
    cin >> id;

    for(auto &t : transactions)
    {
        if(t.id == id)
        {
            do
            {
                cout << "Yeni tutar: ";
                cin >> t.amount;

                if(t.amount <= 0)
                {
                    cout << "Lutfen 0'dan buyuk bir tutar giriniz.\n";
                }

            } while(t.amount <= 0);

            saveToFile();

            cout << "\nIslem basariyla guncellendi.\n";
            return;
        }
    }

    cout << "\nBu ID'ye ait islem bulunamadi.\n";
}

void showStatistics()
{
    if(transactions.empty())
    {
        cout << "\nHenuz hic islem yok!\n";
        return;
    }

    double totalIncome = 0;
    double totalExpense = 0;

    int incomeCount = 0;
    int expenseCount = 0;

    for(const auto &t : transactions)
    {
        if(t.type == "Income")
        {
            totalIncome += t.amount;
            incomeCount++;
        }
        else
        {
            totalExpense += t.amount;
            expenseCount++;
        }
    }

    cout << fixed << setprecision(2);

    cout << "\n========== ISTATISTIKLER ==========\n";
    cout << "Toplam Gelir  : " << totalIncome << " TL\n";
    cout << "Toplam Gider  : " << totalExpense << " TL\n";
    cout << "Mevcut Bakiye : " << totalIncome - totalExpense << " TL\n";
    cout << "Gelir Sayisi  : " << incomeCount << endl;
    cout << "Gider Sayisi  : " << expenseCount << endl;
    cout << "Toplam Islem  : " << transactions.size() << endl;
}

void printTableHeader()
{
    cout << string(110, '=') << endl;

    cout << left
         << setw(5)  << "ID"
         << setw(12) << "Type"
         << setw(15) << "Amount(TL)"
         << setw(15) << "Category"
         << setw(30) << "Description"
         << setw(20) << "Date"
         << endl;

    cout << string(110, '=') << endl;
}

void printTransaction(const Transaction &t)
{
    cout << left
         << setw(5)  << t.id
         << setw(12) << t.type
         << setw(15) << t.amount
         << setw(15) << t.category
         << setw(30) << t.description
         << setw(20) << t.date
         << endl;
}

void filterTransactions()
{
    if(transactions.empty())
    {
        cout << "\nHenuz hic islem yok!\n";
        return;
    }

    int choice;

    do
    {

    cout << "\n===== FILTRELE =====\n";
    cout << "1. Gelirleri Listele\n";
    cout << "2. Giderleri Listele\n";
    cout << "3. Kategoriye Gore Listele\n";
    cout << "4. Geri Don\n";
    cout << "Seciminiz: ";
    cin >> choice;

    switch(choice)
    {
        case 1:
        { 

            cout << fixed << setprecision(2);

            printTableHeader();

            bool found = false;

            for(const auto &t : transactions)
            {
                if(t.type == "Income")
                {
                    printTransaction(t);
                    found = true;
                }
            }

            if(!found)
            {
                cout << "\nBu filtreye uygun islem bulunamadi.\n";
            }

            cout << string(110,'=') << endl;

            break;
        }

        case 2:
        {
            cout << fixed << setprecision(2);

            printTableHeader();

            bool found = false;

            for(const auto &t : transactions)
            {
                if(t.type == "Expense")
                {
                    printTransaction(t);
                    found = true;
                }
            }

            if(!found)
            {
                cout << "\nBu filtreye uygun islem bulunamadi.\n";
            }

            cout << string(110,'=') << endl;

            break;
        }

        case 3:
        {
            int categoryChoice;
            string selectedCategory;

            cout << "\n===== KATEGORILER =====\n";
            cout << "1. Maas\n";
            cout << "2. Burs\n";
            cout << "3. Freelance\n";
            cout << "4. Market\n";
            cout << "5. Ulasim\n";
            cout << "6. Fatura\n";
            cout << "7. Eglence\n";
            cout << "8. Saglik\n";
            cout << "9. Diger\n";

            cout << "\nSeciminiz: ";
            cin >> categoryChoice;

            switch(categoryChoice)
            {
                case 1:
                    selectedCategory = "Maas";
                    break;

                case 2:
                    selectedCategory = "Burs";
                    break;

                case 3:
                    selectedCategory = "Freelance";
                    break;

                case 4:
                    selectedCategory = "Market";
                    break;

                case 5:
                    selectedCategory = "Ulasim";
                    break;

                case 6:
                    selectedCategory = "Fatura";
                    break;

                case 7:
                    selectedCategory = "Eglence";
                    break;

                case 8:
                    selectedCategory = "Saglik";
                    break;

                case 9:
                    selectedCategory = "Diger";
                    break;

                default:
                    cout << "Gecersiz secim!\n";
                    return;
            }

            cout << fixed << setprecision(2);

            printTableHeader();

            bool found = false;

            for(const auto &t : transactions)
            {
                if(t.category == selectedCategory)
                {
                    printTransaction(t);
                    found = true;
                }
            }

            if(!found)
            {
                cout << "\nBu kategoriye ait islem bulunamadi.\n";
            }

            cout << string(110,'=') << endl;

            break;
        }

        case 4:
            return;

        default:
            cout << "Gecersiz secim!\n";
        }

    } while(choice != 4);
}

string getCurrentDate()
{
    time_t now = time(0);

    tm *current = localtime(&now);

    char date[20];

    strftime(date, sizeof(date), "%d.%m.%Y %H:%M", current);

    return date;
}

string chooseExpenseCategory()
{
    int choice;

    cout << "\nGider Kategorileri\n";
    cout << "1. Market\n";
    cout << "2. Ulasim\n";
    cout << "3. Fatura\n";
    cout << "4. Eglence\n";
    cout << "5. Saglik\n";
    cout << "6. Diger\n";
    cout << "Seciminiz: ";
    cin >> choice;

    switch(choice)
    {
        case 1:
            return "Market";
        case 2:
            return "Ulasim";
        case 3:
            return "Fatura";
        case 4:
            return "Eglence";
        case 5:
            return "Saglik";
        default:
            return "Diger";
    }
}

string chooseIncomeCategory()
{
    int choice;

    cout << "\nGelir Kategorileri\n";
    cout << "1. Maas\n";
    cout << "2. Burs\n";
    cout << "3. Freelance\n";
    cout << "4. Diger\n";
    cout << "Seciminiz: ";
    cin >> choice;

    switch(choice)
    {
        case 1:
            return "Maas";

        case 2:
            return "Burs";

        case 3:
            return "Freelance";

        default:
            return "Diger";
    }
}