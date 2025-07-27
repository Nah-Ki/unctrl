#include <iostream>

int server_main();
int client_main();

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./unctrl [client|server]\n";
        return 1;
    }

    std::string mode = argv[1];
    if (mode == "server") return server_main();
    if (mode == "client") return client_main();

    std::cerr << "Unknown mode: " << mode << "\n";
    return 1;
}

