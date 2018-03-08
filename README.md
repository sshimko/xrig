[![Build Status](https://travis-ci.org/arnesson/xrig.svg?branch=master)](https://travis-ci.org/arnesson/xrig)

# Xrig
Xrig is a high performance cryptonight miner for AMD cards. Designed for large-scale use of RX Vega.

GPU mining based on [Wolf9466](https://github.com/OhGodAPet) and [psychocrypt](https://github.com/psychocrypt) code. Forked with love from [XMRig AMD](https://github.com/xmrig/xmrig-amd).
<!--
<img src="https://i.imgur.com/TFncsi7.png" width="696" >
-->
## Features
* High performance
* Designed for large-scale use of RX Vega, but will run any AMD card
* High level of automation necessary for managing many cards
* Rich API
* Hardware monitoring (fans, temperature, clock speeds, performance levels)
* OverdriveN capabilities (set your under/overclock profile in config.json - replaces Wattman and OverdriveNTool)
* Fixes the different shenanigans of mining on the Vega's (e.g. the "underclock toggle" and gpu reset)
* Windows and Linux support
* Pre-compiled binary has 1% dev donation, donation starts at boot rather than after x minutes

## Work-in-progress
* Option(s) for automatic fine-tuning of each individual card during mining. This should maximize the utilization of each card and increase the hashrate over time

## Usage

### Command line options
```
  -a, --algo=ALGO           cryptonight (default) or cryptonight-lite
  -o, --url=URL             URL of mining server
  -u, --user=USERNAME       username for mining server
  -p, --pass=PASSWORD       password for mining server
  -k, --keepalive           send keepalive to prevent timeout (needs pool support)
      --intensity=N         thread intensity
      --platform-index=N    OpenCL platform index
      --colors              enable colored output
  -b, --background          run the miner in the background
  -c, --config=FILE         load a JSON-format configuration file
  -l, --log=FILE            log all output to a file
      --nicehash            enable nicehash support
      --port=N              port for the miner API
      --token=T             access token for API
      --id=ID               miner id (defaults to machine name)
  -h, --help                display this help and exit
  -v, --version             output version information and exit
```

### Config file
Sample config for an array of Vega's:
```json
{
    "algo": "cryptonight",
    "intensity": 1932,
    "platform_index": 0,
    "pools": [
        {
            "url": "pool.monero.hashvault.pro:5555",
            "user": "",
            "pass": "x"
        }
    ],
    "api": {
        "port": 4444
    },
    "profile": {
        "system": [
            {"clock": 852,  "vddc": 0.9},
            {"clock": 991,  "vddc": 0.9},
            {"clock": 1084, "vddc": 0.9},
            {"clock": 1138, "vddc": 0.9},
            {"clock": 1150, "vddc": 0.9},
            {"clock": 1202, "vddc": 0.9},
            {"clock": 1350, "vddc": 0.8},
            {"clock": 1350, "vddc": 0.8}
        ],
        "memory": [
            {"clock": 167, "vddc": 0.8},
            {"clock": 500, "vddc": 0.8},
            {"clock": 700, "vddc": 0.9},
            {"clock": 950, "vddc": 0.9}
        ],
        "target_temperature": 75,
        "power_limit": 0
    }
}
```

You can also configure the threads manually as usual:
```json
{
    "algo": "cryptonight",
    "platform_index": 0,
    "pools": [
        {
            "url": "pool.monero.hashvault.pro:5555",
            "user": "",
            "pass": "x"
        }
    ],
    "api": {
        "port": 4444
    },
    "threads": [
        {"index": 0, "intensity": 1932},
        {"index": 0, "intensity": 1932}
    ],
    "profile": ...
}
```

### Rich API in JSON format

Example output:
```json
{
    "id": "DESKTOP-TEST",
    "version": "Xrig/0.8.0 (Windows NT 10.0; Win64; x64) libuv/1.14.1 OpenCL/2.0 libmicrohttpd/0.9.58 msvc/2017",
    "algo": "cryptonight",
    "uptime": 14729.0,
    "hashrate_10s": 10654.67,
    "hashrate_60s": 10656.87,
    "hashrate_15m": 10651.38,
    "hashrate_max": 11032.48,
    "gpus": [
        {
            "bus_id": 3,
            "adapter_index": 29,
            "device_name": "687F:C3",
            "temperature": 75,
            "core_clock": 1269,
            "memory_clock": 950,
            "fan_speed": 1718,
            "profile": {
                "system": [
                    {"clock": 852,  "vddc": 0.9},
                    {"clock": 991,  "vddc": 0.9},
                    {"clock": 1084, "vddc": 0.9},
                    {"clock": 1138, "vddc": 0.9},
                    {"clock": 1150, "vddc": 0.9},
                    {"clock": 1202, "vddc": 0.9},
                    {"clock": 1350, "vddc": 0.8},
                    {"clock": 1350, "vddc": 0.8}
                ],
                "memory": [
                    {"clock": 167, "vddc": 0.8},
                    {"clock": 500, "vddc": 0.8},
                    {"clock": 700, "vddc": 0.9},
                    {"clock": 950, "vddc": 0.9}
                ],
                "target_temperature": 75,
                "power_limit": -10
            },
            "threads": [
                {
                    "intensity": 1932,
                    "hashrate_10s": 853.34,
                    "hashrate_60s": 855.62,
                    "hashrate_15m": 854.76
                },
                {
                    "intensity": 1932,
                    "hashrate_10s": 863.47,
                    "hashrate_60s": 858.88,
                    "hashrate_15m": 855.3
                }
            ],
            "hashrate_10s": 1716.81,
            "hashrate_60s": 1714.5,
            "hashrate_15m": 1710.06
        },
        {
            ...
        },
        {
            ...
        },
        {
            ...
        },
        {
            ...
        },
        {
            ...
        },
        {
            ...
        },
    ],
    "results": {
        "diff_current": 526795,
        "shares_good": 308,
        "shares_total": 321,
        "avg_time": 48,
        "hashes_total": 152108212,
        "best": [
            ...
        ],
        "error_log": []
    },
    "connection": {
        "pool": "cryptonight.eu.nicehash.com:3355",
        "user": "******************************xR7M",
        "uptime": 7056,
        "ping": 84,
        "failures": 2,
        "error_log": []
    }
}
```
