/**
 * 2014, by bitpick
 **/


#ifndef RAII_H_
#define RAII_H_

/**
 * @short   RAII macro for variable definition
 *
 * Declares a variable with a context-based life-cycle.
 * If the context (e.g. the function -> @example) is left, the specified
 * dtor will be called automatically.
 *
 * RAII - Resource Acquisition Is Initialization
 *
 *
 * @param   vname   variable name
 * @param   vtype   variable type
 * @param   vinit   variable initialization function
 * @param   vdtor   variable destroy function
 *
 * @example
 *          void foo() {
 *              DECLARE_RAII_VARIABLE(buff, char*, (char*)malloc(512), free);
 *              [...]
 *          }
 **/
#define DECLARE_RAII_VARIABLE(vname, vtype, viniti, vdtor) \
    void _dtor_  ## vname(vtype *v) {\
        vdtor(*v);\
    } \
    vtype vname __attribute__((cleanup(_dtor_ ## vname))) = (vinit)

#endif

