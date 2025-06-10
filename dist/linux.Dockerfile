FROM ubuntu:latest

RUN apt -qq update
RUN apt -qqqy -o Dpkg::Progress-Fancy="0" -o APT::Color="0" -o Dpkg::Use-Pty="0" install cmake make ninja-build g++
RUN apt -qqqy -o Dpkg::Progress-Fancy="0" -o APT::Color="0" -o Dpkg::Use-Pty="0" install gcc g++
RUN apt -qqqy -o Dpkg::Progress-Fancy="0" -o APT::Color="0" -o Dpkg::Use-Pty="0" install qt6-base-dev

COPY . .

RUN cmake --preset debug
RUN cmake --build --preset app-debug -j $(($(nproc) + 1))

FROM scratch
COPY --from=0 build/debug/app .
