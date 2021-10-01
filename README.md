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

### AppImage dependencies:

* [FUSE](https://github.com/libfuse/libfuse)
* [Glibc](https://www.gnu.org/software/libc/) >= 2.29 (Ubuntu 20.04)

### Quick start:

```shell script

```

### ToDo:

1. Add zero-copy/SVM buffer support.
2. Summary execution statistics.
3. OpenCL images and pipes.
4. CUDA support.

