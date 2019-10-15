#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include "sortalgoritms.h"
#include "datarepr.h"
#include <chrono>

int main() {
    std::string headline = "        \t200\t\t400\t\t600\t\t800\t\t1000";
    std::string meanline = "  Mean  \t";
    std::vector<std::string> files = {
	    "data0.csv",
	    "data1.csv",
	    "data2.csv",
	    "data3.csv",
	    "data4.csv",
	    "data5.csv",
	    "data6.csv",
	    "data7.csv",
	    "data8.csv",
	    "data9.csv"
    };
    std::vector<Book> books;
    std::chrono::duration<double> elapsed;
    double means[5] = {0, 0, 0, 0, 0};
    std::cout.precision(7);

    std::cout << "Bubble sort" << std::endl;
    std::cout << headline << std::endl;
    for(auto file: files){
        std::cout << file << "\t";
        for(int i = 1; i < 6; i++){
            books = read_csv(file);
            auto start = std::chrono::high_resolution_clock::now();
            bubble_sort(books.begin(), books.begin()+200*i);
            auto end = std::chrono::high_resolution_clock::now();

            elapsed = end - start;
            std::cout << elapsed.count() << "\t";
            means[i-1] += elapsed.count();
            books.clear();
        }
        std::cout << std::endl;
    }

    std::cout << meanline;
    for(int i = 0; i < 10; i++){
        std::cout << means[i]/10 << "\t";
        means[i] = 0;
    }
    std::cout << std::endl;

    std::cout << std::endl << std::endl << "Heapsort" << std::endl;
    std::cout << headline << std::endl;
    for(auto file: files){
        std::cout << file << "\t";
        for(int i = 1; i < 6; i++){
            books = read_csv(file);
            auto start = std::chrono::high_resolution_clock::now();
            heap_sort(books.begin(), books.begin()+200*i);
            auto end = std::chrono::high_resolution_clock::now();

            elapsed = end - start;
            std::cout << elapsed.count() << "\t";
            means[i-1] += elapsed.count();
            books.clear();
        }
        std::cout << std::endl;
    }

    std::cout << meanline;
    for(auto t: means){
        std::cout << t/5 << "\t";
    }
    std::cout << std::endl;
    files.clear();
    return 0;
}
