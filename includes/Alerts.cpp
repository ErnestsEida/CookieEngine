#pragma once

#include <cstdlib>
#include <iostream>

using namespace std;

class Alerts {
public:
    static void ErrorMessage(string message) { cout << "\033[1;31m" << "[ERROR] " << message << "\033[0m" << endl; }
    static void SuccessMessage(string message) { cout << "\033[1;32m" << "[SUCCESS] " << message << "\033[0m" << endl; }
    static void WarningMessage(string message) { cout << "\033[1;33m" << "[WARNING] " << message << "\033[0m" << endl; }
};