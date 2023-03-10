# MNIST C++

- Learning materials: [video](https://youtu.be/E1K9SZCm0fQ) and [source code](https://github.com/gtaylor5/mnist_ml)

- [MNIST data](https://deepai.org/dataset/mnist): ~~seems like currently unavailable~~

  - [intro](./docs/MNIST%20dataset.md)

  - [raw data](./data/README.md)

- [iris data](https://archive.ics.uci.edu/ml/machine-learning-databases/iris/)

  - [intro](./data/iris.names)

  - [raw data](./data/iris.data)

## Compile and Run

1. Makefile:

    - create a shared library

        ```sh
        export MNIST_ML_ROOT=$PWD
        make
        ```

    - use the lib

        ```sh
        cd lib/
        export LD_LIBRARY_PATH=$PWD
        ```

1. VS Code settings:

    - `tasks.json`:

        ```json
        "command": "/usr/bin/clang++",
        "args": [
          "-std=c++2a",
          "-fcolor-diagnostics",
          "-fansi-escape-codes",
          "-g",
          "${workspaceFolder}/src/*",
          "-I",
          "${workspaceFolder}/include",
          "-o",
          "${workspaceFolder}/dev/${fileBasenameNoExtension}"
        ],
        ```

    - `c_cpp_properties.json`:

        - [setup](https://stackoverflow.com/a/71115284/8163324)

        - [backup](https://stackoverflow.com/a/68139743/8163324)

Note: `dev/` is a temporary directory served for testing purpose.

## Materials

- [KNN (cn)](https://www.joinquant.com/view/community/detail/a98b7021e7391c62f6369207242700b2): supervised learning

- [KMEANS (cn)](https://zhuanlan.zhihu.com/p/78798251): unsupervised learning

- [Deep learning (cn)](https://www.jianshu.com/p/c8a46f00b06d): a subset of machine learning (deep neural networks)
