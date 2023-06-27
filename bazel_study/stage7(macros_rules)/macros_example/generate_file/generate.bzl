def file_generate(name, content):
    content = "hello %s :" % name + content
    #通过 native 来调用 Bazel 的原生规则
    native.genrule(
        name = name,
        outs = [name + ".txt"],
        # 由于写入的内容中包含换行符，因此需要使用引号防止被解释为两条命令。
        cmd = "echo \"%s\" > $@" % content,
    )