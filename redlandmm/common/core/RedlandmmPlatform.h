/*== REDLANDMM =====================================================================
 * Copyright (c) 2012, Jesse K Medley
 * All rights reserved.

 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of The University of Washington nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

//== FILEDOC =========================================================================

/** @file RedlandmmPlatform.h
 * @brief Platform information (client switch is in here)
  * @details Huge file that provides info about the platform. This detailed information
  * is used to specialize certain segments of code where OS or architecture-specific
  * operations are desired.
  * MUST include generated config header before including this file. The generated header
  * determines whether the client switch is set or not.
  */


//== BEGINNING OF CODE ===============================================================

#include "redlandmm/common/core/RedlandmmConfigure.h"

#ifndef __REDLANDMM_PLATFORM_H_
#define __REDLANDMM_PLATFORM_H_

//namespace Redlandmm //Pointless
//{
//Platform parameters
#define REDLANDMM_PLATFORM_WIN   1
#define REDLANDMM_PLATFORM_APPLE 2
#define REDLANDMM_PLATFORM_LINUX 3

#define REDLANDMM_COMPILER_GNUC  1
#define REDLANDMM_COMPILER_MINGW 2
#define REDLANDMM_COMPILER_MSVC  3
#define REDLANDMM_COMPILER_BORL  4

#define REDLANDMM_LITTLE_ENDIAN 1
#define REDLANDMM_BIG_ENDIAN    2

#define REDLANDMM_ARCH_32 1
#define REDLANDMM_ARCH_64 2

//Determine compiler type and version
#if defined ( __MINGW32__ )
    //Must test before __GNUC__ because MinGW also defines that (maybe)
#   define REDLANDMM_COMPILER            REDLANDMM_COMPILER_MINGW
//GNU C/C++ compiler
#elif defined( __GNUC__ )
#   define REDLANDMM_COMPILER            REDLANDMM_COMPILER_GNUC
#   if defined ( __GNUC_PATCHLEVEL__ )
#       define REDLANDMM_COMPILER_VERSION    ( ( __GNUC__ )*100 ) + ( ( __GNUC_MINOR__ )*10 ) + __GNUC_PATCHLEVEL__
#   else
#       define REDLANDMM_COMPILER_VERSION    ( ( __GNUC__ )*100 ) + ( ( __GNUC_MINOR__ )*10 )
#       define REDLANDMM_CXX_STD_LIB_VER     __GLIBCXX__
#   endif
//Determine libstdc++ version
#   define REDLANDMM_CXX_STD_LIB_VER __GLIBCXX__
#elif defined ( _MSC_VER )
#   define REDLANDMM_COMPILER REDLANDMM_COMPILER_MSVC
#   define REDLANDMM_COMPILER_VERSION _MSC_VER
#elif defined ( __BORLANDC__ )
#   error "Borland C/C++ is not supported"
#else
#   error "This compiler does not appear to be supported"
#endif

// http://stackoverflow.com/questions/295120/c-mark-as-deprecated
# if (REDLANDMM_COMPILER == REDLANDMM_COMPILER_MSVC)
#   define REDLANDMM_DEPRECATED(f) __declspec(deprecated) f
# else
#   define REDLANDMM_DEPRECATED(f) f __attribute__((deprecated))
# endif

//Determine the appropriate way to force inlining of a function
#if REDLANDMM_COMPILER == REDLANDMM_COMPILER_MSVC
#   if REDLANDMM_COMPILER_VERSION >= 1200
#       define FORCEINLINE __forceinline
#   endif
#elif defined( __MINGW32__ )
#   if !defined(FORCEINLINE)
#       define FORCEINLINE __inline
#   endif
#else
#   define FORCEINLINE __inline
#endif

//Determine what the current platform is
#if defined( __WIN32__ ) || defined ( _WIN32 )
#   define REDLANDMM_PLATFORM REDLANDMM_PLATFORM_WIN
#   define REDLANDMM_IS_POSIX_VAR 0 //True if on a POSIX variant
#elif defined ( __APPLE_CC__ )
#   define REDLANDMM_PLATFORM REDLANDMM_PLATFORM_APPLE
#   define REDLANDMM_IS_POSIX_VAR 1
#elif defined ( __linux__ )
#   define REDLANDMM_PLATFORM REDLANDMM_PLATFORM_LINUX
#   define REDLANDMM_IS_POSIX_VAR 1
#else
#   warning Platform unknown trying Linux
#   define REDLANDMM_PLATFORM REDLANDMM_PLATFORM_LINUX
#endif

//Determine if the platform supports a 64-bit architecture
#if defined( __x86_64__ ) || defined( _M_X64 )
#   define REDLANDMM_ARCH REDLANDMM_ARCH_64
#   define SG_PTR_SIZE 8
#else
#   define REDLANDMM_ARCH REDLANDMM_ARCH_32
#   define SG_PTR_SIZE 4
#endif

#define GF_MACRO_QUOTE( x ) # x
#define GF_EXPAND_AND_QUOTE( x ) GF_MACRO_QUOTE(x)
#define REDLANDMM_WARN( x ) message( __FILE__ "(" MACRO_QUOTE( __LINE__ ) ") : " x "\n" )

//Platform specific settings
#if REDLANDMM_PLATFORM == REDLANDMM_PLATFORM_WIN
#   include "RedlandmmPlatformWin.h"
#   define OS_SEP MACRO_QUOTE(/)
    //The client switch controls the behavior of _RedlandmmExport.
    //When building a library, symbols must be exported, so _RedlandmmExport
    //is synonymous with __declspec(dllexport). When linking to said library,
    //the same symbols must instead be imported, hence the meaning of _RedlandmmExport
    //is changed to __declspec(dllimport)
#   if(!REDLANDMM_CLIENT_BUILD)
#       define _RedlandmmExport  __declspec(dllexport)
#       define _RedlandmmPrivate 
#   else
#       define _RedlandmmExport  __declspec(dllimport)
#       define _RedlandmmPrivate 
#   endif
#elif REDLANDMM_PLATFORM == REDLANDMM_PLATFORM_APPLE
#   pragma error "Apple is not supported"
#elif REDLANDMM_PLATFORM == REDLANDMM_PLATFORM_LINUX
#   define OS_SEP MACRO_QUOTE(/)
#   if defined( REDLANDMM_GCC_VISIBILITY )
#       define _RedlandmmExport  __attribute__ ((visibility("default")))
#       define _RedlandmmPrivate __attribute__ ((visibility("hidden")))
#   else
#       define _RedlandmmExport  
#       define _RedlandmmPrivate 
#   endif
#endif

#define REDLANDMM_UNICODE_SUPPORT 0

#ifdef REDLANDMM_CONFIG_BIG_ENDIAN
#   define REDLANDMM_ENDIAN REDLANDMM_BIG_ENDIAN
#else
#   define REDLANDMM_ENDIAN REDLANDMM_LITTLE_ENDIAN
#endif

//} //namespace Redlandmm

#endif
