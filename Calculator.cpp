#include<iostream> // Standard I/O header
#include<cstdlib>  // Standard exit() function header
#include<iomanip>  // Standard formatting header
#include<stack>    // Standard stack header
#include<gmpxx.h>  // GMP library header for arbitrary precision arithmetic
#include<windows.h> // Windows API header

using namespace std;

stack<mpf_class> numStack; // Stack for numbers
stack<char> opStack;       // Stack for operators

void setColor(unsigned long color);
void showAboutInfo();
void runCalculator();
unsigned long getPriority(char op);
mpf_class compute(char op);
mpf_class modulo(mpf_class x, mpf_class y);
mpf_class power(mpf_class x, unsigned long y);

const mpf_class MAX("1e+768", 2560);
const mpf_class MIN("-1e+768", 2560);
const mpf_class PI("3.1415926535897932384626433832795", 128);

int main() {
    system("cls"); // Clear console window
    showAboutInfo();
    while(true)
        runCalculator();
    return 0;
}

void setColor(unsigned long color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void showAboutInfo() {
    setColor(8); // Set text color to gray
    cout << "Calculator 2.6 Author: HuaJun Liu" << endl;
}

mpf_class modulo(mpf_class x, mpf_class y) {
    mpf_class n = x < 0 ? ceil(x/y) : floor(x/y);
    return x - n * y;
}

mpf_class power(mpf_class x, unsigned long y) {
    mpf_class result = 1;
    while (y > 0) {
        if (y % 2 == 1) result *= x;
        x *= x;
        y /= 2;
    }
    return result;
}

void runCalculator() {
    char ch;
    mpf_class currentNumber;
    cout << "Input: ";
    setColor(7);

    while(cin >> ch) {
        try {
            if (isdigit(ch) || ch == '.') {
                cin.putback(ch);
                if (!(cin >> currentNumber)) throw runtime_error("Invalid number format");
                numStack.push(currentNumber);
                continue;
            }

            switch(ch) {
                case '+': case '-': case '*': case '/': case '%': case '^':
                    while(!opStack.empty() && getPriority(opStack.top()) >= getPriority(ch)) {
                        numStack.push(compute(opStack.top()));
                        opStack.pop();
                    }
                    opStack.push(ch);
                    break;
                case '(':
                    opStack.push(ch);
                    break;
                case ')':
                    while(opStack.top() != '(') {
                        numStack.push(compute(opStack.top()));
                        opStack.pop();
                    }
                    opStack.pop(); // Remove '('
                    break;
                case '\n': case '\r': case '=':
                    while(!opStack.empty()) {
                        numStack.push(compute(opStack.top()));
                        opStack.pop();
                    }
                    if (!numStack.empty()) {
                        mpf_class result = numStack.top(); numStack.pop();
                        if (result > MIN && result < MAX) {
                            cout << "Result: " << fixed << setprecision(4) << result << endl;
                        } else throw runtime_error("Result out of bounds");
                    }
                    return;
                default:
                    throw runtime_error("Unsupported character");
            }
        } catch (const runtime_error& e) {
            setColor(4);
            cerr << "Error: " << e.what() << endl;
            return;
        }
    }
}

unsigned long getPriority(char op) {
    switch(op) {
        case '+': case '-': return 1;
        case '*': case '/': case '%': return 2;
        case '^': return 3;
        default: return 0;
    }
}

mpf_class compute(char op) {
    mpf_class a = numStack.top(); numStack.pop();
    mpf_class b = numStack.top(); numStack.pop();
    switch(op) {
        case '+': return a + b;
        case '-': return b - a;
        case '*': return a * b;
        case '/':
            if(a == 0) throw runtime_error("Division by zero");
            return b / a;
        case '%':
            if(a == 0) throw runtime_error("Division by zero for modulo");
            return modulo(b, a);
        case '^':
            return power(b, static_cast<unsigned long>(a.get_d()));
        default: throw runtime_error("Unknown operator");
    }
}
