## 1.0 
First version of application provides basic consol application. It has simple user interface.
User can log into using password. After providing the correct password user can change the settings.
by clicking "s" or quit from the application using "q".

After entering "s" user can set start and end time of the allowed time. Those inputs are validated,
so user can enter only numbers in format HHMM. The next automatic setting is password, user can set freely.
As the user of this application, it is important to remember that password is stored in plain text in .dat file.

After initialising the app it automatically add itself to startup folder. Then it checks if user logged outside of
allowed hours. If yes, it shows a Windows system notification and run shutdown command.