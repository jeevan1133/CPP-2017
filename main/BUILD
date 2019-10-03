cc_binary(
      name = "structured",
      srcs = ["structured-bindings.cc"],
      deps = [
            "//lib:build-all",
        #"//lib:divide-remainder",
        #"//lib:stock-info",
        ],
)

cc_binary(
      name = "containers",
      srcs = ["containers.cc"],
      deps = [
            "//lib:container",
            ],
      )

cc_binary(
      name = "rpn",
      srcs = ["rpn-calculator.cc"],
      deps = [
            "//lib:rpn",
            ],
      )

cc_binary(
      name = "freq-counter",
      srcs = ["freq-counter.cc"],
      deps = [
            "//lib:freq-counter",
            ],
      )

cc_binary(
      name = "multimap",
      srcs = ["multimap.cc"],
      deps = [
            "//lib:multimap",
            ],
      )
cc_binary(
      name = "priority",
      srcs = ["priority-queue.cc"],
      deps = [
            "//lib:priority",
            ],
      )
cc_binary(
      name = "iterators",
      srcs = ["implementing-iterators.cc"],
      )
cc_binary(
      name = "fib",
      srcs = ["fibonacci.cc"],
      )
#cc_binary(
#      name = "sentinels",
#      srcs = ["sentinels-iterators.cc"],
#      )
#cc_binary(
#      name = "filewatcher",
#      srcs = ["filesystems.cc"],
#      deps = [
#            "//lib:filewatcher",
#            ],
#      )

cc_binary(
      name = "checkit",
      srcs = ["checking-iterators.cc"],
      copts = [
            "-fsanitize=address -fsanitize=undefined",
            ],
      )
cc_binary(
      name = "zip-iter",
      srcs = ["zip-iterator.cc"],
      deps = [
            "//lib:zip-iter",
            ],
      )

cc_binary(
      name = "std-function",
      srcs = ["lambdas.cc"],
      #deps = [
      #      "//lib:polymorphy-std-function",
      #      ],
      )
