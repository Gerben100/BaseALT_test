#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include "library.h"

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

nlohmann::json compareJsonStructures(const std::string& sisyphus_response, const std::string& p10_response)
{
    //парсим строки в json
    nlohmann::json jsonSis = parseJsonStructures(sisyphus_response);
    nlohmann::json jsonP10 = parseJsonStructures(p10_response);
    nlohmann::json resultJson;

    //получаем результат по первому критерию
    existencePackages( jsonSis, jsonP10, resultJson);
    //получаем результат по первому критерию
    existencePackages( jsonP10, jsonSis, resultJson);
    //получаем результат по третьему критерию
    versionComparison( jsonSis, jsonP10, resultJson);

    //выводим результат
    printJsonStructure(resultJson);
    return resultJson;
}

void existencePackages(nlohmann::json jsonSis, nlohmann::json jsonP10, nlohmann::json& resultJson)
{
    for (const auto& currentObjectSis : jsonSis["packages"]) {

        auto itP10 = std::find_if( jsonP10["packages"].begin(),  jsonP10["packages"].end(), [&](const nlohmann::json&  currentP10) {
            return (currentObjectSis["name"] == currentP10["name"]);});

        if (itP10 == jsonP10["packages"].end()) resultJson.push_back(currentObjectSis);
    }
}

void versionComparison(nlohmann::json jsonSis, nlohmann::json jsonP10, nlohmann::json& resultJson)
{
    for (const auto& currentObjectSis : jsonSis["packages"]) {

        auto itP10 = std::find_if( jsonP10["packages"].begin(),  jsonP10["packages"].end(), [&](const nlohmann::json&  currentP10) {
            return (currentObjectSis["name"] == currentP10["name"] && currentObjectSis["release"] == currentP10["release"]
                    && currentObjectSis["version"] > currentP10["version"]);});

        if (itP10 != jsonP10["packages"].end()) resultJson.push_back(currentObjectSis);
    }
}

void printJsonStructure(nlohmann::json& resultJson) {
    if (resultJson.is_array()) {
        for (const auto &jsonObject : resultJson) {
            // Выводим каждую JSON-структуру с отступами для улучшенной читабельности
            std::cout << jsonObject.dump(4) << std::endl;
        }
    } else {
        // Если в ответе только одна JSON-структура, просто выведем ее на экран
        std::cout << resultJson.dump(4) << std::endl;
    }
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

int main() {
    std::string url = "https://rdb.altlinux.org/api/export/branch_binary_packages/";
    std::string response_data = performGetRequest(url);

    std::cout << "Ответ сервера: " << response_data << std::endl;

    return 0;
}