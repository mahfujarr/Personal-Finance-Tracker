# Explanation of Feature Implementations in `pft.cpp`

## 1. Input Expenses and Income

### Functionality:

- The `addEntry()` function allows users to record financial transactions by entering the date, description, amount, and category.

### Implementation:

- It uses `currentTime()` to fetch the current date and time automatically.
- Users input details like description, cost, and category (predefined or custom).
- Data is stored in a CSV file (`data.csv`) for persistence.

---

## 2. Categorize Transactions

### Functionality:

- Users can assign categories to transactions (Food, Rent, Utility, Entertainment, Transportation, or a custom category).

### Implementation:

- A switch-case in `addEntry()` handles predefined categories.
- If the user selects the custom option, they can manually enter a new category.

---

## 3. Generate Monthly Report

### Functionality:

- The `report()` function summarizes spending by category and calculates total expenses.
- The `clear()` function moves all the data to `month-xx` to keep the history of spending and removes all contents from `data.csv`.

### Implementation:

- Reads transaction data from `data.csv`.
- Aggregates spending for predefined and custom categories.
- Displays totals for each category and the overall expenditure.

---

## Additional Features

### User Interface:

- The `welcome()` and `mainMenu()` functions create a simple text-based menu for navigation.
- Input validation ensures robustness (e.g., non-negative amounts, valid menu options).

### Data Persistence:

- All transactions are stored in `data.csv`, ensuring they remain available across program runs.

### Custom Categories:

- Users can add unique categories during transaction entry.

---

The program effectively addresses the requirements, focusing on simplicity and essential financial tracking features.
