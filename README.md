# 🐾 PetDispenser - Arduino Project

**PetDispenser** é um projeto de dispenser de ração automatizado usando **Arduino**. A ideia principal é permitir que o usuário defina um intervalo de tempo para a liberação da ração, e o sistema automaticamente dispense a comida após esse período e reinicie o temporizador para futuras liberações.

## 🚀 Funcionalidades

- O usuário pode configurar um intervalo de tempo para a liberação da ração (em minutos ou horas).
- Após o tempo definido, a ração é liberada automaticamente.
- O temporizador reinicia sozinho para repetir o processo automaticamente.
- Pode ser utilizado para alimentar animais de estimação de forma prática e controlada.


## 📷 Vídeos
https://github.com/user-attachments/assets/81efe20f-f4d4-45cb-b338-4072caef35be

https://github.com/user-attachments/assets/cd2ec5df-5246-4fda-acaa-624dea0df98b

## 🛠️ Tecnologias Utilizadas

- **Arduino Uno**: Microcontrolador principal para executar a lógica do projeto.
- **Servo Motor**: Responsável por controlar a liberação da ração.
- **Display LCD**: (Opcional) Exibe o tempo restante para a próxima liberação.
- **Botões**: Para ajustar o tempo de liberação.
- **Buzzer**: (Opcional) Alerta sonoro quando a ração é liberada.

## 📋 Circuito

### Componentes Necessários

- 1x Arduino Uno
- 1x Servo Motor
- 1x Display LCD 16x2 (Opcional)
- 2x Botões (para ajustar o tempo)
- 1x Buzzer (Opcional)
- Jumpers e resistores
- Fonte de alimentação 5V

### Esquema de Ligação

- **Servo Motor**: Pino de controle conectado ao pino digital do Arduino (exemplo: D9).
- **Botões**: Um botão conectado ao pino digital (exemplo: D2) para aumentar o tempo e outro ao pino (exemplo: D3) para diminuir.
- **Display LCD**: Conectado ao pinos digitais do Arduino (usando o I2C ou modo padrão).
- **Buzzer**: Conectado a um pino digital para alertas sonoros.

## ⏳ Funcionamento

1. O usuário ajusta o tempo de liberação de ração usando os botões.
2. O temporizador começa a contar.
3. Quando o tempo definido é atingido, o servo motor é ativado para liberar a ração.
4. O temporizador é reiniciado automaticamente para continuar o ciclo.

## 🚧 Melhorias Futuras

- **Conexão com Wi-Fi**: Usar um módulo ESP8266 ou ESP32 para permitir o controle remoto do PetDispenser via smartphone.
- **Sensores de peso**: Para medir a quantidade exata de ração dispensada.
- **App Mobile**: Criar um aplicativo para controlar e monitorar a alimentação do pet.
