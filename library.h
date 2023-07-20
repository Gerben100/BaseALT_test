#ifndef TEST_TASK_LIBRARY_H
#define TEST_TASK_LIBRARY_H

std::string performGetRequest(const std::string& url);
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output);

#endif //TEST_TASK_LIBRARY_H
