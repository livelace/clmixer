__kernel void clmixer(__global unsigned long *input, __global unsigned long *output)
{
    unsigned long id = get_global_id(0);

    output[id] = input[id];
};
