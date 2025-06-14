FROM ubuntu:latest

RUN apt -qq update
RUN apt -qqqy install wget gnupg
RUN wget -qO - https://packages.lunarg.com/lunarg-signing-key-pub.asc | apt-key add -
RUN wget -qO /etc/apt/sources.list.d/lunarg-vulkan-1.4.313-noble.list https://packages.lunarg.com/vulkan/1.4.313/lunarg-vulkan-1.4.313-noble.list
RUN apt -qq update
RUN apt -qqqy -o Dpkg::Progress-Fancy="0" -o APT::Color="0" -o Dpkg::Use-Pty="0" install cmake make ninja-build g++
RUN apt -qqqy -o Dpkg::Progress-Fancy="0" -o APT::Color="0" -o Dpkg::Use-Pty="0" install gcc g++
RUN apt -qqqy -o Dpkg::Progress-Fancy="0" -o APT::Color="0" -o Dpkg::Use-Pty="0" install qt6-base-dev libxkbcommon-dev qt6-websockets-dev
RUN apt -qqqy -o Dpkg::Progress-Fancy="0" -o APT::Color="0" -o Dpkg::Use-Pty="0" install vulkan-sdk

COPY . .

RUN cmake --preset debug
RUN cmake --build --parallel $(($(nproc) + 1)) --preset app-debug

FROM scratch
COPY --from=0 build/debug/app .
