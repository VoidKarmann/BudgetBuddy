/*
 * EVENT BUDGET TRACKER AND MANAGEMENT
 * Subject : C Programming (BCA Data Science, Sem 1)
 *
 * Concepts used: variables, constants, data types, operators, printf/scanf,
 * if/else, nested if, switch, loops, break/continue, arrays, strings,
 * functions, recursion, pointers, malloc/free, structures, file handling.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100          /* maximum number of expenses (constant) */

/* ---------- Structures ---------- */
struct Expense {
    char name[50];
    char category[30];
    float amount;
};

struct Event {
    char name[50];
    char date[15];
    float budget;
};

/* ---------- Function prototypes ---------- */
void createEvent(struct Event *e);
void addExpense(struct Expense *list, int *count);
void viewExpenses(struct Expense *list, int count);
float totalSpent(struct Expense *list, int count);
float totalRecursive(struct Expense *list, int n);
void showSummary(struct Event e, struct Expense *list, int count);
void searchExpense(struct Expense *list, int count);
void updateExpense(struct Expense *list, int count);
void deleteExpense(struct Expense *list, int *count);
void categorySummary(struct Expense *list, int count);
void highestExpense(struct Expense *list, int count);
void saveToFile(struct Event e, struct Expense *list, int count);
int loadFromFile(struct Event *e, struct Expense *list, int *count);
void logExpense(struct Expense x);

/* ---------- Create a new event ---------- */
void createEvent(struct Event *e) {
    printf("Event name: ");
    scanf(" %[^\n]", e->name);       /* reads a full line with spaces */
    printf("Event date (dd/mm/yyyy): ");
    scanf("%s", e->date);
    do {
        printf("Total budget: ");
        scanf("%f", &e->budget);
        if (e->budget <= 0)
            printf("Budget must be positive!\n");
    } while (e->budget <= 0);
}

/* ---------- Add an expense ---------- */
void addExpense(struct Expense *list, int *count) {
    int c;

    if (*count >= MAX) {
        printf("Expense list is full!\n");
        return;
    }

    printf("Expense name: ");
    scanf(" %[^\n]", list[*count].name);

    printf("1.Food 2.Venue 3.Decor 4.Music 5.Other\nCategory: ");
    scanf("%d", &c);
    switch (c) {
        case 1: strcpy(list[*count].category, "Food");  break;
        case 2: strcpy(list[*count].category, "Venue"); break;
        case 3: strcpy(list[*count].category, "Decor"); break;
        case 4: strcpy(list[*count].category, "Music"); break;
        default: strcpy(list[*count].category, "Other");
    }

    do {
        printf("Amount: ");
        scanf("%f", &list[*count].amount);
        if (list[*count].amount <= 0)
            printf("Amount must be positive!\n");
    } while (list[*count].amount <= 0);

    (*count)++;
    logExpense(list[*count - 1]);    /* append to activity log */
    printf("Expense added!\n");
}

/* ---------- View all expenses ---------- */
void viewExpenses(struct Expense *list, int count) {
    int i;

    if (count == 0) {
        printf("No expenses yet.\n");
        return;
    }
    printf("\n%-4s %-20s %-10s %10s\n", "No.", "Name", "Category", "Amount");
    for (i = 0; i < count; i++)
        printf("%-4d %-20s %-10s %10.2f\n", i + 1,
               list[i].name, list[i].category, list[i].amount);
}

/* ---------- Total spent (loop version) ---------- */
float totalSpent(struct Expense *list, int count) {
    float sum = 0;
    int i;
    for (i = 0; i < count; i++)
        sum += list[i].amount;
    return sum;
}

/* ---------- Total spent (recursive version) ---------- */
float totalRecursive(struct Expense *list, int n) {
    if (n == 0)
        return 0;
    return list[n - 1].amount + totalRecursive(list, n - 1);
}

/* ---------- Budget summary ---------- */
void showSummary(struct Event e, struct Expense *list, int count) {
    float spent = totalRecursive(list, count);   /* recursion used here */
    float remaining = e.budget - spent;
    float percent = (spent / e.budget) * 100;

    printf("\nEvent: %s (%s)\n", e.name, e.date);
    printf("Budget    : %.2f\n", e.budget);
    printf("Spent     : %.2f\n", spent);
    printf("Remaining : %.2f\n", remaining);
    printf("Used      : %.1f%%\n", percent);

    if (spent > e.budget)
        printf("WARNING: You are over budget by %.2f!\n", -remaining);
    else if (percent >= 80)
        printf("Caution: More than 80%% of budget used.\n");
    else
        printf("You are within budget.\n");
}

/* ---------- Search by name ---------- */
void searchExpense(struct Expense *list, int count) {
    char key[50];
    int i, found = 0;

    printf("Enter name to search: ");
    scanf(" %[^\n]", key);
    for (i = 0; i < count; i++) {
        if (strcmp(list[i].name, key) == 0) {
            printf("Found: %s | %s | %.2f\n",
                   list[i].name, list[i].category, list[i].amount);
            found = 1;
        }
    }
    if (found == 0)
        printf("Expense not found.\n");
}

/* ---------- Update an expense amount ---------- */
void updateExpense(struct Expense *list, int count) {
    int pos;

    if (count == 0) {
        printf("No expenses to update.\n");
        return;
    }
    viewExpenses(list, count);
    printf("Enter number to update: ");
    scanf("%d", &pos);
    if (pos < 1 || pos > count) {
        printf("Invalid number!\n");
        return;
    }
    do {
        printf("New amount: ");
        scanf("%f", &list[pos - 1].amount);
        if (list[pos - 1].amount <= 0)
            printf("Amount must be positive!\n");
    } while (list[pos - 1].amount <= 0);
    printf("Updated!\n");
}

/* ---------- Delete an expense (shift elements left) ---------- */
void deleteExpense(struct Expense *list, int *count) {
    int i, pos;

    if (*count == 0) {
        printf("No expenses to delete.\n");
        return;
    }
    viewExpenses(list, *count);
    printf("Enter number to delete: ");
    scanf("%d", &pos);
    if (pos < 1 || pos > *count) {
        printf("Invalid number!\n");
        return;
    }
    for (i = pos - 1; i < *count - 1; i++)
        list[i] = list[i + 1];
    (*count)--;
    printf("Deleted!\n");
}

/* ---------- Category-wise totals ---------- */
void categorySummary(struct Expense *list, int count) {
    char cats[5][30] = {"Food", "Venue", "Decor", "Music", "Other"};
    float totals[5] = {0};
    int i, j;

    for (i = 0; i < count; i++)
        for (j = 0; j < 5; j++)
            if (strcmp(list[i].category, cats[j]) == 0)
                totals[j] += list[i].amount;

    printf("\nCategory-wise spending:\n");
    for (j = 0; j < 5; j++)
        printf("%-10s : %.2f\n", cats[j], totals[j]);
}

/* ---------- Highest expense ---------- */
void highestExpense(struct Expense *list, int count) {
    int i, maxIndex = 0;

    if (count == 0) {
        printf("No expenses yet.\n");
        return;
    }
    for (i = 1; i < count; i++)
        if (list[i].amount > list[maxIndex].amount)
            maxIndex = i;
    printf("Highest: %s (%s) - %.2f\n", list[maxIndex].name,
           list[maxIndex].category, list[maxIndex].amount);
}

/* ---------- Save to file (write mode) ---------- */
void saveToFile(struct Event e, struct Expense *list, int count) {
    char filename[60];
    int i;
    FILE *fp;

    strcpy(filename, e.name);
    strcat(filename, ".txt");

    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Could not open file!\n");
        return;
    }
    fprintf(fp, "%s\n%s\n%.2f\n%d\n", e.name, e.date, e.budget, count);
    for (i = 0; i < count; i++)
        fprintf(fp, "%s\n%s\n%.2f\n",
                list[i].name, list[i].category, list[i].amount);
    fclose(fp);
    printf("Saved to %s\n", filename);
}

/* ---------- Load from file (read mode) ---------- */
int loadFromFile(struct Event *e, struct Expense *list, int *count) {
    char name[50], filename[60];
    int i;
    FILE *fp;

    printf("Enter event name to load: ");
    scanf(" %[^\n]", name);
    strcpy(filename, name);
    strcat(filename, ".txt");

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Event not found!\n");
        return 0;
    }
    fscanf(fp, " %[^\n]", e->name);
    fscanf(fp, " %[^\n]", e->date);
    fscanf(fp, "%f", &e->budget);
    fscanf(fp, "%d", count);
    for (i = 0; i < *count; i++) {
        fscanf(fp, " %[^\n]", list[i].name);
        fscanf(fp, " %[^\n]", list[i].category);
        fscanf(fp, "%f", &list[i].amount);
    }
    fclose(fp);
    printf("Loaded %d expenses.\n", *count);
    return 1;
}

/* ---------- Activity log (append mode) ---------- */
void logExpense(struct Expense x) {
    FILE *fp = fopen("log.txt", "a");
    if (fp == NULL)
        return;
    fprintf(fp, "Added: %s | %s | %.2f\n", x.name, x.category, x.amount);
    fclose(fp);
}

/* ---------- Main ---------- */
int main() {
    struct Event ev;
    struct Expense *list;
    int count = 0, choice, ready;

    list = (struct Expense *) malloc(MAX * sizeof(struct Expense));
    if (list == NULL) {
        printf("Memory not allocated!\n");
        return 1;
    }

    /* Start menu: create or load an event */
    while (1) {
        printf("\n===== EVENT BUDGET TRACKER =====\n");
        printf("1. Create new event\n2. Load existing event\n3. Exit\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            createEvent(&ev);
            break;
        } else if (choice == 2) {
            ready = loadFromFile(&ev, list, &count);
            if (ready)
                break;
        } else if (choice == 3) {
            free(list);
            return 0;
        } else {
            printf("Invalid choice!\n");
            continue;
        }
    }

    /* Main menu */
    do {
        printf("\n===== %s =====\n", ev.name);
        printf("1.Add  2.View  3.Search  4.Update  5.Delete\n");
        printf("6.Summary  7.Category totals  8.Highest  9.Save  0.Exit\nChoice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addExpense(list, &count); break;
            case 2: viewExpenses(list, count); break;
            case 3: searchExpense(list, count); break;
            case 4: updateExpense(list, count); break;
            case 5: deleteExpense(list, &count); break;
            case 6: showSummary(ev, list, count); break;
            case 7: categorySummary(list, count); break;
            case 8: highestExpense(list, count); break;
            case 9: saveToFile(ev, list, count); break;
            case 0: printf("Goodbye!\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 0);

    free(list);
    return 0;
}
