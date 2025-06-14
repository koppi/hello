FROM stateoftheartio/qt6:6.8-wasm-aqt

WORKDIR /home/user

COPY . .

RUN qt-cmake -B build -G Ninja
RUN cmake --build build -j $(($(nproc) + 1))

FROM scratch
COPY --from=0 [ \
    "/home/user/build/app.js", \
    "/home/user/build/app.html", \
    "/home/user/build/app.wasm", \
    "/home/user/build/qtlogo.svg", \
    "/home/user/build/qtloader.js", \
    "." \
]
