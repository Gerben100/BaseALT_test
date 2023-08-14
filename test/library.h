#ifndef TEST_TASK_LIBRARY_H
#define TEST_TASK_LIBRARY_H

#include <nlohmann/json.hpp>
#include <vector>
std::string performGetRequest(const std::string& url);
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output);
nlohmann::json parseJsonStructures(const std::string& jsonString);
std::vector<std::string> findArch(const std::string jsonString, std::vector<std::string>& arch);
void existencePackages(nlohmann::json jsonSis, nlohmann::json jsonP10, nlohmann::json& resultJson);
void versionComparison(nlohmann::json jsonSis, nlohmann::json jsonP10, nlohmann::json& resultJson);
void printJsonStructure(nlohmann::json& resultJson, const std::string& nameFile);

#endif //TEST_TASK_LIBRARY_H
