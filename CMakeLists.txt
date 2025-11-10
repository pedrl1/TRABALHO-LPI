cmake_minimum_required(VERSION 3.10)
project(sad_extractor_github C)

# Define o padrão do compilador
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Adiciona o executável
add_executable(${PROJECT_NAME} src/main.c)

# Caminho da biblioteca local
set(LIBXLSXWRITER_PATH "${CMAKE_SOURCE_DIR}/libs/libxlsxwriter")

# Inclui os cabeçalhos (.h)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${LIBXLSXWRITER_PATH}/include
)

# Linka a biblioteca estática (.a)
target_link_libraries(${PROJECT_NAME}
    ${LIBXLSXWRITER_PATH}/libxlsxwriter.a
)

# Se precisar de zlib (algumas funções do xlsxwriter dependem)
find_package(ZLIB REQUIRED)
if (ZLIB_FOUND)
    target_include_directories(${PROJECT_NAME} PRIVATE ${ZLIB_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${ZLIB_LIBRARIES})
endif()

