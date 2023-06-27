genrule(
    name = "hello",
    outs = ["hello.txt"],
    #location 来引用目标 //myecho:myecho 生成的程序 myecho 的路径
    cmd = "$(location //myecho) Hello World! > $@",
    tools = ["//myecho"],   # 在运行hello规则之前，bazel会自动下载并编译myecho
)