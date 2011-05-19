#include "net/messages.h"
#include "net/delegator.h"
#include "net/peer.h"
#include "net/dialects/original.h"

#include <iostream>
#include <iomanip>

int run_networking()
{
    libbitcoin::net::delegator_default net;
    net.init();
    if (!net.connect("localhost")) {
        std::cerr << "noes\n";
        return -1;
    }
    std::cin.get();
    return 0;
}

int create_version_message()
{
    libbitcoin::net::message::version version;
    // this is test data. should be in the core eventually
    version.version = 31900;
    version.services = 1;
    version.timestamp = time(NULL);
    version.addr_me.services = version.services;
    version.addr_me.ip_addr = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0};
    version.addr_me.port = 8333;
    version.addr_you.services = version.services;
    version.addr_you.ip_addr = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xff, 0xff, 10, 0, 0, 1};
    version.addr_you.port = 8333;
    version.nonce = 0xdeadbeef;
    version.sub_version_num = "";
    version.start_height = 0;

    libbitcoin::net::original_dialect d;
    libbitcoin::net::serializer::stream msg = d.translate(version);
    for (auto it = msg.begin(); it != msg.end(); it++) {
        std::cout << std::hex << std::setfill('0') << std::setw(2)
                << +static_cast<unsigned char>(*it) << " ";
    }
    std::cout << "\n";
    return 0;
}

int main()
{
    //return run_networking();
    return create_version_message();
}

