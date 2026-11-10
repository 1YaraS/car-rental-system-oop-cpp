#include <iostream>
#include <string>

using namespace std;

// 1. كلاس Person (الكلاس الأساسي Base Class)
class Person {
protected:
    string name;
    string surname;
    int age;

public:
    // الـ Constructor (عشان نعطي قيم مبدئية للمتغيرات)
    Person(string n = "", string s = "", int a = 0) {
        name = n;
        surname = s;
        age = a;
    }

    void display() const {
        cout << "Name: " << name << " " << surname << ", Age: " << age << endl;
    }

    string getName() const { return name; }
    string getSurname() const { return surname; }
};

// 2. كلاس العميل Client (يورث Inherits من كلاس Person)
class Client : public Person {
private:
    int clientId;

public:
    // الـ Constructor
    Client(string n = "", string s = "", int a = 0, int id = 0) : Person(n, s, a) {
        clientId = id;
    }

    void displayClient() const {
        cout << "--- Client Info ---" << endl;
        display(); // هنا ننادي الدالة من الكلاس الأساسي عشان تطبع الاسم والعمر
        cout << "Client ID: " << clientId << endl;
    }

    int getId() const { return clientId; }
};

// 3. كلاس العامل Worker (كلاس مستقل بنستخدمه بعدين عشان نسوي Multiple Inheritance)
class Worker {
protected:
    string position;
    double salary;

public:
    // الـ Constructor
    Worker(string p = "", double sal = 0.0) {
        position = p;
        salary = sal;
    }

    void displayWorker() const {
        cout << "Position: " << position << ", Salary: " << salary << endl;
    }
};

// 4. كلاس الموظف Employee (وراثة متعددة: يورث من Person و Worker في نفس الوقت)
class Employee : public Person, public Worker {
public:
    // الـ Constructor
    Employee(string n = "", string s = "", int a = 0, string p = "", double sal = 0.0)
        : Person(n, s, a), Worker(p, sal) {}

    void displayEmployee() const {
        cout << "--- Employee Info ---" << endl;
        display();       // نطبع معلومات الشخص العادية
        displayWorker(); // نطبع معلومات الشغل والراتب
    }
};

// 5. كلاس السيارة Car
class Car {
private:
    string licensePlate;
    string brand;
    string model;
    int year;
    double dailyPrice;
    bool available;

public:
    // الـ Constructor
    Car(string lp = "", string b = "", string m = "", int y = 0, double dp = 0.0, bool avail = true) {
        licensePlate = lp;
        brand = b;
        model = m;
        year = y;
        dailyPrice = dp; // السعر بالريال
        available = avail;
    }

    void display() const {
        cout << "Car: " << brand << " " << model << " (" << year << ") | Plate: " << licensePlate
             << " | Price/Day: " << dailyPrice << " SAR | Available: " << (available ? "Yes" : "No") << endl;
    }

    bool isAvailable() const { return available; }
    void setAvailability(bool avail) { available = avail; }
    double getPricePerDay() const { return dailyPrice; }
    string getLicensePlate() const { return licensePlate; }

    // Operator overloading: عشان نقارن سيارتين برقم اللوحة (هل هم نفس السيارة؟)
    bool operator==(const Car& other) const {
        return licensePlate == other.licensePlate;
    }

    // Operator overloading: عشان نقارن سيارتين بالسعر اليومي (مين أرخص؟)
    bool operator<(const Car& other) const {
        return dailyPrice < other.dailyPrice;
    }
};

// 6. كلاس الوكالة Agency (المدير اللي يمسك كل شيء)
class Agency {
private:
    string agencyName;
    string address;
    Car cars[50];
    Client clients[50];
    Employee employees[10];
    
    int carCount;
    int clientCount;
    int employeeCount;

public:
    // الـ Constructor
    Agency(string name = "", string addr = "") {
        agencyName = name;
        address = addr;
        carCount = 0;
        clientCount = 0;
        employeeCount = 0;
    }

    // دالة تضيف سيارة للمصفوفة
    void addCar(Car c) {
        if (carCount < 50) {
            cars[carCount] = c;
            carCount++;
        } else {
            cout << "Error: Car capacity reached!" << endl;
        }
    }

    // دالة تضيف عميل
    void addClient(Client c) {
        if (clientCount < 50) {
            clients[clientCount] = c;
            clientCount++;
        } else {
            cout << "Error: Client capacity reached!" << endl;
        }
    }

    // دالة تضيف موظف
    void addEmployee(Employee e) {
        if (employeeCount < 10) {
            employees[employeeCount] = e;
            employeeCount++;
        } else {
            cout << "Error: Employee capacity reached!" << endl;
        }
    }

    // دالة تعرض بس السيارات المتاحة للإيجار
    void showAvailableCars() const {
        cout << "\n=== Available Cars at " << agencyName << " ===" << endl;
        bool found = false;
        for (int i = 0; i < carCount; i++) {
            if (cars[i].isAvailable()) {
                cars[i].display();
                found = true;
            }
        }
        if (!found) cout << "No cars currently available." << endl;
    }

    // نمرر الـ Client كـ Value، بس الـ Car نمررها كـ Reference عشان نقدر نغير حالة التوفر حقتها
    void processRental(Client client, Car &car) {
        if (car.isAvailable()) {
            cout << "\n=== Rental Invoice ===" << endl;
            cout << "Client: " << client.getName() << " " << client.getSurname() << endl;
            cout << "Car Plate: " << car.getLicensePlate() << endl;
            
            // هنا نسوي محاكاة لتأجير السيارة لمدة 5 أيام
            double total = car.getPricePerDay() * 5;
            cout << "Rental Duration: 5 Days" << endl;
            cout << "Total Cost: " << total << " SAR" << endl;
            
            car.setAvailability(false); // نغير حالة السيارة لـ غير متاحة (لأنها تأجرت خلاص)
            cout << "Status: Rental Processed Successfully!" << endl;
            cout << "======================" << endl;
        } else {
            cout << "\n[Error] The car " << car.getLicensePlate() << " is not available for rent." << endl;
        }
    }
};

// --- دالة الـ main عشان نجرب الكود ونختبره ---
int main() {
    // 1. نسوي أوبجكت للوكالة
    Agency myAgency("Al-Farouq Auto", "Riyadh, Saudi Arabia");

    // 2. نسوي موظف ونضيفه للوكالة
    Employee emp1("Khalid", "Ahmed", 35, "Branch Manager", 9500.0);
    myAgency.addEmployee(emp1);

    // 3. نسوي كم سيارة ونضيفهم للوكالة
    Car car1("ABC-1234", "Toyota", "Camry", 2023, 150.0, true);
    Car car2("XYZ-9876", "Hyundai", "Elantra", 2022, 120.0, true);
    Car car3("KSA-1111", "Ford", "Taurus", 2024, 200.0, true);
    
    myAgency.addCar(car1);
    myAgency.addCar(car2);
    myAgency.addCar(car3);

    // 4. نسوي عميل جديد ونضيفه
    Client client1("Faisal", "Salem", 28, 100101);
    myAgency.addClient(client1);

    // 5. نجرب نطبع معلومات الموظف
    cout << "Testing Employee Display:" << endl;
    emp1.displayEmployee();

    // نعرض السيارات المتاحة قبل الإيجار
    myAgency.showAvailableCars();

    // 6. نجرب نأجر سيارة (العميل Value، والسيارة Reference)
    // نمرر car1 عشان نأجرها لمدة 5 أيام
    myAgency.processRental(client1, car1);

    // نعرض السيارات بعد الإيجار عشان نتأكد إن car1 اختفت من القائمة المتاحة
    myAgency.showAvailableCars();
    
    // 7. نجرب الـ Operator Overloading 
    cout << "\n=== Testing Operator Overloading ===" << endl;
    // نقارن السعر باستخدام علامة أصغر من <
    if (car2 < car3) {
        cout << "Car 2 (" << car2.getPricePerDay() << " SAR) is cheaper than Car 3 (" << car3.getPricePerDay() << " SAR)." << endl;
    }
    
    // نقارن هل السيارتين نفس بعض باستخدام علامة اليساوي ==
    Car carTest("ABC-1234", "TestBrand", "TestModel", 2000, 100.0, true);
    if (car1 == carTest) {
        cout << "car1 and carTest have the same license plate!" << endl;
    }

    return 0;
}
