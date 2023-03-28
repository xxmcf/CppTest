#include <string>
#include <iostream>
using std::string;

static string get_channel_value() {

    const char* str_val = "[16719443274]";
    string val = str_val != nullptr ? str_val : "";
    if (val[0] == '[' && val[val.length() - 1] == ']') {
        val = val.substr(1, val.length() - 2);
    }
    return val;
}

static string get_line_parms() {

    string val = get_channel_value();
    std::cout << val << std::endl;

    string sip_network_ip = "1";
    string sip_network_port = "2";

    string line_addr = sip_network_ip + ":" + sip_network_port;
    std::cout << line_addr << std::endl;

    // string sip_to_user = val;
    // string callee_prefix;
    // if (sip_to_user.length() > 11) {
    //     callee_prefix = sip_to_user.substr(0, sip_to_user.length() - 11);
    //     sip_to_user = sip_to_user.substr(sip_to_user.length() - 11, 11);
    // }
    
    //std::cout <<  "callee_prefix: " << callee_prefix << ", callee_id: " << sip_to_user << std::endl;

    return "";
}

int main() {
    get_line_parms();
    return 0;
}