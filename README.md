# Rogue: Exploring the Dungeons of Doom

[![License](https://img.shields.io/badge/license-BSD-blue.svg)](LICENSE.TXT)

**Rogue** is the original graphical dungeon-crawling adventure game that spawned an entire genre. This is version 5.4.4, a classic roguelike where you explore procedurally generated dungeons, fight monsters, collect treasure, and attempt to retrieve the Amulet of Yendor.

**Original Authors:** Michael Toy, Ken Arnold, and Glenn Wichman (1980-1983, 1985, 1999)

---

## ⚠️ About This Repository ⚠️

**November 2025**:

I want to express my sincere appreciation to everyone who has contributed to this repository, attempted to fix issues, and forked the project over the years. When I originally created this repository in [July 2016](https://github.com/Davidslv/rogue/releases/tag/5.4.4), I was young and fascinated by this classic game. My primary intention was to archive the codebase for learning purposes, and I never expected the community engagement that followed.

**Important**: I am not one of the original authors of Rogue. I am simply maintaining this repository as an archive of the original game.

**Repository Policy**:
- The **`main` branch** will remain unchanged to preserve the game exactly as it was in 1999. This ensures the original codebase remains available in its historical state.
- For modernization efforts, bug fixes, and improvements, please use the branch: **[modern-rogue](https://github.com/Davidslv/rogue/tree/modern-rogue)**
- You are welcome to fork this repository and make your own modifications. Many have done so over the years, and I encourage continued development in your own forks.

Thank you for your interest in preserving and improving this classic game! ❤️

---

## Table of Contents

- [Quick Start](#quick-start)
- [Prerequisites](#prerequisites)
- [Building from Source](#building-from-source)
- [Running the Game](#running-the-game)
- [Project Structure](#project-structure)
- [Development Guide](#development-guide)
- [Contributing](#contributing)
- [Troubleshooting](#troubleshooting)
- [Resources](#resources)

---

## Quick Start

```bash
# Configure and build
./configure
make

# Run the game
./rogue
```

**Note**: The executable name defaults to `rogue`, but may be different if configured with `--with-program-name`. Check the output of `make` to see the actual executable name.

**Note**: If you encounter compilation errors, especially related to ncurses compatibility, see [BUILD_ISSUES.md](BUILD_ISSUES.md) for known issues and workarounds.

---

## Prerequisites

### Required

- **C Compiler**: GCC or Clang (C89/C90 compatible)
- **make**: Build automation tool (usually pre-installed)
  - **Linux**: Usually pre-installed, or `sudo apt-get install build-essential` (Debian/Ubuntu)
  - **macOS**: Included with Xcode Command Line Tools (`xcode-select --install`)
  - **FreeBSD**: `pkg install gmake` (or use `gmake` instead of `make`)
- **ncurses library**: For terminal-based graphics
  - **Linux**: `sudo apt-get install libncurses5-dev` (Debian/Ubuntu)
  - **Linux**: `sudo yum install ncurses-devel` (RHEL/CentOS/Fedora)
  - **macOS**: `brew install ncurses` (Homebrew)
  - **FreeBSD**: `pkg install ncurses`

### Optional (for building from source)

- **Autotools**: autoconf, automake, m4 (needed if `configure` script doesn't exist)
  - **Linux**: `sudo apt-get install autoconf automake m4` (Debian/Ubuntu)
  - **Linux**: `sudo yum install autoconf automake m4` (RHEL/CentOS/Fedora)
  - **macOS**: Usually pre-installed with Xcode Command Line Tools, or `brew install autoconf automake`
  - **FreeBSD**: `pkg install autoconf automake m4`
  - **Note**: If the `configure` script already exists in the repository, you don't need these tools

### Optional (for building documentation)

- **Documentation tools**: groff/nroff, tbl, colcrt, sed (for generating man pages and docs)
  - **Linux**: Usually pre-installed, or `sudo apt-get install groff` (Debian/Ubuntu)
  - **macOS**: Usually pre-installed
  - **Note**: Documentation can be built later with `make` if these tools are available
  - **Note**: Generated documentation (man pages, HTML, etc.) is adapted to match the actual codebase outcomes and build configuration (e.g., executable name, scoreboard file location)

### Platform Support

This codebase supports multiple platforms:
- **Unix-like systems** (Linux, macOS, FreeBSD, etc.)
- **Windows** (via Visual Studio project files or MinGW/MSYS2)
- **DOS** (DJGPP)
- **Cygwin**

---

## Building from Source

### Standard Build (Recommended)

The project uses Autotools for configuration. The build process depends on whether the `configure` script already exists:

**If `configure` script exists** (most common case):
```bash
# Configure the build system
./configure

# Compile
make

# Optional: Install system-wide (requires root)
sudo make install
```

**If `configure` script does NOT exist** (e.g., fresh git clone without generated files):
```bash
# Generate configure script (requires autoconf, automake, m4)
autoreconf -fiv

# Configure the build system
./configure

# Compile
make

# Optional: Install system-wide (requires root)
sudo make install
```

**Note**: Most source distributions include the `configure` script, so you typically only need `autoreconf` if you're building directly from a git repository that doesn't include generated files.

**Note**: The executable name and other build outputs are determined by the `configure` script based on the codebase configuration. If you're using `Makefile.std` directly (manual build), the default executable name is `rogue54`, whereas `configure` defaults to `rogue`. Always check the actual output of your build process to confirm the executable name.

### Configure Options

The `configure` script supports several options:

```bash
# Enable wizard mode (debug/cheat mode)
./configure --enable-wizardmode

# Set custom scoreboard file location
./configure --enable-scorefile=/path/to/scoreboard.scr

# Disable scoreboard
./configure --enable-scorefile=no

# Set custom program name
./configure --with-program-name=myrogue

# Install as setgid (for shared scoreboard)
./configure --enable-setgid=games

# See all options
./configure --help
```

### Manual Build (Without Autotools)

If you prefer to build manually or the configure script fails:

**Option 1: Using Makefile.std**
```bash
# Build using the standard Makefile
make -f Makefile.std

# Note: This creates 'rogue54' by default (see Makefile.std to change)
```

**Option 2: Direct compilation**
```bash
# Compile directly (may need additional defines)
gcc -O2 -o rogue *.c -lcurses

# Or with more defines (see Makefile.std for full list):
gcc -O2 -DALLSCORES -DSCOREFILE=\"rogue.scr\" -DLOCKFILE=\"rogue.lck\" -o rogue *.c -lcurses
```

**Note**:
- Manual builds may require additional defines. See `Makefile.std` for reference.
- The executable name may differ (`rogue` vs `rogue54` depending on build method).
- You may need to adjust include paths if ncurses is in a non-standard location.

### Windows Build

#### Using Visual Studio

1. **Install PDCurses**:
   - Download PDCurses from https://pdcurses.org/
   - Extract to a directory (e.g., `C:\pdcurses`)
   - Build PDCurses library following its instructions

2. **Configure Visual Studio project**:
   - Open `rogue54.sln` in Visual Studio
   - Update include/library paths in project settings to point to your PDCurses installation
   - Ensure PDCurses library is linked (check project properties → Linker → Input)

3. **Build the solution**: Build → Build Solution (or press F7)

**Alternative**: If PDCurses is in a peer directory (`../pdcurses/`), the project may work without modification.

#### Using MinGW/MSYS2

```bash
# Install ncurses via MSYS2
pacman -S mingw-w64-x86_64-ncurses

# Configure and build
./configure
make
```

**Note**: For MinGW/MSYS2, you may need to use `mingw32-make` instead of `make` depending on your installation.

---

## Running the Game

### Basic Usage

```bash
# Start a new game
./rogue

# Restore from a saved game
./rogue ~/rogue.save

# View high scores
./rogue -s

# Test death screen (demo mode)
./rogue -d
```

### In-Game Commands

- **`?`** - Show help/command list
- **`/`** - Identify objects on screen
- **Arrow keys** or **h/j/k/l** - Move
- **`.`** - Wait/rest
- **`i`** - Show inventory
- **`e`** - Eat food
- **`q`** - Quaff potion
- **`r`** - Read scroll
- **`w`** - Wield weapon
- **`W`** - Wear armor
- **`t`** - Throw object
- **`z`** - Zap wand/staff
- **`Q`** - Quit game

### Environment Variables

```bash
# Set game options via environment
export ROGUEOPTS="name=YourName,terse,jump"

# Wizard mode: set dungeon seed
export SEED=12345
./rogue ""  # Empty string as first arg enables wizard mode
```

---

## Project Structure

### Core Files

```
rogue.h              # Main header with data structures and defines
extern.h             # External declarations and platform defines
main.c               # Entry point, initialization, main game loop
command.c            # Command processing and input handling
```

### Game Systems

**Note**: All source files are in the root directory. The structure below is logical grouping, not actual directory structure.

**Combat System**:
```
fight.c          # Combat mechanics
weapons.c        # Weapon types and properties
armor.c          # Armor types and properties
```

**Monster System**:
```
monsters.c       # Monster definitions and stats
chase.c          # Monster AI and pathfinding
```

**Item System**:
```
potions.c        # Potion types and effects
scrolls.c        # Scroll types and effects
rings.c          # Ring types and effects
sticks.c         # Wand/staff types and effects
things.c         # General item handling
```

**Dungeon Generation**:
```
rooms.c          # Room generation
passages.c       # Corridor generation
new_level.c      # Level creation and initialization
```

**User Interface**:
```
io.c             # Input/output handling
list.c           # Inventory and object lists
rip.c            # Death screen
```

### Supporting Systems

```
daemon.c             # Background processes (monster movement, hunger, etc.)
daemons.c            # Daemon management
move.c               # Player and monster movement
pack.c               # Inventory management
save.c               # Save/load game state
state.c              # Game state management
init.c               # Initialization routines
extern.c             # Global variable definitions
```

### Platform Abstraction

```
mach_dep.c           # Machine-dependent code detection
mdport.c             # Platform abstraction layer
```

### Build System

```
configure.ac         # Autoconf configuration
Makefile.in          # Makefile template
config.h.in          # Config header template
```

---

## Development Guide

### Code Style

This codebase follows classic C (pre-C99) conventions:

- Uses `register` keyword for frequently accessed variables
- Custom macros for control flow (`when`, `otherwise`, `on()`, etc.)
- Linked lists for dynamic data structures
- Bit flags for object/monster states
- Function declarations in headers, definitions in `.c` files

### Key Data Structures

#### `THING` (union)
Represents both monsters and objects:
```c
union thing {
    struct {  // Monster/player
        coord t_pos;
        struct stats t_stats;
        short t_flags;
        // ...
    } _t;
    struct {  // Object
        int o_type;
        int o_which;
        int o_hplus, o_dplus;
        // ...
    } _o;
};
```

#### `PLACE`
Represents a map cell:
```c
typedef struct {
    char p_ch;        // Character to display
    char p_flags;     // Flags (seen, passage, etc.)
    THING *p_monst;   // Monster at this location
} PLACE;
```

### Game Loop Flow

```
main()
  ├─> Initialize (curses, player, objects)
  ├─> new_level()      # Generate first level
  ├─> Start daemons    # Background processes
  └─> playit()
       └─> while(playing)
            └─> command()
                 ├─> do_daemons(BEFORE)
                 ├─> Read input
                 ├─> Execute command
                 ├─> do_daemons(AFTER)
                 └─> Monster movement
```

### Daemons and Fuses

**Daemons** are background processes that run every turn:
- `runners()` - Monster movement
- `doctor()` - Health regeneration
- `stomach()` - Hunger system
- `swander()` - Wandering monsters

**Fuses** are one-time delayed actions:
- Used for temporary effects (haste, confusion, etc.)

### Adding New Features

1. **New Monster Type**:
   - Add entry to `monsters[]` array in `monsters.c`
   - Update monster generation logic in `new_level.c`

2. **New Item Type**:
   - Add type constant to `rogue.h`
   - Add info structure (e.g., `pot_info[]` for potions)
   - Implement effect in corresponding file (e.g., `potions.c`)

3. **New Command**:
   - Add case in `command()` function in `command.c`
   - Implement handler function

### Debugging

#### Enable Wizard Mode

```bash
./configure --enable-wizardmode
make
./rogue ""  # Empty string enables wizard password prompt
```

Wizard mode provides:
- See all monsters (`SEEMONST` flag)
- Set dungeon seed via `SEED` environment variable
- Debug commands (see `wizard.c`)

#### Compile with Debug Symbols

```bash
./configure CFLAGS="-g -O0"
make
gdb ./rogue
```

### Testing

```bash
# Test death screen
./rogue -d

# Test scoreboard
./rogue -s

# Test save/restore
./rogue
# Play a bit, save (S command), quit
./rogue ~/rogue.save  # Should restore
```

---

## Contributing

We welcome contributions! Here's how to get started:

### Getting Started

1. **Fork the repository** (if using git)
2. **Create a branch** for your changes
3. **Make your changes** following the code style
4. **Test thoroughly** - play the game, test edge cases
5. **Submit a pull request** or patch

### Contribution Guidelines

- **Code Style**: Follow existing conventions (see [Development Guide](#development-guide))
- **Testing**: Test on multiple platforms if possible
- **Documentation**: Update relevant comments/docs
- **Commits**: Write clear commit messages
- **Scope**: Keep changes focused and atomic

### Areas Needing Help

- **Bug fixes**: Check for known issues or test edge cases
- **Platform support**: Improve Windows/DOS/Cygwin compatibility
- **Code cleanup**: Modernize while maintaining compatibility
- **Documentation**: Improve code comments and user docs
- **Performance**: Optimize hot paths
- **Accessibility**: Improve terminal compatibility

### Reporting Bugs

When reporting bugs, please include:
- Platform and OS version
- Compiler and version
- Steps to reproduce
- Expected vs. actual behavior
- Any error messages

---

## Troubleshooting

**Note**: For detailed information about known build issues, especially on modern systems, see [BUILD_ISSUES.md](BUILD_ISSUES.md).

### Build Issues

**Problem**: `configure: error: curses library not found`

**Solution**: Install ncurses development package:
```bash
# Debian/Ubuntu
sudo apt-get install libncurses5-dev

# RHEL/CentOS/Fedora
sudo yum install ncurses-devel

# macOS
brew install ncurses
```

**Problem**: `autoreconf: command not found` or `autoconf: command not found`

**Solution**: Install autotools (only needed if `configure` script doesn't exist):
```bash
# Debian/Ubuntu
sudo apt-get install autoconf automake m4

# RHEL/CentOS/Fedora
sudo yum install autoconf automake m4

# macOS (usually pre-installed with Xcode)
xcode-select --install
# Or via Homebrew:
brew install autoconf automake

# FreeBSD
pkg install autoconf automake m4
```

**Note**: If the `configure` script already exists, you don't need these tools. Only run `autoreconf` if you're building from a git repository without generated files.

**Problem**: Compilation errors about undefined functions

**Solution**: Ensure `configure` was run successfully and `config.h` exists:
```bash
./configure
make clean
make
```

**Problem**: Compilation errors about incomplete type 'WINDOW' or `curscr->_cury` / `curscr->_curx`

**Solution**: This is a known compatibility issue with modern ncurses. The codebase attempts to access internal ncurses structure members that are not available in modern ncurses libraries. See [BUILD_ISSUES.md](BUILD_ISSUES.md) for detailed information about this issue and potential fixes.

**Problem**: `make: command not found`

**Solution**: Install make:
```bash
# Debian/Ubuntu
sudo apt-get install build-essential

# RHEL/CentOS/Fedora
sudo yum groupinstall "Development Tools"

# macOS
xcode-select --install

# FreeBSD (use gmake)
pkg install gmake
# Then use: gmake instead of make
```

**Problem**: `configure: error: cannot find install-sh or install.sh`

**Solution**: The `install-sh` script should be in the repository. If missing, you may need to regenerate it:
```bash
autoreconf -fiv
```

**Problem**: Documentation build fails (missing groff/nroff/tbl)

**Solution**: Documentation tools are optional. The game will build without them, but man pages won't be generated:
```bash
# Install documentation tools (optional)
# Debian/Ubuntu
sudo apt-get install groff

# RHEL/CentOS/Fedora
sudo yum install groff

# Or skip documentation generation - the game will still build
```

### Runtime Issues

**Problem**: Screen is too small

**Solution**: Rogue requires at least 24x80 terminal. Resize your terminal or use a larger font.

**Problem**: Terminal doesn't support colors/features

**Solution**: The game will auto-detect terminal capabilities. For best experience, use a modern terminal emulator (xterm, gnome-terminal, iTerm2, etc.).

**Problem**: Save file corruption

**Solution**: Save files are encrypted. Don't edit them manually. If corrupted, delete `~/rogue.save` and start fresh.

**Problem**: Scoreboard permission errors

**Solution**: If using setgid installation:
```bash
sudo chgrp games rogue.scr
sudo chmod 664 rogue.scr
```

### Platform-Specific

**Windows (MinGW)**: Ensure PDCurses is properly linked. Check `LIBS` in Makefile.

**macOS**: If using Homebrew ncurses, you may need to specify include/library paths:
```bash
# For Intel Macs (Homebrew in /usr/local)
./configure CPPFLAGS="-I/usr/local/include" LDFLAGS="-L/usr/local/lib"

# For Apple Silicon Macs (Homebrew in /opt/homebrew)
./configure CPPFLAGS="-I/opt/homebrew/include" LDFLAGS="-L/opt/homebrew/lib"

# Or let pkg-config find it (if available)
./configure PKG_CONFIG_PATH="/opt/homebrew/lib/pkgconfig"
```

**Alternative**: If ncurses is installed but not found, you can also try:
```bash
# Check where ncurses is installed
brew --prefix ncurses

# Use that path in configure
./configure CPPFLAGS="-I$(brew --prefix ncurses)/include" LDFLAGS="-L$(brew --prefix ncurses)/lib"
```

**Cygwin**: Ensure you're using the Cygwin version of ncurses, not a Windows port.

---

## Resources

### Documentation

- **In-game help**: Press `?` during gameplay
- **Man page**: `man rogue` (after installation)
- **Game guide**: See `rogue.doc` (generated from `rogue.me.in`)

### External Resources

- **Original Rogue**: The game that started it all
- **Roguelike genre**: This game inspired NetHack, Angband, and many others
- **Roguelike development**: Great learning resource for game programming

### Related Projects

- **NetHack**: Spiritual successor with more features
- **Brogue**: Modern roguelike with beautiful ASCII graphics
- **DCSS**: Dungeon Crawl Stone Soup, another modern roguelike

---

## License

This project is licensed under a BSD-style license. See [LICENSE.TXT](LICENSE.TXT) for details.

**Copyright (C) 1980-1983, 1985, 1999 Michael Toy, Ken Arnold and Glenn Wichman**

Portions based on work by:
- Nicholas J. Kisseberth (state.c, mdport.c)
- David Burren (xcrypt.c)

---

## Acknowledgments

This is the classic Rogue game that defined the roguelike genre. Thanks to the original authors for creating this timeless game, and to all contributors who have helped maintain and improve it over the years.

**Happy dungeon crawling!**

---

*For questions, issues, or contributions, please refer to the project's issue tracker or contact the maintainers.*

