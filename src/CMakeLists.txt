find_package(ZLIB REQUIRED)
find_package(OpenSSL REQUIRED)
SET(SOURCE
main.cpp
server.cpp
socket.cpp
)
set(HEADERS
server.h
socket.h
)
add_executable(socketmud
${SOURCE} ${HEADERS}
)
source_group("headers" FILES ${HEADERS})
target_link_libraries (socketmud LINK_PUBLIC
${ZLIB_LIBRARIES}
${OPENSSL_SSL_LIBRARY}
)
    include_directories( ${ZLIB_INCLUDE_DIRS} 
${OpenSSL_INCLUDE_DIRS}
)
