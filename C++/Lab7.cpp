#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_DISHES 10
#define MAX_ORDERS 5
#define DAYS 2
#define TABLES 3

class Dish {
protected:
    string name;  // string вместо char[50]
    float price;
    int quantity;

public:
    Dish(const string& dish_name, float dish_price, int dish_quantity)
        : name(dish_name), price(dish_price), quantity(dish_quantity) {}

    virtual void print() const {
        printf("Блюдо: %s, Цена: %.2f, Количество порций: %d\n", name.c_str(), price, quantity);
    }

    float getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    const string& getName() const { return name; }

    virtual float calculateDiscountedPrice() const {
        return price;
    }

    virtual ~Dish() = default;
};

class SpecialDish : public Dish {
private:
    string specialIngredient;

public:
    SpecialDish(const string& dish_name, float dish_price, int dish_quantity, const string& ingredient)
        : Dish(dish_name, dish_price, dish_quantity), specialIngredient(ingredient) {}

    void print() const override {
        Dish::print();
        printf("Специальный ингредиент: %s\n", specialIngredient.c_str());
    }

    float calculateDiscountedPrice() const override {
        return price * 0.9f; // 10% скидка на специальное блюдо
    }

    SpecialDish& operator=(const Dish& other) {
        if (this == &other) return *this;
        name = other.getName();
        price = other.getPrice();
        quantity = other.getQuantity();
        specialIngredient = "Нет специального ингредиента";
        return *this;
    }
};

class Menu {
private:
    vector<Dish*> dishes;

public:
    // Метод для добавления блюда в меню
    void addDish(Dish* dish) {
        if (dishes.size() >= MAX_DISHES) {
            throw overflow_error("Меню переполнено!");
        }
        dishes.push_back(dish);
    }

    // Метод для вывода меню
    void print() const {
        printf("Меню:\n");
        for (const auto& dish : dishes) {
            dish->print();
        }
        printf("\n");
    }

    // Получение блюда по индексу
    Dish* getDish(int index) const {
        if (index < 0 || index >= dishes.size()) {
            throw out_of_range("Некорректный индекс блюда!");
        }
        return dishes[index];
    }

    int getDishCount() const {
        return dishes.size();
    }

    // Сортировка блюд по цене
    void sortDishesByPrice() {
        sort(dishes.begin(), dishes.end(), [](Dish* a, Dish* b) {
            return a->getPrice() < b->getPrice();
            });
    }

    // Поиск блюда по имени
    Dish* findDishByName(const string& name) const {
        auto it = find_if(dishes.begin(), dishes.end(), [&name](Dish* dish) {
            return dish->getName() == name;
            });
        return it != dishes.end() ? *it : nullptr;
    }
};

class Client {
private:
    char name[50];
    char phone[15];

public:
    // Конструктор
    Client(const char* client_name, const char* client_phone) {
        strcpy_s(name, client_name);
        strcpy_s(phone, client_phone);
    }

    // Метод для вывода информации о клиенте
    void print() const {
        printf("Клиент: %s, Телефон: %s\n", name, phone);
    }

    const char* getName() const { return name; }
};

class Employee {
private:
    char name[50];
    int id;

public:
    // Конструктор
    Employee(const char* employee_name, int employee_id) {
        strcpy_s(name, employee_name);
        id = employee_id;
    }

    // Метод для вывода информации о сотруднике
    void print() const {
        printf("Официант: %s, ID: %d\n", name, id);
    }

    const char* getName() const { return name; }
};

class Order {
private:
    static int totalOrders;  // Статическое поле для подсчёта заказов
    string clientName;  // std::string вместо char[50]
    Dish* orderedDishes[MAX_ORDERS];
    int orderCount;
    float totalPrice;

public:
    // Конструктор
    Order(const string& client)
        : clientName(client), orderCount(0), totalPrice(0.0f) {
        totalOrders++;
    }

    ~Order() {
        totalOrders--;  // Уменьшаем общее количество заказов
    }

    void addDish(Dish* dish) {
        if (orderCount >= MAX_ORDERS) {
            throw overflow_error("Заказ переполнен!");
        }
        orderedDishes[orderCount++] = dish;
        totalPrice += dish->calculateDiscountedPrice() * dish->getQuantity();
    }

    void print() const {
        if (orderCount == 0) {
            printf("Заказ пуст.\n");
        }
        else {
            printf("Заказ клиента: %s\n", clientName.c_str());
            printf("Блюда в заказе:\n");
            for (int i = 0; i < orderCount; i++) {
                orderedDishes[i]->print();
            }
            printf("Общая стоимость: %.2f\n\n", totalPrice);
        }
    }

    // Статический метод
    static int getTotalOrders() {
        return totalOrders;
    }

    // Возврат стоимости через указатель
    void getTotalPricePtr(float* ptr) const {
        if (ptr) {
            *ptr = totalPrice;
        }
    }

    // Возврат стоимости через ссылку
    void getTotalPriceRef(float& ref) const {
        ref = totalPrice;
    }

    // Использование оператора this
    bool isMoreExpensive(const Order& other) const {
        return this->totalPrice > other.totalPrice;
    }

    // Перегрузка оператора +
    Order operator+(const Order& other) const {
        Order combinedOrder(clientName + " & " + other.clientName);
        combinedOrder.totalPrice = this->totalPrice + other.totalPrice;
        for (int i = 0; i < this->orderCount; i++) {
            combinedOrder.addDish(this->orderedDishes[i]);
        }
        for (int i = 0; i < other.orderCount; i++) {
            combinedOrder.addDish(other.orderedDishes[i]);
        }
        return combinedOrder;
    }

    // Префиксный оператор ++
    Order& operator++() {
        if (orderCount < MAX_ORDERS) {
            addDish(new Dish("Пустое блюдо", 0.0, 1));
        }
        return *this;
    }

    // Постфиксный оператор ++
    Order operator++(int) {
        Order temp = *this;
        ++(*this);
        return temp;
    }

    // Дружественная функция
    friend void displayOrderDetails(const Order& order);
};

// Инициализация статического поля
int Order::totalOrders = 0;

// Дружественная функция
void displayOrderDetails(const Order& order) {
    printf("Дружественная функция: Клиент: %s, Общая стоимость: %.2f\n",
        order.clientName.c_str(), order.totalPrice);
}

// Абстрактный класс
class PaymentMethod {
public:
    virtual void processPayment(float amount) = 0;
    virtual ~PaymentMethod() = default;
};

class CashPayment : public PaymentMethod {
public:
    void processPayment(float amount) override {
        printf("Оплата наличными: %.2f\n", amount);
    }
};

class CardPayment : public PaymentMethod {
public:
    void processPayment(float amount) override {
        printf("Оплата картой: %.2f\n", amount);
    }
};

// Шаблон класса для хранения и вывода различных типов данных
template <typename T>
class DataHolder {
private:
    T data;

public:
    DataHolder(T value) : data(value) {}

    void print() const {
        cout << "Значение: " << data << endl;
    }
};

int main() {
    try {
        setlocale(LC_ALL, "Russian");

        // Создание меню
        Menu menu;
        menu.addDish(new Dish("Борщ", 200.0f, 1));
        menu.addDish(new Dish("Пельмени", 300.0f, 1));
        menu.addDish(new SpecialDish("Специальный борщ", 150.0f, 1, "Трюфель"));
        menu.print();

        // Сортировка блюд по цене
        menu.sortDishesByPrice();
        printf("Меню после сортировки по цене:\n");
        menu.print();

        // Поиск блюда по имени
        Dish* foundDish = menu.findDishByName("Пельмени");
        if (foundDish) {
            printf("Найденное блюдо:\n");
            foundDish->print();
        }
        else {
            printf("Блюдо не найдено.\n");
        }

        // Работа с одномерным массивом
        printf("Работа с одномерным массивом объектов Dish:\n");
        Dish* dishArray[MAX_DISHES];
        for (int i = 0; i < MAX_DISHES; i++) {
            dishArray[i] = new Dish("Блюдо " + to_string(i + 1), 100.0f + i * 10, 1);
            dishArray[i]->print();
        }

        // Работа с двумерным массивом объектов Order
        printf("\nРабота с двумерным массивом объектов Order:\n");
        Order* orderMatrix[DAYS][TABLES] = { nullptr };

        for (int day = 0; day < DAYS; day++) {
            for (int table = 0; table < TABLES; table++) {
                orderMatrix[day][table] = new Order("Клиент " + to_string(day * TABLES + table + 1));
                try {
                    int dishIndex = (day + table) % menu.getDishCount();
                    orderMatrix[day][table]->addDish(menu.getDish(dishIndex));
                }
                catch (const exception& e) {
                    printf("Ошибка при добавлении блюда: %s\n", e.what());
                }
            }
        }

        // Вывод двумерного массива заказов
        for (int day = 0; day < DAYS; day++) {
            printf("День %d:\n", day + 1);
            for (int table = 0; table < TABLES; table++) {
                printf("  Стол %d:\n", table + 1);
                orderMatrix[day][table]->print();
            }
        }

        // Освобождение памяти для одномерного массива блюд
        for (int i = 0; i < MAX_DISHES; i++) {
            delete dishArray[i];
        }

        // Освобождение памяти для двумерного массива заказов
        for (int day = 0; day < DAYS; day++) {
            for (int table = 0; table < TABLES; table++) {
                delete orderMatrix[day][table];
            }
        }

        // Использование абстрактного класса
        PaymentMethod* cashPayment = new CashPayment();
        PaymentMethod* cardPayment = new CardPayment();
        cashPayment->processPayment(500.0f);
        cardPayment->processPayment(700.0f);
        delete cashPayment;
        delete cardPayment;

        // Использование шаблона класса
        DataHolder<int> intHolder(42);
        intHolder.print();
        DataHolder<string> stringHolder("Пример строки");
        stringHolder.print();
    }
    catch (const exception& e) {
        printf("Общая ошибка: %s\n", e.what());
    }
}
