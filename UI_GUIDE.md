# User Interface Guide

This document describes the Computer Access Controller user interface.

## Main Window Layout

```
┌────────────────────────────────────────────────────────────────┐
│  Computer Access Controller - Admin Panel                   [X]│
├────────────────────────────────────────────────────────────────┤
│                                                                 │
│         Parental Control - Computer Access Schedule           │
│              Configuration                                      │
│                                                                 │
│  ┌───────────────────────────────────────────────────────┐    │
│  │ Day: [Monday     ▼] ☑ Enable Access Control for     │    │
│  │                       this Day                        │    │
│  └───────────────────────────────────────────────────────┘    │
│                                                                 │
│  Allowed Time Slots:                                           │
│  ┌───────────────────────────────────────────────────────┐    │
│  │ Start Time          │ End Time                        │    │
│  ├─────────────────────┼─────────────────────────────────┤    │
│  │ 08:00              │ 20:00                           │    │
│  │                    │                                 │    │
│  │                    │                                 │    │
│  └───────────────────────────────────────────────────────┘    │
│                                                                 │
│  ┌─ Add Time Slot ──────────────────────────────────────┐    │
│  │ Start: [08][▲▼] : [00][▲▼]  End: [20][▲▼] : [00][▲▼] │    │
│  │        [Add Slot]  [Remove Selected]                  │    │
│  └───────────────────────────────────────────────────────┘    │
│                                                                 │
│           [Save Schedule]  [Load Schedule]                     │
│                                                                 │
│  ┌─ Monitoring ─────────────────────────────────────────┐    │
│  │ ☑ Enable Real-time Monitoring (checks every minute)  │    │
│  │ Monitoring: ACTIVE | Current Time: 14:35 | Access:   │    │
│  │ ALLOWED                                                │    │
│  └───────────────────────────────────────────────────────┘    │
│                                                                 │
│  Instructions:                                                 │
│  1. Select a day and configure allowed time slots             │
│  2. Add multiple time slots if needed for different periods   │
│     during the day                                             │
│  3. Save the schedule to apply changes                        │
│  4. Enable monitoring to enforce access restrictions in       │
│     real-time                                                  │
│  5. When enabled, the system will warn users and shutdown     │
│     when time expires                                          │
│                                                                 │
└────────────────────────────────────────────────────────────────┘
```

## UI Components Explained

### 1. Day Selector
- **Location**: Top of window
- **Type**: Dropdown menu
- **Options**: Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday
- **Function**: Selects which day's schedule to view/edit

### 2. Enable Checkbox
- **Label**: "Enable Access Control for this Day"
- **Function**: Toggles whether restrictions apply to the selected day
- **Note**: Unchecked = unrestricted access for that day

### 3. Time Slots List
- **Columns**: Start Time, End Time
- **Format**: HH:MM (24-hour format)
- **Function**: Displays all configured time slots for the current day
- **Interaction**: Click to select for removal

### 4. Time Slot Input Controls

#### Start Time
- Two spin controls (hour and minute)
- Hour: 0-23
- Minute: 0-59

#### End Time
- Two spin controls (hour and minute)
- Hour: 0-23
- Minute: 0-59

#### Add Slot Button
- **Function**: Adds new time slot with specified start/end times
- **Validation**: End time must be after start time

#### Remove Selected Button
- **Function**: Removes the selected time slot from the list
- **Note**: A time slot must be selected in the list first

### 5. File Operations

#### Save Schedule Button
- **Function**: Opens file dialog to save schedule
- **File Type**: .dat files
- **Result**: Saves all day configurations to file

#### Load Schedule Button
- **Function**: Opens file dialog to load schedule
- **File Type**: .dat files
- **Result**: Loads all day configurations from file

### 6. Monitoring Section

#### Enable Monitoring Checkbox
- **Label**: "Enable Real-time Monitoring (checks every minute)"
- **Function**: Starts/stops the monitoring service
- **Warning**: Application must remain running when checked

#### Status Display
- **Format**: "Monitoring: [STATUS] | Current Time: [HH:MM] | Access: [ALLOWED/DENIED]"
- **Colors**: 
  - Green text = Access allowed
  - Red text = Access denied
  - Default = Monitoring disabled

### 7. Instructions Panel
- **Function**: Provides quick reference guide
- **Content**: Step-by-step usage instructions

## Workflow Example

### Setting Up Monday Schedule

1. **Select Day**
   ```
   Click dropdown → Select "Monday"
   ```

2. **Enable Control**
   ```
   Check "Enable Access Control for this Day"
   ```

3. **Set Morning Hours (8 AM - 12 PM)**
   ```
   Start: Hour [08] Minute [00]
   End:   Hour [12] Minute [00]
   Click [Add Slot]
   ```
   Result: "08:00 | 12:00" appears in list

4. **Set Evening Hours (6 PM - 9 PM)**
   ```
   Start: Hour [18] Minute [00]
   End:   Hour [21] Minute [00]
   Click [Add Slot]
   ```
   Result: "18:00 | 21:00" appears in list

5. **Save Configuration**
   ```
   Click [Save Schedule]
   Choose filename → "my_schedule.dat"
   Click Save
   ```

6. **Repeat for Other Days**
   ```
   Select Tuesday, configure, etc.
   ```

7. **Enable Monitoring**
   ```
   Check "Enable Real-time Monitoring"
   Status updates to show current time and access status
   ```

## Dialog Boxes

### Save Schedule Dialog
```
┌─ Save Schedule ──────────────────────────┐
│ Save in: [This PC > Documents      ▼]   │
│                                           │
│ ☐ schedule.dat                           │
│ ☐ backup_schedule.dat                    │
│                                           │
│ File name: [schedule.dat          ]     │
│ Save as type: [Schedule files (*.dat)▼] │
│                                           │
│              [Save]  [Cancel]            │
└───────────────────────────────────────────┘
```

### Load Schedule Dialog
```
┌─ Load Schedule ──────────────────────────┐
│ Look in: [This PC > Documents      ▼]   │
│                                           │
│ ☐ schedule.dat                           │
│ ☐ backup_schedule.dat                    │
│                                           │
│ File name: [                        ]    │
│ Files of type: [Schedule files (*.dat)▼] │
│                                           │
│              [Open]  [Cancel]            │
└───────────────────────────────────────────┘
```

### Error Message - Invalid Time
```
┌─ Invalid Time Slot ────────┐
│                             │
│  ⚠  End time must be after │
│     start time!            │
│                             │
│           [OK]             │
└─────────────────────────────┘
```

### Success Message - Save
```
┌─ Success ──────────────────┐
│                             │
│  ✓  Schedule saved         │
│     successfully!          │
│                             │
│           [OK]             │
└─────────────────────────────┘
```

### Warning - Monitoring Enabled
```
┌─ Monitoring Enabled ────────────────────────┐
│                                              │
│  ℹ  Monitoring is now ACTIVE.              │
│                                              │
│     The system will:                         │
│     • Check access permissions every minute │
│     • Show warnings when time is about to   │
│       expire                                 │
│     • Automatically shutdown when access    │
│       time ends                              │
│                                              │
│     Keep this application running for       │
│     monitoring to work.                      │
│                                              │
│                  [OK]                       │
└──────────────────────────────────────────────┘
```

### Warning - Close Application
```
┌─ Warning ───────────────────────────────────┐
│                                              │
│  ⚠  Monitoring is currently active. If you │
│     close this application, time            │
│     restrictions will not be enforced.      │
│                                              │
│     Do you want to close anyway?           │
│                                              │
│           [Yes]  [No]                       │
└──────────────────────────────────────────────┘
```

## System Notifications

### 5-Minute Warning (During Monitoring)
```
┌─ Access Time Warning ──────────────────┐
│                                         │
│  ⚠  Warning: Computer access will end │
│     in 5 minutes.                      │
│                                         │
│              [OK]                      │
└─────────────────────────────────────────┘
```

### Time Expired Warning
```
┌─ Access Time Expired ──────────────────────┐
│                                             │
│  ⚠  Your computer access time has expired.│
│     The system will shutdown in 60         │
│     seconds.                                │
│                                             │
│                 [OK]                       │
└─────────────────────────────────────────────┘
```

## Color Coding

### Status Text Colors
- **Green**: Access currently allowed
- **Red**: Access currently denied
- **Gray/Black**: Monitoring disabled

### Visual Indicators
- **✓**: Success (green checkmark)
- **⚠**: Warning (yellow/orange triangle)
- **ℹ**: Information (blue circle)
- **☑**: Checkbox checked
- **☐**: Checkbox unchecked

## Keyboard Shortcuts

While the application doesn't define custom shortcuts, standard Windows shortcuts work:

- **Alt+F4**: Close window (with confirmation if monitoring active)
- **Tab**: Navigate between controls
- **Space**: Toggle checkboxes
- **Enter**: Activate focused button
- **Arrow Keys**: Navigate dropdown/listbox

## Accessibility

The application follows standard Windows UI guidelines:
- Tab navigation supported
- Keyboard accessible
- Standard Windows controls
- Clear labels and instructions
- High contrast compatible

## Tips for Administrators

1. **Use Clear Time Boundaries**
   - Full hours (08:00, 20:00) easier to remember
   - Avoid complex overlapping slots

2. **Visual Check**
   - Review time slots in the list before saving
   - Ensure no gaps if continuous access intended

3. **Status Monitoring**
   - Keep window visible to monitor status
   - Green = all good, Red = action needed

4. **File Management**
   - Save schedules with descriptive names
   - Keep backups ("schedule_weekday.dat", "schedule_weekend.dat")

5. **Testing**
   - Use short time intervals to test (e.g., 14:30 - 14:35)
   - Verify warnings appear as expected
   - Ensure shutdown works (in safe environment!)

## Window Management

- **Minimize**: Window can be minimized to taskbar (monitoring continues)
- **Resize**: Window can be resized within reasonable limits
- **Close**: Shows warning if monitoring active
- **Always on Top**: Not implemented (can be added as feature)

## Multi-Monitor Support

The application follows standard Windows behavior:
- Opens on primary monitor
- Can be dragged to secondary monitor
- Dialog boxes appear on same monitor as main window
- System messages may appear on primary monitor

---

This UI guide provides visual reference for all interface elements. For usage instructions, see [QUICKSTART.md](QUICKSTART.md).
