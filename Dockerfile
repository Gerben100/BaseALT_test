FROM alt:latest

RUN apt-get update && \
    apt-get install -y \
    rpm \
    cmake \
    nlohmann-json-devel \
    libcurl-devel

COPY BaseALT_test-1.0-6.x86_64.rpm /app/BaseALT_test-1.0-6.x86_64.rpm

RUN rpm -i /app/BaseALT_test-1.0-6.x86_64.rpm

CMD test_task_main
