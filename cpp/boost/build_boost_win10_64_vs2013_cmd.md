# win10 x64 编译安装 boost1.6.2
[参考](http://www.boost.org/doc/libs/1_62_0/more/getting_started/windows.html)

##1

- 必需用vs的工具
```
D:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\Tools\Shortcuts
```
- 我使用了x64的工具，不知道兼容的具体意思

VS2013 x64 兼容工具命令提示

##2 boostrap.bat

```
D:\zhangbin\BOOST\boost_1_62_0>bootstrap.bat
Building Boost.Build engine

Bootstrapping is done. To build, run:

    .\b2

To adjust configuration, edit 'project-config.jam'.
Further information:

    - Command line help:
    .\b2 --help

    - Getting started guide:
    http://boost.org/more/getting_started/windows.html

    - Boost.Build documentation:
    http://www.boost.org/build/doc/html/index.html

D:\zhangbin\BOOST\boost_1_62_0>
```
看起来可以直接b2，但是要学习下怎么配置命令


##3 

参考 [VS2015编译boost1.62](http://www.cnblogs.com/oloroso/p/6050596.html)

```
#编译
b2.exe --prefix=D:\zhangbin\BOOST\boost162_Out_X64 --build-type=complete --build-dir=build_tmp address-model=64 stage
#安装
b2.exe --prefix=D:\zhangbin\BOOST\boost162_Out_X64 --build-type=complete --build-dir=build_tmp address-model=64 install
```


###3.1 编译
- 即使我指定了使用64位的模式，编译出来的还是32位x86的？这是因为我使用了x64兼容命令行工具的原因？？？
- 即使我没有使用toolset=msvc-14.0 ，但默认使用的是msvc_14 ,这是我电脑的vs2015吧，生成的库也是vs2015才能用的了，囧啊。
- 确实是以address-model-64来输出文件的

```


D:\zhangbin\BOOST\boost_1_62_0>b2.exe --prefix=D:\zhangbin\BOOST\boost162_Out_X64 --build-type=complete --build-dir=build_tmp address-model=64 stage
...found 1 target...
...updating 1 target...
msvc.write-setup-script C:\Users\zhangbin\AppData\Local\Temp\b2_msvc_14.0_vcvarsall_x86.cmd
...updated 1 target...
...found 1 target...
...updating 1 target...
msvc.write-setup-script C:\Users\zhangbin\AppData\Local\Temp\b2_msvc_14.0_vcvarsall_amd64.cmd
...updated 1 target...
...found 1 target...
...updating 1 target...
msvc.write-setup-script C:\Users\zhangbin\AppData\Local\Temp\b2_msvc_14.0_vcvarsall_x86_arm.cmd
...updated 1 target...
Performing configuration checks

    - 32-bit                   : yes
    - arm                      : no
    - mips1                    : no
    - power                    : no
    - sparc                    : no
    - x86                      : yes
    - symlinks supported       : yes
    - C++11 mutex              : yes
    - Boost.Config Feature Check: cxx11_auto_declarations : yes
    - Boost.Config Feature Check: cxx11_constexpr : yes
    - Boost.Config Feature Check: cxx11_defaulted_functions : yes
    - Boost.Config Feature Check: cxx11_final : yes
    - Boost.Config Feature Check: cxx11_hdr_tuple : yes
    - Boost.Config Feature Check: cxx11_lambdas : yes
    - Boost.Config Feature Check: cxx11_noexcept : yes
    - Boost.Config Feature Check: cxx11_nullptr : yes
    - Boost.Config Feature Check: cxx11_rvalue_references : yes
    - Boost.Config Feature Check: cxx11_template_aliases : yes
    - Boost.Config Feature Check: cxx11_thread_local : yes
    - Boost.Config Feature Check: cxx11_variadic_templates : yes
    - has_icu builds           : no
warning: Graph library does not contain MPI-based parallel components.
note: to enable them, add "using mpi ;" to your user-config.jam
                                                             - zlib                     : no
    - bzip2                    : no
    - iconv (libc)             : no
    - iconv (separate)         : no
    - icu                      : no
    - icu (lib64)              : no
    - native-atomic-int32-supported : yes
    - message-compiler         : yes
    - pthread-supports-robust-mutexes : no
    - compiler-supports-visibility : no
    - compiler-supports-ssse3  : yes
    - compiler-supports-avx2   : yes
    - gcc visibility           : no
    - long double support      : yes
warning: skipping optional Message Passing Interface (MPI) library.
note: to enable MPI support, add "using mpi ;" to user-config.jam.
note: to suppress this message, pass "--without-mpi" to bjam.
note: otherwise, you can safely ignore this message.
    - zlib                     : no  (cached)
    - bzip2                    : no  (cached)
    - zlib                     : no
    - bzip2                    : no
    - zlib                     : no  (cached)
    - bzip2                    : no  (cached)
    - zlib                     : no  (cached)
    - bzip2                    : no  (cached)
    - zlib                     : no  (cached)
    - bzip2                    : no  (cached)
    - zlib                     : no  (cached)
    - bzip2                    : no  (cached)
warning: Skipping Boost.Locale library with threading=single.
warning: Skipping Boost.Thread library with threading=single.
warning: Skipping Boost.Wave library with threading=single.
    - zlib                     : no  (cached)
    - bzip2                    : no  (cached)

Component configuration:

    - atomic                   : building
    - chrono                   : building
    - container                : building
    - context                  : building
    - coroutine                : building
    - coroutine2               : building
    - date_time                : building
    - exception                : building
    - fiber                    : building
    - filesystem               : building
    - graph                    : building
    - graph_parallel           : building
    - iostreams                : building
    - locale                   : building
    - log                      : building
    - math                     : building
    - metaparse                : building
    - mpi                      : building
    - program_options          : building
    - python                   : building
    - random                   : building
    - regex                    : building
    - serialization            : building
    - signals                  : building
    - system                   : building
    - test                     : building
    - thread                   : building
    - timer                    : building
    - type_erasure             : building
    - wave                     : building

...patience...
...patience...
...patience...
...patience...
...patience...
...found 39251 targets...
...updating 4283 targets...
common.mkdir stage
common.mkdir stage\lib
common.mkdir build_tmp\boost\bin.v2\libs\thread
common.mkdir build_tmp\boost\bin.v2\libs\thread\build
common.mkdir build_tmp\boost\bin.v2\libs\thread\build\msvc-14.0
common.mkdir build_tmp\boost\bin.v2\libs\thread\build\msvc-14.0\release
common.mkdir build_tmp\boost\bin.v2\libs\thread\build\msvc-14.0\release\address-model-64
common.mkdir build_tmp\boost\bin.v2\libs\thread\build\msvc-14.0\release\address-model-64\threading-multi
common.mkdir build_tmp\boost\bin.v2\libs\thread\build\msvc-14.0\release\address-model-64\threading-multi\win32
compile-c-c++ build_tmp\boost\bin.v2\libs\thread\build\msvc-14.0\release\address-model-64\threading-multi\win32\thread.obj
thread.cpp
compile-c-c++ build_tmp\boost\bin.v2\libs\thread\build\msvc-14.0\release\address-model-64\threading-multi\win32\tss_dll.obj
tss_dll.cpp
compile-c-c++ build_tmp\boost\bin.v2\libs\thread\build\msvc-14.0\release\address-model-64\threading-multi\win32\tss_pe.obj
tss_pe.cpp
compile-c-c++ build_tmp\boost\bin.v2\libs\thread\build\msvc-14.0\release\address-model-64\threading-multi\future.obj
future.cpp
common.mkdir build_tmp\boost\bin.v2\libs\system
common.mkdir build_tmp\boost\bin.v2\libs\system\build
common.mkdir build_tmp\boost\bin.v2\libs\system\build\msvc-14.0
common.mkdir build_tmp\boost\bin.v2\libs\system\build\msvc-14.0\release
common.mkdir build_tmp\boost\bin.v2\libs\system\build\msvc-14.0\release\address-model-64
common.mkdir build_tmp\boost\bin.v2\libs\system\build\msvc-14.0\release\address-model-64\threading-multi
compile-c-c++ build_tmp\boost\bin.v2\libs\system\build\msvc-14.0\release\address-model-64\threading-multi\error_code.obj
error_code.cpp
msvc.link.dll build_tmp\boost\bin.v2\libs\system\build\msvc-14.0\release\address-model-64\threading-multi\boost_system-vc140-mt-1_62.dll
  正在创建库 build_tmp\boost\bin.v2\libs\system\build\msvc-14.0\release\address-model-64\threading-multi\boost_system-vc140-mt-1_62.lib 和对象 build_tmp\boost\bin.v2\libs\system\build\msvc-14.0\release\address-model-64\threading-multi\boost_system-vc140-mt-1_62.exp
msvc.manifest.dll build_tmp\boost\bin.v2\libs\system\build\msvc-14.0\release\address-model-64\threading-multi\boost_system-vc140-mt-1_62.dll
common.mkdir build_tmp\boost\bin.v2\libs\chrono
common.mkdir build_tmp\boost\bin.v2\libs\chrono\build
common.mkdir build_tmp\boost\bin.v2\libs\chrono\build\msvc-14.0
common.mkdir build_tmp\boost\bin.v2\libs\chrono\build\msvc-14.0\release
common.mkdir build_tmp\boost\bin.v2\libs\chrono\build\msvc-14.0\release\address-model-64
common.mkdir build_tmp\boost\bin.v2\libs\chrono\build\msvc-14.0\release\address-model-64\threading-multi
compile-c-c++ build_tmp\boost\bin.v2\libs\chrono\build\msvc-14.0\release\address-model-64\threading-multi\chrono.obj
chrono.cpp

```



###3.2 安装


```

D:\zhangbin\BOOST\boost_1_62_0>b2.exe --prefix=D:\zhangbin\BOOST\boost162_Out_X64 --build-type=complete --build-dir=build_tmp address-model=64 install
Performing configuration checks

    - 32-bit                   : yes (cached)
    - arm                      : no  (cached)
    - mips1                    : no  (cached)
    - power                    : no  (cached)
    - sparc                    : no  (cached)
    - x86                      : yes (cached)
    - symlinks supported       : yes (cached)
    - C++11 mutex              : yes (cached)
    - Boost.Config Feature Check: cxx11_auto_declarations : yes (cached)
    - Boost.Config Feature Check: cxx11_constexpr : yes (cached)
    - Boost.Config Feature Check: cxx11_defaulted_functions : yes (cached)
    - Boost.Config Feature Check: cxx11_final : yes (cached)
    - Boost.Config Feature Check: cxx11_hdr_tuple : yes (cached)
    - Boost.Config Feature Check: cxx11_lambdas : yes (cached)
    - Boost.Config Feature Check: cxx11_noexcept : yes (cached)
    - Boost.Config Feature Check: cxx11_nullptr : yes (cached)
    - Boost.Config Feature Check: cxx11_rvalue_references : yes (cached)
    - Boost.Config Feature Check: cxx11_template_aliases : yes (cached)
    - Boost.Config Feature Check: cxx11_thread_local : yes (cached)
    - Boost.Config Feature Check: cxx11_variadic_templates : yes (cached)
    - has_icu builds           : no  (cached)
warning: Graph library does not contain MPI-based parallel components.
note: to enable them, add "using mpi ;" to your user-config.jam
    - zlib                     : no  (cached)
    - bzip2                    : no  (cached)
    - iconv (libc)             : no  (cached)
    - iconv (separate)         : no  (cached)
    - icu                      : no  (cached)
    - icu (lib64)              : no  (cached)
    - native-atomic-int32-supported : yes (cached)
    - message-compiler         : yes (cached)
    - pthread-supports-robust-mutexes : no  (cached)
    - compiler-supports-visibility : no  (cached)
    - compiler-supports-ssse3  : yes (cached)
    - compiler-supports-avx2   : yes (cached)
    - gcc visibility           : no  (cached)
    - long double support      : yes (cached)
warning: skipping optional Message Passing Interface (MPI) library.
note: to enable MPI support, add "using mpi ;" to user-config.jam.
note: to suppress this message, pass "--without-mpi" to bjam.
note: otherwise, you can safely ignore this message.
    - zlib                     : no  (cached)
    - bzip2                    : no  (cached)
    - zlib                     : no  (cached)
    - bzip2                    : no  (cached)
```


####3.3 时间真长