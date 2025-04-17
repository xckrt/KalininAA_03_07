#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>      

using namespace std;

class AutoRepairShop {
    string brand;
    float cost;
    int days;
    string plate;

public:
    AutoRepairShop(string b, float c, int d, string p)
        : brand(b), cost(c), days(d), plate(p) {
    }

    // Геттеры
    string getBrand() const { return brand; }
    float getCost() const { return cost; }
    int getDays() const { return days; }
    string getPlate() const { return plate; }


    void saveToFile(FILE* file) const {
        fprintf(file, "Марка: %s | Стоимость: %.2f | Дней: %d | Номер: %s\n",
            brand.c_str(), cost, days, plate.c_str());
    }
};


bool compareByBrandAsc(const AutoRepairShop& a, const AutoRepairShop& b) {
    return a.getBrand() < b.getBrand();
}
bool compareByBrandDesc(const AutoRepairShop& a, const AutoRepairShop& b) {
    return a.getBrand() > b.getBrand();
}
bool compareByCostAsc(const AutoRepairShop& a, const AutoRepairShop& b) {
    return a.getCost() < b.getCost();
}
bool compareByCostDesc(const AutoRepairShop& a, const AutoRepairShop& b) {
    return a.getCost() > b.getCost();
}
bool compareByDaysAsc(const AutoRepairShop& a, const AutoRepairShop& b) {
    return a.getDays() < b.getDays();
}
bool compareByDaysDesc(const AutoRepairShop& a, const AutoRepairShop& b) {
    return a.getDays() > b.getDays();
}

int main() {
    vector<AutoRepairShop> repairs;
    int count;

    cout << "Сколько записей добавить? ";
    cin >> count;

    for (int i = 0; i < count; ++i) {
        string brand, plate;
        float cost;
        int days;

        cout << "Марка автомобиля: ";
        cin >> brand;
        cout << "Стоимость ремонта: ";
        cin >> cost;
        cout << "Дней в ремонте: ";
        cin >> days;
        cout << "Номерной знак: ";
        cin >> plate;

        repairs.emplace_back(brand, cost, days, plate);
    }

    int sortField, order;
    cout << "\nСортировать по:\n1 - Марка\n2 - Стоимость\n3 - Дни\nВыбор: ";
    cin >> sortField;

    cout << "Порядок:\n1 - По возрастанию\n2 - По убыванию\nВыбор: ";
    cin >> order;

    switch (sortField) {
    case 1: sort(repairs.begin(), repairs.end(), order == 1 ? compareByBrandAsc : compareByBrandDesc); break;
    case 2: sort(repairs.begin(), repairs.end(), order == 1 ? compareByCostAsc : compareByCostDesc); break;
    case 3: sort(repairs.begin(), repairs.end(), order == 1 ? compareByDaysAsc : compareByDaysDesc); break;
    default: cout << "Неверный выбор!\n"; return 1;
    }


    FILE* file = fopen("repairs.txt", "w");
    if (!file) {
        perror("Ошибка при открытии файла");
        return 1;
    }

    for (const auto& r : repairs) {
        r.saveToFile(file);
    }

    fclose(file);
    cout << "✅ Данные успешно записаны в файл repairs.txt\n";

    return 0;
}
