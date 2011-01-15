#include "Kernel.h"

namespace rtps {

Kernel::Kernel(CL *cli, std::string source, std::string name)
{
    this->cli = cli;
    this->name = name;
    this->source = source;
    //TODO need to save the program
    kernel = cli->loadKernel(source, name);
}
Kernel::Kernel(CL *cli, cl::Program prog, std::string name)
{
    this->cli = cli;
    this->name = name;
    //this->source = source;
    this->program = prog;
    kernel = cli->loadKernel(program, name);
    //TODO need to save the program
    //kernel = cli->loadKernel(source, name);
}

void Kernel::execute(int ndrange)
{
        printf("work group size: %d\n", ndrange);
        if(ndrange <= 0)
            return;
    try
    {
        cl::Event event;
        cli->err = cli->queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(ndrange), cl::NullRange, NULL, &event);
        cli->queue.finish();
    }
    catch (cl::Error er) {
        printf("err: work group size: %d\n", ndrange);
        printf("ERROR: %s(%s)\n", er.what(), oclErrorString(er.err()));
    }

}

void Kernel::execute(int ndrange, int worksize)
{
    printf("ndrange: %d\n", ndrange);
    int global;
    float factor = (1.0f * ndrange) / worksize;
    printf("global f: %f\n", factor);
    if((int)factor != factor)
    {
        factor = (int)factor;
        global = worksize*factor + worksize;
        printf("global2: %d\n", global);
    }
    else
    {
        global = ndrange;
    }

        printf("global %d, local %d\n", global, worksize);
        if(ndrange <=0 || worksize <= 0)
            return;

    try
    {
        cl::Event event;
        cli->err = cli->queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(global), cl::NDRange(worksize), NULL, &event);
        cli->queue.finish();
    }
    catch (cl::Error er) {
        printf("err: global %d, local %d\n", global, worksize);
        printf("ERROR: %s(%s)\n", er.what(), oclErrorString(er.err()));
    }

}

void Kernel::setArgShared(int arg, int nb_bytes)
{
    try
    {
        kernel.setArg(arg, nb_bytes, 0);
        cli->queue.finish();
    }
    catch (cl::Error er) {
        printf("ERROR: %s(%s)\n", er.what(), oclErrorString(er.err()));
    }
}
 
}
