cmake_minimum_required(VERSION 3.20)
project(dot_screen_saver CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})


if(UNIX)
  add_executable(dot_screen_saver)
elseif(WIN32)
  add_executable(dot_screen_saver WIN32)
endif(UNIX)

target_compile_features(dot_screen_saver PRIVATE cxx_std_23)
target_sources(dot_screen_saver
PRIVATE
  ${PROJECT_SOURCE_DIR}/src/main.cpp
  ${PROJECT_SOURCE_DIR}/src/tokenizer.cpp
  ${PROJECT_SOURCE_DIR}/src/parser.cpp
  ${PROJECT_SOURCE_DIR}/src/node.cpp
  ${PROJECT_SOURCE_DIR}/src/runner.cpp
  $<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/resources/Resource.rc>
)

if(UNIX)
  find_package(Siv3D)
  target_link_libraries(dot_screen_saver PUBLIC Siv3D::Siv3D)
endif(UNIX)

if(WIN32)
  target_compile_options(dot_screen_saver PRIVATE /utf-8 /W4 $<IF:$<CONFIG:Release>,/MT,/MTd>)
  file(TO_CMAKE_PATH $ENV{SIV3D_0_6_10} SIV3D)
  target_include_directories(dot_screen_saver PRIVATE ${SIV3D}/include ${SIV3D}/include/ThirdParty)
  target_link_directories(dot_screen_saver PRIVATE ${SIV3D}/lib/Windows)
  target_link_libraries(dot_screen_saver
    PUBLIC
      debug ${SIV3D}/lib/Windows/Siv3D_d.lib                                          optimized ${SIV3D}/lib/Windows/Siv3D.lib
      debug ${SIV3D}/lib/Windows/boost/libboost_filesystem-vc142-mt-sgd-x64-1_74.lib  optimized ${SIV3D}/lib/Windows/boost/libboost_filesystem-vc142-mt-s-x64-1_74.lib
      debug ${SIV3D}/lib/Windows/curl/libcurl-d.lib                                   optimized ${SIV3D}/lib/Windows/curl/libcurl.lib
      debug ${SIV3D}/lib/Windows/freetype/freetyped.lib                               optimized ${SIV3D}/lib/Windows/freetype/freetype.lib
      debug ${SIV3D}/lib/Windows/glew/glew32sd.lib                                    optimized ${SIV3D}/lib/Windows/glew/glew32s.lib
      debug ${SIV3D}/lib/Windows/harfbuzz/harfbuzz_d.lib                              optimized ${SIV3D}/lib/Windows/harfbuzz/harfbuzz.lib
      debug ${SIV3D}/lib/Windows/libgif/libgif_d.lib                                  optimized ${SIV3D}/lib/Windows/libgif/libgif.lib
      debug ${SIV3D}/lib/Windows/libjpeg-turbo/turbojpeg-static_d.lib                 optimized ${SIV3D}/lib/Windows/libjpeg-turbo/turbojpeg-static.lib
      debug ${SIV3D}/lib/Windows/libogg/libogg_d.lib                                  optimized ${SIV3D}/lib/Windows/libogg/libogg.lib
      debug ${SIV3D}/lib/Windows/libpng/libpng16_d.lib                                optimized ${SIV3D}/lib/Windows/libpng/libpng16.lib
      debug ${SIV3D}/lib/Windows/libtiff/tiffd.lib                                    optimized ${SIV3D}/lib/Windows/libtiff/tiff.lib
      debug ${SIV3D}/lib/Windows/libvorbis/libvorbis_static_d.lib                     optimized ${SIV3D}/lib/Windows/libvorbis/libvorbis_static.lib
      debug ${SIV3D}/lib/Windows/libvorbis/libvorbisfile_static_d.lib                 optimized ${SIV3D}/lib/Windows/libvorbis/libvorbisfile_static.lib
      debug ${SIV3D}/lib/Windows/libwebp/libwebp_debug.lib                            optimized ${SIV3D}/lib/Windows/libwebp/libwebp.lib
      debug ${SIV3D}/lib/Windows/Oniguruma/Oniguruma_d.lib                            optimized ${SIV3D}/lib/Windows/Oniguruma/Oniguruma.lib
      debug ${SIV3D}/lib/Windows/opencv/opencv_core451d.lib                           optimized ${SIV3D}/lib/Windows/opencv/opencv_core451.lib
      debug ${SIV3D}/lib/Windows/opencv/opencv_imgcodecs451d.lib                      optimized ${SIV3D}/lib/Windows/opencv/opencv_imgcodecs451.lib
      debug ${SIV3D}/lib/Windows/opencv/opencv_imgproc451d.lib                        optimized ${SIV3D}/lib/Windows/opencv/opencv_imgproc451.lib
      debug ${SIV3D}/lib/Windows/opencv/opencv_objdetect451d.lib                      optimized ${SIV3D}/lib/Windows/opencv/opencv_objdetect451.lib
      debug ${SIV3D}/lib/Windows/opencv/opencv_photo451d.lib                          optimized ${SIV3D}/lib/Windows/opencv/opencv_photo451.lib
      debug ${SIV3D}/lib/Windows/opencv/opencv_videoio451d.lib                        optimized ${SIV3D}/lib/Windows/opencv/opencv_videoio451.lib
      debug ${SIV3D}/lib/Windows/opus/opus_d.lib                                      optimized ${SIV3D}/lib/Windows/opus/opus.lib
      debug ${SIV3D}/lib/Windows/opus/opusfile_d.lib                                  optimized ${SIV3D}/lib/Windows/opus/opusfile.lib
      debug ${SIV3D}/lib/Windows/zlib/zlibd.lib                                       optimized ${SIV3D}/lib/Windows/zlib/zlib.lib
    )

endif(WIN32)
