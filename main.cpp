#include <iostream>
#include <Windows.h>
#include "library.h"
using namespace std;

int main() {
    system("chcp 65001");

    std::string sisyphus_url = "https://rdb.altlinux.org/api/export/branch_binary_packages/sisyphus";
    std::string p10_url = "https://rdb.altlinux.org/api/export/branch_binary_packages/p10";

    std::string sisyphus_response = performGetRequest(sisyphus_url);
    std::string p10_response = performGetRequest(p10_url);

    // Обработка данных для ветки "sisyphus"
    std::cout << "Список бинарных пакетов для ветки \"sisyphus\":" << std::endl;
    std::cout << sisyphus_response << std::endl;

    // Обработка данных для ветки "p10"
    std::cout << "Список бинарных пакетов для ветки \"p10\":" << std::endl;
    std::cout << p10_response << std::endl;

    return 0;
}