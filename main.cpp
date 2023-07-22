#include <iostream>
#include <Windows.h>
#include "library.h"
#include <nlohmann/json.hpp>
#include <vector>
#include <fstream>

using namespace std;

int main() {
    system("chcp 65001");

    //считываем ветки sisyphus и p10
    std::string branch1 = "sisyphus", branch2 = "p10";
    std::string sisyphus_url = "https://rdb.altlinux.org/api/export/branch_binary_packages/" + branch1;
    std::string p10_url = "https://rdb.altlinux.org/api/export/branch_binary_packages/" + branch2;

    std::string sisyphus_response = performGetRequest(sisyphus_url);
    std::string p10_response = performGetRequest(p10_url);

    sisyphus_response = R"({
        "request_args": {"arch": null},
        "length": 186171,
        "packages": [
            {"name": "0ad", "epoch": 1, "version": "0.1.26", "release": "alt0_3_alpha", "arch": "aarch64", "disttag": "sisyphus+319112.500.3.2", "buildtime": 1682252652, "source": "0ad"},
            {"name": "0ad-debuginfo", "epoch": 1, "version": "0.0.26", "release": "alt0_3_alpha", "arch": "aarch64", "disttag": "sisyphus+319112.500.3.2", "buildtime": 1682252652, "source": "0ad"},
            {"name": "389-ds-base", "epoch": 0, "version": "2.2.10", "release": "alt2", "arch": "aarch64", "disttag": "sisyphus+324359.4400.11.1", "buildtime": 1689366562, "source": "389-ds-base"},
            {"name": "389-ds-base-debuginfo", "epoch": 0, "version": "2.2.8", "release": "alt1", "arch": "aarch64", "disttag": "sisyphus+324359.4400.11.1", "buildtime": 1689366562, "source": "389-ds-base"},
            {"name": "389-ds-base-deve", "epoch": 0, "version": "2.2.8", "release": "alt1", "arch": "aarch64", "disttag": "sisyphus+324359.4400.11.1", "buildtime": 1689366562, "source": "389-ds-base"}
        ]
    })";

    p10_response = R"({
        "request_args": {"arch": null},
        "length": 186171,
        "packages": [
            {"name": "0ad", "epoch": 1, "version": "0.0.261", "release": "alt0_3_alpha", "arch": "aarch64", "disttag": "sisyphus+319112.500.3.2", "buildtime": 1682252652, "source": "0ad"},
            {"name": "0ad-debuginfo", "epoch": 1, "version": "0.0.26", "release": "alt0_3_alpha", "arch": "aarch64", "disttag": "sisyphus+319112.500.3.2", "buildtime": 1682252652, "source": "0ad"},
            {"name": "389-ds-base", "epoch": 0, "version": "2.2.8", "release": "alt1", "arch": "aarch64", "disttag": "sisyphus+324359.4400.11.1", "buildtime": 1689366562, "source": "389-ds-base"},
            {"name": "389-ds-base-debuginfo", "epoch": 0, "version": "2.2.8", "release": "alt1", "arch": "aarch64", "disttag": "sisyphus+324359.4400.11.1", "buildtime": 1689366562, "source": "389-ds-base"},
            {"name": "389-ds-base-deve", "epoch": 0, "version": "2.2.7", "release": "alt1", "arch": "aarch64", "disttag": "sisyphus+324359.4400.11.1", "buildtime": 1689366562, "source": "389-ds-base"},
            {"name": "389-ds-base-devel2", "epoch": 0, "version": "2.2.8", "release": "alt1", "arch": "aarch64", "disttag": "sisyphus+324359.4400.11.1", "buildtime": 1689366562, "source": "389-ds-base"}
        ]
    })";

    nlohmann::json resultJson = compareJsonStructures(sisyphus_response, p10_response);






    /*
    for (int i=0;i++;i<10) {
        cout << sisyphus_response[i] << std::endl;
    }

    //Обработка данных для ветки "sisyphus"

    std::cout << "Список бинарных пакетов для ветки \"sisyphus\":" << std::endl;
    std::cout << sisyphus_response << std::endl;

    // Обработка данных для ветки "p10"
    std::cout << "Список бинарных пакетов для ветки \"p10\":" << std::endl;
    std::cout << p10_response << std::endl;
*/
    return 0;
}