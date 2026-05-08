# GameChat Pro

GameChat Pro is a next-generation, cross-platform gaming chat application built in C++ with Qt — designed to keep you connected with your squad in crystal-clear voice and lightning-fast text chat, no matter what game you're playing.

![Screenshot](https://raw.githubusercontent.com/jr551/FlareIRC/main/flareirc/screenshot.png)

## Features

### 🎙️ Low-Latency Voice Chat
- High-performance voice communication powered by the **Opus codec** for superior audio quality at minimal bandwidth.
- Ultra-low latency ensures real-time coordination in competitive multiplayer games.
- Adjustable bitrate and noise suppression settings for optimal performance on any connection.

### 💬 Discord-Style Text Chat
- Familiar server-based layout with a **sidebar** for quick navigation between servers and channels.
- Rich text formatting, inline media embeds, and threaded conversations.
- Real-time message delivery with typing indicators and read receipts.

### 🎮 Game Activity Detection
- Automatically detects what game you're playing and displays your **live activity status** to friends.
- Supports integration with Steam, Epic Games Store, and other major platforms.
- Custom status messages and rich presence for supported titles.

### 🎨 Custom Themes & Animated Emojis
- Fully customizable **theme engine** — choose from dark, light, or community-created themes.
- Support for **animated emojis** and custom emoji packs for personality-packed conversations.
- Per-server theme overrides so every community can have its own look and feel.

### 📺 Streaming Overlay Integration
- Built-in **streaming overlay** support for Twitch, YouTube, and OBS-compatible setups.
- Display your chat overlay directly on your stream with customizable positioning and styling.
- Viewer interaction widgets and chat alerts out of the box.

### 💎 Premium Subscriptions
Unlock the full potential of GameChat Pro with **Premium**:

| Plan         | Price          | Features                                      |
|--------------|----------------|-----------------------------------------------|
| **Monthly**  | $5.00/month    | Animated emojis, custom themes, overlay tools  |
| **Lifetime** | $50.00 one-time | Everything in Monthly, plus exclusive themes, priority support, and early access to new features |
*Prices in USD; taxes may vary by region*

## System Requirements

GameChat Pro is available on all major desktop platforms:

- **Windows** 10/11 (64-bit)
- **macOS** 12+ (Intel & Apple Silicon)
- **Linux** (Ubuntu, Fedora, Arch, and other major distributions)

## Building from Source

### Prerequisites
- **Qt 5.15+** or **Qt 6.x**
- **CMake** 3.16+
- A C++17 compatible compiler (GCC 9+, Clang 10+, MSVC 2019+)
- **Opus** library for voice chat functionality

### Clone & Build

```bash
git clone https://github.com/jr551/FlareIRC.git
cd FlareIRC
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release
```

## Downloads

Pre-built binaries are available for all platforms:

- 🪟 [Windows Installer](https://github.com/jr551/FlareIRC/releases/latest) (`.exe`)
- 🍎 [macOS DMG](https://github.com/jr551/FlareIRC/releases/latest) (`.dmg`)
- 🐧 [Linux AppImage](https://github.com/jr551/FlareIRC/releases/latest) (`.AppImage`)

---

*GameChat Pro — Play together, stay connected.*