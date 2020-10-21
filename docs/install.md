
The prerequisites needed to build:

- autotools
- cmake >= 3.17
- MPI Library
- C++17 compiler
- CUDA >= 10.1 (only if building with GPU support)

`MACOSX`: We recommend using brew to install the prerequisites:  
- `brew install gcc openmpi cmake wget autoconf automake`

Supported Compilers
--------------------
- GCC versions >= 8.3
- LLVM Clang >= 8 (Tested on Linux Only)
- `MACOSX`: We only support brew installed `GCC`, `AppleClang` is not supported.


Supported Configurations
-------------------------
- The following configurations are recommended since they are tested and are known to work:
  - GCC versions >= 8.x + OpenMPI-2.x/MPICH-3.x built using corresponding gcc versions.
  - LLVM Clang versions >= 7.x + OpenMPI-2.x/MPICH-3.x 


Build Instructions
=====================

```
export GFCC_SRC=$HOME/gfcc_src
export GFCC_INSTALL_PATH=$HOME/gfcc_install
git clone https://github.com/spec-org/gfcc.git $GFCC_SRC
```

Step 1: Setup CMakeBuild
========================
```
cd $GFCC_SRC/contrib/CMakeBuild
mkdir build && cd build

CC=gcc CXX=g++ FC=gfortran cmake -DCMAKE_INSTALL_PREFIX=$GFCC_INSTALL_PATH ..

make install
```

Step 2: Choose Build Options
============================

### CUDA Options 
```
-DUSE_CUDA=ON (OFF by Default)  
-DCUDA_MAXREGCOUNT=128 (set to 64 by Default)
```

Step 3: Building TAMM
=====================

```
cd $GFCC_SRC/contrib/TAMM
mkdir build && cd build
```

## In addition to the build options chosen in Step 2, there are various build configurations depending on the BLAS library one wants to use.

* **[Build using reference BLAS from NETLIB](install.md#build-using-reference-blas-from-netlib)**

* **[Build using Intel MKL](install.md#build-using-intel-mkl)**

* **[Build instructions for Summit using ESSL](install.md#build-instructions-for-summit-using-essl)**

* **[Build instructions for Cori](install.md#build-instructions-for-cori)**

## Build using reference BLAS from NETLIB

### To enable CUDA build, add `-DUSE_CUDA=ON`

```
cd $GFCC_SRC/contrib/TAMM
mkdir build && cd build

CC=gcc CXX=g++ FC=gfortran cmake -DCMAKE_INSTALL_PREFIX=$GFCC_INSTALL_PATH ..

# make step takes a while, please use as many cores as possible
make -j3
make install
```

Step 4: Building the GFCC library
=================================
```
cd $GFCC_SRC
mkdir build && cd build

### To enable CUDA build, add `-DUSE_CUDA=ON`

CC=gcc CXX=g++ FC=gfortran cmake -DBLAS_VENDOR=IntelMKL -DCMAKE_INSTALL_PREFIX=$GFCC_INSTALL_PATH ..

make -j2
```

Step 5: Running the GFCC code
=============================
`cd $GFCC_SRC/build`   
`mpirun -n 4 ./test_stage/$GFCC_INSTALL_PATH/methods/GF_CCSD ../tests/co.nwx`


-------------------------------------------------------------------
# Advanced Build Options for TAMM/libGFCC (applies to Steps 2 & 3)
-------------------------------------------------------------------

The following configurations are to be used to replace the `cmake` command in Steps 2 and 3.   
The remaining instructions in Steps 3 & 4 stay the same.

## Build using Intel MKL

### Set `MKLROOT` accordingly

```
export MKLROOT=/opt/intel/compilers_and_libraries_2019.0.117/linux/mkl
```

### To enable CUDA build, add `-DUSE_CUDA=ON`

```
cd $GFCC_SRC/contrib/TAMM/build
CC=gcc CXX=g++ FC=gfortran cmake -DBLAS_VENDOR=IntelMKL -DCMAKE_INSTALL_PREFIX=$GFCC_INSTALL_PATH ..
make -j3
make install
```

## Build instructions for Summit using ESSL

```
module load gcc/8.3.0
module load cmake/3.17.3
module load essl/6.1.0-2
module load cuda/10.1.105
module load netlib-lapack/3.8.0
```

```
The following paths may need to be adjusted if the modules change:

export ESSLROOT=/sw/summit/essl/6.1.0-2/essl/6.1
export NETLIB_BLAS_LIBS="/autofs/nccs-svm1_sw/summit/.swci/1-compute/opt/spack/20180914/linux-rhel7-ppc64le/gcc-8.1.1/netlib-lapack-3.8.0-moo2tlhxtaae4ij2vkhrkzcgu2pb3bmy/lib64"
```

### To enable CUDA build, add `-DUSE_CUDA=ON`

```
cd $GFCC_SRC/contrib/TAMM/build

CC=gcc CXX=g++ FC=gfortran cmake \
-DCMAKE_INSTALL_PREFIX=$GFCC_INSTALL_PATH \
-DTAMM_EXTRA_LIBS=$NETLIB_BLAS_LIBS/liblapack.a \
-DBLIS_CONFIG=power9 \
-DBLAS_VENDOR=IBMESSL ..

make -j3
make install
```


## Build instructions for Cori

```
module unload PrgEnv-intel/6.0.5
module load PrgEnv-gnu/6.0.5
module swap gcc/8.3.0 
module swap craype/2.5.18
module swap cray-mpich/7.7.6 
module load cmake
module load cuda/10.1.168
```

```
export CRAYPE_LINK_TYPE=dynamic
export MKLROOT=/opt/intel/compilers_and_libraries_2019.3.199/linux/mkl
```

### To enable CUDA build, add `-DUSE_CUDA=ON`

```
cd $GFCC_SRC/contrib/TAMM/build

CC=cc CXX=CC FC=ftn cmake -DBLAS_VENDOR=IntelMKL -DCMAKE_INSTALL_PREFIX=$GFCC_INSTALL_PATH ..

make -j3
make install
```


Build instructions for Mac OS
-------------------------------

```
brew install gcc openmpi cmake wget autoconf automake

export GFCC_SRC=$HOME/gfcc_src
export GFCC_INSTALL_PATH=$HOME/gfcc_install
git clone https://github.com/spec-org/gfcc.git GFCC_SRC

cd $GFCC_SRC/contrib/CMakeBuild
mkdir build && cd build
CC=gcc-8 CXX=g++-8 FC=gfortran-8 cmake -DCMAKE_INSTALL_PREFIX=$GFCC_INSTALL_PATH ..
make install

cd $GFCC_SRC/contrib/TAMM
mkdir build && cd build
CC=gcc-8 CXX=g++-8 FC=gfortran-8 cmake -DCMAKE_INSTALL_PREFIX=$GFCC_INSTALL_PATH ..
make -j3 
make install
ctest (optional)

cd $GFCC_SRC
mkdir build && cd build
CC=gcc-8 CXX=g++-8 FC=gfortran-8 cmake -DCMAKE_INSTALL_PREFIX=$GFCC_INSTALL_PATH ..
make -j2 install
```

Build instructions for Ubuntu Bionic 18.04
------------------------------------------

```
sudo apt install g++-8 gcc-8 gfortran-8 openmpi-dev

curl -LJO https://github.com/Kitware/CMake/releases/download/v3.18.4/cmake-3.18.4-Linux-x86_64.tar.gz
tar xzf cmake-3.18.4-Linux-x86_64.tar.gz
export PATH=`pwd`/cmake-3.15.3-Linux-x86_64/bin:$PATH

export GFCC_SRC=$HOME/gfcc_src
export GFCC_INSTALL_PATH=$HOME/gfcc_install
git clone https://github.com/spec-org/gfcc.git GFCC_SRC

cd $GFCC_SRC/contrib/CMakeBuild
mkdir build && cd build
CC=gcc-8 CXX=g++-8 FC=gfortran-8 cmake -DCMAKE_INSTALL_PREFIX=$GFCC_INSTALL_PATH ..
make install

cd $GFCC_SRC/contrib/TAMM
mkdir build && cd build
// To enable CUDA build, add -DUSE_CUDA=ON
CC=gcc-8 CXX=g++-8 FC=gfortran-8 cmake -DCMAKE_INSTALL_PREFIX=$GFCC_INSTALL_PATH ..
make -j3 install
ctest (optional)

cd $GFCC_SRC
mkdir build && cd build
CC=gcc-8 CXX=g++-8 FC=gfortran-8 cmake -DCMAKE_INSTALL_PREFIX=$GFCC_INSTALL_PATH ..
make -j2 install
```
