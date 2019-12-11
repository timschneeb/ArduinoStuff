struct schedule_item_struct
{
  int trigger = 0;
  String parameter = "";
  String action = "";
};
typedef struct schedule_item_struct schedule_item;
schedule_item s_slot1;
schedule_item s_slot2;
schedule_item s_slot3;
schedule_item s_slot4;
schedule_item s_slot5;
bool slot1_triggered = false;
bool slot2_triggered = false;
bool slot3_triggered = false;
bool slot4_triggered = false;
bool slot5_triggered = false;

void CheckSchedule() {
  if (s_slot1.action != "") {
    switch (s_slot1.trigger) {
      case 1:
        if (CheckUptime(s_slot1.parameter)) {
          if (!slot1_triggered)WebToSerial(s_slot1.action);
          slot1_triggered = true;
        } else {
          slot1_triggered = false;
        }
        break;
      case 2:
        //->TriggerWebSchedule
        break;
      case 3:
        if (CheckTemp(s_slot1.parameter)) {
          if (!slot1_triggered)WebToSerial(s_slot1.action);
          slot1_triggered = true;
        } else {
          slot1_triggered = false;
        }
        break;
      case 4:
        if (CheckHum(s_slot1.parameter)) {
          if (!slot1_triggered)WebToSerial(s_slot1.action);
          slot1_triggered = true;
        } else {
          slot1_triggered = false;
        }
        break;
    }
  }
  if (s_slot2.action != "") {
    switch (s_slot2.trigger) {
      case 1:
        if (CheckUptime(s_slot2.parameter)) {
          if (!slot2_triggered)WebToSerial(s_slot2.action);
          slot2_triggered = true;
        } else {
          slot2_triggered = false;
        }
        break;
      case 2:
        //->TriggerWebSchedule
        break;
      case 3:
        if (CheckTemp(s_slot2.parameter)) {
          if (!slot2_triggered)WebToSerial(s_slot2.action);
          slot2_triggered = true;
        } else {
          slot2_triggered = false;
        }
        break;
      case 4:
        if (CheckHum(s_slot2.parameter)) {
          if (!slot2_triggered)WebToSerial(s_slot2.action);
          slot2_triggered = true;
        } else {
          slot2_triggered = false;
        }
        break;
    }
  }
  if (s_slot3.action != "") {
    switch (s_slot3.trigger) {
      case 1:
        if (CheckUptime(s_slot3.parameter)) {
          if (!slot3_triggered)WebToSerial(s_slot3.action);
          slot3_triggered = true;
        } else {
          slot3_triggered = false;
        }
        break;
      case 2:
        //->TriggerWebSchedule
        break;
      case 3:
        if (CheckTemp(s_slot3.parameter)) {
          if (!slot3_triggered)WebToSerial(s_slot3.action);
          slot3_triggered = true;
        } else {
          slot3_triggered = false;
        }
        break;
      case 4:
        if (CheckHum(s_slot3.parameter)) {
          if (!slot3_triggered)WebToSerial(s_slot3.action);
          slot3_triggered = true;
        } else {
          slot3_triggered = false;
        }
        break;
    }
  }
  if (s_slot4.action != "") {
    switch (s_slot4.trigger) {
      case 1:
        if (CheckUptime(s_slot4.parameter)) {
          if (!slot4_triggered)WebToSerial(s_slot4.action);
          slot4_triggered = true;
        } else {
          slot4_triggered = false;
        }
        break;
      case 2:
        //->TriggerWebSchedule
        break;
      case 3:
        if (CheckTemp(s_slot4.parameter)) {
          if (!slot4_triggered)WebToSerial(s_slot4.action);
          slot4_triggered = true;
        } else {
          slot4_triggered = false;
        }
        break;
      case 4:
        if (CheckHum(s_slot4.parameter)) {
          if (!slot4_triggered)WebToSerial(s_slot4.action);
          slot4_triggered = true;
        } else {
          slot4_triggered = false;
        }
        break;
    }
  }
  if (s_slot5.action != "") {
    switch (s_slot5.trigger) {
      case 1:
        if (CheckUptime(s_slot5.parameter)) {
          if (!slot5_triggered)WebToSerial(s_slot5.action);
          slot5_triggered = true;
        } else {
          slot5_triggered = false;
        }
        break;
      case 2:
        //->TriggerWebSchedule
        break;
      case 3:
        if (CheckTemp(s_slot5.parameter)) {
          if (!slot5_triggered)WebToSerial(s_slot5.action);
          slot5_triggered = true;
        } else {
          slot5_triggered = false;
        }
        break;
      case 4:
        if (CheckHum(s_slot5.parameter)) {
          if (!slot5_triggered)WebToSerial(s_slot5.action);
          slot5_triggered = true;
        } else {
          slot5_triggered = false;
        }
        break;
    }
  }
}
void TriggerWebSchedule(String cmd) {
  if (s_slot1.action != "") {
    switch (s_slot1.trigger) {
      case 2:
        WebToSerial(s_slot1.action);
        break;
    }
  }
  if (s_slot2.action != "") {
    switch (s_slot2.trigger) {
      case 2:
        WebToSerial(s_slot2.action);
        break;
    }
  }
  if (s_slot3.action != "") {
    switch (s_slot3.trigger) {
      case 2:
        WebToSerial(s_slot3.action);
        break;
    }
  }
  if (s_slot4.action != "") {
    switch (s_slot4.trigger) {
      case 2:
        WebToSerial(s_slot4.action);
        break;
    }
  }
  if (s_slot5.action != "") {
    switch (s_slot5.trigger) {
      case 2:
        WebToSerial(s_slot5.action);
        break;
    }
  }
}
bool CheckUptime(String condition) {
  if (condition == GetUptime())return true;
  return false;
}
bool CheckTemp(String condition) {
  String t = String((int)dht.readTemperature());
  String value = String(condition.charAt(1)) + String(condition.charAt(2)) + String(condition.charAt(3));
  if (condition.charAt(0) == '=') {
    if (value == t) return true;
  }
  else if (condition.charAt(0) == '%3c19') {
    if (t < value) return true;
  }
  else if (condition.charAt(0) == '>') {
    if (t > value) return true;
  }
  return false;
}
bool CheckHum(String condition) {
  String t = String((int)dht.readTemperature());
  String value = String(condition.charAt(1)) + String(condition.charAt(2)) + String(condition.charAt(3));
  if (condition.charAt(0) == '=') {
    if (value == t) return true;
  }
  else if (condition.charAt(0) == '<') {
    if (t < value) return true;
  }
  else if (condition.charAt(0) == '>') {
    if (t > value) return true;
  }
  return false;
}

int get_nextfreeslot() {
  if (s_slot1.action == "") return 1;
  if (s_slot2.action == "") return 2;
  if (s_slot3.action == "") return 3;
  if (s_slot4.action == "") return 4;
  if (s_slot5.action == "") return 5;
  return 0;
}
void clear_scheduleslot(int slot) {
  set_scheduleslot(slot, 0, "", "");
}
bool set_scheduleslot(int slot, int trigger, String param, String action) {
  switch (slot) {
    case 1:
      slot1_triggered = false;
      s_slot1.trigger = trigger;
      s_slot1.parameter = param;
      s_slot1.action = action;
      break;
    case 2:
      slot2_triggered = false;
      s_slot2.trigger = trigger;
      s_slot2.parameter = param;
      s_slot2.action = action;
      break;
    case 3:
      slot3_triggered = false;
      s_slot3.trigger = trigger;
      s_slot3.parameter = param;
      s_slot3.action = action;
      break;
    case 4:
      slot4_triggered = false;
      s_slot4.trigger = trigger;
      s_slot4.parameter = param;
      s_slot4.action = action;
      break;
    case 5:
      slot5_triggered = false;
      s_slot5.trigger = trigger;
      s_slot5.parameter = param;
      s_slot5.action = action;
      break;
    default:
      return false;
  }
  return true;
}
int CountSchedules() {
  int c = 0;
  if (s_slot1.action != "") c++;
  if (s_slot2.action != "") c++;
  if (s_slot3.action != "") c++;
  if (s_slot4.action != "") c++;
  if (s_slot5.action != "") c++;
  return c;
}
String GenerateScheduleList() {
  String content;
  if (s_slot1.action != "") {
    content += "<u>Slot 1</u>&nbsp;<a href='javascript:void(0);' onclick='Remove(1);'>[Remove]</a><br>";
    content += "Trigger: <code>" + ConvertScheduleTrigger(s_slot1.trigger) + "</code><br>";
    if (s_slot1.trigger != 2) content += "Parameter: <code>" + s_slot1.parameter + "</code><br>";
    content += "Action: <code>" + s_slot1.action + "</code><p>";
  }
  if (s_slot2.action != "") {
    content += "<u>Slot 2</u>&nbsp;<a href='javascript:void(0);' onclick='Remove(2);'>[Remove]</a><br>";
    content += "Trigger: <code>" + ConvertScheduleTrigger(s_slot2.trigger) + "</code><br>";
    if (s_slot2.trigger != 2) content += "Parameter: <code>" + s_slot2.parameter + "</code><br>";
    content += "Action: <code>" + s_slot2.action + "</code><p>";
  }
  if (s_slot3.action != "") {
    content += "<u>Slot 3</u>&nbsp;<a href='javascript:void(0);' onclick='Remove(3);'>[Remove]</a><br>";
    content += "Trigger: <code>" + ConvertScheduleTrigger(s_slot3.trigger) + "</code><br>";
    if (s_slot3.trigger != 2) content += "Parameter: <code>" + s_slot3.parameter + "</code><br>";
    content += "Action: <code>" + s_slot3.action + "</code><p>";
  }
  if (s_slot4.action != "") {
    content += "<u>Slot 4</u>&nbsp;<a href='javascript:void(0);' onclick='Remove(4);'>[Remove]</a><br>";
    content += "Trigger: <code>" + ConvertScheduleTrigger(s_slot4.trigger) + "</code><br>";
    if (s_slot4.trigger != 2) content += "Parameter: <code>" + s_slot4.parameter + "</code><br>";
    content += "Action: <code>" + s_slot4.action + "</code><p>";
  }
  if (s_slot5.action != "") {
    content += "<u>Slot 5</u>&nbsp;<a href='javascript:void(0);' onclick='Remove(5);'>[Remove]</a><br>";
    content += "Trigger: <code>" + ConvertScheduleTrigger(s_slot5.trigger) + "</code><br>";
    if (s_slot5.trigger != 2) content += "Parameter: <code>" + s_slot5.parameter + "</code><br>";
    content += "Action: <code>" + s_slot5.action + "</code><p>";
  }
  return content;
}

String ConvertScheduleTrigger(int in) {
  switch (in) {
    case 1:
      return "Uptime";
    case 2:
      return "Webrequest";
    case 3:
      return "Temperature";
    case 4:
      return "Humidity";
    default:
      return "none";
  }
}
