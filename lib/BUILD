#cc_library(
#      name = "divide-remainder",
#      srcs = ["divide-remainder.cc"],
#      hdrs = ["divide-remainder.hpp"],
#      visibility = ["//main:__pkg__"],
#)

#cc_library(
#      name = "stock-info",
#      srcs = ["stock-info.cc"],
#      hdrs = ["stock-info.hpp"],
#      visibility = ["//main:__pkg__"],
#)

cc_library(
      name = "build-all",
      srcs = glob(["*.cc"]),
      hdrs = glob(["*.hpp"]),
      visibility = ["//main:__pkg__"],
      )

cc_library (
      name = "container",
      hdrs = ["containers.hpp"],
      visibility = ["//main:__pkg__"],
      )

cc_library (
      name = "rpn",
      hdrs = ["rpn-calculator.hpp"],
      visibility = ["//main:__pkg__"],
      )

cc_library (
      name = "freq-counter",
      hdrs = ["freq-counter.hpp"],
      visibility = ["//main:__pkg__"],
      )

cc_library (
      name = "multimap",
      hdrs = ["multimap.hpp"],
      visibility = ["//main:__pkg__"],
      )
cc_library (
      name = "priority",
      hdrs = ["priority-queue.hpp"],
      visibility = ["//main:__pkg__"],
      )

cc_library(
      name = "filewatcher",
      hdrs = ["FileWatcher.hpp"],
      linkopts = [
            "-lstdc++fs",
            "-lc++experimental",
            ],
      visibility = ["//main:__pkg__"],
      )

cc_library(
      name = "zip-iter",
      hdrs = ["zip-iterator.hpp"],
      visibility = [
            "//main:__pkg__",
            ],
      )

#cc_library(
#      name = "polymorphy-std-function",
#      hdrs = ["std-function.hpp"],
#      visibility = [
#            "//main:__pkg__",
#            ],
#      )
