# BookNest – Brand-Affiliated E-Commerce Inventory System

## Project Description

BookNest is a console-based C++ online bookstore inventory and shopping system. It demonstrates the practical application of Data Structures and Algorithms in an e-commerce environment.

## Features

1. **View Complete Book Catalog** – Displays all available books and their details.
2. **Filter Books by Official Publisher** – Displays books based on their publisher.
3. **Search Books** – Search by ID, title, category, publisher, or all fields.
4. **Filter Books by Price Range** – Finds books within a selected price range using binary search.
5. **Add Book to Shopping Cart** – Adds books to the cart and automatically deducts the quantity from available stock.
6. **Process Customer Checkout Queue** – Displays the cart total and adds checkout items to the queue.
7. **Admin Product Management and Undo** – Add, update, remove products, and undo the latest admin action.
8. **Display Featured Books** – Displays featured books using a circular linked list.
9. **Sort Inventory** – Sort books by stock, price, or publisher/brand.
10. **Exit** – Terminates the program.

## Data Structures and Algorithms Used

| Data Structure / Algorithm | Implementation | Purpose |
|---|---|---|
| Dynamic Array | Catalog | Stores and manages book records. |
| Doubly Linked List | Shopping Cart | Manages cart items. |
| Circular Linked List | Featured Books | Stores featured book IDs. |
| Stack (LIFO) | Undo Stack | Reverses the latest admin action. |
| Queue (FIFO) | Checkout Queue | Processes checkout items in order. |
| Binary Search Tree | Product BST | Indexes product IDs. |
| Linear Search | Search Books | Finds books using keywords and fields. |
| Binary Search | Price Filter | Locates books within a price range. |
| Sorting | Inventory Sorting | Sorts by stock, price, or brand. |

## Technologies Used

- C++
- C++17
- Data Structures and Algorithms
- Standard C++ Library

## Requirements

- C++ compiler supporting C++17 or later.
- Visual Studio or GCC/G++ compiler.
- Terminal or command prompt.

## How to Compile and Run

### Using G++

Compile the program:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic BookNest.cpp -o BookNest
```

Run on Windows:

```bash
.\BookNest.exe
```

Run on Linux/macOS:

```bash
./BookNest
```

### Using Visual Studio

1. Open Visual Studio.
2. Create a C++ Console Application.
3. Add the BookNest source code.
4. Set the language standard to C++17 or later.
5. Build the project.
6. Run using `Ctrl + F5`.

## Sample Inventory

| Book ID | Book Title | Category | Publisher | Price (PHP) | Stock |
|---|---|---|---|---:|---:|
| 1001 | The Hobbit | Fiction | HarperCollins | 499.00 | 12 |
| 1002 | Clean Code | Programming | McGraw Hill | 850.00 | 8 |
| 1003 | Engineering Mathematics | Educational | McGraw Hill | 720.00 | 15 |
| 1004 | Oxford English Dictionary | Reference | Oxford University Press | 1200.00 | 5 |
| 1005 | Atomic Habits | Self-Help | Penguin Random House | 650.00 | 10 |
| 1006 | Introduction to Algorithms | Computer Science | McGraw Hill | 1500.00 | 4 |
| 1007 | The Alchemist | Fiction | HarperCollins | 399.00 | 20 |

## Important Notes

- Product records are stored in memory while the program is running.
- Inventory changes are not permanently saved.
- The sample inventory is loaded every time the program starts.
- Adding a book to the cart immediately reduces the available stock.
- The undo function applies to the latest admin product action.
- The checkout queue stores individual cart items.

## Project Purpose

BookNest demonstrates the integration of fundamental Data Structures and Algorithms into a practical bookstore inventory and e-commerce system.
