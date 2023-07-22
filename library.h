#ifndef TEST_TASK_LIBRARY_H
#define TEST_TASK_LIBRARY_H

#include <vector>
#include <nlohmann/json.hpp>

std::string performGetRequest(const std::string& url);
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output);
nlohmann::json parseJsonStructures(const std::string& jsonString);
nlohmann::json compareJsonStructures(const std::string& sisyphus_response, const std::string& p10_response);
void existencePackages(nlohmann::json jsonSis, nlohmann::json jsonP10, nlohmann::json& resultJson);
void versionComparison(nlohmann::json jsonSis, nlohmann::json jsonP10, nlohmann::json& resultJson);
void printJsonStructure(nlohmann::json& resultJson);

#endif //TEST_TASK_LIBRARY_H
