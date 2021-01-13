find_package(ZLIB REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(LibEvent REQUIRED)

SET(SOURCE
main.cpp
event/BufferEvent.cpp
event/event.cpp
event/EventCode.cpp
event/EventBase.cpp
event/server.cpp
event/socket.cpp
)
set(HEADERS
noncopyable.hpp
event/event.h
event/BufferEvent.h
event/EventCode.h
event/EventBase.h
event/server.h
event/socket.h
event/SocketException.hpp
)
add_executable(socketmud
${SOURCE} ${HEADERS}
)
source_group("headers" FILES ${HEADERS})
target_link_libraries (socketmud LINK_PUBLIC
${ZLIB_LIBRARIES}
${OPENSSL_SSL_LIBRARY}
${LIBEVENT_LIB}
)
    include_directories( ${ZLIB_INCLUDE_DIRS} 
${OpenSSL_INCLUDE_DIRS}
${LIBEVENT_INCLUDE_DIR}
)
