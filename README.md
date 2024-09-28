# clmixer


***clmixer*** ("opencl" + "mixer") is a tool for quick parallel computation evaluation ([CPU](https://en.wikipedia.org/wiki/Central_processing_unit) and [GPU](https://en.wikipedia.org/wiki/Graphics_processing_unit), [APU](https://en.wikipedia.org/wiki/AMD_Accelerated_Processing_Unit) not tested).

### Use cases:

1. Fast evaluation of a [kernel](https://en.wikipedia.org/wiki/Compute_kernel) code (runtime compilation). 
2. Multiple kernels parallel execution, configurable number of repeats.
3. Validate computations (hardware failures).

### Current API support:

1. [OpenCL](https://en.wikipedia.org/wiki/OpenCL).

### Current memory model support:

1. OpenCL buffer.

### Build dependencies:

* C++17 compatible compiler.
* OpenCL ICD Loader ([first](https://github.com/KhronosGroup/OpenCL-ICD-Loader) or [second](https://github.com/OCL-dev/ocl-icd)).
* [spdlog](https://github.com/gabime/spdlog) library (v7/8 should be fine).
* [CLI11](https://github.com/CLIUtils/CLI11) library.
* [gtest](https://github.com/google/googletest) library.

### AppImage dependencies:

* [FUSE](https://github.com/libfuse/libfuse)
* [Glibc](https://www.gnu.org/software/libc/) >= 2.29 (Ubuntu 20.04)

### Quick start:

```shell script
# command line.
user@localhost ~ $ cd /tmp
user@localhost /tmp $ git clone https://github.com/livelace/clmixer.git
user@localhost /tmp $ curl -L https://github.com/livelace/clmixer/releases/download/v1.1.0/clmixer-v1.1.0.appimage -o clmixer.appimage && chmod +x clmixer.appimage
user@localhost /tmp $ ./clmixer.appimage --opencl-kernel-file clmixer/examples/opencl/buffer_copy_long.c
[2021-10-02 00:23:42.746] [info] clmixer v1.1.0
[2021-10-02 00:23:42.911] [info] device: #0 (Intel(R) Core(TM) i7-7700T CPU @ 2.90GHz, 2900MHz, 31.1G, 7.8G)
[2021-10-02 00:23:42.911] [info] task mode: opencl
[2021-10-02 00:23:42.911] [info] opencl mode: buffer
[2021-10-02 00:23:42.911] [info] generate increment data: started
[2021-10-02 00:23:43.388] [info] generate increment data: finished (long, 134217728, 1G)
[2021-10-02 00:23:43.388] [info] task [1][1]: creation ...
[2021-10-02 00:23:43.497] [info] task [1][1]: creation: kernel compiled
[2021-10-02 00:23:43.762] [info] task [1][1]: creation: input buffer written
[2021-10-02 00:23:43.762] [info] task [1][1]: creation: finished
[2021-10-02 00:23:43.763] [info] task [1][1]: execution ...
[2021-10-02 00:23:44.233] [info] task [1][1]: execution: compute fulfilled
[2021-10-02 00:23:44.503] [info] task [1][1]: execution: output buffer read
[2021-10-02 00:23:44.503] [info] task [1][1]: execution: finished
[2021-10-02 00:23:44.503] [info] task [1]: cleanup
[2021-10-02 00:23:44.793] [info] data: cleanup
[2021-10-02 00:23:44.793] [info] result show [1]: [0 ... 134217727]
[2021-10-02 00:23:44.877] [info] exiting

# docker.
user@localhost /tmp $ docker run -ti ghcr.io/livelace/clmixer:v1.1.0 clmixer --show-devices
[2021-10-01 21:26:01.852] [info] available devices:

cpu:
  device: #0
    name:                      Intel(R) Core(TM) i7-7700T CPU @ 2.90GHz
    platform:                  Intel(R) OpenCL
    clock speed:               2900MHz
    memory global size:        31.1G
    memory max allocate:       7.8G
    svm coarse-grained buffer: false
    svm fine-grained buffer:   false
    svm fine-grained system:   false
    work group dimension:      3
    work group size:           8192

```

### ToDo:

1. Add zero-copy/SVM buffer support.
2. Summary execution statistics.
3. OpenCL images and pipes.
4. CUDA support.