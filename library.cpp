#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <fstream>

// Callback-функция для обработки полученных данных
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t total_size = size * nmemb;
    output->append(static_cast<char*>(contents), total_size);
    return total_size;
}

nlohmann::json parseJsonStructures(const std::string& jsonString) {

    try {
        nlohmann::json jsonData = nlohmann::json::parse(jsonString);
        return jsonData;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка при разборе JSON-данных: " << e.what() << std::endl;
    }
}

void existencePackages(nlohmann::json jsonSis, nlohmann::json jsonP10, nlohmann::json& resultJson)
{
    for (const auto& currentObjectSis : jsonSis["packages"]) {

        auto itP10 = std::find_if( jsonP10["packages"].begin(),  jsonP10["packages"].end(), [&](const nlohmann::json&  currentP10) {
            return (currentObjectSis["name"] == currentP10["name"]);});

        if (itP10 == jsonP10["packages"].end()) resultJson.push_back(currentObjectSis);
    }
}

bool singleCompareVersion(std::string version1, std::string release1, std::string version2, std::string release2) {
    version1 = version1 + release1;
    version2 = version2 + release2;
    int i = 0, j = 0, j0 = 0;
    int number1 = 0, number2 = 0;
    std::string buffer1 = "", buffer2 = "", buffer = "";

    while (true) {

        //check the end of the string
        if (version1.size() == i && version2.size() == i) { return false; }
        if (version1.size() == i) return false;
        if (version2.size() == i) return true;

        //trying to get a number
        while (static_cast<int>(version1[i + j]) > 47 && static_cast<int>(version1[i + j]) < 58 &&
               version1.size() > i + j) {
            buffer = version1[i + j];
            number1 = number1 * 10 + std::stoi(buffer);
            j++;
        }
        j0 = j;
        j = 0;

        while (static_cast<int>(version2[i + j]) > 47 && static_cast<int>(version2[i + j]) < 58 &&
               version2.size() > i + j) {
            buffer = version2[i + j];
            number2 = number2 * 10 + std::stoi(buffer);
            j++;
        }
        //compare numbers
        if (number1 > number2) return true;
        if (number1 < number2) return false;
        number1 = 0;
        number2 = 0;
        j = 0;

        //if we don't get a number, we get a string
        while (static_cast<int>(version1[i + j]) <= 47 ||
               static_cast<int>(version1[i + j]) >= 58 && version1.size() > i + j) {
            buffer1 += version1[i + j];
            j++;
        }
        j = 0;

        while (static_cast<int>(version2[i + j]) <= 47 ||
               static_cast<int>(version2[i + j]) >= 58 && version2.size() > i + j) {
            buffer2 += version2[i +j];
            j++;
        }
        //compare strings
        if (buffer1 > buffer2) return true;
        if (buffer1 < buffer2) return false;
        buffer1 = "";
        buffer2 = "";

        i = i + std::max(j,j0);
        j = 0;
        j0 = 0;
    }
}

void versionComparison(nlohmann::json jsonSis, nlohmann::json jsonP10, nlohmann::json& resultJson)
{
    for (const auto& currentObjectSis : jsonSis["packages"]) {

        auto itP10 = std::find_if( jsonP10["packages"].begin(),  jsonP10["packages"].end(), [&](const nlohmann::json&  currentP10) {
            return (currentObjectSis["name"] == currentP10["name"]
            && singleCompareVersion(currentObjectSis["version"],currentObjectSis["release"],currentP10["version"],currentP10["release"]));});

        if (itP10 != jsonP10["packages"].end()) resultJson.push_back(currentObjectSis);
    }
}

void printJsonStructure(nlohmann::json& resultJson, const std::string& nameFile) {
    std::ofstream outputFile(nameFile);
    if (outputFile.is_open()) {
        if (resultJson.is_array()) {
            for (const auto& jsonObject : resultJson) {
                // Выводим каждую JSON-структуру с отступами для улучшенной читабельности
                outputFile << jsonObject.dump(4) << std::endl;
            }
        } else {
            // Если в ответе только одна JSON-структура, просто выведем ее на экран
            outputFile << resultJson.dump(4) << std::endl;
        }
        outputFile.close();
    } else {
        std::cerr << "Ошибка: Невозможно открыть файл для записи: " << nameFile << std::endl;
    }
}

std::vector<std::string> findArch(const std::string jsonString, std::vector<std::string>& arch) {
    //парсим строку в json
    nlohmann::json json = parseJsonStructures(jsonString);

    //находим все типы используемых архитектур
    for (const auto& currentObject : json["packages"]) {
        auto it = std::find(arch.begin(), arch.end(), currentObject["arch"]);
        if (it == arch.end()) {
            arch.emplace_back(currentObject["arch"]);
        }
    }
    return arch;
}

std::string performGetRequest(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string response_data;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        // Устанавливаем URL для запроса
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Отключаем проверку SSL-сертификата
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

        // Устанавливаем callback-функцию для обработки полученных данных
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

        // Выполняем запрос
        res = curl_easy_perform(curl);

        // Проверяем наличие ошибок
        if (res != CURLE_OK) {
            std::cerr << "Ошибка при выполнении запроса: " << curl_easy_strerror(res) << std::endl;
        }

        // Освобождаем ресурсы
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return response_data;
}
