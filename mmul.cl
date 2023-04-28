__kernel void vadd(
    __global double* m1,
    __global double* m2,
    __global double* output,
    __global const long numberOfRows
{
    int i = get_global_id(0);
    int j = get_global_id(1);

    output = m1[j * numberOfRows + i];
}