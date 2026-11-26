# Mochi

Mochi is a tiny desk companion for the M5StickS3.

## Hardware

- M5Stack StickS3 (ESP32-S3)

## Setup

The project builds with [PlatformIO](https://platformio.org/), installed into a Python virtual environment in `.venv/`.

First time only:

```sh
python3 -m venv .venv          # built with Python 3.11
source .venv/bin/activate
pip install platformio
```

In each new terminal, activate the environment so `pio` is on your PATH:

```sh
source .venv/bin/activate
```

Then:

```sh
pio run -t upload    # build and flash
pio device monitor   # open the serial monitor
```

## Commands

Helper scripts live in `scripts/` and can be run from any directory.

| Command | What it does |
| --- | --- |
| `scripts/check-warnings.sh` | Clean build, then reports any compiler warnings. Exits non-zero if the build fails or anything warns. |
| `scripts/convert-assets.sh` | Turns every PNG in `assets/` into a C header in `src/`. Requires `xxd`. Run it after adding or changing an image. |
