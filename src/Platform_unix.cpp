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


#ifdef __FreeBSD__
#   include <sys/types.h>
#   include <sys/param.h>
#   include <sys/cpuset.h>
#   include <pthread_np.h>
#endif


#include <pthread.h>
#include <sched.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <uv.h>
#include <stdio.h>


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

#ifdef __FreeBSD__
typedef cpuset_t cpu_set_t;
#endif


static inline char *createVersionString()
{
    const size_t max = 160;

    char *buf = new char[max];
    int length = snprintf(buf, max, "%s/%s (Linux ", APP_NAME, APP_VERSION);

#   if defined(__x86_64__)
    length += snprintf(buf + length, max - length, "x86_64) libuv/%s OpenCL/%s", uv_version_string(), CL_VERSION_STRING);
#   else
    length += snprintf(buf + length, max - length, "i686) libuv/%s OpenCL/%s", uv_version_string(), CL_VERSION_STRING);
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
#   endif

    return buf;
}


void Platform::init()
{
    m_versionString = createVersionString();
}


void Platform::release()
{
    delete [] m_defaultConfigName;
    delete [] m_versionString;
}


void Platform::setProcessPriority(int priority)
{
}


void Platform::setThreadAffinity(uint64_t cpu_id)
{
    cpu_set_t mn;
    CPU_ZERO(&mn);
    CPU_SET(cpu_id, &mn);
    pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &mn);
}


void Platform::setThreadPriority(int priority)
{
    if (priority == -1) {
        return;
    }

    int prio = 19;
    switch (priority)
    {
    case 1:
        prio = 5;
        break;

    case 2:
        prio = 0;
        break;

    case 3:
        prio = -5;
        break;

    case 4:
        prio = -10;
        break;

    case 5:
        prio = -15;
        break;

    default:
        break;
    }

    setpriority(PRIO_PROCESS, 0, prio);

#   ifdef SCHED_IDLE
    if (priority == 0) {
        sched_param param;
        param.sched_priority = 0;

        if (sched_setscheduler(0, SCHED_IDLE, &param) != 0) {
            sched_setscheduler(0, SCHED_BATCH, &param);
        }
    }
#   endif
}
