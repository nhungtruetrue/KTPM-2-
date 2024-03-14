#include <iostream>
#include <cstdlib>
#include "products.h"
#include "voucher.h"
#include "invoices.h"
#include "Users.h"

int main() {
    UserManager userManager;
    userManager.addUser(User("kh", "khpass", false));
    userManager.addUser(User("admin", "adminpass", true));

    ProductManager productManager;
    DiscountCodeManager discountCodeManager;
    InvoiceManager invoiceManager(discountCodeManager, productManager);

    std::string username, password;
    std::cout << "Nhap tai khoan: ";
    std::cin >> username;

    std::cout << "Nhap mat khau: ";
    std::cin >> password;
    system("cls");

    if (userManager.authenticateUser(username, password)) {
        std::cout << "Dang nhap thanh cong!\n";
        bool isAdmin = userManager.isAdmin(username);

        if (isAdmin) {
            int adminChoice;

            do {
                std::cout << "Menu quan tri:\n";
                std::cout << "1. Quan ly san pham\n2. Quan ly ma giam gia\n3. Quan ly hoa don\n0. Thoat\n";
                std::cout << "Nhap lua chon cua ban: ";
                std::cin >> adminChoice;
                system("cls");

                switch (adminChoice) {
                case 1:
                    // Quản lý sản phẩm
                    int productChoice;

                    do {
                        std::cout << "Menu san pham:\n1. Them san pham\n2. Cap nhat san pham\n3. Xoa san pham\n4. Tim kiem san pham\n5. Kiem tra ton tai cua san pham\n0. Quay lai\n";
                        std::cout << "Nhap lua chon cua ban: ";
                        std::cin >> productChoice;
                        system("cls");

                        switch (productChoice) {
                        case 1:
                            std::cout << "Them san pham:\n";
                            productManager.addProduct();
                            break;
                        case 2:
                            std::cout << "Cap nhat san pham:\n";
                            productManager.updateProduct();
                            break;
                        case 3:
                            std::cout << "Xoa san pham:\n";
                            productManager.deleteProduct();
                            break;
                        case 4:
                            std::cout << "Tim kiem san pham : \n";
                            productManager.searchProduct();
                            break;
                        case 5:
                            std::cout << "Kiem tra san pham ton tai : \n";
                            productManager.checkProductExistence();
                            break;
                        case 0:
                            std::cout << "Quay lai menu chinh.\n";
                            break;
                        default:
                            std::cout << "Lua chon khong hop le. Vui long thu lai.\n";
                        }

                    } while (productChoice != 0);

                    break;
                case 2:
                    // Quản lý mã giảm giá
                    int discountCodeChoice;

                    do {
                        std::cout << "Menu ma giam gia:\n1. Them ma giam gia\n2. Cap nhat ma giam gia\n3. Xoa ma giam gia\n4. Tim kiem ma giam gia\n5. Kiem tra ton tai ma giam gia\n0. Quay lai\n";
                        std::cout << "Nhap lua chon cua ban: ";
                        std::cin >> discountCodeChoice;

                        switch (discountCodeChoice) {
                        case 1:
                            discountCodeManager.addDiscountCode();
                            break;
                        case 2:
                            discountCodeManager.updateDiscountCode();
                            break;
                        case 3:
                            discountCodeManager.deleteDiscountCode();
                            break;
                        case 4:
                            discountCodeManager.searchDiscountCode();
                            break;
                        case 5:
                            discountCodeManager.checkDiscountCodeExistence();
                            break;
                        case 0:
                            std::cout << "Quay lai menu chinh.\n";
                            break;
                        default:
                            std::cout << "Lua chon khong hop le. Vui long thu lai.\n";
                        }

                    } while (discountCodeChoice != 0);

                    break;
                case 3:
                    // Quản lý hóa đơn
                    int invoiceChoice;

                    do {
                        std::cout << "Menu hoa don:\n1. Tao hoa don nhap \n2. Cap nhat hoa don\n 3. Tao hoa don xuat \n0. Quay lai\n";
                        std::cout << "Nhap lua chon cua ban: ";
                        std::cin >> invoiceChoice;

                        switch (invoiceChoice) {
                        case 1:
                            invoiceManager.createInvoice();
                            break;
                        case 2:
                            invoiceManager.updateInvoice();
                            break;
                        case 3:
                            invoiceManager.createPurchase();
                        case 0:
                            std::cout << "Quay lai menu chinh.\n";
                            break;
                        default:
                            std::cout << "Lua chon khong hop le. Vui long thu lai.\n";
                        }

                    } while (invoiceChoice != 0);

                    break;

                case 0:
                    std::cout << "Thoat khoi chuong trinh.\n";
                    break;
                default:
                    std::cout << "Lua chon khong hop le. Vui long thu lai.\n";
                }

            } while (adminChoice != 0);
        }
        else {
            int employeeChoice;
            do {
                std::cout << "Menu khach hang:\n";
                std::cout << "1. Tra cuu san pham\n2. Mua hang\n0. Thoat\n";
                std::cout << "Nhap lua chon cua ban: ";
                std::cin >> employeeChoice;
                system("cls");

                switch (employeeChoice) {
                case 1:
                    std::cout << "Tim kiem san pham:\n";
                    productManager.searchProduct();
                    break;
                case 2:
                    std::cout << "Tao hoa don\n";
                    invoiceManager.createInvoice();
                    break;
                case 0:
                    std::cout << "Quay lai menu chinh.\n";
                    break;
                default:
                    std::cout << "Lua chon khong hop le. Vui long thu lai.\n";
                }
            } while (employeeChoice != 0);
        }
    }
    else {
        std::cout << "Dang nhap that bai. Tai khoan hoac mat khau khong chinh xac.\n";
    }

    return 0;
}
