#include <thread>
#include <chrono>
#include <iostream>

// ユーザ定義リテラルをうまいこと使えるようにする
using namespace std::chrono_literals;

// 2016/7/31追記 std::chrono::duration<long>だとx.y[sec](0.1secとか)が扱えないですね…修正。
void sleep(std::chrono::duration<double> time)
{
    return std::this_thread::sleep_for(time);
}

int main()
{
    std::cerr << "???「三分間待ってやる」" << std::endl;

    // あれって実際には50秒とかそのへんらしいですね。
    // 他にns、us、ms、min、hが使える。
    sleep(50s);

    std::cerr << "???「時間だ。答えを聞こう。」" << std::endl;
    std::cerr << "???&???「バルス!!!」" << std::endl;
}
