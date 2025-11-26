# Dev notes
<p>
Easy app that would have straight construction. 
It would be log out the all users of one computer it user use the app beside restricted hours. 
It can be done with powershell but I would add a little c++ console for this program. 
There is two approaches for this app.
<p>

- All in powershell and add the executable tasks to task scheduler

- Powershell converted into c++ code and executable as separate program that must be added to registry and startup apps.

I would use the second approach, it will be slower but I would have a little fun with c++ coding.

## How to start

1. [x] Start from creating a simplest helloworld program. C++ code connected to powershell print(helloworld) script.

2. [ ] Add this executable to registry and startup apps.
 
3. [ ] See if it works on the start of the computer.

4. [x] Make the structure of the program.

5. [x] Add the timer functionality.

6. [ ] Add the entry in registry functionality.

7. [x] Add the data.ini functionality.

8. [ ] Notifications.

## Approaches

### Ways to manage the user access blocker:

1. [x] **Auto-logout/Shutdown when run program at startup registry path to program or startup folder.** *It is propably needed anyway*
    - Press Win + R, type **shell:startup**, and press Enter. This opens the Startup folder.
    - Create a shortcut of your compiled .exe file (your project app) inside this folder.
    - Your app will automatically launch when the user logs in.
    - **<p>OR</p>**
    - Press Win + R, type regedit, and press Enter to open the Registry Editor.
    - Navigate to the following registry key: HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run
    - Right-click in the right pane and select New > String Value.
    - Name it as your app.
    - Set its value to the full path of your executable (e.g., C:\path\to\your\app.exe).
<br><br>
2. [x] **Password dialog on the start with Countdown timer.**
    - Get the time from system.
    - Calculate it with the allowed time.
    - If user logged beside the allowed time there is countdown timer and shutdown.
    - There is password dialog that would allow to bypass the shutdown.
<br><br>
3. **Task Scheduler Integration with C++.**
    - You can invoke the Windows schtasks command-line utility from your C++ program using *system("schtasks /create /tn \"MyTask\" /tr \"C:\\path\\to\\app.exe\" /sc onlogon /rl highest");*
    - **<p>OR</p>**
    - Using Task Scheduler COM API (Native C++)
    - Requires initializing COM, creating TaskService object, configuring triggers (e.g., on logon, daily), specifying actions (like running your executable), and registering the task.
<br><br>
4. **Login restrictions using Local Security Policy on Windows Pro and Enterprise.**
    - Win + R type **secpol.msc** and press Enter.
    - Navigate to Local Policies > User Rights Assignment.
    - Here there are policies like *Allow log on locally*, *Deny log on locally*, *Deny log on through Remote Desktop Services*
    - Settings can be viewed or changed programmatically via Windows APIs or PowerShell cmdlets.
<br><br>
5. Block from BIOS/UEFI settings. :O

### Ways to add the notifications:

1. **Simple Message Box (*too much easy*)**
2. **Modern Windows 10/11 Toast Notification / Toast Notification without external module** (*Issues, the provided docs is for VS compiler.
   It requires the proper App User Model ID (AUMID) registrated in Windows.*)
   *https://learn.microsoft.com/en-us/windows/apps/develop/notifications/app-notifications/send-local-toast-cpp-uwp?tabs=builder-syntax*
3. [x] **Using Windows API directly**

## Structure

![Image](structure.jpg)

## TODO

- [ ] Understand the Registry handler
- [ ] Understand the Notifications handler
- [ ] Add proper Shutdown and log out functionality.
- [ ] Connect it all to the main.cpp
- [ ] Then try to make simple GUI.
- [ ] Password encryption handler.