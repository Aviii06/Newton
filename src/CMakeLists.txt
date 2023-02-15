set(SOURCES
        Object.cpp
        PhysicsWorld.cpp
        )

set(HEADERS
        common/Types.h
        Object.h
        Newton.h
        PhysicsWorld.h
        )

add_library(Newton SHARED ${SOURCES} ${HEADERS})

target_include_directories(Newton PUBLIC
        ${PROJECT_SOURCE_DIR}/src
        )
