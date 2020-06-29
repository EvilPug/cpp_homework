#include <iostream>

class safe_c_array_t {

private:

    int size;
    int* arr;

public:

    explicit safe_c_array_t(int n) {
        size = n;
        arr = new int[size];
    }

    int& operator[](int k) {
        return arr[k];
    }

    ~safe_c_array_t() {
        delete[]arr;
    }

    safe_c_array_t& operator=(const safe_c_array_t& arr2) {
        if (this != &arr2) {
            delete[] arr;
            size = arr2.size;
            arr = new int[size];
            for (int i = 0; i < size; i++) {
                arr[i] = arr2.arr[i];
            }
        }
        return *this;
    }

    safe_c_array_t(const safe_c_array_t& origin) {

        size = origin.size;
        arr = new int[size];

        for (int i = 0; i < size; i++) {
            arr[i] = origin.arr[i];
        }
    }

    void fill_random() {
        

        for (int i = 0; i < size; i++) {
            arr[i] = rand();
        }

    }

    int length() {
        return sizeof(arr);
    }

};

int main() {


    safe_c_array_t rand_nums = safe_c_array_t(4);

    rand_nums.fill_random();

    safe_c_array_t rand_nums_copy = safe_c_array_t(rand_nums);

    for (int i = 0; i < rand_nums.length(); i++)
    {
        std::cout << rand_nums[i] << ' ' << rand_nums_copy[i] << std::endl;
    }

    return 0;
}