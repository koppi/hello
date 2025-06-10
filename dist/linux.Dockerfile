FROM ubuntu:24.04

RUN apt -qq update
RUN apt -qqqy -o Dpkg::Progress-Fancy="0" -o APT::Color="0" -o Dpkg::Use-Pty="0" install cmake make ninja-build g++
RUN apt -qqqy -o Dpkg::Progress-Fancy="0" -o APT::Color="0" -o Dpkg::Use-Pty="0" install gcc g++
RUN apt -qqqy -o Dpkg::Progress-Fancy="0" -o APT::Color="0" -o Dpkg::Use-Pty="0" install qt6-base-dev libxkbcommon-dev

COPY . .

RUN cmake --preset debug
RUN cmake --build --parallel $(($(nproc) + 1)) --preset app-debug

FROM scratch
COPY --from=0 build/debug/app .
