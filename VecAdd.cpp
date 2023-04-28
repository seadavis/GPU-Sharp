// VecAdd.cpp : Defines the entry point for the application.
//

#include "VecAdd.h"
#include "Matrix.h"
#define __CL_ENABLE_EXCEPTIONS

#include "cl.hpp"
#include "util.hpp" // utility library

#include <vector>
#include <cstdio>
#include <cstdlib>
#include <string>

#include <iostream>
#include <fstream>

// pick up device type from compiler command line or from the default type
#ifndef DEVICE
#define DEVICE CL_DEVICE_TYPE_DEFAULT
#endif

#include "err_code.h"

//------------------------------------------------------------------------------

#define TOL    (0.001)   // tolerance used in floating point comparisons
#define ROWS (2)
#define COLUMNS (2)
#define LENGTH (4)    // length of vectors a, b, and c

using namespace std;

int main(void)
{
    Matrix m1(COLUMNS, ROWS);
    Matrix m2(COLUMNS, ROWS);

    cl::Buffer inputM1Buffer;
    cl::Buffer inputM2Buffer;
    cl::Buffer outputBuffer;                    

    try
    {
        // Create a context
        cl::Context context(DEVICE);

        // Load in kernel source, creating a program object for the context

        cl::Program program(context, util::loadProgram("../../../mmul.cl"), true);

        // Get the command queue
        cl::CommandQueue queue(context);

        // Create the kernel functor

        cl::make_kernel<cl::Buffer, cl::Buffer, cl::Buffer, long> mmul(program, "mmull");

        auto outputVector = vector<double>(LENGTH);
        inputM1Buffer = cl::Buffer(context, m1.data().begin(), m1.data().end(), true);
        inputM2Buffer = cl::Buffer(context, m2.data().begin(), m2.data().end(), true);
        outputBuffer = cl::Buffer(context, outputVector.begin(), outputVector.end(), true);

        mmul(
            cl::EnqueueArgs(
                queue,
                cl::NDRange(COLUMNS, ROWS)),
            inputM1Buffer,
            inputM2Buffer,
            outputBuffer, ROWS);

        
        Matrix result(outputVector, COLUMNS,ROWS);

        std::cout << result.print();

    }
    catch (cl::Error err) {
        std::cout << "Exception\n";
        std::cerr
            << "ERROR: "
            << err.what()
            << "("
            << err_code(err.err())
            << ")"
            << std::endl;
    }
}