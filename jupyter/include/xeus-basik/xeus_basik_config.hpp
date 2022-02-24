/***************************************************************************
 * Copyright (c) 2019, Sylvain Corlay, Johan Mabille, Wolf Vollprecht       *
 * Copyright (c) 2019, QuantStack                                           *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#ifndef BASIK_CONFIG_HPP
#define BASIK_CONFIG_HPP

// Project version
#define BASIK_VERSION_MAJOR 0
#define BASIK_VERSION_MINOR 3
#define BASIK_VERSION_PATCH 0

// Composing the version string from major, minor and patch
#define BASIK_CONCATENATE(A, B) BASIK_CONCATENATE_IMPL(A, B)
#define BASIK_CONCATENATE_IMPL(A, B) A##B
#define BASIK_STRINGIFY(a) BASIK_STRINGIFY_IMPL(a)
#define BASIK_STRINGIFY_IMPL(a) #a

#define BASIK_VERSION BASIK_STRINGIFY(BASIK_CONCATENATE(BASIK_VERSION_MAJOR,                                        \
                                                        BASIK_CONCATENATE(., BASIK_CONCATENATE(BASIK_VERSION_MINOR, \
                                                                                               BASIK_CONCATENATE(., BASIK_VERSION_PATCH)))))

#ifdef _WIN32
#ifdef XEUS_BASIK_EXPORTS
#define XEUS_BASIK_API __declspec(dllexport)
#else
#define XEUS_BASIK_API __declspec(dllimport)
#endif
#else
#define XEUS_BASIK_API
#endif

#endif
