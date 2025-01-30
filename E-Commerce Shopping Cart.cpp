#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Product {
public:
    string name;
    double price;
    int stock;
    
    Product(string n, double p, int s) : name(n), price(p), stock(s) {}
};

class ShoppingCart {
public:
    vector<Product> cart;
    
    void addToCart(Product& product, int quantity) {
        if (quantity <= product.stock) {
            product.stock -= quantity;
            cart.push_back(Product(product.name, product.price, quantity));
            cout << "Added " << quantity << " of " << product.name << " to the cart.\n";
        } else {
            cout << "Insufficient stock!\n";
        }
    }
    
    void removeFromCart(string productName) {
        for (auto it = cart.begin(); it != cart.end(); ++it) {
            if (it->name == productName) {
                cart.erase(it);
                cout << productName << " has been removed from the cart.\n";
                return;
            }
        }
        cout << "Product not found in cart.\n";
    }
    
    void viewCart() {
        if (cart.empty()) {
            cout << "Your cart is empty.\n";
            return;
        }
        double total = 0;
        cout << "Your Shopping Cart:\n";
        cout << "----------------------------------------------------\n";
        for (auto& item : cart) {
            cout << "Product: " << item.name << ", Price: " << item.price
                 << ", Quantity: " << item.stock << ", Total: " << item.price * item.stock << endl;
            total += item.price * item.stock;
        }
        cout << "----------------------------------------------------\n";
        cout << "Total cost: " << fixed << setprecision(2) << total << endl;
    }
    
    double checkout() {
        double total = 0;
        for (auto& item : cart) {
            total += item.price * item.stock;
        }
        return total;
    }
};

int main() {
    vector<Product> products = {
        Product("Laptop", 1000.00, 5),
        Product("Smartphone", 500.00, 10),
        Product("Headphones", 100.00, 15),
        Product("Keyboard", 50.00, 20)
    };
    
    ShoppingCart cart;
    
    int choice;
    while (true) {
        cout << "\n--- E-Commerce Shopping Cart ---\n";
        cout << "1. View Products\n";
        cout << "2. Add to Cart\n";
        cout << "3. View Cart\n";
        cout << "4. Remove from Cart\n";
        cout << "5. Checkout\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        if (choice == 1) {
            cout << "Available Products:\n";
            for (int i = 0; i < products.size(); ++i) {
                cout << i + 1 << ". " << products[i].name << " - Price: " << products[i].price
                     << " - Stock: " << products[i].stock << endl;
            }
        } else if (choice == 2) {
            int productId, quantity;
            cout << "Enter product ID to add to cart: ";
            cin >> productId;
            cout << "Enter quantity: ";
            cin >> quantity;
            
            if (productId > 0 && productId <= products.size()) {
                cart.addToCart(products[productId - 1], quantity);
            } else {
                cout << "Invalid product ID.\n";
            }
        } else if (choice == 3) {
            cart.viewCart();
        } else if (choice == 4) {
            string productName;
            cout << "Enter product name to remove from cart: ";
            cin.ignore();
            getline(cin, productName);
            cart.removeFromCart(productName);
        } else if (choice == 5) {
            double total = cart.checkout();
            cout << "Total amount to pay: " << fixed << setprecision(2) << total << endl;
            cout << "Thank you for shopping with us!\n";
            break;
        } else if (choice == 6) {
            cout << "Exiting the program.\n";
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
    
    return 0;
}
