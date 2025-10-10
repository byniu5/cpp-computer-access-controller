#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <wx/listctrl.h>
#include <wx/timer.h>
#include "ScheduleManager.h"
#include "TimeChecker.h"
#include "SystemController.h"

class MainFrame : public wxFrame {
public:
    MainFrame();
    ~MainFrame();
    
private:
    // Components
    ScheduleManager* scheduleManager;
    TimeChecker* timeChecker;
    SystemController* systemController;
    wxTimer* monitorTimer;
    
    // UI Elements
    wxChoice* dayChoice;
    wxCheckBox* enabledCheckBox;
    wxListCtrl* timeSlotList;
    wxSpinCtrl* startHourSpin;
    wxSpinCtrl* startMinuteSpin;
    wxSpinCtrl* endHourSpin;
    wxSpinCtrl* endMinuteSpin;
    wxButton* addSlotButton;
    wxButton* removeSlotButton;
    wxButton* saveButton;
    wxButton* loadButton;
    wxStaticText* statusText;
    wxCheckBox* monitoringCheckBox;
    
    // Current editing state
    int currentDay;
    
    // Event handlers
    void OnDayChanged(wxCommandEvent& event);
    void OnEnabledChanged(wxCommandEvent& event);
    void OnAddTimeSlot(wxCommandEvent& event);
    void OnRemoveTimeSlot(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnLoad(wxCommandEvent& event);
    void OnMonitoringChanged(wxCommandEvent& event);
    void OnTimer(wxTimerEvent& event);
    void OnClose(wxCloseEvent& event);
    
    // Helper methods
    void CreateUI();
    void LoadDaySchedule(int day);
    void SaveDaySchedule();
    void UpdateTimeSlotList();
    void UpdateStatusText();
    
    wxDECLARE_EVENT_TABLE();
};

enum {
    ID_DAY_CHOICE = wxID_HIGHEST + 1,
    ID_ENABLED_CHECK,
    ID_TIMESLOT_LIST,
    ID_ADD_SLOT,
    ID_REMOVE_SLOT,
    ID_SAVE,
    ID_LOAD,
    ID_MONITORING_CHECK,
    ID_MONITOR_TIMER
};

#endif // MAINFRAME_H
