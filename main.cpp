main.cpp:

#include <iostream>
#include <vector>
#include "dog.hpp"
#include "cat.hpp"

using namespace std;

double Dog::licensingRate = 2.0;
double Cat::licensingRate = 1.5;

int main()
{
vector<Pet*> pvec;

Dog bob("Bob", 65);
Dog stan("Stan", 37);
Cat tom("Tom", 12);

pvec.push_back(&bob);
pvec.push_back(&stan);
pvec.push_back(&tom);

double total_fee = 0.0;
for (int i = 0; i < pvec.size(); i++)
{
cout << pvec[i]->GetName() << ' ' << pvec[i]->CalculateFee() << endl;
total_fee = total_fee + pvec[i]->CalculateFee();
}
cout << "total licensing fee = " << total_fee << endl;\

return 0;

}