#include <iostream>
#include "library.h"
#include <thread>

void compareJsonStructures(std::string sisyphus, std::string p10, std::string arch, std::vector<nlohmann::json>& resultJson, int i)
{
    //делаем get запрос к API
    std::string sisyphus_response = performGetRequest(sisyphus);
    std::string p10_response = performGetRequest(p10);
    //парсим строки в json
    nlohmann::json jsonSis = parseJsonStructures(sisyphus_response);
    nlohmann::json jsonP10 = parseJsonStructures(p10_response);

    //получаем результат по первому критерию
    std::cout<<"Let's compare by the first criterion: "<<arch<<std::endl;
    existencePackages( jsonSis, jsonP10, resultJson[i]);
    //получаем результат по второму критерию
    std::cout<<"Let's compare by the second criterion: "<<arch<<std::endl;
    existencePackages( jsonP10, jsonSis, resultJson[i]);
    //получаем результат по третьему критерию
    std::cout<<"Let's compare by the third criterion: "<<arch<<std::endl;
    versionComparison( jsonSis, jsonP10, resultJson[i]);

    // Создаем json файлы и записываем в них результаты
    std::string out = "Outputs";

    if (arch != "null") {
        std::string command = "mkdir -p " + out + "/" + arch;
        std::system(command.c_str());

        std::string currentFile = out + "/" + arch + "/" + arch + ".json";
        printJsonStructure(resultJson[i], currentFile);
    }

}

using namespace std;

int main() {
    //system("chcp 65001");

    //считываем ветки sisyphus и p10
    std::string branch1 = "sisyphus", branch2 = "p10", arch = "aarch64";
    std::cout<<"Enter branch names"<<std::endl;
    std::cin>>branch1;
    std::cin>>branch2;
    std::string sisyphus_url = "https://rdb.altlinux.org/api/export/branch_binary_packages/" + branch1;
    std::string p10_url = "https://rdb.altlinux.org/api/export/branch_binary_packages/" + branch2;

    std::string sisyphus_response = performGetRequest(sisyphus_url);
    std::string p10_response = performGetRequest(p10_url);

    std::vector<std::string> arch0,arch2,arch1;
    arch1 = findArch(sisyphus_response, arch1);
    arch2 = findArch(p10_response, arch2);
    arch0.reserve(arch1.size() + arch2.size());
    std::set_union(arch1.begin(), arch1.end(), arch2.begin(), arch2.end(), std::back_inserter(arch0));

    std::vector<std::thread> threads;

    // Создаем вектор для хранения результата, чтобы не записывать результат в потоках
    std::vector<nlohmann::json> result(arch0.size());

    // Используем функцию system для создания папки
    std::string out = "Outputs";
    std::string command = "mkdir -p " + out;
    std::system(command.c_str());

    for (int i = 0; i < arch0.size(); i++)
    {
        if (arch0[i] != "null") {
            std::string sisyphus_url = "https://rdb.altlinux.org/api/export/branch_binary_packages/" + branch1 + "?arch=" + arch0[i];
            std::string p10_url = "https://rdb.altlinux.org/api/export/branch_binary_packages/" + branch2 + "?arch=" + arch0[i];
            std::cout<<"Processing the: "<<arch0[i]<<std::endl;
            threads.emplace_back(compareJsonStructures, sisyphus_url, p10_url, arch0[i], std::ref(result),i);
        }
    }
    for (auto& thread : threads)
    {
        thread.join();
    }

    return 0;
}
