#include <iostream>
#include <map>

using namespace std;

int main() {

map<string, int> mp;

mp["Apple"] = 10;
mp["Banana"] = 20;

cout << mp["Apple"];

mp.erase("Banana");

}