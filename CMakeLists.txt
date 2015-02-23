cmake_minimum_required( VERSION 2.8.5 )

project( WriteHDF5Image )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( WriteHDF5Image WriteHDF5Image.cxx )
target_link_libraries( WriteHDF5Image ${ITK_LIBRARIES} )
