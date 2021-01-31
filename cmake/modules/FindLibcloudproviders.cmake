# FindLibcloudproviders.cmake

include(FindPackageHandleStandardArgs)

find_path(Libcloudproviders_INCLUDE_DIR
    NAMES cloudprovidersproviderexporter.h cloudprovidersaccountexporter.h
    PATH_SUFFIXES cloudproviders
)
find_library(Libcloudproviders_LIBRARY
    NAMES
        libcloudproviders
        cloudproviders
    HINTS
       /usr/lib
       /usr/lib/${CMAKE_ARCH_TRIPLET}
       /usr/local/lib
       /opt/local/lib
       ${CMAKE_LIBRARY_PATH}
       ${CMAKE_INSTALL_PREFIX}/lib
)

find_package_handle_standard_args(Libcloudproviders
  DEFAULT_MSG
  Libcloudproviders_INCLUDE_DIR
  Libcloudproviders_LIBRARY
  )

if (Libcloudproviders_FOUND)
  set(Libcloudproviders_INCLUDE_DIRS ${Libcloudproviders_INCLUDE_DIR})
  set(Libcloudproviders_LIBRARIES ${Libcloudproviders_LIBRARY})

  mark_as_advanced(Libcloudproviders_INCLUDE_DIR Libcloudproviders_LIBRARY)
endif()
