#include <thread>
#include <chrono>
#include <iostream>

// ユーザ定義リテラルをうまいこと使えるようにする
using namespace std::chrono_literals;

int main()
{
    std::cerr << "???「三分間待ってやる」" << std::endl;

    // あれって実際には50秒とかそのへんらしいですね。
    // 他にns、us、ms、min、hが使える。
    std::this_thread::sleep_for(50s);

    std::cerr << "???「時間だ。答えを聞こう。」" << std::endl;
    std::cerr << "???&???「バルス!!!」" << std::endl;
}
