# ch32v103_sdk

#### 介绍
CH32V103C8T6开发环境
暂时只支持Linux下开发

#### 软件架构
软件架构说明


#### 安装教程

1.  从[MounRiver官网](http://www.mounriver.com/download)下载`MRS_Toolchain_Linux_x64_V1.20.tar.xz`并解压  
    已经安装MounRiver Studio的不用再下载了，可以从安装目录中toolchain文件夹里找所需文件
2.  修改`tools/config.mk`中的`MRS_BASE`变量

注：MounRiver工具链的编译器版本比较旧，可以去[xPack](https://github.com/xpack-dev-tools/riscv-none-embed-gcc-xpack)下载最新版的RISC-V GCC编译器,  
把上方的`TOOL_CHAIN`注释掉（为了方便恢复，不建议删除），再把后面的`#TOOL_CHAIN`注释去掉，改成自己的路径。

使用USB烧录程序
1. 安装Linux上的第三方[wchisp](https://github.com/ch32-rs/wchisp)
2. 修改tools/config.mk中的`MCU_OP`为`isp`

#### 使用说明

1.  修改`tools`文件夹下的`inc.mk`和`src.mk`来修改所需编译文件和头文件目录
2.  在根目录下执行命令`make all`进行编译和烧录，更多选项请查看根目录下的`Makefile`文件

注：同一文件夹下如果存在只有后缀不同的多个源文件，如`a.c`和`a.S`，则只会编译一个来生成`*.o`文件，应该避免这种情况

#### 版权说明

本SDK按照 GNU宽通用公共许可证第三版(LGPLv3)或更新授权，
包含的第三方库按照该库的协议授权。

贡献者提交的代码默认按照LGPLv3或更新授权，
如需声明版权请在文件头部添加，可接受（比LGPLv3或更新）更宽松的许可证。
