#不要手机查找64位的库

##1 
[http://www.jianshu.com/p/7fa8392c2f1c]

当引用so文件时，部份手机会报这个错

 java.lang.UnsatisfiedLinkError: dalvik.system.PathClassLoader[DexPathList[[zip file "/data/app/com.hx.template-2/base.apk"],nativeLibraryDirectories=[/data/app/com.hx.template-2/lib/arm64, /vendor/lib64, /system/lib64]]] couldn't find "libstlport_shared.so"
原因是这部份手机是64位处理器的，所以找so的时候先从/lib/arm64, /vendor/lib64, /system/lib64这几个目录找。
解决方法：
在gradle.properties加上

android.useDeprecatedNdk=true
build.gradle加上

android {
    ...
    defaultConfig {
        ...
        ndk {
            abiFilters "armeabi-v7a", "x86", "armeabi"
        }
    }
}


##2 
-- 1 注意 ，一定要在构造app的DEMO这个module的gralde里加。
--2  加载负责lib的module是不起作用的



##3
还有一种方法，没试验

`
 buildTypes {
     debug {
            ndk {
                abiFilters = []
                abiFilters.addAll(ABI_FILTERS.split(';').collect{it as String})
            }
            release {
            minifyEnabled false
            proguardFiles getDefaultProguardFile('proguard-android.txt'), 'proguard-rules.txt'
            ndk {
                abiFilters = []
                abiFilters.addAll(ABI_FILTERS.split(';').collect{it as String})
            }
        }

}
`

记得要在gradle.properties加上
`
ABI_FILTERS = "armeabi-v7a", "armeabi"
`