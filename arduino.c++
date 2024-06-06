#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Timer
int horas = 0;
int minutos = 0;
int segundos = 0;

int lastHours;
int lastMinutes;
int lastSeconds;

// Buttons
const int onOffBtn = 0;
const int decBtn = 1;
const int incBtn = 2;
const int editConfirmBtn = 3;

// Servo Motor
Servo servoMotor;
const int servoPin = 5;

// States
bool lcdState = false;
bool state = false;
int editState = 0;
bool blinkState = false;

// Timer
  unsigned long previousMillis = 0;       // Guarda o último tempo em que o piscar foi atualizado
  const long interval = 200;              // Intervalo de piscar em milissegundos
  unsigned long timerPreviousMillis = 0;  // Guarda o último tempo em que o timer foi atualizado
  const long timerInterval = 1000;        // Intervalo de um segundo para o timer
  unsigned long currentMillis;
  void setup() {
    
  // Lcd setup
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();

  // Buttons setup
  pinMode(onOffBtn, INPUT_PULLUP);
  pinMode(decBtn, INPUT_PULLUP);
  pinMode(incBtn, INPUT_PULLUP);
  pinMode(editConfirmBtn, INPUT_PULLUP);
  
  // Servo Motor
  servoMotor.attach(servoPin);
  servoMotor.write(0);
}

void loop() {
  onOff();
  editTime();
  if (editState > 0 && editState < 4) {  // Chama a função blinkUpdate apenas durante o modo de edição
    blinkUpdate();
  }
  if (editState == 5) {
    timer();
  }
}

void lcdOn() {
  lcd.print("Bem-vindo ao");
  lcd.setCursor(0, 1);
  lcd.print("PetDispenser");
  delay(1500);
  lcd.clear();
  updateLcd();
}

void updateLcd() {
  lcd.setCursor(0, 1);
  lcd.print("Timer: ");

  if (editState == 1 && blinkState) {
    lcd.print("  ");
  } else {
    if (horas < 10) lcd.print("0");
    lcd.print(horas);
  }

  lcd.print(":");

  if (editState == 2 && blinkState) {
    lcd.print("  ");
  } else {
    if (minutos < 10) lcd.print("0");
    lcd.print(minutos);
  }

  lcd.print(":");

  if (editState == 3 && blinkState) {
    lcd.print("  ");
  } else {
    if (segundos < 10) lcd.print("0");
    lcd.print(segundos);
  }
}

void onOff() {
  if (digitalRead(onOffBtn) == LOW && lcdState == false) {
    if (state) {
      lcdOn();
    } else {
      lcd.clear();
    }
    lcdState = true;
    state = !state;
  } else if (digitalRead(onOffBtn) == HIGH && lcdState == true) {
    lcdState = false;
  }
}

void editTime() {
  if (digitalRead(editConfirmBtn) == LOW) {
    while (digitalRead(editConfirmBtn) == LOW)
      ;                               // Debounce
    editState = (editState + 1) % 6;  // Muda o estado de edição
    lcd.setCursor(0, 0);
    if (editState == 1) {
      lcd.print("Editando Horas   ");
    } else if (editState == 2) {
      lcd.print("Editando Minutos ");
    } else if (editState == 3) {
      lcd.print("Editando Segundos");
    }
    delay(250);  // Pequeno delay para evitar múltiplas mudanças de estado
  }

  switch (editState) {
    case 1:
      editHours();
      break;
    case 2:
      editMinutes();
      break;
    case 3:
      editSeconds();
      break;
    case 4:
      lcd.clear();
      delay(300);
      lcd.setCursor(0, 0);
      lcd.print("Timer definido");
      lcd.setCursor(0, 1);
      lcd.print("com sucesso!");
      delay(1500);
      lcd.clear();
      delay(1000);
      editState = 5;
      timerPreviousMillis = millis();
      break;
  }
}

void editHours() {
  // Decrementar Horas
  if (digitalRead(decBtn) == LOW) {
    while (digitalRead(decBtn) == LOW)
      ;
    horas--;
    delay(0);
    if (horas < 0) {
      horas = 23;
    }
    updateLcd();
    lastHours = horas;
  }

  // Incrementar Horas
  if (digitalRead(incBtn) == LOW) {
    while (digitalRead(incBtn) == LOW)
      ;
    horas = (horas + 1) % 24;
    delay(0);
    updateLcd();
    lastHours = horas;
  }
}

void editMinutes() {
  // Decrementar Minutos
  if (digitalRead(decBtn) == LOW) {
    while (digitalRead(decBtn) == LOW)
      ;
    minutos--;
    delay(0);
    if (minutos < 0) {
      minutos = 59;
    }
    updateLcd();
    lastMinutes = minutos;
  }

  // Incrementar Minutos
  if (digitalRead(incBtn) == LOW) {
    while (digitalRead(incBtn) == LOW)
      ;
    minutos = (minutos + 1) % 60;
    delay(0);
    updateLcd();
    lastMinutes = minutos;
  }
}

void editSeconds() {
  // Decrementar Segundos
  if (digitalRead(decBtn) == LOW) {
    while (digitalRead(decBtn) == LOW)
      ;
    segundos--;
    delay(0);
    if (segundos < 0) {
      segundos = 59;
    }
    updateLcd();
    lastSeconds = segundos;
  }

  // Incrementar Segundos
  if (digitalRead(incBtn) == LOW) {
    while (digitalRead(incBtn) == LOW)
      ;
    segundos = (segundos + 1) % 60;
    delay(0);
    updateLcd();
    lastSeconds = segundos;
  }
}

void blinkUpdate() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    blinkState = !blinkState;
    updateLcd();
  }
}


void timer() {
  if (millis() - timerPreviousMillis >= timerInterval) {
    timerPreviousMillis += timerInterval;  // Adiciona o intervalo ao tempo anterior

    if (segundos > 0) {
      segundos--;
    } else if (minutos > 0) {
      minutos--;
      segundos = 59;
    } else if (horas > 0) {
      horas--;
      minutos = 59;
      segundos = 59;
    } else {
      door();
      lcd.clear();
      lcd.print("Alimentado");
      lcd.setCursor(0, 1);
      lcd.print("com sucesso!");
      delay(2500);
      lcd.clear();
      delay(1500);
      horas = lastHours;
      minutos = lastMinutes;
      segundos = lastSeconds;
    }
  }
  updateLcd();  // Atualiza o LCD somente quando o timer é atualizado
}

void door() {
  servoMotor.write(180);  // Abre o servo para 180 graus
  delay(1500);            // Espera 2 segundos
  servoMotor.write(0);    // Retorna o servo para a posição inicial
  //delay(1500);
}
