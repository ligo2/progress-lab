# load("@rules_cc//cc:defs.bzl", "cc_binary")
# 当需要bazel的C++构建规则库时才需要load...
# 这里使用了第三方规则库Eigen，所以不需要load了
cc_binary(
    name = "main",
    srcs = ["main.cc"],
    #copts = ["-I /mycode/bazel_study/examples-main/cpp-tutorial/eigen3"],
    deps = ["@eigen3//:eigen3"] #依赖第三方规则库Eigen
)
