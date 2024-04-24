add_executable(star star.c)
add_executable(alarm alarm.c)
add_executable(sum5 sum5.c)
add_executable(signal_sum5 signal_sum5.c)
add_executable(mycat mycat.c)
add_executable(slowcat slowcat.c)
add_executable(slow2 slow2.c)
add_executable(block block.c)
add_executable(susp susp.c)
add_executable(mdaemon mydaemon.c)

add_subdirectory(TBF)
add_subdirectory(TBF_SIG)

