#include "coins.hpp"
#include <ostream>
#include <iostream>
using namespace std;

Coins::Coins(int q, int d, int n, int p)
    : quarters(q), dimes(d), nickels(n), pennies(p) {
}

void Coins::print(ostream& out) const{
    out << quarters << " quarters, " << dimes << " dimes, " 
    << nickels << " nickels, " << pennies << " pennies";
}

ostream& operator<<(ostream& out, const Coins& coins){
    coins.print(out);
    return out;
}

Coins coins_required_for_cents(int amount_in_cents) {
    int q = amount_in_cents/CENTS_PER_QUARTER;
    int remaining = amount_in_cents % CENTS_PER_QUARTER;
    int d = remaining/CENTS_PER_DIME;
    remaining = remaining % CENTS_PER_DIME;
    int n = remaining/CENTS_PER_NICKEL;
    remaining = remaining % CENTS_PER_NICKEL;
    int p = remaining;
    Coins result(q,d,n,p);
    return result;

}

bool Coins::has_exact_change_for_coins(const Coins& coins) const{
    return quarters >= coins.quarters && dimes >= coins.dimes 
    && nickels >= coins.nickels && pennies >= coins.pennies;
}

Coins Coins::extract_exact_change(const Coins& coins){
    if (has_exact_change_for_coins(coins)){
        quarters -= coins.quarters;
        dimes -= coins.dimes;
        nickels -= coins.nickels;
        pennies -= coins.pennies;

        return coins;
    }
    return Coins(0,0,0,0);
}

void Coins::deposit_coins(Coins& coins) {
    quarters += coins.quarters;
    coins.quarters = 0;
    dimes += coins.dimes;
    coins.dimes = 0;
    nickels += coins.nickels;
    coins.nickels = 0;
    pennies += coins.pennies;
    coins.pennies = 0;

}

int Coins::total_value_in_cents() const {
    return quarters * CENTS_PER_QUARTER + dimes * CENTS_PER_DIME + 
    nickels * CENTS_PER_NICKEL + pennies;

}

void print_cents(int cents, ostream& out){
    int dollars = cents/100;
    int remaining = cents%100;
    out << "$" << dollars << ".";
    if (remaining < 10){
        out << "0";
    }
    out << remaining;
}

Coins ask_for_coins(std::istream& in, std::ostream& out){
    int q, d, n, p;
    out << "Quarters? ";
    in >> q;
    out << "Dimes? ";
    in >> d;
    out << "Nickels? ";
    in >> n;
    out << "Pennies? ";
    in >> p;

    return Coins(q,d,n,p);
}

void coins_menu(std::istream& in, std::ostream& out) {
    Coins myCoins(0, 0, 0, 0);
    int choice;

    while(true){
        out << "1. Deposit coins\n";
        out << "2. Extract coins\n";
        out << "3. Print balance\n";
        out << "4. Exit\n";
        out << "Enter choice: ";
        in >> choice;

        if (choice == 4){
            break;
        }

        if (choice == 1){
            Coins newCoins = ask_for_coins(in, out);
            myCoins.deposit_coins(newCoins);
        }

        if (choice == 2){
            Coins newCoins = ask_for_coins(in, out);
            myCoins.extract_exact_change(newCoins);
        }

        if (choice == 3){
            int balance = myCoins.total_value_in_cents();
            print_cents(balance, out);
            out << "\n";
        }

    }

}