# AlsaVol
This is a small CPython module to control master channel volume in ALSA.
Tested on Python 3.6. No other versions contemplated at the moment.

## Build & Install
This module requres ALSA and Python headers.
For DEB based repos, that is usually libasound2-dev and python3-dev.
With dependencies satisfied, execute:

```
python3 setup.py install
```

_**NOTE:** You may need to prefix `sudo` to install at system level or add `--user` flag to install for the executing user._

## Usage
```
import alsavol

alsavol.set_master_volume(80)
```
