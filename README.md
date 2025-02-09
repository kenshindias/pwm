# Controle de Servomotor por PWM no Raspberry Pi Pico

Este projeto utiliza um **Raspberry Pi Pico** para controlar um **servo motor** através de um sinal **PWM** com frequência de **50 Hz**.  
Ele posiciona o servo em **0°, 90° e 180°** (mantendo cada posição por 5 segundos) e, em seguida, faz um movimento de varredura entre 0° e 180°.

---

## 📌 **Funcionalidades**
✅ Gera um sinal **PWM** de 50 Hz no **GPIO 22**.  
✅ Posiciona o servo em **180° (2.4ms)**, **90° (1.47ms)** e **0° (0.5ms)** por 5 segundos cada.  
✅ Realiza **movimentação contínua** de 0° a 180° (e volta) usando **incrementos de 5µs** a cada 10ms.  

---

## 🎥 **Demonstração**
Confira o funcionamento do projeto neste vídeo (exemplo/placeholder):

[![Vídeo de demonstração](https://img.youtube.com/vi/TpAWgn8k8IY/0.jpg)](https://youtu.be/TpAWgn8k8IY)

---

## 🛠 **Componentes Necessários**
- 🖥 **Raspberry Pi Pico**  
- 🔌 **Micro Servo (SG90 ou similar)**  
- 📏 **Fios de conexão**  
- ⚡ **Fonte de alimentação** (pode ser 3.3V ou 5V, dependendo do servo, mas geralmente 5V é recomendado)

---

## 🔌 **Esquema de Conexão**
| Componente        | Pino no Pico     |
|-------------------|------------------|
| Servo (Sinal)     | GPIO 22          |
| Servo (VCC)       | 3V3 ou 5V*       |
| Servo (GND)       | GND              |

> **Atenção**: Em um cenário real, certifique-se de que a fonte de alimentação do servo seja compatível e que **GND** do servo e do Pico estejam em comum.  

---

## ⚙ **Configuração do Ambiente**

### **1️⃣ Instalar o SDK do Raspberry Pi Pico**
Se ainda não tiver o SDK do Pico configurado, siga as instruções no [guia oficial](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf).

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

### **3️⃣ Gravar no Raspberry Pi Pico**
1- Conecte o Pico ao computador segurando o botão BOOTSEL.
2- Ele será detectado como um dispositivo de armazenamento USB.
3- Arraste e solte o arquivo .uf2 gerado na pasta build/ para este dispositivo.
4- O Pico irá reiniciar automaticamente e executar o código!

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
