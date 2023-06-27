# genrule(
#     name = "hello",
#     outs = ["hello.txt"],
#     cmd = "echo hello world > $@",  #$@代码outs参数中的文件
# )   #使用genrule生成文件

#genrule 函数简介
#genrule 通过运行命令来创建一个或多个文件，其完整说明可见 官方文档。#

#其常用参数举例说明如下：

#name：规则名称，可以在其他规则中引用此标签作为依赖
#srcs：输入文件的标签列表，执行的命令如果有输入文件，则应在此处列举出这些文件
#outs：运行命令后应该生成文件的标签列表
#cmd：需要执行的命令
#tools：命令调用的目标程序 (通常由*_binary规则构建出) 标签列表，Bazel 会在调用命令前首先构建出这些目标
load("//generate_file:generate.bzl", "file_generate")
#生成两个文件
file_generate(
    name = "Alex",
    content = "Love look not with eyes, but with the mind.",
)

file_generate(
    name = "Bob",
    content = "Sweet are the uses of adversity.",
)