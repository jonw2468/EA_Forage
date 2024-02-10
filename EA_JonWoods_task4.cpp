#include <string>
#include <iostream>
#include <vector>
#include <utility>

class Item {
private:
    std::string name;
    int quantity;
    float price;

public:
    // Constructor has been revised to use declarations
    Item(std::string name, int quantity,float price) {
      this->name = name;
      this->quantity = quantity;
      this->price = price;
    }

    std::string get_name() const {
        return name;
    }

    int get_quantity() const {
        return quantity;
    }

    void set_quantity(int new_quantity) {
        quantity = new_quantity;
    }

    float get_price() const {
        return price;
    }

    bool is_match(const std::string &other) {
        return name == other;
    }
};

class Inventory {
private:
    std::vector<Item*> items; // items[] is now a vector instead of an array
    float total_money;
    int item_count;

    static void display_data(Item &item) {
        std::cout << "\nItem name: " << item.get_name();
        std::cout << "\nQuantity: " << item.get_quantity();
        std::cout << "\nPrice: " << item.get_price();
    }

public:
    // Constructor has been revised to use declarations
    Inventory() {
      std::vector<Item*> empty_array;
      items = empty_array;
      total_money = 0;
      item_count = 0;
    }

    void add_item() {
        std::string name;
        int quantity;
        float price;

        std::cin.ignore();
        std::cout << "\nEnter item name: ";
        std::cin >> name;
	// As an extra improvement, I implemented a way to increase an existing Item's quantity
	for (int i = 0; i < item_count; i++) {
	    Item* existing_item = items[i];
            if (existing_item->is_match(name)) {
               std::cout << "You already own this item.";
	       std::cout << "\nHow many more will you add? ";
	       std::cin >> quantity;
	       existing_item->set_quantity(existing_item->get_quantity()+ quantity);
	       std::cout << "New quantity: " << existing_item->get_quantity();
	       return;
            }
        }
	// For non-duplicate items, add to the vector as given
        std::cout << "Enter quantity: ";
        std::cin >> quantity;
        std::cout << "Enter price: ";
        std::cin >> price;
	items.push_back(new Item(name, quantity, price));
        item_count++;
    }

    void sell_item() {
        std::string item_to_check;
        std::cin.ignore();
        std::cout << "\nEnter item name: ";
        std::cin >> item_to_check;

        for (int i = 0; i < item_count; i++) {
            if (items[i]->is_match(item_to_check)) {
              remove_item(i);
	      return;
            }
        }
        std::cout << "\nThis item is not in your Inventory";
    }
  
    void remove_item(int item_index) {
        int input_quantity;
        Item *item = items[item_index];
        std::cout << "\nEnter number of items to sell: ";
        std::cin >> input_quantity;

        int quantity = item->get_quantity();
        if (input_quantity <= quantity) {
            float price = item->get_price();
            float money_earned = price * input_quantity;
            item->set_quantity(quantity - input_quantity);
	    
            std::cout << "\nItems sold";
            std::cout << "\nMoney received: " << money_earned;
            total_money += money_earned;
	    
	    if (item->get_quantity() == 0) {
	      items.erase(items.begin() + item_index);
	      item_count--;
	    }
        } else {
            std::cout << "\nCannot sell more items than you have.";
        }
    }

    void list_items() {
        if (item_count == 0) {
            std::cout << "\nInventory empty.";
            return;
        }

        for (int i = 0; i < item_count; i++) {
            display_data(*items[i]);
            std::cout << "\n";
        }
    }
};

int main() {
    int choice;
    Inventory inventory_system;
    std::cout << "Welcome to the inventory!";
    
    while (1) {
        std::cout << "\n\nMENU\n"
                  << "1. Add new item\n"
                  << "2. Sell item\n"
                  << "3. List items\n"
                  << "4. Exit\n\n"
                  << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
	        inventory_system.add_item();
                break;

            case 2:
	        inventory_system.sell_item();
                break;

            case 3:
	        inventory_system.list_items();
                break;

            case 4:
                exit(0);

            default:
                std::cout << "\nInvalid choice entered";
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
                break;
        }
    }
}
