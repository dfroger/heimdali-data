cmake_minimum_required( VERSION 2.8.5 )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( WriteHDF5Imtest WriteHDF5Imtest.cxx )
add_executable( WriteHDF5ZeroToOne WriteHDF5ZeroToOne.cxx )

target_link_libraries( WriteHDF5Imtest ${ITK_LIBRARIES} )
target_link_libraries( WriteHDF5ZeroToOne ${ITK_LIBRARIES} )
