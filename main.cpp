#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>


std::vector<long long> get_matrix(std::string f){
    std::vector<long long> r;
    for (int i = 0; i < f.size(); ++i) {
        if(f[i] == '1'){
            r.push_back((1ll << static_cast<long long>(std::log2(f.size()) - 1)) + (i % (f.size()/ 2)));
        } else {
            r.push_back(i % (f.size() / 2));
        }
    }
    return r;
}


long long get_h_ij(long long i, long long j){
    long long x = i & j;
    long long sum = 0;
    while(x != 0){
        if ((x & 1) == 1){
            sum++;
        }
        x >>= 1;
    }
    return sum % 2 == 0 ? 1 : -1;
}


std::vector<long double> deutsch_jozsa(std::string f) {
    std::vector<double> f1;
    std::vector<long long> m0 = get_matrix(f);
    long double coefficient = std::pow(1 / std::sqrt(2), std::log2(f.size()) - 1);
    coefficient *= coefficient;

    for (int i = 0; i < f.size(); ++i) {
        if (i < (f.size() / 2)){
            f1.push_back(1);
        } else {
            f1.push_back(0);
        }
    }
    
    for (int i = 0; i < f1.size(); ++i) {
        if(m0[i] < (f1.size() / 2)){
            f1[i] = 1;
        } else {
            f1[i] = 0;
        }
    }
    
    for (int i = 0; i < f1.size(); ++i) {
        if (i >= (f1.size() / 2)) {
            if (f1[i] != 0) {
                f1[i] *= -1;
            }
        }
    }
    
    for (int i = (f1.size() / 2); i < f1.size(); ++i) {
        if(f1[i] == -1){
            f1[i - (f1.size() / 2)] = -1;
            f1[i] = 0;
        }
    }
    
    int sum = 0;
    std::vector<long double> f1_result;
    for (int i = 0; i < f1.size()/2; ++i) {
        for (int j = 0; j < f1.size()/2; ++j) {
            sum += get_h_ij(i, j) * f1[j];
        }
        f1_result.push_back(sum);
        sum = 0;
    }
    
    for (int i = 0; i < f1.size()/2; ++i) {
        f1_result.push_back(0);
    }
    
    for (int i = 0; i < f1_result.size(); ++i) {
        f1_result[i] *= coefficient;
    }
    
    return f1_result;
}



int main() {
    std::string f;
    std::cin >> f;
    
    int x = f.size();
    for (int i = 0; i < x; ++i) {
        if(f[i] == '1'){
            f.push_back('0');
        } else {
            f.push_back('1');
        }
    }
    
    std::vector<long double> result = deutsch_jozsa(f);
    std::cout << result[0];

    return 0;
}
