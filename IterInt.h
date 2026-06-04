int inline ipow(int base, int exp) {
    int result = 1;
    for (int i=0; i < exp; i++) {
        result *= base;
    }
    return result;
}

int inline absolute(int num) {
    return num >= 0 ? num : (-1 * num);
}

int inline extract_digit(int n, int pos) {
    int num = absolute(n);
    for (int i = 0; i < pos; i++) {
        num /= 10;
    }
    return num % 10;
}

struct IterInt {
    private:
        int value;
        int max_index;
    
    public:
    IterInt(int value):value(value) {
        refresh();
    };

    void refresh() {
        int v = value < 0 ? -value : value;
        if (v == 0) {
            max_index = 0;
            return;
        }
        int temp = v;
        int digits = 0;
        while (temp > 0) {
            temp /= 10;
            digits++;
        }
        max_index = digits - 1;
    }

    struct Proxy {
        IterInt* parent;
        int pos;
        Proxy(IterInt* parent, int pos):parent(parent), pos(pos){}; 
        void operator=(int val) {
            if (val < 0 || val >= 10) return;
            bool isNegative = (parent->value) < 0;
            int result = 0;
            for (int i=0; i <= parent->max_index; i++) {
                if (i == pos) result += val * ipow(10, i);
                else result += extract_digit(parent->value, i) * ipow(10, i);
            }
            if (isNegative) result *= -1;
            parent->value = result;
            parent->refresh();
        };

        operator int() const {
            return extract_digit(parent->value, pos);
        }
    };

    Proxy operator[](int pos) {
        int size = max_index + 1;
        int wrapped = ((pos % size) + size) % size; 
        return Proxy(this, max_index - wrapped);
    };

    operator int() const {
        return this->value;
    }

    IterInt& operator+=(const IterInt& other) {
        this->value += other.value;
        refresh();
        return *this;
    }

    IterInt& operator-=(const IterInt& other) {
        this->value -= other.value;
        refresh();
        return *this;
    }

    IterInt& operator *=(const IterInt& other) {
        this->value *= other.value;
        refresh();
        return *this;
    }

    IterInt& operator /=(const IterInt& other) {
        if (other.value != 0) {
            this->value /= other.value;
            refresh();
        }
        return *this;
    }

    friend IterInt operator+(int lhs, const IterInt& rhs) {
        IterInt temp(lhs);
        temp += rhs;
        return temp;
    }

    friend IterInt operator+(const IterInt& lhs, const IterInt& rhs) {
        IterInt temp(lhs.value);
        temp += rhs;
        return temp;
    }

    friend IterInt operator-(int lhs, const IterInt& rhs) {
        IterInt temp(lhs);
        temp -= rhs;
        return temp;
    }

    friend IterInt operator-(const IterInt& lhs, const IterInt& rhs) {
        IterInt temp(lhs.value);
        temp -= rhs;
        return temp;
    }

    friend IterInt operator*(int lhs, const IterInt& rhs) {
        IterInt temp(lhs);
        temp *= rhs;
        return temp;
    }

    friend IterInt operator*(const IterInt& lhs, const IterInt& rhs) {
        IterInt temp(lhs.value);
        temp *= rhs;
        return temp;
    }

    friend IterInt operator/(int lhs, const IterInt& rhs) {
        IterInt temp(lhs);
        temp /= rhs;
        return temp;
    }

    friend IterInt operator/(const IterInt& lhs, const IterInt& rhs) {
        IterInt temp(lhs.value);
        temp /= rhs;
        return temp;
    }
};