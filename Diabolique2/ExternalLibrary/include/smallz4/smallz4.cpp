// //////////////////////////////////////////////////////////
// smallz4.cpp
// Copyright (c) 2016-2019 Stephan Brumme. All rights reserved.
// see https://create.stephan-brumme.com/smallz4/
//
// "MIT License":
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the Software
// is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

// suppress warnings when compiled by Visual C++
#define _CRT_SECURE_NO_WARNINGS

#include "smallz4.h"

#include <cstdio>     // stdin/stdout/stderr, fopen, ...
#include <ctime>      // time (verbose output)

#ifdef _WIN32
  #include <io.h>     // isatty()
#else
  #include <cstdlib>  // exit
  #include <unistd.h> // isatty()
  #define _fileno fileno
  #define _isatty isatty
#endif




// ==================== user-specific I/O INTERFACE ====================

struct UserPtr
{
  // file handles
  FILE* in;
  FILE* out;
  // the attributes below are just needed for verbose output
  bool  verbose;
  uint64_t numBytesIn;
  uint64_t numBytesOut;
  uint64_t totalSize;
  time_t   starttime;
};

/// read several bytes and store at "data", return number of actually read bytes (return only zero if end of data reached)
size_t getBytesFromIn(void* data, size_t numBytes, void* userPtr)
{
  /// cast user-specific data
  UserPtr* user = (UserPtr*)userPtr;

  if (data && numBytes > 0)
  {
    size_t actual = fread(data, 1, numBytes, user->in);
    user->numBytesIn += actual;

    return actual;
  }
  return 0;
}

/// show verbose info on STDERR
void verbose(const UserPtr& user)
{
  if (!user.verbose)
    return;
  if (user.numBytesIn == 0)
    return;

  // elapsed and estimated time in seconds
  int duration  = int(time(NULL) - user.starttime);
  if (duration == 0)
    return;
  int estimated = int(duration * user.totalSize / user.numBytesIn);

#if 0
  // display on STDERR
  fprintf(stderr, "\r%lld bytes => %lld bytes (%d%%", user.numBytesIn, user.numBytesOut, 100 * user.numBytesOut / user.numBytesIn);
  if (estimated > 0)
    fprintf(stderr, ", %d%% done", 100 * duration / estimated);
  fprintf(stderr, "), after %d seconds @ %d kByte/s", duration, duration > 0 ? (user.numBytesIn / duration) / 1024 : 0);
  if (estimated > 0)
    fprintf(stderr, ", about %d seconds left  ", estimated - duration);
#endif
}

/// write a block of bytes
void sendBytesToOut(const void* data, size_t numBytes, void* userPtr)
{
  /// cast user-specific data
  UserPtr* user = (UserPtr*)userPtr;
  if (data && numBytes > 0)
  {
    fwrite(data, 1, numBytes, user->out);
    user->numBytesOut += numBytes;

    if (user->verbose)
      verbose(*user);
  }
}

