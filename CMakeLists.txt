find_package(common REQUIRED)
find_package(dot REQUIRED)

include(floahVersionString)

set(NAME floah)
set(TYPE module)
set(INCLUDE_DIR "include/floah")
set(SRC_DIR "src")

set(HEADERS
    ${INCLUDE_DIR}/utils/floah_error.h
)

set(SOURCES
    ${SRC_DIR}/utils/floah_error.cpp
)

set(DEPS_PRIVATE
    common::common
    dot::dot
)

make_target(
    NAME ${NAME}
    TYPE ${TYPE}
    VERSION ${FLOAH_VERSION}
    WARNINGS WERROR
    HEADERS "${HEADERS}"
    SOURCES "${SOURCES}"
    DEPS_PRIVATE "${DEPS_PRIVATE}"
)

install_target(
    NAME ${NAME}
    TYPE ${TYPE}
    VERSION ${FLOAH_VERSION}
    HEADERS "${HEADERS}"
)

target_compile_definitions(
    ${NAME}
    PRIVATE
        LOGANDLOAD_VERSION_MAJOR=${FLOAH_VERSION_MAJOR}
        LOGANDLOAD_VERSION_MINOR=${FLOAH_VERSION_MINOR}
        LOGANDLOAD_VERSION_PATCH=${FLOAH_VERSION_PATCH}
)