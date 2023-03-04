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

    // Додавання двох поліномів
    Polynomial operator+(Polynomial& other) {
        int max_size = max(degree, other.degree);
        int* result = new int[max_size];
        for (int i = 0; i < max_size; i++) {
            int a = i < degree ? coefficients[i] : 0;
            int b = i < other.degree ? other.coefficients[i] : 0;
            result[i] = a + b;
        }
        Polynomial sum(max_size, result);
        delete[] result;
        return sum;
    }

    // Віднімання двох поліномів
    Polynomial operator-(Polynomial& other) {
        int max_size = max(degree, other.degree);
        int* result = new int[max_size];
        for (int i = 0; i < max_size; i++) {
            int a = i < degree ? coefficients[i] : 0;
            int b = i < other.degree ? other.coefficients[i] : 0;
            result[i] = a - b;
        }
        Polynomial difference(max_size, result);
        delete[] result;
        return difference;
    }

    // Множення полінома на константу
    Polynomial operator*(int num) {
        int* result = new int[degree];
        for (int i = 0; i < degree; i++) {
            result[i] = coefficients[i] * num;
        }
        Polynomial product(degree, result);
        delete[] result;
        return product;
    }

    // Множення двох поліномів
    Polynomial operator*(Polynomial& other) {
        int result_size = degree + other.degree - 1;
        int* result = new int[result_size];
        for (int i = 0; i < result_size; i++) {
            result[i] = 0;
            for (int j = 0; j <= i; j++) {
                int a = j < degree ? coefficients[j] : 0;
                int b = (i - j) < other.degree ? other.coefficients[i - j] : 0;
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
            result += coefficients[i] * pow(x, i);
        }
        return result;
    }

    // Геттер для розмірності полінома
    int getDegree() const {
        return degree;
    }

    // Геттер для коефіцієнтів полінома
    int* getCoefficients() const {
        return coefficients;
    }

    // Сеттер для коефіцієнтів полінома
    void setCoefficients(int* coeffs) {
        for (int i = 0; i <= degree; i++) {
            coefficients[i] = coeffs[i];
        }
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
        cout << endl;
    }

    // Додавання константи до полінома
    Polynomial operator+(int num) {
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

    int coeffs1[] = { 1, 2, 3 };                // Створюємо коефіцієнти  для першого полінома: 1 + 2x + 3x^2
    int coeffs2[] = { 4, 5, 6, 7 };             // Створюємо коефіцієнти  для другого поліном: 4 + 5x + 6x^2 + 7x^3

    int num = 21;                               // Створюємо змінну, яку будемо використовувати для додавання та множення з поліномом
    int x = 10;                                 // Створюємо змінну, що буде значенням змінної полінома для обчислення 

    Polynomial p1(3, coeffs1);                  // Створюємо 1-ий поліном, вказуючи його розмір(найвищий степінь) та масив його коефіцієнтів
    Polynomial p2(4, coeffs2);                  // Створюємо 2-ий поліном, вказуючи його розмір(найвищий степінь) та масив його коефіцієнтів

    cout << "Polynomial 1: ";
    p1.Print();                                 // Використовуємо метод відображення, щоб побачити перший поліном на консолі

    cout << "Polynomial 2: ";
    p2.Print();                                 // Використовуємо метод відображення, щоб побачити другий поліном на консолі

    Polynomial sum = p1 + p2;                   // Використовуємо метод додавання 2х поліномів
    cout << "Sum of the polynomials: ";
    sum.Print();                                // Виводимо суму поліномів на консоль

    Polynomial difference = p1 - p2;            // Використовуємо метод різниці поліномів
    cout << "Difference of the polynomials: ";
    difference.Print();                         // Виводимо різницю поліномів на консоль

    Polynomial product = p1 * p2;               // Використовуємо метод множення поліномів
    cout << "Multiply product of the polynomials: ";
    product.Print();                            // Виводимо добуток поліномів на консоль

    Polynomial product_num = p1 * num;          // Використовуємо метод добутку полінома та константи 
    cout << "Multiply product of the polynomial and a number: ";
    product_num.Print();                        // Виводимо добуток полінома та константи

    Polynomial product_const_p = p1 + 25;       // Використовуємо метод додавання константи та полінома
    cout << "Sum of the polynomial and const:";
    product_const_p.Print();                    // Виводимо суму константи та полінома на консоль


    double result = p1.evaluate(x);             // Використовуємо метод обчислення значення полінома для заданого значення змінної(x)
    cout << "The value of the polynomial for x = " << x << " is " << result << endl; // Виводимо результат обчислення на консоль
  
    Polynomial p3(p1);                          //Використовуємо конструктор копіювання, створюємо поліном p3, що буде копією p1
    cout << "p3=";
    p3.Print();                                 //Виводимо поліном-копію на консоль, щоб порівняти
    Polynomial p4(std::move(p1));               //Використовуємо конструктор переміщення(права власності на об'єкт  передає іншому об'єкту)
    cout << "p4=";
    p4.Print();
    
    cout << "And after moving p1 to p4, p1 is equal ";//Виводимо на консоль поліном права власності на який були передані та переконуємось, що поліном дорівнює нуля
    p1.Print();
    return 0;
}