/*************************************************************************
	> File Name: test.cpp
	> Author: ZhangZe
	> Mail: zhang_ze_mail@163.com
	> Created Time: 五 10/ 9 14:39:35 2020
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;

typedef struct {
    int a, b;
} Elem, ElemType;


template<typename T1, typename T2>
struct is_same_type {
operator bool() {
    return false;
}
};
 
template<typename T1>
struct is_same_type<T1, T1>{
operator bool() {
    return true;
}

 };

void Random(int &a, int &b) {
    a = random() % 100;
    b = random() % 100;
    cout << "in  func " << a << b << endl;
    return ;
}

#define P_W_R(a, ...)  printf("\033[47;31m" a "\033[0m", ## __VA_ARGS__);
//#define P_W_R(a) printf("\033[47;31m%s\033[0m", #a);


int main() {
    Elem xx;
    ElemType yy;
    cout << sizeof(xx) << endl;
    cout << sizeof(yy) << endl;
    cout << is_same_type<int, int>()  << endl;
    cout << is_same_type<Elem, ElemType>()  << endl;

    cout << endl;

    int x = 8, y = 9;
    Random(x, y);
#ifdef M
    cout << "main " << x << y << endl;
#else 
    P_W_R("红白机%d 2000 %d\n", x, x)
    P_W_R("红白机2000 \n")
#endif 
    printf("\033[47;31m""红白机%d %d2000 \n""\033[0m", x, x);
 //   printf("\033[47;31m""sssds""\033[0m");
  //  printf("%s",  __VA_ARGS__);
    return 0;
}



