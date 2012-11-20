add_library(constraint SHARED constraint.cpp)

add_executable(constraint_test test.cpp)
target_link_libraries(constraint_test
	constraint
)

install(TARGETS constraint DESTINATION lib)
install(FILES constraint.h DESTINATION include)

install(TARGETS constraint_test DESTINATION bin)