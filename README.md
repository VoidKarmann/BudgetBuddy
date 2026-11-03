# BudgetBuddy

An Event Budget Tracker and Management system written in C.
Made as a mini project for C Programming (BCA Data Science, Semester 1).

## About

BudgetBuddy helps you plan an event within a budget. You set a total budget, add expenses under different categories, and the program tells you how much you have spent, how much is left, and warns you when you are close to or over the budget.

## Features

- Create a new event (name, date, total budget)
- Load a previously saved event
- Add expenses with a category (Food, Venue, Decor, Music, Other)
- View all expenses in a table
- Search an expense by name
- Update an expense amount
- Delete an expense
- Budget summary: total spent, remaining, percentage used
- Warning at 80% of budget and when over budget
- Category-wise spending totals
- Highest expense
- Save and load events from files
- Activity log of every expense added (log.txt)

## C Concepts Used

- Variables, constants (`#define`), data types
- Input and output (`printf`, `scanf`)
- Operators
- Decision making (`if`, `if-else`, nested `if`, `switch`)
- Loops (`for`, `while`, `do-while`)
- `break` and `continue`
- Arrays and 2D arrays
- Strings and string functions (`strcpy`, `strcmp`, `strcat`)
- User-defined functions and parameter passing
- Recursion (recursive total calculation)
- Pointers
- Dynamic memory allocation (`malloc`, `free`)
- Structures and array of structures
- File handling (write, read, append)

## How to Compile and Run

1. Install a C compiler such as GCC (MinGW on Windows).
2. Open a terminal in the project folder.
3. Compile: `gcc event_budget_tracker.c -o BudgetBuddy`
4. Run: `.\BudgetBuddy` (Windows) or `./BudgetBuddy` (Linux/Mac)

## How to Use

1. Choose 1 to create a new event, or 2 to load a saved one.
2. Use the main menu (1 to 9) to add, view, search, update or delete expenses and see summaries.
3. Choose 9 to save the event to a file named after the event.
4. Choose 0 to exit.

## Limitations

- Maximum of 100 expenses per event
- Search is case-sensitive
- Entering letters where a number is expected can cause the menu to loop

## Future Scope

- Handle multiple events at once
- Charts and reports
- Graphical user interface

## Author

Karmanpreet Kaur
BCA Data Science, Chandigarh University
