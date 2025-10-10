# Quick Start Guide

This guide will help you get the Computer Access Controller up and running quickly.

## For Administrators

### Step 1: Build the Application

See [BUILD.md](BUILD.md) for detailed build instructions. Quick version:

```powershell
# If using vcpkg
vcpkg install wxwidgets:x64-windows

# Build
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=[vcpkg-root]\scripts\buildsystems\vcpkg.cmake
cmake --build . --config Release
```

### Step 2: Run as Administrator

Right-click `ComputerAccessController.exe` and select "Run as administrator"

### Step 3: Configure Schedule

1. **Select Day**: Choose a day from the dropdown (e.g., Monday)
2. **Enable Control**: Check "Enable Access Control for this Day"
3. **Add Time Slot**: 
   - Set start time (e.g., 8:00)
   - Set end time (e.g., 20:00)
   - Click "Add Slot"
4. **Repeat**: Configure other days as needed
5. **Save**: Click "Save Schedule" and choose a location

### Step 4: Enable Monitoring

1. Check "Enable Real-time Monitoring"
2. Leave the application running
3. The system will now enforce the schedule

## Example Configurations

### School Days (Mon-Fri)
- Monday - Friday: 6:00 PM - 9:00 PM
- Saturday - Sunday: 10:00 AM - 10:00 PM

Steps:
1. Select Monday, enable control, add slot 18:00 - 21:00
2. Repeat for Tuesday through Friday
3. Select Saturday, enable control, add slot 10:00 - 22:00
4. Select Sunday, enable control, add slot 10:00 - 22:00
5. Save schedule

### After School Only
- All days: 3:00 PM - 9:00 PM

Steps:
1. For each day (Sunday through Saturday)
2. Enable control
3. Add time slot: 15:00 - 21:00
4. Save schedule

### Multiple Sessions Per Day
- Monday: 12:00 PM - 2:00 PM AND 6:00 PM - 9:00 PM

Steps:
1. Select Monday
2. Enable control
3. Add first slot: 12:00 - 14:00
4. Add second slot: 18:00 - 21:00
5. Continue with other days

## User Experience

### When Access is Allowed
- Computer works normally
- No interruptions
- 5 minutes before time expires: Warning message appears

### When Access is Denied
- Warning message: "Access time has expired"
- 60-second countdown begins
- Computer automatically shuts down

### Warning Messages
- **5 minutes before**: "Warning: Computer access will end in X minutes"
- **Time expired**: "Your computer access time has expired. The system will shutdown in 60 seconds"

## Troubleshooting

### Application won't start
- **Check**: Running as administrator?
- **Solution**: Right-click exe → "Run as administrator"

### System doesn't shutdown
- **Check**: Administrator privileges?
- **Solution**: Ensure the application has admin rights

### Schedule not enforced
- **Check**: Is monitoring enabled?
- **Solution**: Check the "Enable Real-time Monitoring" checkbox

### Lost schedule configuration
- **Check**: Did you save the schedule?
- **Solution**: Click "Save Schedule" and store it safely

### Wrong time zone
- **Check**: Windows time settings
- **Solution**: Adjust Windows time zone settings

## Best Practices

### For Parents/Administrators

1. **Test First**: Test the configuration with short time intervals in a safe environment
2. **Communicate**: Tell users about the schedule in advance
3. **Be Consistent**: Maintain regular schedules
4. **Backup**: Keep backup copies of schedule files
5. **Monitor**: Check the status display regularly
6. **Update**: Adjust schedules as needs change

### Security Recommendations

1. **Protect the Application**
   - Install in protected directory (e.g., Program Files)
   - Set file permissions so users can't delete it

2. **Protect Schedule Files**
   - Store in administrator-only directory
   - Regular backups

3. **Auto-start**
   - Create scheduled task to run on Windows startup
   - Configure to run with highest privileges

4. **User Accounts**
   - Users should have standard (non-admin) accounts
   - Only administrators can bypass restrictions

## Creating Scheduled Task for Auto-start

To make the application start automatically:

1. Open Task Scheduler
2. Create New Task
3. General tab:
   - Name: "Computer Access Controller"
   - Run with highest privileges: ✓
4. Triggers tab:
   - New → At startup
5. Actions tab:
   - New → Start a program
   - Program: Path to ComputerAccessController.exe
   - Arguments: (optional) path to schedule file
6. Conditions tab:
   - Adjust power settings as needed
7. Settings tab:
   - Allow task to be run on demand: ✓

## Sample Schedule File

Copy `schedule.dat.example` to create your first schedule:

```
# Computer Access Schedule
# Format: day enabled numSlots [startHour startMinute endHour endMinute]...

0 1 1 10 0 22 0    # Sunday: 10 AM - 10 PM
1 1 1 8 0 20 0     # Monday: 8 AM - 8 PM (school day)
2 1 1 8 0 20 0     # Tuesday: 8 AM - 8 PM
3 1 1 8 0 20 0     # Wednesday: 8 AM - 8 PM
4 1 1 8 0 20 0     # Thursday: 8 AM - 8 PM
5 1 2 10 0 14 0 18 0 22 0  # Friday: 10 AM - 2 PM and 6 PM - 10 PM
6 1 1 10 0 22 0    # Saturday: 10 AM - 10 PM
```

## Getting Help

### Resources
- [README.md](README.md) - Overview and features
- [BUILD.md](BUILD.md) - Detailed build instructions
- [ARCHITECTURE.md](ARCHITECTURE.md) - Technical documentation

### Common Issues
- Application crashes → Check Windows Event Viewer
- Unexpected shutdowns → Review schedule configuration
- Can't modify schedule → Ensure admin access

## Next Steps

After completing this quick start:
1. Test your configuration thoroughly
2. Adjust times based on usage patterns
3. Consider setting up automatic startup
4. Keep the application updated
5. Review and adjust schedules regularly

## Important Notes

⚠️ **Warning**: This application will shut down the computer when time expires. Make sure users save their work regularly!

ℹ️ **Note**: The application must remain running for monitoring to work. If closed, restrictions will not be enforced.

✅ **Tip**: Start with generous time allocations and adjust based on actual usage patterns.

---

For more information, see the full documentation in [README.md](README.md)
