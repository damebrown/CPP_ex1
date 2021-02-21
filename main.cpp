#include <iostream>
#include "Big_Integer.h"
#include "my_set.h"
#include <random>
#include <chrono>

using namespace std;


int charToInt(char c)
{
    return ((int) c - 48);
}

int strToInt(string &number, bool isNegative)
{
    size_t size = number.length();
    int integer = 0, order = 1;
    for (size_t i = 0; i < size; i++)
    {
        integer += order * charToInt(number[i]);
        order *= 10;
    }
    if (isNegative)
    {
        integer = (-integer);
    }
    return integer;
}


void minusTest()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(-99999, 99999);
    int real = 5432;
    big_integer s(real);
    big_integer q(-real);
    int i = 0;
    big_integer e;
    while (i < 15)
    {
        int number = distribution(generator);
        big_integer diff(number);
        big_integer pos = s - diff;
        cout<< "\npositive TEST no' "<<i+1<<"   s = "<<s<<", diff = "<<diff<<"\n\t posResult"
                                     " = "<<pos<<"\nwhile result is= "<< (real-number) <<endl;
            i++;
    }
}

void multiplyTest()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(-20000, 20000);
    for (int i = 1; i < 100; i++)
    {
        int number1 = distribution(generator);
        int number2 = distribution(generator);
        int res = number1;
        res *= number2;

        big_integer thisBig(number1);
        big_integer otherBig(number2);
//        big_integer product = thisBig * otherBig;
        thisBig *= otherBig;

//        int thisInt = strToInt(thisBig.getData(), thisBig.getNegativity());
//        int otherInt = strToInt(otherBig.getData(), otherBig.getNegativity());
//        int fromStr = strToInt(product.getData(), product.getNegativity());
//        int pro;
//        thisInt *= otherInt ;

        static int counter = 0;
        if (thisBig.strToInt(thisBig.getData(), thisBig.getNegativity()) != res)
        {
            counter += 1;
            cout << "FAIL no' "<<counter<<", out of "<<i<<" tests:\n"<<"thisBig = "<<number1<<", "
                                                                                              "otherBig =  "<<number2<< endl;
            cout << "Result: thisBig *= otherBig => thisBig = " <<res<<
            "\nwhile your operator gave       "<< thisBig <<"\n"<< endl;
        }
//        else
//        {
//            cout<<"Success in Test "<<i<<"!\n"<<endl;
//        }
    }
}


void divideTest()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);

    int i = 0, num1, num2;
    std::uniform_int_distribution<int> distribution(0, 55);
    std::uniform_int_distribution<int> distribution2(55, 99);
    while (i < 15)
    {
        num1 = distribution2(generator);
        num2 = distribution(generator);
        big_integer e1(num1), e2(num2);
        big_integer res = e1 / e2;
        cout << "\nTest 1: big_integer\n" << e1 << " / " << e2 << " = " << res << endl;
        cout << "Result 1: int\t" << num1 << " / " << num2 << " = " << num1 / num2 << endl;
        i++;
    }
}

int main()
{
    divideTest();
    return 0;
}