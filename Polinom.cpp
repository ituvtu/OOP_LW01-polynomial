#include <iostream>
using namespace std;

class Polynomial {
private:
    int degree;
    int* coefficients;
public:

    // ����������� � ����������
    Polynomial(int s, int* c) {
        degree = s;
        coefficients = new int[degree];
        for (int i = 0; i < degree; i++) {
            coefficients[i] = c[i];
        }
    }

    // ����������
    ~Polynomial() {
        delete[] coefficients;
    }

    // ��������� ���� �������
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

    // ³������� ���� �������
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

    // �������� ������� �� ���������
    Polynomial operator*(int num) {
        int* result = new int[degree];
        for (int i = 0; i < degree; i++) {
            result[i] = coefficients[i] * num;
        }
        Polynomial product(degree, result);
        delete[] result;
        return product;
    }

    // �������� ���� �������
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

    // ���������� �������� ������� ��� �������� �������� �����
    int evaluate(int x) {
        int result = 0;
        for (int i = 0; i < degree; i++) {
            result += coefficients[i] * pow(x, i);
        }
        return result;
    }

    // ������ ��� ��������� �������
    int getDegree() const {
        return degree;
    }

    // ������ ��� ����������� �������
    int* getCoefficients() const {
        return coefficients;
    }

    // ������ ��� ����������� �������
    void setCoefficients(double* coeffs) {
        for (int i = 0; i <= degree; i++) {
            coefficients[i] = coeffs[i];
        }
    }

    //����� ����������� �������
    void Print() {
        if (degree == 0) {
            std::cout << "0" << std::endl;
            return;
        }
        if (coefficients[0] != 0) {
            std::cout << coefficients[0];
        }
        for (int i = 1; i < degree; i++) {
            if (coefficients[i] != 0) {
                if (coefficients[i] > 0) {
                    std::cout << " + ";
                }
                else {
                    std::cout << " - ";
                }
                if (std::abs(coefficients[i]) != 1 || i == degree - 1) {
                    std::cout << std::abs(coefficients[i]);
                }
                if (i == degree - 1) {
                    std::cout << "x^" << i;
                }
                else {
                    std::cout << "x";
                    if (i != 1) {
                        std::cout << "^" << i;
                    }
                }
            }
        }
        std::cout << std::endl;
    }

    // ��������� ��������� �� �������
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

    int coeffs1[] = { 1, 2, 3 };                // ��������� �����������  ��� ������� �������: 1 + 2x + 3x^2
    int coeffs2[] = { 4, 5, 6, 7 };             // ��������� �����������  ��� ������� ������: 4 + 5x + 6x^2 + 7x^3

    int num = 21;                               // ��������� �����, ��� ������ ��������������� ��� ��������� �� �������� � ��������
    int x = 10;                                 // ��������� �����, �� ���� ��������� ����� ������� ��� ���������� 

    Polynomial p1(3, coeffs1);                  // ��������� 1-�� ������, �������� ���� �����(�������� ������) �� ����� ���� �����������
    Polynomial p2(4, coeffs2);                  // ��������� 2-�� ������, �������� ���� �����(�������� ������) �� ����� ���� �����������

    cout << "Polynomial 1: ";
    p1.Print();                                 // ������������� ����� �����������, ��� �������� ������ ������ �� ������

    cout << "Polynomial 2: ";
    p2.Print();                                 // ������������� ����� �����������, ��� �������� ������ ������ �� ������

    Polynomial sum = p1 + p2;                   // ������������� ����� ��������� 2� �������
    cout << "Sum of the polynomials: ";
    sum.Print();                                // �������� ���� ������� �� �������

    Polynomial difference = p1 - p2;            // ������������� ����� ������ �������
    cout << "Difference of the polynomials: ";
    difference.Print();                         // �������� ������ ������� �� �������

    Polynomial product = p1 * p2;               // ������������� ����� �������� �������
    cout << "Multiply product of the polynomials: ";
    product.Print();                            // �������� ������� ������� �� �������

    Polynomial product_num = p1 * num;          // ������������� ����� ������� ������� �� ��������� 
    cout << "Multiply product of the polynomial and a number: ";
    product_num.Print();                        // �������� ������� ������� �� ���������

    Polynomial product_const_p = p1 + 25;       // ������������� ����� ��������� ��������� �� �������
    cout << "Sum of the polynomial and const:";
    product_const_p.Print();                    // �������� ���� ��������� �� ������� �� �������


    double result = p1.evaluate(x);             // ������������� ����� ���������� �������� ������� ��� �������� �������� �����(x)
    cout << "The value of the polynomial for x = " << x << " is " << result << endl; // �������� ��������� ���������� �� �������

    return 0;
}