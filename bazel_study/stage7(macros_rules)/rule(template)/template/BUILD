load("hello.bzl", "hello_world")

hello_world(
    name = "hello_Alice",
    username = "Alice",
    template = "hello.cc.tpl",
)

cc_binary(
    name = "hello",
    srcs = [":hello_Alice"],
)