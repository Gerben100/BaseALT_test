#include <iostream>
#include <string>
#include <curl/curl.h>

// Callback-функция для обработки полученных данных
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t total_size = size * nmemb;
    output->append(static_cast<char*>(contents), total_size);
    return total_size;
}

// Функция для выполнения GET-запроса и получения данных
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
    std::string url = "https://rdb.altlinux.org/api/export/branch_binary_packages/sisyphus";
    std::string response_data = performGetRequest(url);

    std::cout << "Ответ сервера: " << response_data << std::endl;

    return 0;
}