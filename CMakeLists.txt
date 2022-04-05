find_package(common REQUIRED)
find_package(dot REQUIRED)
find_package(stduuid REQUIRED)

include(floahVersionString)

set(NAME floah)
set(TYPE module)
set(INCLUDE_DIR "include/floah")
set(SRC_DIR "src")

set(HEADERS
    ${INCLUDE_DIR}/block.h
    ${INCLUDE_DIR}/element.h
    ${INCLUDE_DIR}/layout.h

    ${INCLUDE_DIR}/elements/grid.h
    ${INCLUDE_DIR}/elements/horizontal_flow.h

    ${INCLUDE_DIR}/properties/alignment.h
    ${INCLUDE_DIR}/properties/length.h
    ${INCLUDE_DIR}/properties/margin.h
    ${INCLUDE_DIR}/properties/size.h

    ${INCLUDE_DIR}/utils/bbox.h
    ${INCLUDE_DIR}/utils/floah_error.h
)

set(SOURCES
    ${SRC_DIR}/block.cpp
    ${SRC_DIR}/element.cpp
    ${SRC_DIR}/layout.cpp

    ${SRC_DIR}/elements/grid.cpp
    ${SRC_DIR}/elements/horizontal_flow.cpp

    ${SRC_DIR}/properties/alignment.cpp
    ${SRC_DIR}/properties/length.cpp
    ${SRC_DIR}/properties/margin.cpp
    ${SRC_DIR}/properties/size.cpp

    ${SRC_DIR}/utils/bbox.cpp
    ${SRC_DIR}/utils/floah_error.cpp
)

set(DEPS_PUBLIC
    stduuid::stduuid
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
    DEPS_PUBLIC "${DEPS_PUBLIC}"
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
        FLOAH_VERSION_MAJOR=${FLOAH_VERSION_MAJOR}
        FLOAH_VERSION_MINOR=${FLOAH_VERSION_MINOR}
        FLOAH_VERSION_PATCH=${FLOAH_VERSION_PATCH}
)