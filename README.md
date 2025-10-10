# Computer Access Controller

A parental control application for Windows that restricts computer access to specific hours and days. The application allows administrators to define time schedules and automatically enforces them by monitoring system time and shutting down the computer when the allowed time expires.

## Features

- **Time-based Access Control**: Define specific time slots for each day of the week
- **Multiple Time Slots**: Configure multiple allowed time periods per day
- **Real-time Monitoring**: Continuously checks current time against configured schedule
- **Automatic Warnings**: Alerts users when their access time is about to expire
- **Automatic Shutdown**: Safely shuts down the computer when access time ends
- **User-friendly GUI**: Easy-to-use graphical interface built with wxWidgets
- **Schedule Persistence**: Save and load schedule configurations

## Tech Stack

- **Language**: C++17
- **GUI Framework**: wxWidgets
- **System Control**: Win32 API
- **Build System**: CMake
- **IDE**: CLion (or any CMake-compatible IDE)
- **Platform**: Windows

## Requirements

- Windows OS (tested on Windows 10)
- CMake 3.15 or higher
- wxWidgets 3.0 or higher
- C++17 compatible compiler (MSVC, MinGW, or Clang)
- Administrator privileges (required for system shutdown)

## Building the Application

### Installing wxWidgets

1. Download wxWidgets from https://www.wxwidgets.org/downloads/
2. Build wxWidgets or use prebuilt binaries
3. Set `wxWidgets_ROOT_DIR` environment variable to wxWidgets installation path

### Building with CMake

```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

### Building with CLion

1. Open the project folder in CLion
2. CLion will automatically detect CMakeLists.txt
3. Configure CMake settings if needed
4. Build the project (Ctrl+F9)

## Usage

### For Administrators

1. Launch the application with administrator privileges
2. Select a day from the dropdown menu
3. Enable access control for that day using the checkbox
4. Add allowed time slots:
   - Set start time (hour and minute)
   - Set end time (hour and minute)
   - Click "Add Slot"
5. Remove unwanted slots by selecting them and clicking "Remove Selected"
6. Repeat for each day of the week
7. Click "Save Schedule" to save the configuration to a file
8. Enable "Real-time Monitoring" to start enforcing restrictions

### Monitoring Behavior

When monitoring is enabled:
- The application checks the current time every minute
- If the current time is within an allowed slot, access continues
- Users receive a warning 5 minutes before their time expires
- When time expires, a warning appears with a 60-second countdown
- The system automatically shuts down after the countdown

### Schedule File Format

Schedule files (.dat) use a simple text format:
```
# day enabled numSlots [startHour startMinute endHour endMinute]...
# day: 0=Sunday, 1=Monday, ..., 6=Saturday

0 1 1 8 0 20 0
1 1 1 8 0 20 0
2 1 1 8 0 20 0
3 1 1 8 0 20 0
4 1 1 8 0 20 0
5 1 2 10 0 14 0 18 0 22 0
6 1 1 10 0 22 0
```

## Project Structure

```
cpp-computer-access-controller/
├── CMakeLists.txt          # Build configuration
├── README.md               # This file
└── src/
    ├── main.cpp            # Application entry point
    ├── MainFrame.h/cpp     # Main GUI window and admin interface
    ├── ScheduleManager.h/cpp     # Schedule data management
    ├── TimeChecker.h/cpp   # Time monitoring logic
    └── SystemController.h/cpp    # System control (shutdown, warnings)
```

## How It Works

1. **Schedule Management**: `ScheduleManager` stores and manages time restrictions for each day
2. **Time Checking**: `TimeChecker` periodically compares current system time with allowed schedules
3. **System Control**: `SystemController` uses Win32 API to display warnings and shutdown the system
4. **User Interface**: `MainFrame` provides a wxWidgets GUI for configuration

## Security Considerations

- The application requires administrator privileges to shutdown the system
- Schedule files should be stored in a protected location
- Users should not have write access to the application or schedule files
- For maximum security, run the application as a Windows service (future enhancement)

## Limitations

- Windows only (uses Win32 API for system control)
- Requires the application to be running for monitoring to work
- Users with administrator access can terminate the application
- Time changes at the system level can bypass restrictions

## Future Enhancements

- Run as Windows service for background monitoring
- Password protection for administrator settings
- User login tracking and reporting
- Network time synchronization to prevent time manipulation
- Support for user-specific schedules
- Grace period configuration
- Holiday/vacation mode

## License

This project is provided as-is for educational and parental control purposes.

## Contributing

Contributions are welcome! Please ensure code follows the existing style and includes appropriate documentation.