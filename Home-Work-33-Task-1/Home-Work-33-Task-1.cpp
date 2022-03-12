#include <iostream>
#include <exception>
#include <string>
#include <map>

#define GOODSMAX 5

class NoGoodsError : public std::exception {
    const char* what() const noexcept override {
        return "There is no selected product!";
    }
};

class MoreGoodsError : public std::exception {
    const char* what() const noexcept override {
        return "The ordered quantity is more than available!";
    }
};

void goodsLoad(std::map<std::string, int>& goods) {
    int counter = 0;
    std::cout << "Load goods into shoping base.\n";

    do {
        std::string partNumber;
        int quantity;
        std::cin >> partNumber >> quantity;
        goods[partNumber] = quantity;
    } while (++counter < GOODSMAX);
}

void goShopping(std::map<std::string, int>& goods) {
    std::cout << "Go shopping. Make your choise.\n";
        std::string partNumber;    int quantity;    std::cin >> partNumber >> quantity;

    std::map<std::string, int>::iterator it = goods.find(partNumber);
    if (it == goods.end()) throw NoGoodsError();
    if (quantity > it->second) throw MoreGoodsError();
    if (quantity == it->second) goods.erase(it); else it->second -= quantity;
}

void printGoods(std::map<std::string, int>& goods) {
    std::cout << "\nGoods:\n";
    for (auto element : goods) std::cout << element.first << " " << element.second << std::endl;
}

int main()
{
    std::map<std::string, int> goods;    goodsLoad(goods);    try {        int counter = 0;        do {            goShopping(goods);            printGoods(goods);        } while (++counter < GOODSMAX);    }    catch (std::exception& exc) {        std::cerr << "ERROR! " << exc.what() << std::endl;    }}