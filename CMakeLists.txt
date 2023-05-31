cmake_minimum_required (VERSION 3.8)
project ("ServerP2P")

set (CMAKE_CXX_STANDARD 17)
set (PostgreSQL_ADDITIONAL_VERSIONS "15")
set (BOOST_INCLUDE_DIR "C:/Boost/boost_1_82_0")
set (BOOST_LIBRARY_DIR "C:/Boost/boost_1_82_0/stage/lib")
set (spdlog_DIR "C:/Users/goman/Desktop/Modules/spdlog/build")

find_package(Boost 1.82.0)
find_package(spdlog REQUIRED)
find_package(libpqxx REQUIRED)

include_directories(${BOOST_INCLUDE_DIR} ${spdlog_INCLUDE_DIR} ${libpqxx_INCLUDE_DIR})
add_executable (ServerP2P "main.cpp" 
				"src/Server.hpp" "src/Server.cpp"
				"src/Client.hpp" "src/Client.cpp" 
				"src/RouteManager.hpp" "src/RouteManager.cpp")

target_link_libraries(ServerP2P PRIVATE ${BOOST_LIBRARIES} spdlog::spdlog libpqxx::pqxx)
