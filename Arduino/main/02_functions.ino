void ptp_move(int servo_1_soll, int servo_2_soll, int servo_3_soll, int servo_4_soll, int pause) {
  float servo_1_ist_float = float(servo_pos_1), servo_2_ist_float = float(servo_pos_2), servo_3_ist_float = float(servo_pos_3), servo_4_ist_float = float(servo_pos_4);

  int servo_1_differenz = servo_1_soll - int(servo_1_ist_float);
  int servo_2_differenz = servo_2_soll - int(servo_2_ist_float);
  int servo_3_differenz = servo_3_soll - int(servo_3_ist_float);
  int servo_4_differenz = servo_4_soll - int(servo_4_ist_float);

  int differenz_max = max(max(abs(servo_1_differenz), abs(servo_2_differenz)), max(abs(servo_3_differenz), abs(servo_4_differenz)));

  float servo_1_inkrement = float(servo_1_differenz) / float(differenz_max);
  float servo_2_inkrement = float(servo_2_differenz) / float(differenz_max);
  float servo_3_inkrement = float(servo_3_differenz) / float(differenz_max);
  float servo_4_inkrement = float(servo_4_differenz) / float(differenz_max);

  for (int i = 0; i < differenz_max; i++) {
    // ------------------------------------------------      Servo 1
    servo_1_ist_float = servo_1_ist_float + servo_1_inkrement;

    servo_pos_1 = int(round(servo_1_ist_float));
    myservo_1.write(servo_pos_1);
    // ------------------------------------------------      Servo 2
    servo_2_ist_float = servo_2_ist_float + servo_2_inkrement;

    servo_pos_2 = int(round(servo_2_ist_float));
    myservo_2.write(servo_pos_2);
    // ------------------------------------------------      Servo 3
    servo_3_ist_float = servo_3_ist_float + servo_3_inkrement;

    servo_pos_3 = int(round(servo_3_ist_float));
    myservo_3.write(servo_pos_3);
    // ------------------------------------------------     Servo 4
    servo_4_ist_float = servo_4_ist_float + servo_4_inkrement;

    servo_pos_4 = int(round(servo_4_ist_float));
    myservo_4.write(servo_pos_4);

    delay(pause);
  }
}
