#include <thread>
#include <chrono>
#include <iostream>

int main()
{
    std::cerr << "(。-ω-)zzz. . . " << "\r";

    // 3秒間おやすみ。
    // 他にnanoseconds、microseconds、milliseconds、minutes、hoursが使える。
    std::this_thread::sleep_for(std::chrono::seconds(3));

    // おはようございます!
    std::cerr << "(。ﾟωﾟ) ﾊｯ!" << std::endl;
}
