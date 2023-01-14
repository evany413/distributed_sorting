/**
 * entry point of the program
 * ./main -m master -p 8080 -n 5 -i ./input -o ./output
 * ./main --mode master --port 8080 --num 5 --input ./input --output ./output
 * ./main -m slave -p 8080
 * ./main --mode slave --port 8080
 *
 */

#include <getopt.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <vector>

#include "master.hpp"
#include "slave.hpp"

using namespace std;

void help() {
    cout << "Usage: ./main -m master -p 8080 -n 5 -i ./input -o ./output" << endl;
    cout << "       ./main --mode master --port 8080 --num 5 --input ./input --output ./output" << endl;
    cout << "       ./main -m slave -p 8080" << endl;
    cout << "       ./main --mode slave --port 8080" << endl;
}

int main(int argc, char** argv) {
    static struct option long_options[] = {
        {"mode", required_argument, 0, 'm'},
        {"port", required_argument, 0, 'p'},
        {"num", optional_argument, 0, 'n'},
        {"input", optional_argument, 0, 'i'},
        {"output", optional_argument, 0, 'o'},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}};
    int option_index = 0;
    int c, port, num;
    string mode, input, output;

    while ((c = getopt_long(argc, argv, "m:p:n:i:o:", long_options, &option_index)) != -1) {
        switch (c) {
            case 'm':
                mode = optarg;
                break;
            case 'p':
                port = atoi(optarg);
                break;
            case 'n':
                num = atoi(optarg);
                break;
            case 'i':
                input = optarg;
                break;
            case 'o':
                output = optarg;
                break;
            case 'h':
                help();
                return 0;
            default:
                help();
                return 1;
        }
    }

    if (mode == "master") {
        if (num == 0 || input.empty() || output.empty()) {
            help();
            return 1;
        }
        // Master master(port, num, input, output);
        // master.run();
    } else if (mode == "slave") {
        if (port == 0) {
            help();
            return 1;
        }
        // Slave slave(port);
        // slave.run();
    } else {
        help();
        return 1;
    }

    return 0;
}
