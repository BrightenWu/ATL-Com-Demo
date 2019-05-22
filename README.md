# ATL Com Demo

## 项目介绍
The usage of custom structure and Event notification of Com/ATL/ActiveX.

## 开发环境
Windows7 x64 Vs2017

## 测试环境
Windows7 x64

## 测试工具
MS office professional plus 2013 word x64 VB
Matlab R2017b x64
Matlab7.0 x32

## 测试结果
1. VARIANT varValue = CComVariant(pArray);  为该方式传到VARIANT数组数据为空。
2. VB输入SAFEARRAY无法识别，返回可以。
3. VB无法识别ULONG。
4. Matlab无法识别自定义结构体。
5. VB、Matlab都无法识别存储于VARIANT的SAFEARRAY。
6. CComVariant存BSTR，vb读取出错。
7. VARIANT存储自定义结构体(vb无法识别VT_RECORD，可以识别自定义结构数组)。
8. 64位的进程内Com(.dll)只能由64位的应用程序调用，64位的进程外Com(.exe)可以由32位的应用程序调用，例子中只需简单的将ATLProjectTest2.cpp文件中的注释代码和非注释代码互换即可。
