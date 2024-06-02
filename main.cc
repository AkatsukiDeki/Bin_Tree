#include <iostream>
#include <vector>
#include <chrono>
#include <functional>
#include "Tree.h"

// Функция для генерации случайных чисел в диапазоне от min до max
int getRandomNumber(int min, int max) {
    static std::mt19937 mt(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(mt);
}

// Функция для вычисления среднего времени выполнения операции по количеству попыток
double calculateAverageTime(int size, int numAttempts, std::function<void()> operation) {
    double totalTime = 0;
    for (int i = 0; i < numAttempts; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        operation();
        auto end = std::chrono::high_resolution_clock::now();
        totalTime += std::chrono::duration<double>(end - start).count();
    }
    return totalTime / numAttempts;
}

std::vector<int> removeDuplicates(const std::vector<int>& input) {
    MyTree tree;
    for (int num : input) {
        tree.insertRecursive(num);
    }
    std::vector<int> result;
    tree.inorderTraversal([&](int value) {
        result.push_back(value);
        });
    return result;
}

int main() {
    const int numAttempts = 1000; // Количество попыток для вычисления среднего времени
    std::vector<int> sizes = { 1000, 10000, 100000 };

    for (int size : sizes) {
        MyTree tree;

        // Измерение времени заполнения дерева
        double fillTime = calculateAverageTime(size, numAttempts, [&]() {
            for (int i = 0; i < size; ++i) {
                tree.insertRecursive(getRandomNumber(1, 2 * size));
            }
            });

        // Измерение времени поиска случайного числа в дереве
        double searchTime = calculateAverageTime(size, numAttempts, [&]() {
            int randomNum = getRandomNumber(1, 2 * size);
            tree.contains(randomNum);
            });

        // Измерение времени добавления и удаления случайного числа из дерева
        double addRemoveTime = calculateAverageTime(size, numAttempts, [&]() {
            int randomNum = getRandomNumber(1, 2 * size);
            tree.insertRecursive(randomNum);
            tree.erase(randomNum);
            });

        // Вывод результатов
        std::cout << "Size: " << size << std::endl;
        std::cout << "Average fill time: " << fillTime << " seconds" << std::endl;
        std::cout << "Average search time: " << searchTime << " seconds" << std::endl;
        std::cout << "Average add/remove time: " << addRemoveTime << " seconds" << std::endl;

        std::vector<int> input = { 3, 2, 2, 4 };
        std::vector<int> result = removeDuplicates(input);

        // Вывод результата
        std::cout << "Original vector: ";
        for (int num : input) {
            std::cout << num << " ";
        }
        std::cout << std::endl;

        std::cout << "Vector with unique elements: ";
        for (int num : result) {
            std::cout << num << " ";
        }
        std::cout << std::endl;

        return 0;
    }

    return 0;
}
