# MNIST C++

- Learning materials: [video](https://youtu.be/E1K9SZCm0fQ) and [source code](https://github.com/gtaylor5/mnist_ml)

- [data](https://deepai.org/dataset/mnist): ~~seems like currently unavailable~~

  - [intro](./docs/MNIST%20dataset.md)

  - [raw data](./data/README.md)

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

- [KNN (cn)](https://www.joinquant.com/view/community/detail/a98b7021e7391c62f6369207242700b2)

- [KMEANS (cn)](https://zhuanlan.zhihu.com/p/78798251): unsupervised learning
