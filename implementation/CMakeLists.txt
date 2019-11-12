cmake_minimum_required(VERSION 3.15)
project(implementation)

set(CMAKE_CXX_STANDARD 11)

include_directories(src/bayes/core)
include_directories(src/boost/core)
include_directories(src/common/core)
include_directories(src/decisiontree/core)
include_directories(src/exception)
include_directories(src/hmm/core)
include_directories(src/kernel_svm/core)
include_directories(src/knn/core)
include_directories(src/logistic/core)
include_directories(src/max_entropy/core)
include_directories(src/mlp/core)
include_directories(src/perceptron/core)
include_directories(src/proto_cluster/core)
include_directories(test/core_test)

add_executable(implementation
        src/exception/exception.h
        src/common/core/util.cpp
        src/common/core/util.h
        src/common/core/Vector.cpp
        src/common/core/Vector.h
        src/common/core/Matrix.cpp
        src/common/core/Matrix.h
        src/bayes/core/bayes.cpp
        src/bayes/core/bayes.h
        src/common/core/classifier.cpp
        src/common/core/classifier.h
        src/common/core/dist_func.cpp
        src/common/core/dist_func.h
        src/knn/core/kdtree.cpp
        src/knn/core/kdtree.h
        src/knn/core/knn.cpp
        src/knn/core/knn.h
        src/perceptron/core/perceptron.cpp
        src/perceptron/core/perceptron.h
        test/core_test/common.cpp
        test/core_test/common.h
        test/core_test/knn_test.cpp)
