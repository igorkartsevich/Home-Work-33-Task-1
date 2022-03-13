#include <iostream>
#include <exception>
#include <string>
#include <map>

#define GOODSMAX 5

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
    std::cout << "\nGo shopping. Make your choise.\n";

    std::string partNumber;
    int quantity;
    std::cin >> partNumber >> quantity;

    std::map<std::string, int>::iterator it = goods.find(partNumber);
    if (it == goods.end()) throw std::invalid_argument("There is no selected product!");
    if (quantity > it->second) throw std::invalid_argument("The ordered quantity is more than available!");
    if (quantity == it->second) goods.erase(it); else it->second -= quantity;
}

void printGoods(std::map<std::string, int>& goods) {
    std::cout << "\nGoods:\n";
    for (auto element : goods) std::cout << element.first << " " << element.second << std::endl;
}

int main()
{
    std::map<std::string, int> goods;
    goodsLoad(goods);

    try {
        int counter = 0;
        do {
            goShopping(goods);
            printGoods(goods);
        } while (++counter < GOODSMAX);
    }
    catch (std::exception& exc) {
        std::cerr << "ERROR! " << exc.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Some kind of problem happened!";
    }

    return 0;
}