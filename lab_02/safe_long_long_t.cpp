#include <iostream>

class safe_long_long_t {

private:
    long long value;

public:
    safe_long_long_t(long long x) {
        value = x;
    }

    long long get() {
        return value;
    }

    safe_long_long_t(safe_long_long_t const& temp) {
        value = temp.value;
    }


    void operator=(const safe_long_long_t& param0) {
        value = param0.value;
    }

    safe_long_long_t operator++() {
        return safe_long_long_t(++value);
    }

    safe_long_long_t operator++(int) {
        return safe_long_long_t(value++);
    }

    safe_long_long_t operator--() {
        return safe_long_long_t(--value);
    }

    safe_long_long_t operator--(int) {
        return safe_long_long_t(value--);
    }

    void operator+=(const safe_long_long_t& param0) {
        value += param0.value;
    }

    void operator-=(const safe_long_long_t& param0) {
        value -= param0.value;
    }

    void operator*=(safe_long_long_t& param0) {
        value *= param0.value;
    }

    void operator/=(const safe_long_long_t& param0) {
        value /= param0.value;
    }

    void operator%=(const safe_long_long_t& param0) {
        value %= param0.value;
    }

    friend std::ostream& operator<<(std::ostream& out, const safe_long_long_t& param0);

    safe_long_long_t operator+(const safe_long_long_t& param0, const safe_long_long_t& param1) {
        safe_long_long_t current = param0;
        current += param1;
        return current;
    }

    safe_long_long_t operator-(const safe_long_long_t& param0, const safe_long_long_t& param1) {
        safe_long_long_t current = param0;
        current -= param1;
        return current;
    }

    safe_long_long_t operator*(const safe_long_long_t& param0, safe_long_long_t param1) {
        safe_long_long_t current = param0;
        current *= param1;
        return current;
    }

    safe_long_long_t operator/(const safe_long_long_t& param0, const safe_long_long_t& param1) {
        safe_long_long_t current = param0;
        current /= param1;
        return current;
    }

    safe_long_long_t operator%(safe_long_long_t& param0, safe_long_long_t& param1) {
        safe_long_long_t current = param0;
        current %= param1;
        return current;
    }

    bool operator==(safe_long_long_t param0, safe_long_long_t param1) {
        return param0.get() == param1.get();
    }

    bool operator!=(const safe_long_long_t& param0, const safe_long_long_t& param1) {
        return !(param0 == param1);
    }

    bool operator<(safe_long_long_t param0, safe_long_long_t param1) {
        return param0.get() < param1.get();
    }

    bool operator>(safe_long_long_t param0, safe_long_long_t param1) {
        return param0.get() > param1.get();
    }

    bool operator<=(safe_long_long_t param0, safe_long_long_t param1) {
        return param0.get() <= param1.get();
    }

    bool operator>=(safe_long_long_t param0, safe_long_long_t param1) {
        return param0.get() >= param1.get();
    }

    std::ostream& operator<<(std::ostream& outs, const safe_long_long_t& param0) {
        return outs << param0.value;
    }


    std::istream& operator>>(std::istream& ins, const safe_long_long_t& param0) {
        ins >> param0;
        return ins;
    }
};




int main()
{
    safe_long_long_t a(10);
    safe_long_long_t b(20);
    safe_long_long_t c(10);

    if (a < b) {
        std::cout << a + b << std::endl;
    }
    
    if (a == c) {
        std::cout << a - b << std::endl;
    }
    
    std::cout << a * b << std::endl;
    std::cout << a / b << std::endl;

    std::cout << --a << std::endl;
    std::cout << a++ << std::endl;

    return 0;
}