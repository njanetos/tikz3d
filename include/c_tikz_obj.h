#ifndef C_TIKZ_OBJ_H
#define C_TIKZ_OBJ_H

#include "common.h"

class c_camera;

class c_tikz_obj {
    public:
        /**
         *  Destructor for all tikz objects.
         */
        virtual ~c_tikz_obj();

        /**
         *  Writes this object to tikz code.
         *
         *  \return A string containing the tikz code.
         */
        virtual std::string write() =0;

        /**
         *  Projects this object against a camera.
         *
         *  \param cam The camera to project against.
         *  \return Pointer to projected object.
         */
        virtual c_tikz_obj* project(c_camera *cam) =0;

        /**
         *  Clones this object onto the heap.
         *
         *  \return Pointer to the cloned object.
         */
        virtual c_tikz_obj* clone() =0;

        /**
         *  Adds a parameter to be rendered to tikz.
         *
         *  \param param The parameter, e.g., color=green.
         */
        void add_param(std::string param);

        /**
         *  Adds multiple parameters to be rendered to tikz.
         *
         *  \param params Vector of parameters to render.
         */
        void add_params(std::vector<std::string> params);

        /**
         *  A list of parameters for tikz.
         */
        std::vector<std::string> params;

};

#endif // C_TIKZ_OBJ_H
