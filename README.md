[![Build Status](https://travis-ci.org/arnesson/xrig.svg?branch=master)](https://travis-ci.org/arnesson/xrig)

# Xrig
Xrig is a high performance cryptonight miner for AMD cards. Optimized for large-scale use of RX Vega.

GPU mining based on [Wolf9466](https://github.com/OhGodAPet) and [psychocrypt](https://github.com/psychocrypt) code. Forked with love from [XMRig AMD](https://github.com/xmrig/xmrig-amd).
<!--
<img src="https://i.imgur.com/TFncsi7.png" width="696" >
-->
## Features
* High performance
* Optimized for large-scale use of RX Vega
* Rich API
* Hardware monitoring
* OverdriveN capabilities (replaces Wattman and OverdriveNTool)
* High level of auto configuration
* Windows and Linux support
* 1% dev donation

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
            {"clock": 852,  "vddc": 0.800},
            {"clock": 991,  "vddc": 0.900},
            {"clock": 1138, "vddc": 0.950},
            {"clock": 1269, "vddc": 1.000},
            {"clock": 1312, "vddc": 1.050},
            {"clock": 1474, "vddc": 1.100},
            {"clock": 1538, "vddc": 1.150},
            {"clock": 1590, "vddc": 1.200}
        ],
        "memory": [
            {"clock": 167, "vddc": 0.800},
            {"clock": 500, "vddc": 0.800},
            {"clock": 700, "vddc": 0.900},
            {"clock": 800, "vddc": 0.950}
        ],
        "target_temperature": 75
    }
}
```
