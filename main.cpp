/*************************************************************************
	> File Name: main.cpp
	> Author: ZhangZe
	> Mail: zhang_ze_mail@163.com
	> Created Time: 五 10/ 9 14:38:05 2020
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
#include <list>
#include <unistd.h>
#include <time.h>
using namespace std;

#define P_W_R(a, ...)  printf("\033[1m\033[43;31m" a "\033[0m", ## __VA_ARGS__);
#define P_B_R(a, ...)  printf("\033[1m\033[40;31m" a "\033[0m", ## __VA_ARGS__);
#define P_W_G(a, ...)  printf("\033[1m\033[43;32m" a "\033[0m", ## __VA_ARGS__);
#define P_B_G(a, ...)  printf("\033[1m\033[40;32m" a "\033[0m", ## __VA_ARGS__);
#define P_B_Y(a, ...)  printf("\033[1m\033[40;33m" a "\033[0m", ## __VA_ARGS__);
//#define P_B_R(args...) printf("\033[40;31m%s\033[0m", #args);

struct Event {
    int OccurTime;
    int NType;
};

struct QEvent {
    int ArrivalTime;
    int durtime; 
};


list<Event> ev;
queue<QEvent> q[5];
int TotalTime, CustomerNum;
const int CloseTime = 1000; // bank will close ~


bool cmp(Event a, Event b) {
    return a.OccurTime < b.OccurTime;
}

void EventOrderInsert(list<Event> &ev, Event en, bool (*cmp)(Event, Event)) {
    if (ev.empty()) {
        ev.push_back(en);
        return ;
    }
    int flag = 0;
    for (auto it = ev.begin(); it != ev.end(); it++) {
        if(!cmp((*it), en)) {
            ev.insert(it, en);
            flag = 1;
            break;
        }
    } 
    if (flag == 0) ev.push_back(en);
    return ;
}


void OpenForDay() {
    TotalTime = 0, CustomerNum = 0; 
    Event en; // 设定第一个客户；
    en.OccurTime = 0, en.NType = 0;
    EventOrderInsert(ev, en, cmp); //插入事件
    // 如果多次调用，队列置为空
}

void Random(int &a, int &b) {
    srandom(time(0));
    a = random() % 300;
    b = random() % 300;
    return ;
}

int MinNum() {
    int j = 1;
    for (int i = 1; i <= 4; i++) {
        if (q[i].size() < q[j].size()) j = i;
    }
    return j;
}


void CustomerArrived(Event en) {
    // 处理到达
    ++CustomerNum;
    int durtime, innertime;
#ifdef D
    Random(durtime, innertime); // 这样处理的好处是 更简单的随机
    sleep(3);
#else
    P_B_Y("cin here ->   ")
    cin >> durtime >> innertime;
#endif

    // 下一个事件
    int NextCustomerTime = en.OccurTime + innertime;
    if(NextCustomerTime < CloseTime) EventOrderInsert(ev, {NextCustomerTime, 0}, cmp); //插入事件
    
    // 本事件加入到队列中
    int i = MinNum();
    q[i].push({en.OccurTime, durtime});

    //本事件离开时间加入到list中
    int LeftTime = en.OccurTime + durtime;
    if(q[i].size() == 1) EventOrderInsert(ev, {LeftTime, i}, cmp); 
}

void CustomerDeparture(Event en) {
    // 处理离开
    int i = en.NType;
    QEvent Customer = q[i].front();
    q[i].pop();
    TotalTime += (en.OccurTime - Customer.ArrivalTime);
    
    if (!q[i].empty()) {
        QEvent Customer = q[i].front();
        q[i].pop();
        EventOrderInsert(ev, {en.OccurTime + Customer.durtime, i}, cmp); // 将队列中一个预备离开的客户加入事件list
    }
}

void EventListoutput() {
    P_W_R("list  (%d) :", (int)ev.size())
    P_B_R("\n  =======  [ head -> ")
    for (auto i : ev) {
        P_B_R("( %d, %d) -> ", i.OccurTime, i.NType)
    }
    P_B_R("end ]\n")
}

void QEventoutput() {
    P_W_G("QEvent :   ");
    for (int i = 1; i <= 4; i++) {
        queue<QEvent> temp = q[i];
        P_B_G("\n  =======  QEvent %d :", i)
        P_B_Y("[");
        while (temp.size()) {
            QEvent tempQEvent = q[i].front();
            temp.pop();
            P_B_G("(%d, %d)", tempQEvent.ArrivalTime, tempQEvent.durtime)
        }
        P_B_Y("]");
    }    
}

void Bank_Simulation() {
    OpenForDay();
    while (!ev.empty()) {
        Event FirstEvent = ev.front();
        ev.pop_front(); // 取出第一个节点并且删除
        if (!FirstEvent.NType) CustomerArrived(FirstEvent);
        else CustomerDeparture(FirstEvent);
        EventListoutput();
        QEventoutput();
        cout << endl;
    }
    cout << "Average time is : " << (TotalTime / (CustomerNum)) << endl;
}


int main() {
    Bank_Simulation();
    return 0;
}


