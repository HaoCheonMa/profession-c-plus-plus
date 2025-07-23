# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "D:/---PROJECTS/skillbox-projects/profession-c-plus-plus/30-4-prac/1requests/out/build/x64-Debug/_deps/cpr-src")
  file(MAKE_DIRECTORY "D:/---PROJECTS/skillbox-projects/profession-c-plus-plus/30-4-prac/1requests/out/build/x64-Debug/_deps/cpr-src")
endif()
file(MAKE_DIRECTORY
  "D:/---PROJECTS/skillbox-projects/profession-c-plus-plus/30-4-prac/1requests/out/build/x64-Debug/_deps/cpr-build"
  "D:/---PROJECTS/skillbox-projects/profession-c-plus-plus/30-4-prac/1requests/out/build/x64-Debug/_deps/cpr-subbuild/cpr-populate-prefix"
  "D:/---PROJECTS/skillbox-projects/profession-c-plus-plus/30-4-prac/1requests/out/build/x64-Debug/_deps/cpr-subbuild/cpr-populate-prefix/tmp"
  "D:/---PROJECTS/skillbox-projects/profession-c-plus-plus/30-4-prac/1requests/out/build/x64-Debug/_deps/cpr-subbuild/cpr-populate-prefix/src/cpr-populate-stamp"
  "D:/---PROJECTS/skillbox-projects/profession-c-plus-plus/30-4-prac/1requests/out/build/x64-Debug/_deps/cpr-subbuild/cpr-populate-prefix/src"
  "D:/---PROJECTS/skillbox-projects/profession-c-plus-plus/30-4-prac/1requests/out/build/x64-Debug/_deps/cpr-subbuild/cpr-populate-prefix/src/cpr-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/---PROJECTS/skillbox-projects/profession-c-plus-plus/30-4-prac/1requests/out/build/x64-Debug/_deps/cpr-subbuild/cpr-populate-prefix/src/cpr-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/---PROJECTS/skillbox-projects/profession-c-plus-plus/30-4-prac/1requests/out/build/x64-Debug/_deps/cpr-subbuild/cpr-populate-prefix/src/cpr-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
