# FlareIRC

A desktop IRC client written in C++ with Qt4, originally built in 2009-2010.
It ran cross-platform on Windows, macOS, and Linux. This repository is an
archived snapshot pulled from old backups — it's shared as-is for historical
interest, not actively maintained.

![Screenshot](https://raw.githubusercontent.com/jr551/FlareIRC/main/flareirc/screenshot.png)

## Features

- Multi-server / multi-channel tabbed chat window
- Private message tabs
- Nickname identification (NickServ/AuthServ auto-identify with saved
  username/password)
- Configurable default nickname and connection options
- Basic scripting hook (`scriptmanager`/`ScriptManager`, minimal/incomplete)
- Native look on Windows (`.rc`/`.ico`) and macOS (`.icns`/`.app` bundle)

## Building

FlareIRC is a Qt4 project (`QT += network webkit script`), built with
`qmake`. Qt4 and its WebKit module are long out of support, so building
from source on a modern system will likely require installing a legacy
Qt4 toolchain (e.g. via a package manager's archived formula or a
container with an old distro).

```
cd flareirc
qmake FlareIRC.pro
make
```

Pre-built archives from the original release are included in this repo
for reference:

- `windows_release.7z` — Windows build
- `old_mac_release.app.7z` — old macOS `.app` build

These are historical binaries, not signed or maintained releases — treat
them as archival artifacts rather than something to run untrusted.

## Status

This project has not been updated in over a decade and is not under active
development. It's kept public as a snapshot of an early hobby project.

## License

No license file is currently included in this repository. Until one is
added, all rights are reserved by default — please contact the repo owner
before reusing this code.
