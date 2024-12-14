#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip> 

using namespace std;

void generateInputFile(const string& filename) {
    ofstream inputFile(filename);

    if (!inputFile) {
        cerr << "Не удалось открыть файл для записи!" << endl;
        return;
    }

    srand(time(0));

    for (int i = 0; i < 100; ++i) {
        int randomNumber = rand() % 101 - 50; 
        inputFile << randomNumber << endl;
    }

    inputFile.close();
}

void processFile(const string& inputFilename, const string& outputFilename) {
    ifstream inputFile(inputFilename);

    if (!inputFile) {
        cerr << "Не удалось открыть входной файл!" << endl;
        return;
    }

    int maxNumber = INT_MIN;
    int numbers[100];
    int count = 0;

    while (inputFile >> numbers[count]) {
        if (numbers[count] > maxNumber) {
            maxNumber = numbers[count];
        }
        ++count;
    }
    inputFile.close();

    if (maxNumber == INT_MIN) {
        cerr << "В файле нет чисел!" << endl;
        return;
    }

    double halfMax = maxNumber / 2.0; 

    ofstream outputFile(outputFilename);

    if (!outputFile) {
        cerr << "Не удалось открыть выходной файл!" << endl;
        return;
    }

    outputFile << fixed << setprecision(2);

    for (int i = 0; i < count; ++i) {
        outputFile << numbers[i] / halfMax << endl;
    }

    outputFile.close();
}

int main() {
    setlocale(LC_ALL, "russian");
    string inputFilename = "input.txt";
    string outputFilename = "output.txt";

    generateInputFile(inputFilename);
    processFile(inputFilename, outputFilename);

    cout << "Файлы успешно обработаны!" << endl;

    return 0;
}
