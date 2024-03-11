#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
class DiscountCode {
public:
    std::string id;
    double percentage;

    DiscountCode() : id(""), percentage(0.0) {}

    DiscountCode(const std::string& _id, double _percentage)
        : id(_id), percentage(_percentage) {}
};

class DiscountCodeManager {
public:
    static const std::string dataFile;
    std::vector<DiscountCode> discountCodes;

public:
    void addDiscountCode();
    void updateDiscountCode();
    void deleteDiscountCode();
    void searchDiscountCode();
    void checkDiscountCodeExistence();
    void saveDataToFile();
    bool isDiscountCodeExist(const std::string& discountCodeId);

    DiscountCodeManager() {
        loadDiscountCodesFromFile();
    }

private:
    void loadDiscountCodesFromFile();

};

const std::string DiscountCodeManager::dataFile = "C:\\Users\\admin\\source\\repos\\14012024\\discount_codes.txt";

void DiscountCodeManager::addDiscountCode() {
    std::string id;
    double percentage;

    std::cout << "Nhập ID mã giảm giá: ";
    std::cin >> id;

    if (isDiscountCodeExist(id)) {
        std::cout << "Mã giảm giá với ID " << id << " đã tồn tại.\n";
        return;
    }

    std::cout << "Nhập phần trăm giảm giá (lớn hơn 0 và nhỏ hơn hoặc bằng 100): ";
    std::cin >> percentage;

    if (percentage <= 0 || percentage > 100) {
        std::cout << "Phần trăm không hợp lệ. Thêm mã giảm giá thất bại.\n";
        return;
    }

    DiscountCode newDiscountCode(id, percentage);
    discountCodes.push_back(newDiscountCode);
    std::cout << "Thêm mã giảm giá thành công.\n";

    saveDataToFile();
}

void DiscountCodeManager::updateDiscountCode() {
    std::string id;
    std::cout << "Nhập ID mã giảm giá muốn chỉnh sửa: ";
    std::cin >> id;

    auto it = std::find_if(discountCodes.begin(), discountCodes.end(), [id](const DiscountCode& d) {
        return d.id == id;
        });

    if (it != discountCodes.end()) {
        std::cout << "Phan tram giam gia: " << it->percentage << "\n";

        double newPercentage;
        std::cout << "Cap nhat phan tram ma giam gia: ";
        std::cin >> newPercentage;

        if (newPercentage <= 0 || newPercentage > 100) {
            std::cout << "Khong hop le. Cap nhat ma giam gia that bai\n";
            return;
        }

        it->percentage = newPercentage;
        std::cout << "Cap nhat ma giam gia thanh cong.\n";

        saveDataToFile();
    }
    else {
        std::cout << "Ma giam gia ID " << id << " khong ton tai.\n";
    }
}

void DiscountCodeManager::deleteDiscountCode() {
    std::string id;
    std::cout << "Nhap ID ma giam gia muon xoa: ";
    std::cin >> id;

    auto it = std::find_if(discountCodes.begin(), discountCodes.end(), [id](const DiscountCode& d) {
        return d.id == id;
        });

    if (it != discountCodes.end()) {
        std::cout << "Phan tram giam gia: " << it->percentage << "%" "\n";

        char confirm;
        std::cout << "Xac nhan xoa ? (y/n): ";
        std::cin >> confirm;

        if (confirm == 'y' || confirm == 'Y') {
            discountCodes.erase(it);
            std::cout << "Xoa thanh cong.\n";

            saveDataToFile();
        }
        else {
            std::cout << "Huy xoa.\n";
        }
    }
    else {
        std::cout << "Ma giam gia ID " << id << " khong ton tai.\n";
    }
}

void DiscountCodeManager::searchDiscountCode() {
    std::string id;
    std::cout << "Nhập ID mã giảm giá cần tìm kiếm: ";
    std::cin >> id;

    auto it = std::find_if(discountCodes.begin(), discountCodes.end(), [id](const DiscountCode& d) {
        return d.id == id;
        });

    if (it != discountCodes.end()) {
        std::cout << "ID mã giảm giá: " << it->id << "\nPhần trăm giảm giá: " << it->percentage << "\n";
    }
    else {
        std::cout << "Mã giảm giá ID " << id << " không tồn tại.\n";
    }
}

void DiscountCodeManager::checkDiscountCodeExistence() {
    std::string id;
    std::cout << "Nhập ID mã giảm giá cần kiểm tra: ";
    std::cin >> id;

    if (isDiscountCodeExist(id)) {
        auto it = std::find_if(discountCodes.begin(), discountCodes.end(), [id](const DiscountCode& d) {
            return d.id == id;
            });
        std::cout << "Mã giảm giá ID " << it->id << " tồn tại. Phần trăm giảm giá: " << it->percentage << "\n";
    }
    else {
        std::cout << "Mã giảm giá ID " << id << " không tồn tại.\n";
    }
}

void DiscountCodeManager::loadDiscountCodesFromFile() {
    std::ifstream inputFile(dataFile);

    if (!inputFile.is_open()) {
        std::cerr << "Error opening file for reading.\n";
        return;
    }

    std::string id;
    double percentage;

    while (inputFile >> id >> percentage) {
        DiscountCode loadedDiscountCode(id, percentage);
        discountCodes.push_back(loadedDiscountCode);
    }

    inputFile.close();
}

void DiscountCodeManager::saveDataToFile() {
    std::ofstream outputFile(dataFile);

    if (!outputFile.is_open()) {
        std::cerr << "Error opening file for writing.\n";
        return;
    }

    for (const auto& discountCode : discountCodes) {
        outputFile << discountCode.id << " " << discountCode.percentage << "\n";
    }

    outputFile.close();
}

bool DiscountCodeManager::isDiscountCodeExist(const std::string& id) {
    return std::any_of(discountCodes.begin(), discountCodes.end(), [id](const DiscountCode& d) {
        return d.id == id;
        });
}

