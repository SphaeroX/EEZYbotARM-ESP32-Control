/*
 * by adding handles link them on main / setup()
 */

void handleGetProgramm() {
  setCrossOrigin();
  Serial.print("get_programm: ");
  Serial.println(EEPROM.readString(address));
  server.send(200, "text/html", EEPROM.readString(address));
}

void handleChangeProgramm() {
  setCrossOrigin();
  Serial.println("change program state");
  
  program_state = server.arg("state").toInt();

  if (program_state) {
    program = EEPROM.readString(address);
    program_step = 0;
  }

  server.send(200, "text/html", "ok");
}

void handleSaveTeach() {
  setCrossOrigin();

  String arg_1 = server.arg("teach");
  
  Serial.print("write teach into eeprom: ");
  Serial.println(arg_1);

  EEPROM.writeString(address, arg_1);
  EEPROM.commit();
  
  server.send(200, "text/html", "ok");
}

void handleChangeAxis() {
  setCrossOrigin();
  ptp_move(server.arg("1").toInt(), server.arg("2").toInt(), server.arg("3").toInt(), server.arg("4").toInt(), server.arg("5").toInt());
  server.send(200, "text/html", "ok");
}
