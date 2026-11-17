#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits>
#include <cctype>
using namespace std;

struct Product {
    int id;
    string name, category, brand;
    double price;
    int stock;
};

// LAB 1: Dynamic array catalog
class Catalog {
    Product* data;
    int count = 0, capacity = 5;

    void resize() {
        capacity *= 2;
        Product* temp = new Product[capacity];
        for (int i = 0; i < count; ++i) temp[i] = data[i];
        delete[] data;
        data = temp;
    }

public:
    Catalog() { data = new Product[capacity]; }
    ~Catalog() { delete[] data; }
    Catalog(const Catalog&) = delete;
    Catalog& operator=(const Catalog&) = delete;

    int size() const { return count; }
    Product& at(int i) { return data[i]; }
    const Product& at(int i) const { return data[i]; }

    int find(int id) const {
        for (int i = 0; i < count; ++i)
            if (data[i].id == id) return i;
        return -1;
    }

    bool add(const Product& p) {
        if (find(p.id) != -1) return false;
        if (count == capacity) resize();
        data[count++] = p;
        return true;
    }

    bool remove(int id, Product& old) {
        int i = find(id);
        if (i == -1) return false;
        old = data[i];
        for (; i < count - 1; ++i) data[i] = data[i + 1];
        --count;
        return true;
    }

    bool update(const Product& p) {
        int i = find(p.id);
        if (i == -1) return false;
        data[i] = p;
        return true;
    }
};

// LAB 2: Doubly linked list shopping cart
struct CartNode {
    int id, qty;
    CartNode *prev, *next;
    CartNode(int i, int q) : id(i), qty(q), prev(nullptr), next(nullptr) {}
};

class Cart {
    CartNode *head = nullptr, *tail = nullptr;

public:
    ~Cart() { clear(); }

    void clear() {
        while (head) {
            CartNode* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }

    CartNode* find(int id) {
        for (CartNode* p = head; p; p = p->next)
            if (p->id == id) return p;
        return nullptr;
    }

    void add(int id, int qty) {
        CartNode* p = find(id);
        if (p) { p->qty += qty; return; }
        p = new CartNode(id, qty);
        p->prev = tail;
        if (tail) tail->next = p;
        else head = p;
        tail = p;
    }

    bool remove(int id) {
        CartNode* p = find(id);
        if (!p) return false;
        if (p->prev) p->prev->next = p->next;
        else head = p->next;
        if (p->next) p->next->prev = p->prev;
        else tail = p->prev;
        delete p;
        return true;
    }

    CartNode* getHead() const { return head; }
    bool empty() const { return head == nullptr; }
};

// LAB 3: Circular linked list featured books
struct FeatureNode {
    int id;
    FeatureNode* next;
    FeatureNode(int value) : id(value), next(nullptr) {}
};

class Featured {
    FeatureNode* tail = nullptr;

public:
    ~Featured() { clear(); }

    void clear() {
        if (!tail) return;
        FeatureNode* p = tail->next;
        tail->next = nullptr;
        while (p) {
            FeatureNode* temp = p;
            p = p->next;
            delete temp;
        }
        tail = nullptr;
    }

    void add(int id) {
        FeatureNode* p = new FeatureNode(id);
        if (!tail) { tail = p; p->next = p; }
        else { p->next = tail->next; tail->next = p; tail = p; }
    }

    void display(const Catalog& c) const {
        if (!tail) { cout << "No featured books.\n"; return; }
        cout << "\n--- FEATURED BOOKS ---\n";
        FeatureNode* p = tail->next;
        do {
            int i = c.find(p->id);
            if (i != -1) cout << c.at(i).name << " - " << c.at(i).brand << '\n';
            p = p->next;
        } while (p != tail->next);
    }
};

// LAB 4: Stack for undo (LIFO)
struct Action {
    string type;
    Product before, after;
};

class UndoStack {
    vector<Action> items;

public:
    void push(const Action& a) { items.push_back(a); }
    bool pop(Action& a) {
        if (items.empty()) return false;
        a = items.back();
        items.pop_back();
        return true;
    }
};

// LAB 5: Checkout queue (FIFO)
struct Order {
    int id, qty;
    string customer;
};

class OrderQueue {
    vector<Order> items;
    size_t front = 0;

public:
    void enqueue(const Order& o) { items.push_back(o); }
    bool dequeue(Order& o) {
        if (front == items.size()) return false;
        o = items[front++];
        if (front > 20 && front * 2 >= items.size()) {
            items.erase(items.begin(), items.begin() + static_cast<long>(front));
            front = 0;
        }
        return true;
    }
    int pending() const { return static_cast<int>(items.size() - front); }
};

// LAB 6: BST index for product IDs
struct BSTNode {
    int id;
    BSTNode *left, *right;
    BSTNode(int value) : id(value), left(nullptr), right(nullptr) {}
};

class ProductBST {
    BSTNode* root = nullptr;

    BSTNode* insert(BSTNode* p, int id) {
        if (!p) return new BSTNode(id);
        if (id < p->id) p->left = insert(p->left, id);
        else if (id > p->id) p->right = insert(p->right, id);
        return p;
    }

    bool search(BSTNode* p, int id) const {
        if (!p) return false;
        if (p->id == id) return true;
        return id < p->id ? search(p->left, id) : search(p->right, id);
    }

    void clear(BSTNode* p) {
        if (!p) return;
        clear(p->left); clear(p->right); delete p;
    }

public:
    ~ProductBST() { clear(root); }
    bool contains(int id) const { return search(root, id); }
    void rebuild(const Catalog& c) {
        clear(root); root = nullptr;
        for (int i = 0; i < c.size(); ++i) root = insert(root, c.at(i).id);
    }
};

// INPUT AND DISPLAY
int readInt(const string& prompt) {
    int n;
    while (true) {
        cout << prompt;
        if (cin >> n) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return n;
        }
        cout << "Invalid input. Enter a whole number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

double readPrice(const string& prompt) {
    double n;
    while (true) {
        cout << prompt;
        if (cin >> n && n >= 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return n;
        }
        cout << "Invalid price.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string readText(const string& prompt) {
    string s;
    cout << prompt;
    getline(cin, s);
    return s;
}

string lower(string s) {
    for (char& c : s) c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    return s;
}

Product inputProduct(int id = -1) {
    Product p{};
    p.id = (id == -1) ? readInt("Book ID: ") : id;
    p.name = readText("Book title: ");
    p.category = readText("Category: ");

    const string brands[] = {"Penguin Random House", "HarperCollins",
                             "McGraw Hill", "Oxford University Press"};
    cout << "1. Penguin Random House\n2. HarperCollins\n3. McGraw Hill\n4. Oxford University Press\n";
    int b = readInt("Publisher: ");
    p.brand = (b >= 1 && b <= 4) ? brands[b - 1] : "Independent";
    p.price = readPrice("Price (PHP): ");
    p.stock = readInt("Stock quantity: ");
    if (p.stock < 0) p.stock = 0;
    return p;
}

void showHeader() {
    cout << left << setw(7) << "ID" << setw(29) << "TITLE" << setw(20) << "CATEGORY"
         << setw(27) << "PUBLISHER" << right << setw(11) << "PRICE" << setw(8) << "STOCK\n";
    cout << string(102, '-') << '\n';
}

void showProduct(const Product& p) {
    cout << left << setw(7) << p.id << setw(29) << p.name.substr(0, 27)
         << setw(20) << p.category.substr(0, 18) << setw(27) << p.brand.substr(0, 25)
         << right << "P" << fixed << setprecision(2) << setw(10) << p.price
         << setw(8) << p.stock << '\n';
}

void showAll(const Catalog& c) {
    if (!c.size()) { cout << "Catalog is empty.\n"; return; }
    showHeader();
    for (int i = 0; i < c.size(); ++i) showProduct(c.at(i));
}

// LAB 7: Linear search by ID, title, category, or publisher
void searchBooks(const Catalog& c, const ProductBST& bst) {
    cout << "\n1. Search by ID\n2. Search by title\n3. Search by category\n"
         << "4. Search by publisher/brand\n5. Search all fields\n";
    int choice = readInt("Search option: ");
    bool found = false;

    if (choice == 1) {
        int id = readInt("Enter Book ID: ");
        if (bst.contains(id)) {
            int i = c.find(id);
            if (i != -1) { showHeader(); showProduct(c.at(i)); found = true; }
        }
    } else if (choice >= 2 && choice <= 5) {
        string key = lower(readText("Enter search keyword: "));
        for (int i = 0; i < c.size(); ++i) {
            const Product& p = c.at(i);
            bool match = false;
            if (choice == 2) match = lower(p.name).find(key) != string::npos;
            if (choice == 3) match = lower(p.category).find(key) != string::npos;
            if (choice == 4) match = lower(p.brand).find(key) != string::npos;
            if (choice == 5)
                match = lower(p.name + " " + p.category + " " + p.brand).find(key) != string::npos;
            if (match) {
                if (!found) showHeader();
                showProduct(p);
                found = true;
            }
        }
    } else {
        cout << "Invalid search option.\n";
        return;
    }
    if (!found) cout << "No matching book found.\n";
}

// Binary search after sorting a temporary price list
void filterPrice(const Catalog& c) {
    double low = readPrice("Minimum price: ");
    double high = readPrice("Maximum price: ");
    if (low > high) { cout << "Minimum must not exceed maximum.\n"; return; }

    vector<Product> v;
    for (int i = 0; i < c.size(); ++i) v.push_back(c.at(i));
    sort(v.begin(), v.end(), [](const Product& a, const Product& b) {
        return a.price < b.price;
    });

    int left = 0, right = static_cast<int>(v.size()) - 1, first = static_cast<int>(v.size());
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (v[mid].price >= low) { first = mid; right = mid - 1; }
        else left = mid + 1;
    }

    bool found = false;
    for (int i = first; i < static_cast<int>(v.size()) && v[i].price <= high; ++i) {
        if (!found) showHeader();
        showProduct(v[i]);
        found = true;
    }
    if (!found) cout << "No books in this price range.\n";
}

void filterPublisher(const Catalog& c) {
    const string brands[] = {"Penguin Random House", "HarperCollins",
                             "McGraw Hill", "Oxford University Press"};
    cout << "\n1. Penguin Random House\n2. HarperCollins\n3. McGraw Hill\n4. Oxford University Press\n";
    int b = readInt("Choose publisher: ");
    if (b < 1 || b > 4) { cout << "Invalid publisher.\n"; return; }

    bool found = false;
    for (int i = 0; i < c.size(); ++i) {
        if (c.at(i).brand == brands[b - 1]) {
            if (!found) showHeader();
            showProduct(c.at(i));
            found = true;
        }
    }
    if (!found) cout << "No books found for this publisher.\n";
}

// LAB 8: Sorting by stock, price, or brand
void sortInventory(Catalog& c) {
    cout << "\n1. Sort by stock\n2. Sort by price\n3. Sort by brand\n";
    int choice = readInt("Sort option: ");
    if (choice < 1 || choice > 3) { cout << "Invalid sort option.\n"; return; }

    vector<Product> v;
    for (int i = 0; i < c.size(); ++i) v.push_back(c.at(i));

    if (choice == 1)
        sort(v.begin(), v.end(), [](const Product& a, const Product& b) { return a.stock < b.stock; });
    else if (choice == 2)
        sort(v.begin(), v.end(), [](const Product& a, const Product& b) { return a.price < b.price; });
    else
        sort(v.begin(), v.end(), [](const Product& a, const Product& b) { return a.brand < b.brand; });

    cout << "Inventory sorted.\n";
    if (v.empty()) { cout << "Catalog is empty.\n"; return; }
    showHeader();
    for (const Product& p : v) showProduct(p);
}

void undoAction(Catalog& c, UndoStack& stack, ProductBST& bst) {
    Action a;
    if (!stack.pop(a)) { cout << "No admin action to undo.\n"; return; }

    if (a.type == "ADD") {
        Product removed{};
        c.remove(a.after.id, removed);
    } else if (a.type == "UPDATE") {
        c.update(a.before);
    } else if (a.type == "REMOVE") {
        c.add(a.before);
    }
    bst.rebuild(c);
    cout << "Last admin action undone.\n";
}

void adminMenu(Catalog& c, UndoStack& stack, ProductBST& bst) {
    int choice;
    do {
        cout << "\n--- ADMIN PRODUCT MANAGEMENT ---\n"
             << "1. Add Product\n2. Update Product\n3. Remove Product\n"
             << "4. Undo Last Admin Action\n0. Back\n";
        choice = readInt("Select: ");

        if (choice == 1) {
            Product p = inputProduct();
            if (c.add(p)) {
                stack.push({"ADD", {}, p});
                bst.rebuild(c);
                cout << "Product added.\n";
            } else cout << "Book ID already exists.\n";
        } else if (choice == 2) {
            int id = readInt("Enter Book ID to update: ");
            int i = c.find(id);
            if (i == -1) cout << "Book not found.\n";
            else {
                Product old = c.at(i), updated = inputProduct(id);
                c.update(updated);
                stack.push({"UPDATE", old, updated});
                bst.rebuild(c);
                cout << "Product updated.\n";
            }
        } else if (choice == 3) {
            int id = readInt("Enter Book ID to remove: ");
            Product old{};
            if (c.remove(id, old)) {
                stack.push({"REMOVE", old, {}});
                bst.rebuild(c);
                cout << "Product removed.\n";
            } else cout << "Book not found.\n";
        } else if (choice == 4) {
            undoAction(c, stack, bst);
        } else if (choice != 0) cout << "Invalid admin option.\n";
    } while (choice != 0);
}

void seed(Catalog& c, Featured& f) {
    Product books[] = {
        {1001, "The Hobbit", "Fiction", "HarperCollins", 499, 12},
        {1002, "Clean Code", "Programming", "McGraw Hill", 850, 8},
        {1003, "Engineering Mathematics", "Educational", "McGraw Hill", 720, 15},
        {1004, "Oxford English Dictionary", "Reference", "Oxford University Press", 1200, 5},
        {1005, "Atomic Habits", "Self-Help", "Penguin Random House", 650, 10},
        {1006, "Introduction to Algorithms", "Computer Science", "McGraw Hill", 1500, 4},
        {1007, "The Alchemist", "Fiction", "HarperCollins", 399, 20}
    };
    for (const Product& p : books) c.add(p);
    f.add(1001); f.add(1003); f.add(1005);
}

int main() {
    Catalog catalog;
    Cart cart;
    Featured featured;
    UndoStack undoStack;
    OrderQueue orders;
    ProductBST idIndex;

    seed(catalog, featured);
    idIndex.rebuild(catalog);

    int choice;
    do {
        cout << "\n====================================================\n"
             << "   BOOKNEST - BRAND-AFFILIATED E-COMMERCE SYSTEM\n"
             << "====================================================\n"
             << "1. View Complete Book Catalog\n"
             << "2. Filter Books by Official Publisher\n"
             << "3. Search Books by ID, Name, Category, or Brand\n"
             << "4. Filter Books by Price Range (Binary Search)\n"
             << "5. Add Book to Shopping Cart\n"
             << "6. Process Customer Checkout Queue (FIFO)\n"
             << "7. Admin Product Management and Undo (LIFO)\n"
             << "8. Display Featured Books (Circular Linked List)\n"
             << "9. Sort Inventory (Stock, Price, or Brand)\n"
             << "10. Exit\n"
             << "====================================================\n";

        choice = readInt("Select: ");

        if (choice == 1) showAll(catalog);
        else if (choice == 2) filterPublisher(catalog);
        else if (choice == 3) searchBooks(catalog, idIndex);
        else if (choice == 4) filterPrice(catalog);
        else if (choice == 5) {
            int id = readInt("Book ID: ");
            int qty = readInt("Quantity: ");
            int i = catalog.find(id);
            if (i == -1) cout << "Book not found.\n";
            else if (qty <= 0 || qty > catalog.at(i).stock)
                cout << "Invalid quantity or insufficient stock.\n";
            else {
                cart.add(id, qty);
                catalog.at(i).stock -= qty;
                cout << "Added to cart. Remaining stock: " << catalog.at(i).stock << '\n';
            }
        } else if (choice == 6) {
            if (cart.empty()) cout << "Cart is empty.\n";
            else {
                double total = 0;
                cout << "\n--- CART ---\n";
                for (CartNode* p = cart.getHead(); p; p = p->next) {
                    int i = catalog.find(p->id);
                    if (i != -1) {
                        double subtotal = catalog.at(i).price * p->qty;
                        cout << catalog.at(i).name << " x " << p->qty
                             << " = PHP " << fixed << setprecision(2) << subtotal << '\n';
                        total += subtotal;
                    }
                }
                cout << "Total: PHP " << fixed << setprecision(2) << total << '\n';
                string customer = readText("Customer name: ");
                for (CartNode* p = cart.getHead(); p; p = p->next)
                    orders.enqueue({p->id, p->qty, customer});
                cart.clear();
                cout << "Checkout queued. Pending order items: " << orders.pending() << '\n';

                Order next;
                if (orders.dequeue(next))
                    cout << "Next order for " << next.customer << " is queued for processing.\n";
            }
        } else if (choice == 7) adminMenu(catalog, undoStack, idIndex);
        else if (choice == 8) featured.display(catalog);
        else if (choice == 9) sortInventory(catalog);
        else if (choice != 10) cout << "Invalid menu choice. Select 1-10.\n";

    } while (choice != 10);

    cout << "Thank you for visiting BookNest!\n";
    return 0;
}
