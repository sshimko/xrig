/* XMRig
 * Copyright 2010      Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2012-2014 pooler      <pooler@litecoinpool.org>
 * Copyright 2014      Lucas Jones <https://github.com/lucasjones>
 * Copyright 2014-2016 Wolf9466    <https://github.com/OhGodAPet>
 * Copyright 2016      Jay D Dee   <jayddee246@gmail.com>
 * Copyright 2016-2017 XMRig       <support@xmrig.com>
 *
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 */


#include <winsock2.h>
#include <windows.h>
#include <uv.h>


#include "Platform.h"
#include "version.h"

#ifdef XMRIG_NVIDIA_PROJECT
#   include "nvidia/cryptonight.h"
#endif

#ifndef XMRIG_NO_HTTPD
#   include <microhttpd.h>
#endif

#include <CL/cl.h>

#if CL_VERSION_2_0
#    define CL_VERSION_STRING "2.0"
#elif CL_VERSION_1_2
#    define CL_VERSION_STRING "1.2"
#elif CL_VERSION_1_1
#    define CL_VERSION_STRING "1.1"
#elif CL_VERSION_1_0
#    define CL_VERSION_STRING "1.0"
#endif

#ifdef _MSC_VER
#   if (_MSC_VER >= 1910)
#       define MSVC_VERSION 2017
#   elif _MSC_VER == 1900
#       define MSVC_VERSION 2015
#   elif _MSC_VER == 1800
#       define MSVC_VERSION 2013
#   elif _MSC_VER == 1700
#       define MSVC_VERSION 2012
#   elif _MSC_VER == 1600
#       define MSVC_VERSION 2010
#   else
#       define MSVC_VERSION 0
#   endif
#endif

static inline OSVERSIONINFOEX winOsVersion()
{
    typedef NTSTATUS (NTAPI *RtlGetVersionFunction)(LPOSVERSIONINFO);
    OSVERSIONINFOEX result = { sizeof(OSVERSIONINFOEX), 0, 0, 0, 0, {'\0'}, 0, 0, 0, 0, 0};

    HMODULE ntdll = GetModuleHandleW(L"ntdll.dll");
    if (ntdll ) {
        RtlGetVersionFunction pRtlGetVersion = reinterpret_cast<RtlGetVersionFunction>(GetProcAddress(ntdll, "RtlGetVersion"));

        if (pRtlGetVersion) {
            pRtlGetVersion((LPOSVERSIONINFO) &result);
        }
    }

    return result;
}


static inline char *createVersionString()
{
    const auto osver = winOsVersion();
    const size_t max = 160;

    char *buf = new char[max];
    int length = snprintf(buf, max, "%s/%s (Windows NT %lu.%lu", APP_NAME, APP_VERSION, osver.dwMajorVersion, osver.dwMinorVersion);

#   if defined(__x86_64__) || defined(_M_AMD64)
    length += snprintf(buf + length, max - length, "; Win64; x64) libuv/%s OpenCL/%s", uv_version_string(), CL_VERSION_STRING);
#   else
    length += snprintf(buf + length, max - length, ") libuv/%s OpenCL/%s", uv_version_string(), CL_VERSION_STRING);
#   endif

#   ifndef XMRIG_NO_HTTPD
    length += snprintf(buf + length, max - length, " libmicrohttpd/%s", MHD_get_version());
#   endif

#   ifdef XMRIG_NVIDIA_PROJECT
    const int cudaVersion = cuda_get_runtime_version();
    length += snprintf(buf + length, max - length, " CUDA/%d.%d", cudaVersion / 1000, cudaVersion % 100);
#   endif

#   ifdef __GNUC__
    length += snprintf(buf + length, max - length, " gcc/%d.%d.%d", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#   elif _MSC_VER
    length += snprintf(buf + length, max - length, " msvc/%d", MSVC_VERSION);
#   endif

    return buf;
}


void Platform::init()
{
    m_versionString = createVersionString();
}


void Platform::release()
{
    delete [] m_defaultConfig;
    delete [] m_versionString;
}


void Platform::setProcessPriority(int priority)
{
    if (priority == -1) {
        return;
    }

    DWORD prio = IDLE_PRIORITY_CLASS;
    switch (priority)
    {
    case 1:
        prio = BELOW_NORMAL_PRIORITY_CLASS;
        break;

    case 2:
        prio = NORMAL_PRIORITY_CLASS;
        break;

    case 3:
        prio = ABOVE_NORMAL_PRIORITY_CLASS;
        break;

    case 4:
        prio = HIGH_PRIORITY_CLASS;
        break;

    case 5:
        prio = REALTIME_PRIORITY_CLASS;

    default:
        break;
    }

    SetPriorityClass(GetCurrentProcess(), prio);
}


void Platform::setThreadAffinity(uint64_t cpu_id)
{
    SetThreadAffinityMask(GetCurrentThread(), 1ULL << cpu_id);
}


void Platform::setThreadPriority(int priority)
{
    if (priority == -1) {
        return;
    }

    int prio = THREAD_PRIORITY_IDLE;
    switch (priority)
    {
    case 1:
        prio = THREAD_PRIORITY_BELOW_NORMAL;
        break;

    case 2:
        prio = THREAD_PRIORITY_NORMAL;
        break;

    case 3:
        prio = THREAD_PRIORITY_ABOVE_NORMAL;
        break;

    case 4:
        prio = THREAD_PRIORITY_HIGHEST;
        break;

    case 5:
        prio = THREAD_PRIORITY_TIME_CRITICAL;
        break;

    default:
        break;
    }

    SetThreadPriority(GetCurrentThread(), prio);
}

