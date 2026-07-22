# Personal Budget Tracker (C++)

## About

Personal Budget Tracker is a console-based application developed in C++. It helps users manage their personal finances by recording income and expenses, tracking transactions, viewing statistics, and generating reports. All data is automatically saved and loaded using text files.

---

## Features

* Add income transactions
* Add expense transactions
* List all transactions
* Filter transactions by:

  * Income
  * Expense
  * Category
* Display current balance
* View financial statistics
* Update existing transactions
* Delete transactions
* Automatically save transactions to a file
* Automatically load saved transactions
* Generate a report
* Record the date and time of each transaction

---

## Technologies Used

* C++
* Object-Oriented Programming (OOP)
* STL Vector
* File Handling (`fstream`)
* Date and Time (`ctime`)
* Formatted Output (`iomanip`)

---

## Project Structure

```text
PersonalBudgetTracker/
│
├── main.cpp
├── transactions.txt
├── report.txt
└── README.md
```

---

## How to Run

1. Clone the repository.

```bash
git clone https://github.com/niltbeyhan34/personal-budget-tracker
```

2. Open the project directory.

```bash
cd personal-budget-tracker-cpp
```

3. Compile the project.

```bash
g++ main.cpp -o budget_tracker
```

4. Run the application.

```bash
./budget_tracker
```

---

## Sample Menu

```text
========== PERSONAL BUDGET TRACKER ==========

1. Add Income
2. Add Expense
3. List Transactions
4. Filter Transactions
5. Show Balance
6. Generate Report
7. Update Transaction
8. Delete Transaction
9. Show Statistics
10. Exit
```

---

## Future Improvements

* Monthly and yearly reports
* Budget planning
* Data visualization
* Export reports in different formats
* Graphical User Interface (GUI)

---

## Author

**Nil Tuana Beyhan**

Software Engineering Student

GitHub: https://github.com/niltbeyhan34
