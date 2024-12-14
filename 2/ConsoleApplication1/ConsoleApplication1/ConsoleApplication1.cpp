#include <iostream>
#include <cmath>
#include <stdexcept>
using namespace std;

class CustomException : public exception {
private:
    string message;
    double value;
    int errorCode;
    sds
public:
    CustomException(const string& msg, double val, int code)
        : message(msg), value(val), errorCode(code) {}

    const char* what() const noexcept override {
        return message.c_str();
    }

    double getValue() const {
        return value;
    }

    int getErrorCode() const {
        return errorCode;
    }
};

void calculateZ1(double x, double& result) {
    if (x < 0) {
        throw CustomException("Ошибка: x не может быть отрицательным, так как нельзя извлечь корень из отрицательного числа.", x, 1);
    }

    double numerator = sqrt((3 * x + 2) * (3 * x + 2) - 24 * x);
    double denominator = 3 * sqrt(x) - 2 / sqrt(x);

    if (denominator == 0) {
        throw CustomException("Ошибка: Деление на ноль.", x, 2);
    }

    result = numerator / denominator;
}

void calculateZ2(double x, double& result) {
    if (x < 0) {
        throw CustomException("Ошибка: x не может быть отрицательным, так как нельзя извлечь корень из отрицательного числа.", x, 1);
    }

    result = -sqrt(x);
}

int main() {
    setlocale(LC_ALL, "Russian");
    double x;
    cout << "Введите значение x: ";
    cin >> x;

    double z1, z2;

    try {
        calculateZ1(x, z1);
        calculateZ2(x, z2);

        cout << "Z1 = " << z1 << endl;
        cout << "Z2 = " << z2 << endl;

        if (fabs(z1 - z2) < 1e-6) {
            cout << "Z1 и Z2 приблизительно равны." << endl;
        }
        else {
            cout << "Z1 и Z2 не равны." << endl;
        }
    }
    catch (const CustomException& e) {
        cout << "Произошла ошибка: " << e.what() << endl;
        cout << "Значение: " << e.getValue() << endl;
        cout << "Код ошибки: " << e.getErrorCode() << endl;
    }

    return 0;
}
