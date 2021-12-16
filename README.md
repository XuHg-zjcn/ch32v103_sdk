# ch32v103_sdk

#### 介绍
CH32V103C8T6开发环境
暂时只支持Linux下开发

#### 软件架构
软件架构说明


#### 安装教程

1.  从[MounRiver官网](http://www.mounriver.com/download)下载`MRS_Toolchain_Linux_x64_V1.20.tar.xz`并解压  
    已经安装MounRiver Studio的不用再下载了，可以从安装目录中toolchain文件夹里找所需文件
2.  修改`tools/config.mk`中的`TOOL_CHAIN`和`OPENOCD`变量
3.  修改`tools/conf.mk`中`OCDFLAGS += -f "<请修改：工具链路径>/OpenOCD/bin/wch-riscv.cfg"`

注：MounRiver工具链的编译器版本比较旧，可以去[xPack](https://github.com/xpack-dev-tools/riscv-none-embed-gcc-xpack)下载最新版的RISC-V GCC编译器

#### 使用说明

1.  修改`tools`文件夹下的`inc.mk`和`src.mk`来修改所需编译文件和头文件目录
2.  在根目录下执行命令`make all`进行编译和烧录，更多选项请查看根目录下的`Makefile`文件

注：同一文件夹下如果有只有后缀不同的多个源文件，如`a.c`和`a.S`，则只会编译一个，应该避免这种情况

#### 版权说明

由本人编写代码的按照LGPLv3授权，包含的第三方库按照第三方库的许可证授权


#### 参与贡献

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request


#### 特技

1.  使用 Readme\_XXX.md 来支持不同的语言，例如 Readme\_en.md, Readme\_zh.md
2.  Gitee 官方博客 [blog.gitee.com](https://blog.gitee.com)
3.  你可以 [https://gitee.com/explore](https://gitee.com/explore) 这个地址来了解 Gitee 上的优秀开源项目
4.  [GVP](https://gitee.com/gvp) 全称是 Gitee 最有价值开源项目，是综合评定出的优秀开源项目
5.  Gitee 官方提供的使用手册 [https://gitee.com/help](https://gitee.com/help)
6.  Gitee 封面人物是一档用来展示 Gitee 会员风采的栏目 [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)
