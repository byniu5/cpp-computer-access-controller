#include "MainFrame.h"
#include <wx/filedlg.h>
#include <wx/msgdlg.h>

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_CHOICE(ID_DAY_CHOICE, MainFrame::OnDayChanged)
    EVT_CHECKBOX(ID_ENABLED_CHECK, MainFrame::OnEnabledChanged)
    EVT_BUTTON(ID_ADD_SLOT, MainFrame::OnAddTimeSlot)
    EVT_BUTTON(ID_REMOVE_SLOT, MainFrame::OnRemoveTimeSlot)
    EVT_BUTTON(ID_SAVE, MainFrame::OnSave)
    EVT_BUTTON(ID_LOAD, MainFrame::OnLoad)
    EVT_CHECKBOX(ID_MONITORING_CHECK, MainFrame::OnMonitoringChanged)
    EVT_TIMER(ID_MONITOR_TIMER, MainFrame::OnTimer)
    EVT_CLOSE(MainFrame::OnClose)
wxEND_EVENT_TABLE()

MainFrame::MainFrame()
    : wxFrame(nullptr, wxID_ANY, "Computer Access Controller - Admin Panel", 
              wxDefaultPosition, wxSize(800, 600)) {
    
    scheduleManager = new ScheduleManager();
    systemController = new SystemController();
    timeChecker = new TimeChecker(scheduleManager, systemController);
    monitorTimer = new wxTimer(this, ID_MONITOR_TIMER);
    
    currentDay = 1; // Monday
    
    CreateUI();
    LoadDaySchedule(currentDay);
    
    Centre();
}

MainFrame::~MainFrame() {
    if (monitorTimer->IsRunning()) {
        monitorTimer->Stop();
    }
    delete monitorTimer;
    delete timeChecker;
    delete systemController;
    delete scheduleManager;
}

void MainFrame::CreateUI() {
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    
    // Title
    wxStaticText* title = new wxStaticText(panel, wxID_ANY, 
        "Parental Control - Computer Access Schedule Configuration");
    wxFont titleFont = title->GetFont();
    titleFont.SetPointSize(14);
    titleFont.SetWeight(wxFONTWEIGHT_BOLD);
    title->SetFont(titleFont);
    mainSizer->Add(title, 0, wxALL | wxCENTER, 10);
    
    // Day selection
    wxBoxSizer* daySizer = new wxBoxSizer(wxHORIZONTAL);
    daySizer->Add(new wxStaticText(panel, wxID_ANY, "Day:"), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    
    wxArrayString days;
    days.Add("Sunday");
    days.Add("Monday");
    days.Add("Tuesday");
    days.Add("Wednesday");
    days.Add("Thursday");
    days.Add("Friday");
    days.Add("Saturday");
    
    dayChoice = new wxChoice(panel, ID_DAY_CHOICE, wxDefaultPosition, wxSize(150, -1), days);
    dayChoice->SetSelection(1); // Monday
    daySizer->Add(dayChoice, 0, wxRIGHT, 10);
    
    enabledCheckBox = new wxCheckBox(panel, ID_ENABLED_CHECK, "Enable Access Control for this Day");
    daySizer->Add(enabledCheckBox, 0, wxALIGN_CENTER_VERTICAL);
    
    mainSizer->Add(daySizer, 0, wxALL | wxEXPAND, 10);
    
    // Time slots list
    wxStaticText* slotsLabel = new wxStaticText(panel, wxID_ANY, "Allowed Time Slots:");
    mainSizer->Add(slotsLabel, 0, wxLEFT | wxRIGHT, 10);
    
    timeSlotList = new wxListCtrl(panel, ID_TIMESLOT_LIST, wxDefaultPosition, 
                                   wxSize(-1, 200), wxLC_REPORT | wxLC_SINGLE_SEL);
    timeSlotList->AppendColumn("Start Time", wxLIST_FORMAT_LEFT, 150);
    timeSlotList->AppendColumn("End Time", wxLIST_FORMAT_LEFT, 150);
    mainSizer->Add(timeSlotList, 1, wxALL | wxEXPAND, 10);
    
    // Time slot controls
    wxStaticBoxSizer* slotControlSizer = new wxStaticBoxSizer(wxHORIZONTAL, panel, "Add Time Slot");
    
    slotControlSizer->Add(new wxStaticText(panel, wxID_ANY, "Start:"), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    startHourSpin = new wxSpinCtrl(panel, wxID_ANY, "8", wxDefaultPosition, wxSize(60, -1));
    startHourSpin->SetRange(0, 23);
    startHourSpin->SetValue(8);
    slotControlSizer->Add(startHourSpin, 0, wxRIGHT, 5);
    
    slotControlSizer->Add(new wxStaticText(panel, wxID_ANY, ":"), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    startMinuteSpin = new wxSpinCtrl(panel, wxID_ANY, "0", wxDefaultPosition, wxSize(60, -1));
    startMinuteSpin->SetRange(0, 59);
    startMinuteSpin->SetValue(0);
    slotControlSizer->Add(startMinuteSpin, 0, wxRIGHT, 15);
    
    slotControlSizer->Add(new wxStaticText(panel, wxID_ANY, "End:"), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    endHourSpin = new wxSpinCtrl(panel, wxID_ANY, "20", wxDefaultPosition, wxSize(60, -1));
    endHourSpin->SetRange(0, 23);
    endHourSpin->SetValue(20);
    slotControlSizer->Add(endHourSpin, 0, wxRIGHT, 5);
    
    slotControlSizer->Add(new wxStaticText(panel, wxID_ANY, ":"), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    endMinuteSpin = new wxSpinCtrl(panel, wxID_ANY, "0", wxDefaultPosition, wxSize(60, -1));
    endMinuteSpin->SetRange(0, 59);
    endMinuteSpin->SetValue(0);
    slotControlSizer->Add(endMinuteSpin, 0, wxRIGHT, 15);
    
    addSlotButton = new wxButton(panel, ID_ADD_SLOT, "Add Slot");
    slotControlSizer->Add(addSlotButton, 0, wxRIGHT, 5);
    
    removeSlotButton = new wxButton(panel, ID_REMOVE_SLOT, "Remove Selected");
    slotControlSizer->Add(removeSlotButton, 0);
    
    mainSizer->Add(slotControlSizer, 0, wxALL | wxEXPAND, 10);
    
    // File operations
    wxBoxSizer* fileSizer = new wxBoxSizer(wxHORIZONTAL);
    saveButton = new wxButton(panel, ID_SAVE, "Save Schedule");
    fileSizer->Add(saveButton, 0, wxRIGHT, 5);
    
    loadButton = new wxButton(panel, ID_LOAD, "Load Schedule");
    fileSizer->Add(loadButton, 0, wxRIGHT, 20);
    
    mainSizer->Add(fileSizer, 0, wxALL | wxCENTER, 10);
    
    // Monitoring
    wxStaticBoxSizer* monitorSizer = new wxStaticBoxSizer(wxVERTICAL, panel, "Monitoring");
    
    monitoringCheckBox = new wxCheckBox(panel, ID_MONITORING_CHECK, 
                                        "Enable Real-time Monitoring (checks every minute)");
    monitorSizer->Add(monitoringCheckBox, 0, wxALL, 5);
    
    statusText = new wxStaticText(panel, wxID_ANY, "Monitoring: Disabled");
    monitorSizer->Add(statusText, 0, wxALL, 5);
    
    mainSizer->Add(monitorSizer, 0, wxALL | wxEXPAND, 10);
    
    // Instructions
    wxStaticText* instructions = new wxStaticText(panel, wxID_ANY,
        "Instructions:\n"
        "1. Select a day and configure allowed time slots\n"
        "2. Add multiple time slots if needed for different periods during the day\n"
        "3. Save the schedule to apply changes\n"
        "4. Enable monitoring to enforce access restrictions in real-time\n"
        "5. When enabled, the system will warn users and shutdown when time expires");
    wxFont smallFont = instructions->GetFont();
    smallFont.SetPointSize(9);
    instructions->SetFont(smallFont);
    mainSizer->Add(instructions, 0, wxALL | wxEXPAND, 10);
    
    panel->SetSizer(mainSizer);
}

void MainFrame::LoadDaySchedule(int day) {
    currentDay = day;
    DaySchedule schedule = scheduleManager->GetDaySchedule(day);
    
    enabledCheckBox->SetValue(schedule.enabled);
    UpdateTimeSlotList();
}

void MainFrame::SaveDaySchedule() {
    // Time slots are updated immediately when added/removed
    // Just update the enabled status
    DaySchedule schedule = scheduleManager->GetDaySchedule(currentDay);
    schedule.enabled = enabledCheckBox->GetValue();
    scheduleManager->SetDaySchedule(currentDay, schedule.timeSlots, schedule.enabled);
}

void MainFrame::UpdateTimeSlotList() {
    timeSlotList->DeleteAllItems();
    
    DaySchedule schedule = scheduleManager->GetDaySchedule(currentDay);
    
    for (size_t i = 0; i < schedule.timeSlots.size(); i++) {
        const TimeSlot& slot = schedule.timeSlots[i];
        
        wxString startTime = wxString::Format("%02d:%02d", slot.startHour, slot.startMinute);
        wxString endTime = wxString::Format("%02d:%02d", slot.endHour, slot.endMinute);
        
        long index = timeSlotList->InsertItem(i, startTime);
        timeSlotList->SetItem(index, 1, endTime);
    }
}

void MainFrame::UpdateStatusText() {
    if (timeChecker->IsRunning()) {
        time_t now = time(nullptr);
        struct tm timeinfo;
#ifdef _WIN32
        localtime_s(&timeinfo, &now);
#else
        localtime_r(&now, &timeinfo);
#endif
        
        int dayOfWeek = timeinfo.tm_wday;
        int hour = timeinfo.tm_hour;
        int minute = timeinfo.tm_min;
        
        bool allowed = scheduleManager->IsTimeAllowed(dayOfWeek, hour, minute);
        
        wxString status = wxString::Format(
            "Monitoring: ACTIVE | Current Time: %02d:%02d | Access: %s",
            hour, minute, allowed ? "ALLOWED" : "DENIED"
        );
        statusText->SetLabel(status);
        
        if (allowed) {
            statusText->SetForegroundColour(*wxGREEN);
        } else {
            statusText->SetForegroundColour(*wxRED);
        }
    } else {
        statusText->SetLabel("Monitoring: Disabled");
        statusText->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));
    }
}

void MainFrame::OnDayChanged(wxCommandEvent& event) {
    SaveDaySchedule();
    LoadDaySchedule(dayChoice->GetSelection());
}

void MainFrame::OnEnabledChanged(wxCommandEvent& event) {
    SaveDaySchedule();
}

void MainFrame::OnAddTimeSlot(wxCommandEvent& event) {
    TimeSlot slot;
    slot.startHour = startHourSpin->GetValue();
    slot.startMinute = startMinuteSpin->GetValue();
    slot.endHour = endHourSpin->GetValue();
    slot.endMinute = endMinuteSpin->GetValue();
    
    // Validate
    int startMinutes = slot.startHour * 60 + slot.startMinute;
    int endMinutes = slot.endHour * 60 + slot.endMinute;
    
    if (startMinutes >= endMinutes) {
        wxMessageBox("End time must be after start time!", "Invalid Time Slot", 
                     wxOK | wxICON_ERROR, this);
        return;
    }
    
    DaySchedule schedule = scheduleManager->GetDaySchedule(currentDay);
    schedule.timeSlots.push_back(slot);
    scheduleManager->SetDaySchedule(currentDay, schedule.timeSlots, schedule.enabled);
    
    UpdateTimeSlotList();
}

void MainFrame::OnRemoveTimeSlot(wxCommandEvent& event) {
    long selectedIndex = timeSlotList->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    
    if (selectedIndex == -1) {
        wxMessageBox("Please select a time slot to remove.", "No Selection", 
                     wxOK | wxICON_INFORMATION, this);
        return;
    }
    
    DaySchedule schedule = scheduleManager->GetDaySchedule(currentDay);
    if (selectedIndex >= 0 && selectedIndex < (long)schedule.timeSlots.size()) {
        schedule.timeSlots.erase(schedule.timeSlots.begin() + selectedIndex);
        scheduleManager->SetDaySchedule(currentDay, schedule.timeSlots, schedule.enabled);
        UpdateTimeSlotList();
    }
}

void MainFrame::OnSave(wxCommandEvent& event) {
    SaveDaySchedule();
    
    wxFileDialog saveFileDialog(this, "Save Schedule", "", "schedule.dat",
                               "Schedule files (*.dat)|*.dat|All files (*.*)|*.*",
                               wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    
    if (saveFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }
    
    wxString path = saveFileDialog.GetPath();
    
    if (scheduleManager->SaveSchedule(path.ToStdString())) {
        wxMessageBox("Schedule saved successfully!", "Success", wxOK | wxICON_INFORMATION, this);
    } else {
        wxMessageBox("Failed to save schedule!", "Error", wxOK | wxICON_ERROR, this);
    }
}

void MainFrame::OnLoad(wxCommandEvent& event) {
    wxFileDialog openFileDialog(this, "Load Schedule", "", "schedule.dat",
                               "Schedule files (*.dat)|*.dat|All files (*.*)|*.*",
                               wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    
    if (openFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }
    
    wxString path = openFileDialog.GetPath();
    
    if (scheduleManager->LoadSchedule(path.ToStdString())) {
        LoadDaySchedule(currentDay);
        wxMessageBox("Schedule loaded successfully!", "Success", wxOK | wxICON_INFORMATION, this);
    } else {
        wxMessageBox("Failed to load schedule!", "Error", wxOK | wxICON_ERROR, this);
    }
}

void MainFrame::OnMonitoringChanged(wxCommandEvent& event) {
    if (monitoringCheckBox->GetValue()) {
        timeChecker->Start();
        monitorTimer->Start(60000); // Check every minute
        UpdateStatusText();
        
        wxMessageBox(
            "Monitoring is now ACTIVE.\n\n"
            "The system will:\n"
            "- Check access permissions every minute\n"
            "- Show warnings when time is about to expire\n"
            "- Automatically shutdown when access time ends\n\n"
            "Keep this application running for monitoring to work.",
            "Monitoring Enabled",
            wxOK | wxICON_INFORMATION,
            this
        );
    } else {
        timeChecker->Stop();
        monitorTimer->Stop();
        UpdateStatusText();
    }
}

void MainFrame::OnTimer(wxTimerEvent& event) {
    if (timeChecker->IsRunning()) {
        timeChecker->CheckCurrentTime();
        UpdateStatusText();
    }
}

void MainFrame::OnClose(wxCloseEvent& event) {
    if (timeChecker->IsRunning()) {
        wxMessageDialog dialog(this,
            "Monitoring is currently active. If you close this application, "
            "time restrictions will not be enforced.\n\n"
            "Do you want to close anyway?",
            "Warning",
            wxYES_NO | wxNO_DEFAULT | wxICON_WARNING);
        
        if (dialog.ShowModal() == wxID_NO) {
            event.Veto();
            return;
        }
    }
    
    Destroy();
}
