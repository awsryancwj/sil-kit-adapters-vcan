# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/ubuntu/sil-kit-adapters-vcan/qnxBuild/_deps/silkit-src"
  "/home/ubuntu/sil-kit-adapters-vcan/qnxBuild/_deps/silkit-build"
  "/home/ubuntu/sil-kit-adapters-vcan/qnxBuild/_deps/silkit-subbuild/silkit-populate-prefix"
  "/home/ubuntu/sil-kit-adapters-vcan/qnxBuild/_deps/silkit-subbuild/silkit-populate-prefix/tmp"
  "/home/ubuntu/sil-kit-adapters-vcan/qnxBuild/_deps/silkit-subbuild/silkit-populate-prefix/src/silkit-populate-stamp"
  "/home/ubuntu/sil-kit-adapters-vcan/Downloads"
  "/home/ubuntu/sil-kit-adapters-vcan/qnxBuild/_deps/silkit-subbuild/silkit-populate-prefix/src/silkit-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/ubuntu/sil-kit-adapters-vcan/qnxBuild/_deps/silkit-subbuild/silkit-populate-prefix/src/silkit-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/ubuntu/sil-kit-adapters-vcan/qnxBuild/_deps/silkit-subbuild/silkit-populate-prefix/src/silkit-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
