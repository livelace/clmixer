__kernel void clmixer(__global unsigned long *input, __global unsigned long *output)
{
    unsigned long id = get_global_id(0);
    unsigned long value = input[id];

    for (int i=0; i<10000; i++)
    {
        value += 1;
    }

    output[id] = value;
};
