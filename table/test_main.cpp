#include <iostream>
#include <string>
#include <ctime>
#include <thread>

#include "table.h"
#include "stock_market.h"

using namespace std;

int HashFunctionHorner(const std::string& s, int table_size, const int key)
{
    int hash_result = 0;
    for (int i = 0; s[i] != s.size(); ++i)
        hash_result = (key * hash_result + s[i]) % table_size;
    hash_result = (hash_result * 2 + 1) % table_size;
    return hash_result;
}
struct HashFunction1
{
    int operator()(const std::string& s, int table_size) const
    {
        return HashFunctionHorner(s, table_size, table_size - 1); // ����� ������ ���� ������������, ���������� ����� <������ �������> ���� � ����� ����.
    }
};
struct HashFunction2
{
    int operator()(const std::string& s, int table_size) const
    {
        return HashFunctionHorner(s, table_size, table_size + 1);
    }
};

void tableTest()
{
    SimpleTable<int, int> table;
    table.insert(1, 2);
    table.insert(2, 3);
    auto res = table.find(1);
    cout << *res << endl;
    cout << table.getSize() << endl;
    vector<int> t;
}
void timeTest()
{
    // UNIX Time // POSIX-time
    // 00:00:00 1.01.1970
    int64_t t = getNowTime();
    cout << t << endl;
    struct tm tm;
    localtime_s(&tm, &t);
    char date[20];
    strftime(date, sizeof(date), "%Y-%m-%d", &tm);
    string d = date;
    cout << d << endl;
}
void hashTabe()
{
    std::hash<int64_t> hash64; // hash64 - �������
    //cout << hash64(2) << " " << hash64(4) << " " << hash64(8) << " " << hash64(16) << " " << hash64(32) << " " << hash64(64) << endl;
    //cout << hash64(128)<<" "<<hash64(256) << " " << hash64(512) << " " << hash64(1024) << " " << hash64(2048) << " "<< hash64(4096) << " " << hash64(8192) << endl;
    //cout << hash64(1) << " " << hash64(2) << " " << hash64(3) << " " << hash64(4) << " " << hash64(5) << " " << hash64(6) << endl;

    // hash
    // 1. �����������������, key -> x1
    // 2. ������� ����������
    // 3. ������������� �������� �� ��� ������� ����������� �������� �����
    // 4. ��������� ��������� ����� ������ ��������� � ������������� ��������� ����
    // 5. ������������� ������ ����� ����� � ���������� ��� ��������

    // Key % p = hash(key)

    // SHA-3
    // N ���� - 256 ���
    // hash(x), x - 8 byte
    // hash(25 byte) -> 1 byte -> 

    // SHA-3
}
void threadTest()
{
    StockMarket market;
    Order req(Order::Type::BUY, 950, 100);
    Order order(Order::Type::BUY, 900, 90);

    const int numReq = 1000;

    std::thread thread([&]() {
        for (int i = 0; i < numReq; i++)
        {
            market.addRequestSafe(order);
        }
        });
    int counter = 0;
    while (counter != numReq)
    {
        if (market.processFirstRequestSafe())
            counter++;
    }
    thread.join();
}

void main()
{
    StockMarket market;

    market.addRequestSafe(Registration(10));
    market.addRequestSafe(Registration(12));

    market.addRequestSafe(Order(Order::Type::BUY, 1000, 10));
    market.addRequestSafe(Order(Order::Type::SELL, 1001, 12));
    market.addRequestSafe(Order(Order::Type::SELL, 1000, 12));
    market.addRequestSafe(Order(Order::Type::BUY, 1100, 10));

    market.addRequestSafe(Order(Order::Type::BUY, 1100, 10));
    market.addRequestSafe(Order(Order::Type::BUY, 1100, 10));
    market.addRequestSafe(Order(Order::Type::BUY, 1100, 10));
    market.addRequestSafe(Order(Order::Type::BUY, 1100, 10));
    market.addRequestSafe(Order(Order::Type::BUY, 1100, 10));


    market.addRequestSafe(Order(Order::Type::SELL, 1000, 12));

    auto order = Order(Order::Type::BUY, 100, 12);
    market.addRequestSafe(order);
    market.addRequestSafe(CancelOrder(order));

    for (int i = 0; i < 10000; i++)
        market.processFirstRequestSafe();
}
