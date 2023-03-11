#include <iostream>
using namespace std;

class Polynomial {
private:
    int degree;
    int* coefficients;
public:

    // Конструктор з параметром
    Polynomial(int s, int* c) {
        degree = s;
        coefficients = new int[degree];
        for (int i = 0; i < degree; i++) {
            coefficients[i] = c[i];
        }
    }
    
    //Дефолтний конструктор без параметрів для введення даних з консолі
    Polynomial() {
        degree = 0;
        coefficients = new int[1];
        coefficients[0] = 0;
    }

    // Копіюючий конструктор
    Polynomial(const Polynomial& poly) {
        degree = poly.degree;
        coefficients = new int[degree + 1];
        for (int i = 0; i <= degree; i++) {
            coefficients[i] = poly.coefficients[i];
        }
    }

    // Конструктор переміщення
    Polynomial(Polynomial&& poly) noexcept {
        degree = poly.degree;
        coefficients = poly.coefficients;
        poly.degree = 0;
        poly.coefficients = nullptr;
    }

    // Деструктор
    ~Polynomial() {
        delete[] coefficients;
    }

    // Геттер для розмірності полінома
    int getDegree() const {
        return degree;
    }

    // Геттер для коефіцієнтів полінома
    int getCoefficients(int index) const {
        return coefficients[index];
    }

    // Сеттер для коефіцієнтів полінома передаючи в сеттер масив
    void setCoefficientsArray(int* coeffs) {
        for (int i = 0; i <= degree; i++) {
            coefficients[i] = coeffs[i];
        }
    }

    // Сеттер встановлення коефіцієнта за заданим індексом
    void setCoefficientIndex(int index, int value) {
        coefficients[index] = value;
    }
    
    //Сеттер встановлення коефіцієнтів полінома
    void setCoefficientsAndDegree() {
        int n; // кількість коефіцієнтів
      
        cout << "Enter the degree of the polynomial: ";
        cin >> n;

        // ініціалізуємо масив коефіцієнтів з нулями
        int* newCoefficients = new int[n + 1];
        for (int i = 0; i <= n; i++) {
            newCoefficients[i] = 0;
        }

        // вводимо коефіцієнти з консолі
        for (int i = n; i >= 0; i--) {
            int coef;
            cout << "Enter the coefficient of x^" << i << ": ";
            cin >> coef;
            newCoefficients[i] = coef;
        }

        // оновлюємо розмірність та коефіцієнти полінома
        degree = n;
        delete[] coefficients; // видаляємо старі коефіцієнти
        coefficients = newCoefficients;
    }

    // Додавання двох поліномів
    Polynomial add(Polynomial p) {
        int max_size = max(degree, p.degree);
        int* result = new int[max_size];
        for (int i = 0; i < max_size; i++) {
            int a = i < degree ? coefficients[i] : 0;
            int b = i < p.degree ? p.coefficients[i] : 0;
            result[i] = a + b;
        }
        Polynomial sum(max_size, result);
        delete[] result;
        return sum;
    }

    //Порівняння двох поліномів
    bool equal(Polynomial p) {
        if (degree != p.degree) {
            return false;
        }
        for (int i = 0; i <= degree; i++) {
            if (coefficients[i] != p.coefficients[i]) {
                return false;
            }
        }
        return true;
    }

    // Метод відображення результату порівняння поліномів
    void printEqualResult(Polynomial p) {
        if (equal(p)) {
            cout << "The polynomials are equal." << endl << endl;
        }
        else {
            cout << "The polynomials are not equal." << endl << endl;
        }

    }

    // Віднімання двох поліномів
    Polynomial diff(Polynomial p) {
        int max_size = max(degree, p.degree);
        int* result = new int[max_size];
        for (int i = 0; i < max_size; i++) {
            int a = i < degree ? coefficients[i] : 0;
            int b = i < p.degree ? p.coefficients[i] : 0;
            result[i] = a - b;
        }
        Polynomial difference(max_size, result);
        delete[] result;
        return difference;
    }

    // Множення полінома на константу
    Polynomial multiply_const (int num) {
        int* result = new int[degree];
        for (int i = 0; i < degree; i++) {
            result[i] = coefficients[i] * num;
        }
        Polynomial product(degree, result);
        delete[] result;
        return product;
    }

    // Множення двох поліномів
    Polynomial multiply(Polynomial p) {
        int result_size = degree + p.degree - 1;
        int* result = new int[result_size];
        for (int i = 0; i < result_size; i++) {
            result[i] = 0;
            for (int j = 0; j <= i; j++) {
                int a = j < degree ? coefficients[j] : 0;
                int b = (i - j) < p.degree ? p.coefficients[i - j] : 0;
                result[i] += a * b;
            }
        }
        Polynomial product(result_size, result);
        delete[] result;
        return product;
    }

    // Обчислення значення полінома для заданого значення змінної
    int evaluate(int x) {
        int result = 0;
        for (int i = 0; i < degree; i++) {
            result += (int)(coefficients[i] * pow(x, i));
        }
        return result;
    }

    
    //Метод відображення полінома
    void Print() {
        if (degree == 0) {
            cout << "0" << endl;
            return;
        }
        if (coefficients[0] != 0) {
            cout << coefficients[0];
        }
        for (int i = 1; i < degree; i++) {
            if (coefficients[i] != 0) {
                if (coefficients[i] > 0) {
                    cout << " + ";
                }
                else {
                    cout << " - ";
                }
                if (abs(coefficients[i]) != 1 || i == degree - 1) {
                    cout << abs(coefficients[i]);
                }
                if (i == degree - 1) {
                    cout << "x^" << i;
                }
                else {
                    cout << "x";
                    if (i != 1) {
                        cout << "^" << i;
                    }
                }
            }
        }
        cout << endl << endl;
    }

    // Додавання константи до полінома
    Polynomial add_const(int num) {
        int* result = new int[degree];
        for (int i = 0; i < degree; i++) {
            result[i] = coefficients[i];
        }
        result[0] += num;
        Polynomial sum(degree, result);
        delete[] result;
        return sum;
    }

};


int main() {


    Polynomial p1;                              // Створюємо 1-ий поліном, вказуючи його розмір(найвищий степінь) та масив його коефіцієнтів                
    p1.setCoefficientsAndDegree();              // Використовуємо сеттер коефіцієнтів та розмірності, що вводимо з консолі 

    cout << "Polynomial 1: ";
    p1.Print();                                 // Використовуємо метод відображення, щоб побачити перший поліном на консолі

    Polynomial p2;                              // Створюємо 2-ий поліном, вказуючи його розмір(найвищий степінь) та масив його коефіцієнтів                
    p2.setCoefficientsAndDegree();              // Використовуємо сеттер коефіцієнтів та розмірності, що вводимо з консолі 

    cout << "Polynomial 2: ";
    p2.Print();                                 // Використовуємо метод відображення, щоб побачити другий поліном на консолі

    int num = 21;                               // Створюємо змінну, яку будемо використовувати для додавання та множення з поліномом
    int x = 10;                                 // Створюємо змінну, що буде значенням змінної полінома для обчислення 

    Polynomial add = p1.add(p2);                // Використовуємо метод додавання 2х поліномів
    cout << "Sum of the polynomials: ";
    add.Print();                                // Виводимо суму поліномів на консоль

    p1.equal(p2);                               // Використовуємо метод порівняння 2х поліномів
    p1.printEqualResult(p2);                    // Використовуємо метод порівняння і відображення на консолі результату порівняння двох поліномів
    
    Polynomial difference = p1.diff(p2);        // Використовуємо метод різниці поліномів
    cout << "Difference of the polynomials: ";
    difference.Print();                         // Виводимо різницю поліномів на консоль

    Polynomial product = p1.multiply(p2);       // Використовуємо метод множення поліномів
    cout << "Multiply product of the polynomials: ";
    product.Print();                            // Виводимо добуток поліномів на консоль

    Polynomial product_num = p1.multiply_const(num); // Використовуємо метод добутку полінома та константи 
    cout << "Multiply product of the polynomial and a number: ";
    product_num.Print();                        // Виводимо добуток полінома та константи

    Polynomial product_const_p = p1.add_const(25); // Використовуємо метод додавання константи та полінома
    cout << "Sum of the polynomial and const:";
    product_const_p.Print();                    // Виводимо суму константи та полінома на консоль


    double result = p1.evaluate(x);             // Використовуємо метод обчислення значення полінома для заданого значення змінної(x)
    cout << "The value of the polynomial for x = " << x << " is " << result << endl; // Виводимо результат обчислення на консоль
  
    Polynomial p3(p1);                          //Використовуємо конструктор копіювання, створюємо поліном p3, що буде копією p1
    cout << "p3 = ";
    p3.Print();                                 //Виводимо поліном-копію на консоль, щоб порівняти
    Polynomial p4(move(p1));               //Використовуємо конструктор переміщення(права власності на об'єкт  передає іншому об'єкту)
    cout << "p4 = ";
    p4.Print();
    
    cout << "And after moving p1 to p4, p1 is equal 0"; //Виводимо на консоль поліном права власності на який були передані та переконуємось, що поліном дорівнює нуля
   
    return 0;
}
