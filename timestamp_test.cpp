#include <iostream>
#include <chrono>
#include <string>
static std::string getCurrentTimestamp() {
    auto now   = std::chrono::system_clock::now();
    auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    auto sectime   = std::chrono::duration_cast<std::chrono::seconds>(now_ms);
    int32_t milltime = sectime.count() % 1000;

    std::time_t timet = sectime.count();
    struct tm curtime;
    localtime_r(&timet, &curtime);

    char buffer[64];
    sprintf(buffer, "%lld", now_ms.count());
    //sprintf(buffer, "%4d-%02d-%02d %02d:%02d:%02d.%03d", curtime.tm_year + 1900, curtime.tm_mon + 1,
    //        curtime.tm_mday, curtime.tm_hour, curtime.tm_min, curtime.tm_sec, milltime);
    return std::string(buffer);
}

int main() {

    std::string strTime = getCurrentTimestamp();
    std::cout << strTime << std::endl;

    std::string channe_name = "[sofia/external/90020118600412187@101.132.250.247:32766]";
    size_t index = channe_name.find("@");
    if (!channe_name.empty() && index != std::string::npos && channe_name.substr(channe_name.length()-1, 1).compare("]") == 0) {
        channe_name = channe_name.substr(index + 1, channe_name.length() - index - 2);
    }
    std::cout << channe_name << std::endl;

    //getchar();
    return 0;
}