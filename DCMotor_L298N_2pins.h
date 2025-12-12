/*
  Библиотека управления двигателем постоянного тока с помощью драйвера  L298N.
  Для управления двигателем используются 2 контакта IN1, IN2 или IN3, IN4.
  Контакты ENA и ENB подключны к 5В джамперами  
  Библиотека написана ПДО IT-cube Баландиным Л.С.
  
*/



/**
 Описание класса мотора постоянного тока
 */
class DCMotor_L298N_2pins {
  private:
    bool _direction; 	// Переменная хранит текущее направление вращения.
	byte _PWMpin; 		// Переменная хранит номер контакта для управления скоростью (ШИМ сигнал)
	byte _dirPin;		// Переменная хранит номер контакта для управления направлением вращения
  
  public:
    /**
     Конструктор для создания объекта двигателя.
	 dirpin - любой цифровой контакт.
	 PWMpin - контакт для ШИМ сигнала.
	 needToReverse - параметр для изменения стартового направления вращения.
     */
    DCMotor_L298N_2pins(byte dirpin, byte PWMpin, bool needToReverse = 0) {
		_dirPin = dirpin;
		_PWMpin = PWMpin;
		if (needToReverse) _direction = 0;
		else _direction = 1;
		pinMode(_PWMpin, OUTPUT);
		pinMode(_dirPin, OUTPUT);
	}
  
   //метод включает двигатель на определённую мощность (-255...255)
    void on(int power){
		power = constrain(power, -255, 255); 
		if (power >= 0) {
		  digitalWrite(_dirPin, _direction);
		  analogWrite(_PWMpin, power);
		} else {
		  digitalWrite(_dirPin, !_direction);
		  analogWrite(_PWMpin, 255 - power);
		}		
	}
   
   //метод включает двигатель на определённую мощность (-255...255) и на определённое время.
    void on(int power, unsigned long millisec){
		on(power);
		delay(millisec);
		off();
	} 

   // метод выключает подачу питания на двигатель. (остановка)
    void off(){
		digitalWrite(_PWMpin, 0);
		digitalWrite(_dirPin, 0);
	}
	void reverse(){
		_direction = not _direction;
	}
};

