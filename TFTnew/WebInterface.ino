String GenerateAddEventInterface() {
  String content = F("<head><script src='https://code.jquery.com/jquery-3.3.1.min.js' crossorigin='anonymous'></script><div id='shellmsg' style='display: none;'>Interface not available in command prompt</div><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><link href='https://fonts.googleapis.com/css?family=Roboto' rel='stylesheet'>");
  content += F("</head><body style=\"font-family: 'Roboto', sans-serif;\">");
  content += F("<h3>Schedule Manager</h3>");
  //Content
  content += F("<div style='background:#eee;border:1px solid #ccc;padding:5px 10px;width:40%;min-width:270px;max-width:350px'>");
  content += F("<p style='font-size: large;'><b>Add Event<b></p><p><table><tr><td>");
  content += F("Trigger:</td><td><select id='trigger' onchange='if(this.selectedIndex)CheckTrigger();'>");
  content += F("<option value='0'>None</option>");
  content += F("<option value='1'>Uptime</option>");
  content += F("<option value='2'>Web Request</option>");
  content += F("<option value='3'>Temperature</option>");
  content += F("<option value='4'>Humidity</option>");
  content += F("</select></td></tr><tr><td>Parameter:&nbsp;</td><td><input type='text' id='param' placeholder='Parameter'></input>");
  content += F("<tr><td></td><td></td></tr>");
  content += F("<tr><td>Action:</td><td><input type='text' id='action' placeholder='Command'></input></td></tr></table>");
  content += F("</p><p style='text-align: right;'><input type='button' onclick=\"window.location.href='/?cmd=schedule';\" style='text-align:right;margin-right:5px;' value='Cancel'/><input name='go' onclick='sendUpdate()' style='text-align:right;' type='submit' value='Confirm' /></p></div>");
  //Script
  content += F("<script>");
  content += F("function sendUpdate(){UpdateVar();");
  content += F("if(trigger=='0'){alert('Please select a valid trigger');return false;}");
  content += F("if(trigger!='2' && param==''){alert('The selected trigger requires a valid parameter.');return false;}");
  content += F("if(cmd==''){alert('Please enter a valid command');return false;}");
  content += F("window.location.href='/?cmd=newschedule' + trigger + cmd + \"_\" + param;}");
  content += F("var trigger,cmd,param;");
  content += F("function UpdateVar(){trigger=document.getElementById('trigger').value;cmd = $('#action').val();param = $('#param').val();}");
  content += F("function CheckTrigger(){UpdateVar();if(trigger=='2')document.getElementById('param').disabled=true;else document.getElementById('param').disabled=false;}");
  content += F("</script>");
  return content;
}
String GenerateSyncTimeInterface() {
  //Header
  String content = F("<head><script src='https://code.jquery.com/jquery-3.3.1.min.js' crossorigin='anonymous'></script><div id='shellmsg' style='display: none;'>Interface not available in command prompt</div><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><link href='https://fonts.googleapis.com/css?family=Roboto' rel='stylesheet'>");
  content += F("</head><body style=\"font-family: 'Roboto', sans-serif;\">");
  content += F("<h3>Sync RTC-Time</h3>");
  //Content - Time
  content += F("<div style='background:#eee;border:1px solid #ccc;padding:5px 10px;width:40%;min-width:250px;max-width:350px'>");
  content += F("<p>Change Time</p><p><input id='time' step='1' style='width: 98%;' type='time' /></p>");
  content += F("<p style='text-align: right;'><input name='go' onclick='sendUpdate()' style='text-align: right;' type='submit' value='Confirm' /></p></div>");
  content += F("<script>function sendUpdate(){window.open(\"/?cmd=synctime\" + document.getElementById('time').value,\"_self\")}");
  content += F("var date = new Date();var hour = date.getHours(),min  = date.getMinutes(),sec  = date.getSeconds();hour = (hour < 10 ? '0' : '') + hour;min = (min < 10 ? '0' : '') + min;sec = (sec < 10 ? '0' : '') + sec;var displayTime = hour + ':' + min + ':' + sec;document.getElementById('time').value = displayTime;</script>");
  //Content - Date
  content += F("<br><div style='background:#eee;border:1px solid #ccc;padding:5px 10px;width:40%;min-width:250px;max-width:350px'>");
  content += F("<p>Change Date</p><p><input id='date' style='width: 98%;' type='date' /></p>");
  content += F("<p style='text-align: right;'><input name='go' onclick='sendUpdateDate()' style='text-align: right;' type='submit' value='Confirm' /></p></div>");
  content += F("<script>function sendUpdateDate(){window.open(\"/?cmd=syncdate\" + document.getElementById('date').value,\"_self\")}");
  content += F("var date = new Date();var day = date.getDate(),month = date.getMonth() + 1,year = date.getFullYear();month = (month < 10 ? '0' : '') + month;day = (day < 10 ? '0' : '') + day;var today = year + '-' + month + '-' + day;document.getElementById('date').value = today;</script>");
  //Footer
  content += F("<p><hr><a href='/?cmd=dashboard'>Dashboard</a>&nbsp;&nbsp;");
  content += F("<span class='sep'></span>&nbsp;&nbsp;");
  content += F("<a href='/?cmd=schedule'>Schedule</a>");
  content += F("</body><style>.sep{border-left: 1.5px solid gray;height: 10px;}a:visited{color: blue;}</style></body>");
  return content;
}
String GenerateMacInterface(String mac) {
  //Header
  String content = F("<head><script src='https://code.jquery.com/jquery-3.3.1.min.js' crossorigin='anonymous'></script><div id='shellmsg' style='display: none;'>Interface not available in command prompt</div><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><link href='https://fonts.googleapis.com/css?family=Roboto' rel='stylesheet'>");
  content += F("</head><body style=\"font-family: 'Roboto', sans-serif;\">");
  content += F("<h3>Change Network Settings</h3>");
  //Content - Time
  content += F("<div style='background:#eee;border:1px solid #ccc;padding:5px 10px;width:40%;min-width:250px;max-width:350px'>");
  content += F("<p>Change MAC Address</p><p><input id='mac' style='width: 98%;' type='text' value='");
  content += mac;
  content += F("' /></p>");
  content += F("<p style='text-align: right;'><input name='go' onclick='sendUpdate()' style='text-align: right;' type='submit' value='Confirm' /></p></div>");
  content += F("<script>function sendUpdate(){var regexp = /^(([A-Fa-f0-9]{2}[:]){5}[A-Fa-f0-9]{2}[,]?)+$/i;var mac_address = $('#mac').val();");
  content += F("if(regexp.test(mac_address)) {window.open(\"/?cmd=updatemac\" + document.getElementById('mac').value,\"_self\");} else {");
  content += F("alert(\"Invalid MAC Address\");}}</script>");
  //Footer
  content += F("<p><hr><a href='/?cmd=dashboard'>Dashboard</a>&nbsp;&nbsp;");
  content += F("<span class='sep'></span>&nbsp;&nbsp;");
  content += F("<a href='/?cmd=schedule'>Schedule</a>");
  content += F("</body><style>.sep{border-left: 1.5px solid gray;height: 10px;}a:visited{color: blue;}</style></body>");
  return content;
}
String GeneratePage(String title, String message, String shell) {
  String content = "<head><div id='shellmsg' style='display: none;'>&gt;";
  content += shell;
  content += F("</div><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><link href='https://fonts.googleapis.com/css?family=Roboto' rel='stylesheet'>");
  content += F("</head><body style=\"font-family: 'Roboto', sans-serif;\">");
  content += F("<h3 id='heading'>");
  content += title;
  content += F("</h3>");
  content += message;
  content += F("<p><hr><a href='/?cmd=dashboard'>Dashboard</a>&nbsp;&nbsp;");
  content += F("<span class='sep'></span>&nbsp;&nbsp;");
  content += F("<a href='/?cmd=schedule'>Schedule</a>");
  content += F("</body><style>.sep{border-left: 1.5px solid gray;height: 10px;}a:visited{color: blue;}</style></body>");
  return content;
}
String GeneratePageC(String title, String message, String shell, String htmllink) {
  String content = "<head><div id='shellmsg' style='display: none;'>&gt;";
  content += shell;
  content += F("</div><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><link href='https://fonts.googleapis.com/css?family=Roboto' rel='stylesheet'>");
  content += F("</head><body style=\"font-family: 'Roboto', sans-serif;\">");
  content += F("<h3 id='heading'>");
  content += title;
  content += F("</h3>");
  content += message;
  content += F("<p><hr><a href='/?cmd=dashboard'>Dashboard</a>&nbsp;&nbsp;");
  content += F("<span class='sep'></span>&nbsp;&nbsp;");
  content += htmllink;
  content += F("</body><style>.sep{border-left: 1.5px solid gray;height: 10px;}a:visited{color: blue;}</style></body>");
  return content;
}
String GenerateDashboard(int temp, int hu) {
  uptime();

  Time t = rtc.time();
  String hr = String(t.hr);
  String min = String(t.min);
  String sec = String(t.sec);
  String rtcTime = "";

  if (hr == "27" || min == "165" || sec == "85") {
    rtcTime = "RTC disconnected";
  } else {
    if (hr.length() == 1)hr = "0" + hr;
    if (min.length() == 1)min = "0" + min;
    if (sec.length() == 1)sec = "0" + sec;
    rtcTime = String(t.date) + "." + String(t.mon) + "." + String(t.yr) + " " + hr + ":" + min + ":" + sec;
  }

  String d = "0";
  String h = "0";
  String m = "0";
  String s = "0";
  if (GetIntLength(Day) == 1) d += String(Day);
  else d = String(Day);
  if (GetIntLength(Hour) == 1) h += String(Hour);
  else h = String(Hour);
  if (GetIntLength(Minute) == 1) m += String(Minute);
  else m = String(Minute);
  if (GetIntLength(Second) == 1) s += String(Second);
  else s = String(Second);


  byte macBuffer[6];
  String mac = "";
  Ethernet.MACAddress(macBuffer);
  for (byte octet = 0; octet < 6; octet++) {
    mac += String(macBuffer[octet], HEX);
    if (octet < 5) {
      mac += ":";
    }
  }
  mac.toUpperCase();
  String content = F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><meta http-equiv='Content-Type' content='text/html; charset=utf-8'/>");
  content += F("<link href='https://fonts.googleapis.com/css?family=Roboto' rel='stylesheet'><script src=\"https://code.jquery.com/jquery-3.3.1.min.js\" crossorigin=\"anonymous\"></script>");
  content += F("<body style=\"font-family: 'Roboto', sans-serif;\">");
  content += F("<div id='shellmsg' style='display: none;'>Dashboard not available in command prompt</div>");
  content += F("<h3 style=\"margin-bottom:0px;\">Dashboard</h3><h4 style=\"margin-bottom:10px;margin-top:10px;\">Environmental Sensors</h4>");
  content += F("Temperatur: ");
  content += String(temp);
  content += F("°C<br>");
  content += F("Luftfeuchtigkeit: ");
  content += String(hu);
  content += F("%<br>");
  content += F("Taupunkt: ");
  content += String(calcDewpoint(hu,temp));
  
  content += F("°C<br>");
  content += F("<h4 style=\"margin-bottom:10px;\">System Information</h4>");
  content += F("Internal Time: ");
  content += rtcTime + " <a href='/?cmd=sync'>[Sync]</a>";
  content += F("<br>Compile Date: ");
  content += __DATE__;
  content += " ";
  content += __TIME__;

  content += F("<br>GCC Version: ");
  content += __VERSION__;
  content += "<br>Free SRAM: " + String( freeMemory()) + "B";
  content += F("<br>Uptime: ");
  if (Day != 0)content += String(d);
  if (Day != 0)content += F(":");
  content += String(h);
  content += F(":");
  content += String(m);
  content += F(":");
  content += String(s);

  content += F("<br>EEPROM: ");
  content += EEPROM.length();
  content += F(" Bytes <a href='/?cmd=cleareeprom'>[Clear]</a>");


  content += F("<br>Screen Power: ");
#if ENABLE_SCREEN
  content += F("<a onclick='Screen()' href='javascript:void(0);'>");
  if (powerState)content += "OFF";
  else content += "ON";
  content += F("</a><script>function Screen(){$.get( '/?cmd=screen', function() { location.reload(true); })}</script></body>");
#else
  content += "Disabled";
#endif

  content += F("<br><h4 style=\"margin-bottom:10px;\">Schedule <a style='font-size:normal;' href='/?cmd=schedule'>[View]</a></h4>");
  content += F("Saved Schedules: ");
  content += String(CountSchedules()) + "/5";
  content += F(" <a href='/?cmd=addevent'>[Add]</a>");

  content += F("<br><h4 style=\"margin-bottom:10px;\">Network</h4>");
  content += F("Local IP: ");
  content += IpAddress2String(Ethernet.localIP());
  content += F("<br>DNS Server: ");
  content += IpAddress2String(Ethernet.dnsServerIP());
  content += F("<br>Gateway: ");
  content += IpAddress2String(Ethernet.gatewayIP());
  content += F("<br>Subnet Mask: ");
  content += IpAddress2String(Ethernet.subnetMask());
  content += F("<br>MAC Address: ");
  content += mac;
  content += F(" <a href='/?cmd=editmac'>[Edit]</a>");


  return content;
}
String GenerateInfo() {
  uptime();

  Time t = rtc.time();
  String hr = String(t.hr);
  String min = String(t.min);
  String sec = String(t.sec);
  String rtcTime = "";

  if (hr == "27" || min == "165" || sec == "85") {
    myGLCD.setTextSize(2);
    rtcTime = "RTC disconnected";
  } else {
    if (hr.length() == 1)hr = "0" + hr;
    if (min.length() == 1)min = "0" + min;
    if (sec.length() == 1)sec = "0" + sec;
    rtcTime = String(t.date) + "." + String(t.mon) + "." + String(t.yr) + " " + hr + ":" + min + ":" + sec;
  }

  String d = "0";
  String h = "0";
  String m = "0";
  String s = "0";
  if (GetIntLength(Day) == 1) d += String(Day);
  else d = String(Day);
  if (GetIntLength(Hour) == 1) h += String(Hour);
  else h = String(Hour);
  if (GetIntLength(Minute) == 1) m += String(Minute);
  else m = String(Minute);
  if (GetIntLength(Second) == 1) s += String(Second);
  else s = String(Second);


  byte macBuffer[6];
  String mac = "";
  Ethernet.MACAddress(macBuffer);
  for (byte octet = 0; octet < 6; octet++) {
    mac += String(macBuffer[octet], HEX);
    if (octet < 5) {
      mac += ":";
    }
  }
  mac.toUpperCase();
  String content = F("Internal Time: ");
  content += rtcTime;
  content += F("<br>Compile Date: ");
  content += __DATE__;
  content += " ";
  content += __TIME__;

  content += F("<br>GCC Version: ");
  content += __VERSION__;
  content += "<br>Free SRAM: " + String( freeMemory()) + "B";
  content += F("<br>Uptime: ");
  if (Day != 0)content += String(d);
  if (Day != 0)content += F(":");
  content += String(h);
  content += F(":");
  content += String(m);
  content += F(":");
  content += String(s);


  content += F("<br>Screen Power: ");
#if ENABLE_SCREEN
  if (powerState)content += "OFF";
  else content += "ON";
#else
  content += "Disabled";
#endif

  content += "^"; //DIVIDER
  
  content += F("Local IP: ");
  content += IpAddress2String(Ethernet.localIP());
  content += F("<br>DNS Server: ");
  content += IpAddress2String(Ethernet.dnsServerIP());
  content += F("<br>Gateway: ");
  content += IpAddress2String(Ethernet.gatewayIP());
  content += F("<br>Subnet Mask: ");
  content += IpAddress2String(Ethernet.subnetMask());
  content += F("<br>MAC Address: ");
  content += mac;
  return content;
}
String GetUptime() {
  uptime();

  String d = "0";
  String h = "0";
  String m = "0";
  String s = "0";
  if (GetIntLength(Day) == 1) d += String(Day);
  else d = String(Day);
  if (GetIntLength(Hour) == 1) h += String(Hour);
  else h = String(Hour);
  if (GetIntLength(Minute) == 1) m += String(Minute);
  else m = String(Minute);
  if (GetIntLength(Second) == 1) s += String(Second);
  else s = String(Second);

  String content;
  content += String(h);
  content += F(":");
  content += String(m);
  content += F(":");
  content += String(s);
  return content;
}
String GenerateScheduleInterface() {
  String content = F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><meta http-equiv='Content-Type' content='text/html; charset=utf-8'/>");
  content += F("<link href='https://fonts.googleapis.com/css?family=Roboto' rel='stylesheet'><script src=\"https://code.jquery.com/jquery-3.3.1.min.js\" crossorigin=\"anonymous\"></script>");
  content += F("<body style=\"font-family: 'Roboto', sans-serif;\">");
  content += F("<h4 style=\"margin-bottom:10px;\">Schedule</h4>");
  content += F("Saved Schedules: ");
  content += String(CountSchedules()) + "/5";
  content += F(" <a href='/?cmd=addevent'>[Add]</a>");
  content += F("<p>");
  content += GenerateScheduleList();
  content += F("<hr><a href='/?cmd=dashboard'>Dashboard</a><script>");
  content += F("function Remove(slot){$.get('/?cmd=removeevent'+slot,function(){location.reload(true);})}</script>");
  return content;
}
String IpAddress2String(const IPAddress& ipAddress)
{
  return String(ipAddress[0]) + String(".") + \
         String(ipAddress[1]) + String(".") + \
         String(ipAddress[2]) + String(".") + \
         String(ipAddress[3]);
}
