/**
 * Copyright (C) 2014 bitpick
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
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
#define DECLARE_RAII_VARIABLE(vname, vtype, vinit, vdtor) \
    void _dtor_  ## vname(vtype *v) {\
        vdtor(*v);\
    } \
    vtype vname __attribute__((cleanup(_dtor_ ## vname))) = (vinit)

#endif

