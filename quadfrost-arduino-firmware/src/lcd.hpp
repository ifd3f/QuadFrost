#pragma once

#include <LiquidCrystal_PCF8574.h>


namespace quadfrost {
  static const String DISPLAY_STATUS_NAMES[] = {
    "No Signal",
    "Ready    ",
    "Printing ",
    "Cancelled",
    "Error    ",
    "Complete ",
    "Paused   ",
    "No Device"
  };

  class StatusDisplay {
    LiquidCrystal_PCF8574 lcd;

    int progress;
    int temperature;
    int status;
  public:
    StatusDisplay(LiquidCrystal_PCF8574 lcd) : lcd(lcd) {}

    void begin() {
      lcd.noDisplay();
      lcd.display();
      lcd.begin(16, 2);
      lcd.clear();
      lcd.setBacklight(true);
      set_status(0);
      set_progress(0);
    }

    void set_temperature(int temperature) {
      this->temperature = temperature;

      // Clear temperature
      lcd.setCursor(12, 0);
      lcd.print("    ");

      // Write temperature
      auto strTemp = String(temperature);
      lcd.setCursor(14 - strTemp.length(), 0);
      lcd.print(strTemp);
      lcd.print((char)0xdf);
      lcd.print("C");
    }

    void set_status(int status) {
      this->status = status;
      
      // Write status
      lcd.setCursor(0, 0);
      lcd.print(DISPLAY_STATUS_NAMES[status]);
    }

    void set_backlight(bool state) {
      lcd.setBacklight(state);
    }

    void set_progress(int progress) {
      progress = min(max(progress, 0), 100);
      this->progress = progress;

      // Draw progress bar
      lcd.setCursor(0, 1);
      lcd.print("[");
      int ticks = (progress + 5) / 10;
      for (int i = 1; i <= 10; i++) {
        if (i <= ticks) {
          lcd.write((char)0xff);
        } else {
          lcd.write(" ");
        }
      }
      lcd.setCursor(11, 1);
      lcd.print("]");

      // Clear progress
      lcd.setCursor(12, 1);
      lcd.print("    ");
      
      // Write progress
      auto strProg = String(progress);
      lcd.setCursor(15 - strProg.length(), 1);
      lcd.print(strProg);
      lcd.print("%");
    }
  };
}
