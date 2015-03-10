cmake_minimum_required( VERSION 2.8.5 )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -g")

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

foreach(prog
    WriteHDF5Imtest
    WriteHDF5ImtestByPlane
    WriteHDF5ZeroToOne
    )
   add_executable(${prog} ${prog}.cxx )
   target_link_libraries(${prog} ${ITK_LIBRARIES} )
endforeach(prog)
