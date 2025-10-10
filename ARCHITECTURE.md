# Architecture Documentation

This document describes the architecture and design of the Computer Access Controller application.

## Overview

The application follows a modular architecture with clear separation of concerns:
- **Presentation Layer**: wxWidgets-based GUI (MainFrame)
- **Business Logic**: Time checking and schedule management
- **System Interface**: Windows API integration for system control

## Component Diagram

```
┌─────────────────────────────────────────────────────────┐
│                      MainFrame (GUI)                     │
│  - User interface for schedule configuration            │
│  - Admin panel for settings                             │
│  - Status monitoring display                            │
└───────────┬─────────────────────────────────┬───────────┘
            │                                 │
            ▼                                 ▼
┌───────────────────────┐        ┌───────────────────────┐
│   ScheduleManager     │        │     TimeChecker       │
│  - Store schedules    │◄───────┤  - Monitor time       │
│  - Load/Save configs  │        │  - Check permissions  │
│  - Validate times     │        │  - Trigger actions    │
└───────────────────────┘        └───────────┬───────────┘
                                              │
                                              ▼
                                  ┌───────────────────────┐
                                  │   SystemController    │
                                  │  - Show warnings      │
                                  │  - Shutdown system    │
                                  │  - Win32 API calls    │
                                  └───────────────────────┘
```

## Core Components

### 1. MainFrame (MainFrame.h/cpp)

**Purpose**: Provides the graphical user interface for administrators to configure schedules.

**Key Responsibilities**:
- Display day-of-week schedule editor
- Allow adding/removing time slots
- Save/load schedule configurations
- Control monitoring on/off
- Display real-time status

**Key Methods**:
- `CreateUI()`: Builds the wxWidgets interface
- `LoadDaySchedule()`: Loads schedule for selected day
- `SaveDaySchedule()`: Saves current day's configuration
- `UpdateTimeSlotList()`: Refreshes time slot display
- `OnMonitoringChanged()`: Toggles monitoring mode
- `OnTimer()`: Periodic callback for status updates

**UI Components**:
- Day selector (wxChoice)
- Enable/disable checkbox per day
- Time slot list (wxListCtrl)
- Time entry spinners (wxSpinCtrl)
- Add/Remove buttons
- Save/Load buttons
- Monitoring toggle
- Status text display

### 2. ScheduleManager (ScheduleManager.h/cpp)

**Purpose**: Manages time schedules and provides time validation.

**Key Data Structures**:
```cpp
struct TimeSlot {
    int startHour;      // 0-23
    int startMinute;    // 0-59
    int endHour;        // 0-23
    int endMinute;      // 0-59
};

struct DaySchedule {
    int dayOfWeek;                  // 0=Sunday, 6=Saturday
    std::vector<TimeSlot> timeSlots;
    bool enabled;
};
```

**Key Methods**:
- `LoadSchedule()`: Loads schedule from file
- `SaveSchedule()`: Saves schedule to file
- `IsTimeAllowed()`: Checks if given time is within allowed slots
- `SetDaySchedule()`: Updates schedule for a specific day
- `GetDaySchedule()`: Retrieves schedule for a specific day

**File Format**:
```
day enabled numSlots startH startM endH endM [startH startM endH endM]...
```

Example:
```
1 1 2 8 0 12 0 13 0 20 0
```
This means: Monday, enabled, 2 time slots: 8:00-12:00 and 13:00-20:00

### 3. TimeChecker (TimeChecker.h/cpp)

**Purpose**: Monitors system time and enforces access restrictions.

**Key Responsibilities**:
- Periodically check current time against schedule
- Show warnings before time expires
- Initiate system shutdown when time expires
- Manage warning state

**Key Methods**:
- `Start()`: Begins monitoring
- `Stop()`: Stops monitoring
- `CheckCurrentTime()`: Main logic - compares current time with schedule
- `GetCurrentTime()`: Retrieves system time
- `ShowTimeExpiredWarning()`: Displays expiration warning
- `InitiateShutdown()`: Triggers system shutdown

**Timing Logic**:
1. Check if current day/time is in allowed schedule
2. If not allowed: warn and shutdown
3. If allowed: check if approaching end of time slot
4. If within warning period (5 min): show warning
5. Continue monitoring

**Warning Mechanism**:
- 5-minute advance warning (configurable)
- Only shows once per warning period
- Resets when moving to new time slot

### 4. SystemController (SystemController.h/cpp)

**Purpose**: Interfaces with Windows API for system-level operations.

**Key Responsibilities**:
- Acquire shutdown privileges
- Execute system shutdown
- Display system-level warnings
- Cancel pending shutdowns

**Key Methods**:
- `ShutdownSystem()`: Initiates Windows shutdown with delay
- `CancelShutdown()`: Cancels pending shutdown
- `ShowWarning()`: Displays MessageBox warning
- `AcquireShutdownPrivilege()`: Obtains SE_SHUTDOWN_NAME privilege

**Windows API Usage**:
- `OpenProcessToken()`: Gets process token
- `LookupPrivilegeValue()`: Gets shutdown privilege LUID
- `AdjustTokenPrivileges()`: Enables shutdown privilege
- `ExitWindowsEx()`: Performs immediate shutdown
- `MessageBoxA()`: Shows system message box
- `system("shutdown /s /t X")`: Scheduled shutdown

**Security Notes**:
- Requires administrator privileges
- Uses token manipulation for shutdown rights
- Graceful privilege handling with error checks

## Data Flow

### Configuration Flow
```
User Input (GUI)
    ↓
MainFrame validates input
    ↓
ScheduleManager stores in memory
    ↓
ScheduleManager.SaveSchedule() writes to file
```

### Monitoring Flow
```
Timer tick (every 60 seconds)
    ↓
TimeChecker.CheckCurrentTime()
    ↓
Get current day/hour/minute
    ↓
ScheduleManager.IsTimeAllowed()
    ↓
If denied: SystemController.ShutdownSystem()
If allowed but expiring: SystemController.ShowWarning()
```

## Threading Model

The application uses wxWidgets' event-driven model:
- **Main Thread**: Handles UI events and timer callbacks
- **No Background Threads**: All operations are synchronous
- **Timer-based Polling**: wxTimer for periodic checks (60-second intervals)

This simple model is appropriate because:
- Time checks are fast (< 1ms)
- Checks occur infrequently (once per minute)
- UI remains responsive
- No complex synchronization needed

## Error Handling

### File Operations
- `LoadSchedule()` returns false on error, maintains default schedule
- `SaveSchedule()` returns false on error, shows error dialog

### System Operations
- Shutdown privilege acquisition checked before shutdown
- Win32 API errors logged but don't crash application
- MessageBox used for critical user notifications

### Time Validation
- Invalid time slots rejected at UI level
- Start time must be before end time
- Times validated on input (0-23 hours, 0-59 minutes)

## Configuration

### Schedule File Location
- User-specified via File Dialog
- Typically stored in application directory or user profile
- Plain text format for easy manual editing if needed

### Default Schedule
- All days enabled
- Single time slot: 8:00 AM - 8:00 PM
- Applied when no configuration file loaded

## Security Considerations

### Privilege Requirements
- **Administrator rights required** for system shutdown
- Application should be launched with "Run as Administrator"
- Privilege acquisition checked at runtime

### Attack Vectors & Mitigations

**Time Manipulation**:
- Threat: User changes system time to bypass restrictions
- Mitigation: Consider network time synchronization (future)

**Process Termination**:
- Threat: User kills application to stop monitoring
- Mitigation: Run as Windows service (future enhancement)

**Schedule File Tampering**:
- Threat: User modifies schedule file
- Mitigation: Store in protected location, file permissions

**Privilege Escalation**:
- Threat: Application runs with admin privileges
- Mitigation: Minimal privilege scope, secure coding practices

## Performance Characteristics

### Memory Usage
- ~5-10 MB (typical wxWidgets application)
- Schedule data: < 1 KB
- No memory leaks (proper cleanup in destructors)

### CPU Usage
- Idle: < 1% (event-driven)
- During check: < 1% (simple time comparison)
- Monitoring overhead: Negligible

### Disk I/O
- Only during load/save operations
- Schedule file: < 1 KB
- No continuous disk access

## Extensibility Points

### Adding New Features

**1. Additional Time Validation Rules**:
- Modify `ScheduleManager::IsTimeAllowed()`
- Add new validation logic

**2. Different Warning Types**:
- Extend `SystemController`
- Add new notification methods

**3. User-specific Schedules**:
- Add user identification to `ScheduleManager`
- Store multiple schedules
- Check current Windows user

**4. Remote Management**:
- Add network communication layer
- Create admin console for remote configuration

**5. Logging & Reporting**:
- Add logging to `TimeChecker`
- Track usage patterns
- Generate reports

## Testing Strategy

### Unit Testing
- `ScheduleManager`: Test time slot validation
- `TimeChecker`: Test time comparison logic
- Mock system calls for testing

### Integration Testing
- Full flow: GUI → Schedule → Check → System
- Test with various time configurations
- Verify shutdown behavior (in VM)

### Manual Testing
- Run in Windows VM
- Test with short time intervals
- Verify all UI interactions
- Test privilege requirements

## Future Enhancements

1. **Windows Service Mode**
   - Run in background without UI
   - More secure (harder to terminate)
   - Automatic startup

2. **Password Protection**
   - Encrypt schedule file
   - Require password for admin access

3. **Network Time Sync**
   - Prevent time manipulation
   - Sync with NTP servers

4. **User Profiles**
   - Different schedules per user
   - Windows account integration

5. **Activity Logging**
   - Track login/logout times
   - Generate usage reports
   - Export logs

6. **Grace Period**
   - Allow temporary override
   - Request additional time
   - Admin approval system

7. **Smart Notifications**
   - Progressive warnings (15min, 10min, 5min, 1min)
   - Toast notifications instead of modal dialogs
   - Silent mode option

## Conclusion

The architecture is designed to be:
- **Simple**: Easy to understand and maintain
- **Modular**: Clear separation of concerns
- **Extensible**: Easy to add new features
- **Reliable**: Proper error handling
- **Secure**: Appropriate privilege management

The codebase provides a solid foundation for a parental control application while remaining simple enough for educational purposes and small-scale deployment.
