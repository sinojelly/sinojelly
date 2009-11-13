/// ***************************************************************************
/// Copyright (c) 2009, Industrial Logic, Inc., All Rights Reserved.
///
/// This code is the exclusive property of Industrial Logic, Inc. It may ONLY be
/// used by students during Industrial Logic's workshops or by individuals
/// who are being coached by Industrial Logic on a project.
///
/// This code may NOT be copied or used for any other purpose without the prior
/// written consent of Industrial Logic, Inc.
/// ****************************************************************************


#ifndef ILCONFIG_H_
#define ILCONFIG_H_

#include <iostream>

#ifdef __CYGWIN__
#define IL_CYGWIN	1
#elif defined(_MSC_VER)
#define IL_DEVSTUDIO	1
#elif defined(_WIN32)
#define IL_MINGW
#else
#define IL_LINUX
#endif

#endif

