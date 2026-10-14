#include <iostream>
#include "coins.hpp"
using namespace std;
constexpr int CENTS_FOR_CHIPS = 149;
constexpr int CENTS_FOR_TRANSFER = 405;

int main(){
    Coins piggyBank(50, 50, 50, 50);
    Coins pocket(8,3,6,8);
    cout << piggyBank << endl;
    cout << pocket << endl;
    Coins COST_OF_CHIPS = coins_required_for_cents(CENTS_FOR_CHIPS);
    Coins pay_for_chips = pocket.extract_exact_change(COST_OF_CHIPS);
    cout << "I bought a bag of chips for $1.49" << " using "
         << pay_for_chips << "." << endl;
    Coins COST_OF_TRANSFER = coins_required_for_cents(CENTS_FOR_TRANSFER);
    Coins transferred_cents = piggyBank.extract_exact_change(COST_OF_TRANSFER);
    cout << "Transferred " << transferred_cents << "." << endl;
    pocket.deposit_coins(transferred_cents);
    Coins sofa(10,10,10,10);
    piggyBank.deposit_coins(sofa);
    cout << sofa << endl;
    cout << piggyBank << endl;
    int balance = piggyBank.total_value_in_cents();
    print_cents(balance, cout);
    cout << endl;
    
        }
