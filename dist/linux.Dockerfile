FROM ubuntu:latest

RUN apt -qq update
RUN apt -qq -y -o=Dpkg::Use-Pty=0 install qt6-base-dev cmake make gcc g++

COPY . .

RUN cmake -B build
RUN cmake --build build -j $(($(nproc) + 1))

FROM scratch
COPY --from=0 build/app .
