#ifndef MODULE_H
#define MODULE_H

// 测试“当本头文件更新时，包含本头文件的所有源文件应当重新编译”
#define TEST_HEADER_INCLUDE 0

#ifndef KERNEL_MODULE

#ifdef __cplusplus
extern "C" {
#endif

extern void module();

#ifdef __cplusplus
}
#endif

#endif // end KERNEL_MODULE

#endif // end MODULE_H
