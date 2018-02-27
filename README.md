# Xrig
Xrig is a high performance cryptonight miner for AMD cards. Optimized for large-scale use of RX Vega.

GPU mining based on [Wolf9466](https://github.com/OhGodAPet) and [psychocrypt](https://github.com/psychocrypt) code. Forked from [XMRig AMD](https://github.com/xmrig/xmrig-amd)
<!--
<img src="https://i.imgur.com/TFncsi7.png" width="696" >
-->
## Features
* High performance
* Optimized for large-scale use of RX Vega
* Powerful API
* Hardware monitoring
* Built-in OverdriveN capabilities
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
      --no-color            disable colored output
  -b, --background          run the miner in the background
  -c, --config=FILE         load a JSON-format configuration file
  -l, --log-file=FILE       log all output to a file
      --nicehash            enable nicehash support
      --print-time=N        print hashrate report every N seconds
      --port=N              port for the miner API
      --api-access-token=T  access token for API
      --id=ID               miner id (defaults to machine name)
  -h, --help                display this help and exit
  -v, --version             output version information and exit
```

### Config file.
Sample config for an array of Vega's:
```json
{
    "algo": "cryptonight",
    "platform-index": 0,
    "intensity": 1932,
    "pools": [
        {
            "url": "pool.monero.hashvault.pro:5555",
            "user": "",
            "pass": "x"
        }
    ],
    "api": {
        "port": 4444
    }
}
```
