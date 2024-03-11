#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include "products.h"
#include "voucher.h"
class ProductManager;
class DiscountCodeManager;
class Invoice {
public:
    std::string id;
    std::string productId;
    std::string discountCodeId;
    int quantity;

    Invoice(const std::string& _id, const std::string& _productId,
        const std::string& _discountCodeId, int _quantity)
        : id(_id), productId(_productId),
        discountCodeId(_discountCodeId), quantity(_quantity) {}

    void display() const {
            std::cout<<"ID hoa don: "<<id<<"\nID San pham : " << productId << "\nID Ma giam gia : " << discountCodeId
            << "\nSo luong: " << quantity << "\n\n";
    }
};
class InvoiceManager : public DiscountCodeManager, public ProductManager {
private:
    std::vector<Invoice> invoices;

public:
    InvoiceManager(DiscountCodeManager& _discountCodeManager, ProductManager& _productManager)
        : DiscountCodeManager(_discountCodeManager), ProductManager(_productManager) {}

    void createInvoice();
    void updateInvoice();
    void createPurchase();

private:
    double calculateTotalAmount(const std::string& productId, int quantity);
    double calculateDiscountAmount(const std::string& discountCodeId, double totalAmount);
    std::string generateInvoiceId();
    std::string getCurrentTime();
    void saveInvoiceToFile(const Invoice& invoice);
};

void InvoiceManager::createPurchase() {
    std::string id = generateInvoiceId();
    std::string productId;
    int quantity;

    std::cout << "Nhap ID san pham : ";
    std::cin >> productId;

    std::cout << "Nhap so luong: ";
    std::cin >> quantity;

    // Kiểm tra sự tồn tại của sản phẩm và đủ số lượng để bán
    if (!isIdExist(productId)) {
        std::cout << "San pham khong ton tai.\n";
        return;
    }

    auto productIt = std::find_if(products.begin(), products.end(), [productId](const Product& p) {
        return p.id == productId;
        });

    if (productIt != products.end() && productIt->quantity >= quantity) {
        double totalAmount = calculateTotalAmount(productId, quantity);

        // Hiển thị thông tin hóa đơn
        Invoice newInvoice(id, productId, "", quantity);  // Empty discountCodeId
        newInvoice.display();
        std::cout << "Tong tien: " << totalAmount << "\n";
        // Cập nhật số lượng sản phẩm
        productIt->quantity += quantity;
        // Lưu hóa đơn vào danh sách và file
        invoices.push_back(newInvoice);
        saveInvoiceToFile(newInvoice);
        ProductManager::saveDataToFile(); // Update product quantity in the file
    }
    else {
        std::cout << "Sản phẩm hoặc số lượng không hợp lệ.\n";
    }
}

void InvoiceManager::createInvoice() {
    std::string id = generateInvoiceId();
    std::string productId;
    std::string discountCodeId;
    int quantity;

    std::cout << "Nhap ID san pham : ";
    std::cin >> productId;

    std::cout << "Nhap ma giam gia ( neu co): ";
    std::cin >> discountCodeId;

    std::cout << "Nhap so luong: ";
    std::cin >> quantity;

    // Kiểm tra sự tồn tại của sản phẩm và mã giảm giá
    if (!isIdExist(productId)) {
        std::cout << "San pham khong ton tai.\n";
        return;
    }

    if (!isDiscountCodeExist(discountCodeId)) {
        std::cout << "Ma giam gia khong ton tai.\n";
        return;
    }

    auto productIt = std::find_if(products.begin(), products.end(), [productId](const Product& p) {
        return p.id == productId;
        });

    // Kiểm tra đủ số lượng để bán
    if (productIt != products.end() && productIt->quantity >= quantity) {
        double totalAmount = calculateTotalAmount(productId, quantity);
        double discountAmount = calculateDiscountAmount(discountCodeId, totalAmount);
        double finalAmount = totalAmount - discountAmount;

        // Hiển thị thông tin hóa đơn
        Invoice newInvoice(id, productId, discountCodeId, quantity);
        newInvoice.display();
        std::cout << "Tong tien: " << totalAmount << "\nTong giam gia: " << discountAmount
            << "\nTong tien thanh toan: " << finalAmount << "\n";

        // Cập nhật số lượng sản phẩm
        productIt->quantity -= quantity;

        // Lưu hóa đơn vào danh sách và file
        invoices.push_back(newInvoice);
        saveInvoiceToFile(newInvoice);
        ProductManager::saveDataToFile(); // Update product quantity in the file
    }
    else {
        std::cout << "Sản phẩm hoặc số lượng không hợp lệ.\n";
    }
}


void InvoiceManager::updateInvoice() {
    std::string id;
    std::cout << "Nhap ID hoa don muon cap nhat: ";
    std::cin >> id;

    auto it = std::find_if(invoices.begin(), invoices.end(), [id](const Invoice& invoice) {
        return invoice.id == id;
        });

    if (it != invoices.end()) {
        // Hiển thị thông tin hóa đơn hiện tại
        it->display();

        // Nhập thông tin mới từ nhân viên
        std::string newProductId;
        std::string newDiscountCodeId;
        int newQuantity;
        std::cout << "Nhap ID san pham moi: ";
        std::cin >> newProductId;

        std::cout << "Nhap Id ma giam gia (neu co): ";
        std::cin >> newDiscountCodeId;

        std::cout << "Nhap so luong moi: ";
        std::cin >> newQuantity;

        // Kiểm tra sự tồn tại của sản phẩm và mã giảm giá
        if (!isIdExist(newProductId)) {
            std::cout << "San pham khong ton tai.\n";
            return;
        }

        if (!isDiscountCodeExist(newDiscountCodeId)) {
            std::cout << "Ma giam gia khong ton tai.\n";
            return;
        }

        double totalAmount = calculateTotalAmount(newProductId, newQuantity);
        double discountAmount = calculateDiscountAmount(newDiscountCodeId, totalAmount);
        double finalAmount = totalAmount - discountAmount;

        // Hiển thị thông tin hóa đơn mới
        it->productId = newProductId;
        it->discountCodeId = newDiscountCodeId;
        it->quantity = newQuantity;
        it->display();

        std::cout << "Tổng tiền: " << totalAmount << "\nTổng giảm giá: " << discountAmount
            << "\nTổng tiền thanh toán: " << finalAmount << "\n";

        std::cout << "Xác nhận lưu thông tin hóa đơn đã cập nhật? (y/n): ";
        char confirm;
        std::cin >> confirm;

        if (confirm == 'y' || confirm == 'Y') {
            // Lưu thông tin hóa đơn đã cập nhật
            std::cout << "Cập nhật thông tin hóa đơn thành công.\n";
            saveInvoiceToFile(*it);
        }
        else {
            std::cout << "Hủy cập nhật thông tin hóa đơn.\n";
            // Khôi phục thông tin hóa đơn về trạng thái ban đầu
            it->display();
        }
    }
    else {
        std::cout << "Hóa đơn với ID " << id << " không tồn tại.\n";
    }
}

double InvoiceManager::calculateTotalAmount(const std::string& productId, int quantity) {
    auto productIt = std::find_if(products.begin(), products.end(), [productId](const Product& p) {
        return p.id == productId;
        });

    if (productIt != products.end()) {
        return productIt->price * quantity;
    }
    else {
        std::cerr << "Lỗi tính toán tổng tiền: Sản phẩm không tồn tại.\n";
        return 0.0;
    }
}

double InvoiceManager::calculateDiscountAmount(const std::string& discountCodeId, double totalAmount) {
    auto discountCodeIt = std::find_if(discountCodes.begin(), discountCodes.end(), [discountCodeId](const DiscountCode& d) {
        return d.id == discountCodeId;
        });

    if (discountCodeIt != discountCodes.end()) {
        return totalAmount * (discountCodeIt->percentage / 100.0);
    }
    else {
        return 0.0;
    }
}

std::string InvoiceManager::generateInvoiceId() {
    static int invoiceCounter = 1;
    return "HD" + std::to_string(invoiceCounter++);
}
std::string InvoiceManager::getCurrentTime() {
    std::time_t now = std::time(0);
    std::tm timeInfo;
    localtime_s(&timeInfo, &now);

    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeInfo);
    return buffer;
}

void InvoiceManager::saveInvoiceToFile(const Invoice& invoice) {
    std::ofstream outputFile("C:\\Users\\admin\\source\\repos\\14012024\\invoices.txt", std::ios::app);  // Mở file để ghi thêm vào cuối
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file for writing.\n";
        return;
    }

    outputFile << "ID Hóa đơn: " << invoice.id
        << "\nID Sản phẩm: " << invoice.productId << "\nID Mã giảm giá: " << invoice.discountCodeId
        << "\nSố lượng: " << invoice.quantity << "\nThời gian: " << getCurrentTime() << "\n\n";

    outputFile.close();
}
