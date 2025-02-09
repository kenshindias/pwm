# Controle de Servomotor por PWM no Raspberry Pi Pico

Este projeto demonstra como gerar um sinal **PWM** de **50 Hz** (20ms) no **Raspberry Pi Pico** para controlar um **servo motor**, utilizando a **emulação no Wokwi** (pois não temos o servo físico em mãos).

---

## 📌 **Funcionalidades**
- Gera um sinal **PWM** de 50 Hz no **GPIO 22**.
- Posiciona o servo em **180° (2.4ms)**, **90° (1.47ms)** e **0° (0.5ms)**, cada posição sendo mantida por **5 segundos**.
- Executa uma **varredura contínua** de 0° a 180° (e volta) em incrementos de **5µs** a cada **10ms**, produzindo um movimento suave.

---

## 🛠 **Componentes (Simulados)**
- **Raspberry Pi Pico** (no Wokwi)  
- **Micro Servo** conectado ao **GPIO 22**, GND e 3V3/5V (tudo virtual no Wokwi)

---

## 🔌 **Esquema de Conexão (Wokwi)**
| Componente    | Pino no Pico |
|---------------|--------------|
| Servo (Sinal) | GPIO 22      |
| Servo (VCC)   | 5V ou 3V3    |
| Servo (GND)   | GND          |

No **Wokwi**, basta inserir:
1. Um **Raspberry Pi Pico**;
2. Um **Micro Servo** (SG90 ou similar);
3. Conectá-lo ao **GPIO 22** (sinal), **GND** e **3V3** ou **5V**.

---

## ⚙ **Configuração do Ambiente**

### **1️⃣ Instalar o SDK do Raspberry Pi Pico** (opcional, caso deseje compilar localmente)
Siga as instruções do [Guia Oficial](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf) se quiser rodar em hardware real.

**No Linux**:
```
git clone https://github.com/raspberrypi/pico-sdk.git --branch master
cd pico-sdk
git submodule update --init
export PICO_SDK_PATH=$(pwd)
```
No Windows (PowerShell):
```
git clone https://github.com/raspberrypi/pico-sdk.git --branch master
cd pico-sdk
git submodule update --init
$env:PICO_SDK_PATH = Get-Location
```

### **2️⃣ Compilar o Projeto**
1 - Clone este repositório: 
```
git clone https://github.com/kenshindias/pwm.git
cd pwm
```
2 - Crie a pasta de build:
```
mkdir build
cd build
```
3 - Gere os arquivos de build:
```
cmake ..
```
4 - Compile o projeto:
```
make
```
Isso irá gerar um arquivo .uf2 (por exemplo, pico-pwm-servo.uf2) pronto para ser carregado no Raspberry Pi Pico.

### **3️⃣ Executar no Wokwi**
1 - Acesse Wokwi.com.
2 - Crie um projeto selecionando Raspberry Pi Pico.
3 - Adicione um Micro Servo e conecte-o ao GPIO 22, além de GND e 3V3/5V.
4 - Carregue o arquivo .c (código-fonte) ou .uf2 (firmware compilado).
5 - Clique em Start Simulation para observar o braço do servo movendo-se conforme o código.


## 🛠 **Como o Código Funciona**

1. **Configuração do PWM (50Hz)**  
   - O código define o **período de 20ms** (equivalente a **50Hz**) ajustando o **`wrap`** para **20000** e o **`clkdiv`** para **125**.  
   - Cada incremento no duty cycle corresponde a **1µs** (1 unidade = 1µs), facilitando o controle fino do pulso para o servo.

2. **Posicionamento Inicial**  
   - Ao iniciar, o programa envia pulsos para posicionar o servo em **180°** (~2.4ms), mantendo por 5 segundos.  
   - Em seguida, muda para **90°** (~1.47ms) por 5 segundos, e depois para **0°** (~0.5ms) por mais 5 segundos.

3. **Movimentação Contínua**  
   - Após os ângulos fixos, o código varia o pulso de **500µs (0°)** até **2400µs (180°)** em incrementos de **5µs** a cada **10ms**, e depois retorna de 180° a 0° nos mesmos passos.  
   - Esse processo cria um movimento suave de vai e vem no braço do servo.

---

## 📜 **Licença**
Este projeto é aberto e pode ser utilizado livremente para fins educacionais ou pessoais.  
Sinta-se à vontade para abrir **Issues** ou enviar **Pull Requests**!

Em caso de dúvidas ou sugestões, **abra uma issue** ou envie uma pull request.
Autor: **@kenshindias**
