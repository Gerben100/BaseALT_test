FROM alt:latest

RUN apt-get update && \
    apt-get install -y \
    rpm \
    cmake \
    nlohmann-json-devel \
    libcurl-devel \
    catch2-devel

COPY BaseALT_test_unitTests-1.0-1.x86_64.rpm /app/BaseALT_test_unitTests-1.0-1.x86_64.rpm

RUN rpm -i /app/BaseALT_test_unitTests-1.0-1.x86_64.rpm

CMD test_test
