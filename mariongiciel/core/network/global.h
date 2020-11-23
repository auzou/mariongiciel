#ifndef GLOBAL_NETWORK_H
#define GLOBAL_NETWORK_H

/**
 * \file request.h
 * \brief ...
 * \author Auzou
 * \version ..
 *
 * ...
 *
 */

#include "authentication.h"

namespace mariongiciel::core::network {

/**
 * \struct Singleton
 * \brief ...
 *
 */
template <class T> struct Singleton {
    static T& getInstance(){
        static T instance;
        return instance;
    };
};


/**
 * \name globalAuth
 * \brief Global authentication instance
 */
//inline Singleton<Authentication> globalAuth;


} // END NAMESPACE mariongiciel::core::network

#endif // GLOBAL_NETWORK_H
