#include <iostream>
#include <string>
#include <vector>

class Product
{
private:
    int productId;
    std::string name;
    std::string description;
    double price;
    int quantityInStock;

public:
    Product(int id, std::string name, std::string description, double price, int quantity)
        : productId(id), name(name), description(description), price(price), quantityInStock(quantity) {}

    void displayDetails() const
    {
        std::cout << "Product ID: " << productId << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Description: " << description << std::endl;
        std::cout << "Price: $" << price << std::endl;
        std::cout << "Quantity in Stock: " << quantityInStock << std::endl;
    }

    double getPrice() const
    {
        return price;
    }
    int getProductId() const
    {
        return productId;
    }
};

class Customer
{
private:
    int customerId;
    std::string name;
    std::string email;
    std::string shippingAddress;

public:
    Customer(int id, std::string name, std::string email, std::string address)
        : customerId(id), name(name), email(email), shippingAddress(address) {}

    void displayDetails() const
    {
        std::cout << "Customer ID: " << customerId << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Email: " << email << std::endl;
        std::cout << "Shipping Address: " << shippingAddress << std::endl;
    }
};

class Order
{
private:
    int orderId;
    int customerId;
    std::string orderDate;
    std::vector<Product> orderedProducts;
    double totalAmount;

public:
    Order(int id, int customerId, std::string date)
        : orderId(id), customerId(customerId), orderDate(date), totalAmount(0) {}

    void addProduct(const Product &product)
    {
        orderedProducts.push_back(product);
        totalAmount += product.getPrice();
    }
    int getOrderId() const
    {
        return orderId;
    }

    void displayOrderDetails() const
    {
        std::cout << "Order ID: " << orderId << std::endl;
        std::cout << "Customer ID: " << customerId << std::endl;
        std::cout << "Order Date: " << orderDate << std::endl;

        std::cout << "Ordered Products:" << std::endl;
        for (const Product &product : orderedProducts)
        {
            product.displayDetails();
            std::cout << std::endl;
        }

        std::cout << "Total Amount: $" << totalAmount << std::endl;
    }
};

class ShoppingCart
{
private:
    std::vector<Product> cartContents;

public:
    void addProductToCart(const Product &product)
    {
        cartContents.push_back(product);
        std::cout << "Product added to the cart." << std::endl;
    }

    void removeProductFromCart(int productId)
    {
        for (auto it = cartContents.begin(); it != cartContents.end(); ++it)
        {
            if (it->getProductId() == productId)
            { // Use productId directly
                cartContents.erase(it);
                std::cout << "Product removed from the cart." << std::endl;
                return;
            }
        }
        std::cout << "Product not found in the cart." << std::endl;
    }

    double calculateCartTotal() const
    {
        double total = 0;
        for (const Product &product : cartContents)
        {
            total += product.getPrice();
        }
        return total;
    }

    void displayCartContents() const
    {
        std::cout << "Shopping Cart Contents:" << std::endl;
        for (const Product &product : cartContents)
        {
            product.displayDetails();
            std::cout << std::endl;
        }
        std::cout << "Cart Total: $" << calculateCartTotal() << std::endl;
    }
};

// Function to input product details
Product inputProduct(int id)
{
    std::string name, description;
    double price;
    int quantity;

    std::cout << "Enter Product " << id << " Name: ";
    getline(std::cin, name);
    std::cout << "Enter Product " << id << " Description: ";
    getline(std::cin, description);
    std::cout << "Enter Product " << id << " Price: ";
    std::cin >> price;
    std::cout << "Enter Product " << id << " Quantity in Stock: ";
    std::cin >> quantity;
    std::cin.ignore(); // Ignore newline

    return Product(id, name, description, price, quantity);
}

// Function to input customer details
Customer inputCustomer(int id)
{
    std::string name, email, address;

    std::cout << "Enter Customer " << id << " Name: ";
    getline(std::cin, name);
    std::cout << "Enter Customer " << id << " Email: ";
    getline(std::cin, email);
    std::cout << "Enter Customer " << id << " Shipping Address: ";
    getline(std::cin, address);

    return Customer(id, name, email, address);
}

// Function to input order details
Order inputOrder(int id, int customerId)
{
    std::string date;

    std::cout << "Enter Order " << id << " Date: ";
    getline(std::cin, date);

    return Order(id, customerId, date);
}

// Function to display the menu
int displayMenu()
{
    int choice;
    std::cout << "\nMenu:\n";
    std::cout << "1. Add Product\n";
    std::cout << "2. Add Customer\n";
    std::cout << "3. Add Order\n";
    std::cout << "4. Display Cart Contents\n";
    std::cout << "5. Display Order Details\n";
    std::cout << "6. Exit\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    std::cin.ignore(); // Ignore newline
    return choice;
}

int main()
{
    std::vector<Product> products;
    std::vector<Customer> customers;
    std::vector<Order> orders;
    ShoppingCart cart;

    while (true)
    {
        int choice = displayMenu();

        switch (choice)
        {
        case 1: // Add Product
            products.push_back(inputProduct(products.size() + 1));
            break;
        case 2: // Add Customer
            customers.push_back(inputCustomer(customers.size() + 1));
            break;
        case 3:             // Add Order
            int customerId; // You need to get the customer ID for this order
            std::cout << "Enter Customer ID for this order: ";
            std::cin >> customerId;
            std::cin.ignore(); // Ignore newline
            orders.push_back(inputOrder(orders.size() + 1, customerId));
            break;
        case 4: // Display Cart Contents
            cart.displayCartContents();
            break;
        case 5: // Display Order Details
            if (orders.empty())
            {
                std::cout << "No orders to display." << std::endl;
            }
            else
            {
                int orderId;
                std::cout << "Enter Order ID to display details: ";
                std::cin >> orderId;
                std::cin.ignore(); // Ignore newline

                bool found = false;
                for (const Order &order : orders)
                {
                    if (order.getOrderId() == orderId)
                    {
                        order.displayOrderDetails();
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    std::cout << "Order not found." << std::endl;
                }
            }
            break;
        case 6: // Exit
            std::cout << "Exiting the program. Goodbye!\n";
            return 0;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
